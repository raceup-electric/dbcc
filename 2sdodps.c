/* @brief SDO_DPS helpers
 * @copyright SUBLEQ LTD. (2025)
 * @license MIT */
#include "2sdodps.h"
#include "util.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_NAME_LENGTH (512u)

static bool check_opcode_valtable(dbc_t *dbc)
{
	static const struct {
		unsigned value;
		const char *name;
	} expected[] = {
		{ 1u,   "GET_REQ" },
		{ 2u,   "SET_REQ" },
		{ 3u,   "GET_ALL_REQ" },
		{ 128u, "RES" },
		{ 253u, "ERR_OUT_OF_RANGE" },
		{ 254u, "ERR_WRITE_RO" },
		{ 255u, "ERR" },
	};

	assert(dbc);

	for (size_t i = 0; i < dbc->val_table_count; i++) {
		val_list_t *table = dbc->val_tables[i];
		if (!table || !table->name)
			continue;
		if (strcmp(table->name, "OPCODES"))
			continue;

		if (table->val_list_item_count != (sizeof(expected) / sizeof(expected[0])))
			return false;

		for (size_t j = 0; j < table->val_list_item_count; j++) {
			val_list_item_t *item = table->val_list_items[j];
			if (!item || !item->name)
				return false;
			if (item->value != expected[j].value)
				return false;
			if (strcmp(item->name, expected[j].name))
				return false;
		}
		return true;
	}

	return false;
}

static bool has_sdo_prefix(const char *name)
{
	assert(name);
	return strncmp(name, "SDO", 3) == 0;
}

static signal_t *find_signal_by_name(can_msg_t *msg, const char *name)
{
	assert(msg);
	assert(name);
	for (size_t i = 0; i < msg->signal_count; i++) {
		signal_t *sig = msg->sigs[i];
		if (!sig || !sig->name)
			continue;
		if (!strcmp(sig->name, name))
			return sig;
	}
	return NULL;
}

static signal_t *find_multiplexed_signal_by_value(can_msg_t *msg, unsigned value)
{
	assert(msg);
	for (size_t i = 0; i < msg->signal_count; i++) {
		signal_t *sig = msg->sigs[i];
		if (sig && sig->is_multiplexed && sig->switchval == value)
			return sig;
	}
	return NULL;
}

static bool check_opcode_signal(can_msg_t *msg)
{
	assert(msg);
	signal_t *opcode = find_signal_by_name(msg, "opcode");
	if (!opcode || !opcode->val_list)
		return false;
	if (!opcode->val_list->is_val_table_reference)
		return false;
	if (!opcode->val_list->val_table_name)
		return false;
	return strcmp(opcode->val_list->val_table_name, "OPCODES") == 0;
}

static bool check_required_signals(can_msg_t *msg, signal_t **var_id_out)
{
	assert(msg);
	assert(var_id_out);

	signal_t *opcode = find_signal_by_name(msg, "opcode");
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	signal_t *flags = find_signal_by_name(msg, "flags");
	signal_t *dbc_hash = find_signal_by_name(msg, "dbc_hash");

	if (!opcode || !var_id || !flags || !dbc_hash)
		return false;

	*var_id_out = var_id;
	return true;
}

static bool check_multiplexed_layout(can_msg_t *msg, signal_t *var_id)
{
	(void)var_id;
	assert(msg);

	size_t mux_count = 0;
	for (size_t i = 0; i < msg->signal_count; i++) {
		signal_t *sig = msg->sigs[i];
		if (!sig || !sig->is_multiplexed)
			continue;
		if (sig->start_bit != 24u)
			return false;
		if (sig->bit_length == 0u)
			return false;
		for (size_t j = i + 1; j < msg->signal_count; j++) {
			signal_t *other = msg->sigs[j];
			if (!other || !other->is_multiplexed)
				continue;
			if (other->switchval == sig->switchval)
				return false;
		}
		mux_count++;
	}

	return mux_count > 0;
}

static bool check_var_id_names_match_mux(can_msg_t *msg, signal_t *var_id)
{
	assert(msg);
	assert(var_id);
	if (!var_id->val_list)
		return false;

	val_list_t *vals = var_id->val_list;
	if (vals->val_list_item_count == 0)
		return false;

	for (size_t i = 0; i < vals->val_list_item_count; i++) {
		val_list_item_t *item = vals->val_list_items[i];
		if (!item || !item->name)
			return false;

		size_t matches = 0;
		for (size_t j = 0; j < msg->signal_count; j++) {
			signal_t *sig = msg->sigs[j];
			if (!sig || !sig->is_multiplexed || !sig->name)
				continue;
			if (sig->switchval == item->value) {
				if (strcmp(sig->name, item->name))
					return false;
				matches++;
			}
		}
		if (matches != 1)
			return false;
	}

	for (size_t i = 0; i < msg->signal_count; i++) {
		signal_t *sig = msg->sigs[i];
		bool found = false;
		if (!sig || !sig->is_multiplexed || !sig->name)
			continue;
		for (size_t j = 0; j < vals->val_list_item_count; j++) {
			val_list_item_t *item = vals->val_list_items[j];
			if (!item || !item->name)
				continue;
			if (item->value == sig->switchval && !strcmp(item->name, sig->name)) {
				found = true;
				break;
			}
		}
		if (!found)
			return false;
	}

	return true;
}

static bool check_sdo_message(can_msg_t *msg)
{
	assert(msg);
	assert(msg->name);
	if (!has_sdo_prefix(msg->name))
		return false;

	signal_t *var_id = NULL;
	if (!check_required_signals(msg, &var_id))
		return false;
	if (!check_opcode_signal(msg))
		return false;
	if (!var_id->is_multiplexor)
		return false;
	if (!check_multiplexed_layout(msg, var_id))
		return false;
	if (!check_var_id_names_match_mux(msg, var_id))
		return false;

	return true;
}

static can_msg_t **filter_sdo_messages(dbc_t *dbc, size_t *filtered_count)
{
	assert(dbc);
	assert(filtered_count);

	*filtered_count = 0;
	if (!dbc->messages || dbc->message_count == 0)
		return NULL;

	can_msg_t **filtered = calloc(dbc->message_count, sizeof(*filtered));
	assert(filtered);

	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		if (!msg || !msg->name)
			continue;
		if (!check_sdo_message(msg))
			continue;
		filtered[(*filtered_count)++] = msg;
	}

	return filtered;
}

static void ensure_dir(const char *path)
{
	assert(path);
	if (mkdir(path, 0777) == -1 && errno != EEXIST)
		error("error creating folder '%s': %s", path, emsg());
}

static char *format_alloc(const char *fmt, ...)
{
	assert(fmt);
	va_list ap;
	va_start(ap, fmt);
	va_list ap_copy;
	va_copy(ap_copy, ap);
	int needed = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);
	if (needed < 0)
		error("vsnprintf failed");
	char *buf = allocate((size_t)needed + 1);
	vsnprintf(buf, (size_t)needed + 1, fmt, ap_copy);
	va_end(ap_copy);
	return buf;
}

static char *sanitize_identifier(const char *name, bool lower)
{
	assert(name);
	char *out = duplicate(name);
	const size_t len = strlen(out);
	if (!len)
		return out;
	if (!isalpha((unsigned char)out[0]) && out[0] != '_')
		out[0] = '_';
	for (size_t i = 0; i < len; i++) {
		if (!isalnum((unsigned char)out[i]) && out[i] != '_') {
			out[i] = '_';
			continue;
		}
		if (lower)
			out[i] = (char)tolower((unsigned char)out[i]);
	}
	return out;
}

static char *sanitize_macro(const char *name)
{
	assert(name);
	char *out = sanitize_identifier(name, false);
	for (size_t i = 0; out[i]; i++)
		out[i] = (char)toupper((unsigned char)out[i]);
	return out;
}

static char *snake_to_pascal(const char *name)
{
	assert(name);
	char *snake = sanitize_identifier(name, true);
	char *out = allocate(strlen(snake) + 1);
	size_t j = 0;
	bool upper_next = true;
	for (size_t i = 0; snake[i]; i++) {
		if (snake[i] == '_') {
			upper_next = true;
			continue;
		}
		out[j++] = upper_next ?
			(char)toupper((unsigned char)snake[i]) :
			snake[i];
		upper_next = false;
	}
	out[j] = '\0';
	free(snake);
	return out;
}

static const char *board_name(const can_msg_t *msg)
{
	assert(msg);
	assert(msg->name);
	assert(has_sdo_prefix(msg->name));
	return msg->name + 3;
}

static char *board_file_name(const can_msg_t *msg)
{
	return sanitize_identifier(board_name(msg), true);
}

static char *board_type_name(const can_msg_t *msg)
{
	return snake_to_pascal(board_name(msg));
}

static const char *determine_unsigned_type(unsigned length)
{
	const char *type = "std::uint64_t";
	if (length <= 32u)
		type = "std::uint32_t";
	if (length <= 16u)
		type = "std::uint16_t";
	if (length <= 8u)
		type = "std::uint8_t";
	return type;
}

static const char *determine_signed_type(unsigned length)
{
	const char *type = "std::int64_t";
	if (length <= 32u)
		type = "std::int32_t";
	if (length <= 16u)
		type = "std::int16_t";
	if (length <= 8u)
		type = "std::int8_t";
	return type;
}

static const char *determine_type(unsigned length, bool is_signed, bool is_floating)
{
	if (is_floating) {
		if (length != 32u)
			error("SDO_DPS does not support floating signals with bit length %u", length);
		return "float";
	}
	return is_signed ? determine_signed_type(length) : determine_unsigned_type(length);
}

static bool signal_is_floating(signal_t *sig)
{
	assert(sig);
	return sig->is_floating || sig->sigval == 1u || sig->sigval == 2u;
}

static const char *signal_api_type(signal_t *sig)
{
	assert(sig);
	if (sig->scaling != 1.0 || sig->offset != 0.0)
		return "float";
	return determine_type(sig->bit_length, sig->is_signed, signal_is_floating(sig));
}

static const char *signal_wire_type(signal_t *sig)
{
	assert(sig);
	if (signal_is_floating(sig))
		return determine_type(sig->bit_length, false, true);
	if (sig->scaling != 1.0 || sig->offset != 0.0)
		return "float";
	return determine_type(sig->bit_length, sig->is_signed, false);
}

static const char *callback_type_prefix(signal_t *sig)
{
	const char *type = signal_api_type(sig);
	if (!strcmp(type, "std::uint8_t"))
		return "Uint8";
	if (!strcmp(type, "std::uint16_t"))
		return "Uint16";
	if (!strcmp(type, "std::uint32_t"))
		return "Uint32";
	if (!strcmp(type, "std::uint64_t"))
		return "Uint64";
	if (!strcmp(type, "std::int8_t"))
		return "Int8";
	if (!strcmp(type, "std::int16_t"))
		return "Int16";
	if (!strcmp(type, "std::int32_t"))
		return "Int32";
	if (!strcmp(type, "std::int64_t"))
		return "Int64";
	if (!strcmp(type, "float"))
		return "Float";
	error("unsupported callback type: %s", type);
	return "Invalid";
}

static void validate_supported_signal_type(signal_t *sig)
{
	assert(sig);
	if (sig->sigval == 2u)
		error("SDO_DPS does not support double signals: %s", sig->name);
	if (signal_is_floating(sig) && sig->bit_length != 32u)
		error("SDO_DPS only supports 32-bit float signals: %s", sig->name);
}

static bool signal_type_seen_before(can_msg_t *msg, size_t upto, signal_t *sig)
{
	assert(msg);
	assert(sig);
	const char *type = signal_api_type(sig);
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	assert(var_id && var_id->val_list);
	for (size_t i = 0; i < upto; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *prev_sig = find_multiplexed_signal_by_value(msg, item->value);
		assert(prev_sig);
		if (!strcmp(signal_api_type(prev_sig), type))
			return true;
	}
	return false;
}

static unsigned sdo_value_bit_length(can_msg_t *msg, unsigned var_id)
{
	signal_t *sig = find_multiplexed_signal_by_value(msg, var_id);
	assert(sig);
	return sig->bit_length;
}

static can_msg_t *find_message_by_id(dbc_t *dbc, unsigned long id)
{
	assert(dbc);
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		if (msg && msg->id == id)
			return msg;
	}
	return NULL;
}

static void apply_sigval_to_signal(signal_t *sig, unsigned typed)
{
	assert(sig);
	sig->sigval = typed;
	if (typed == 1u || typed == 2u)
		sig->is_floating = true;
}

static void apply_sigval_overrides(dbc_t *dbc, const char *dbc_file)
{
	assert(dbc);
	assert(dbc_file);
	FILE *in = fopen(dbc_file, "rb");
	if (!in)
		error("error opening '%s': %s", dbc_file, emsg());

	char line[1024];
	while (fgets(line, sizeof line, in)) {
		unsigned long id = 0;
		unsigned typed = 0;
		char name[MAX_NAME_LENGTH] = { 0 };
		const int n = sscanf(line, " SIG_VALTYPE_ %lu %511s : %u ;", &id, name, &typed);
		if (n != 3)
			continue;

		can_msg_t *msg = find_message_by_id(dbc, id);
		if (!msg)
			continue;

		signal_t *sig = find_signal_by_name(msg, name);
		if (!sig)
			continue;

		apply_sigval_to_signal(sig, typed);
	}

	fclose(in);
}

static void emit_generated_banner(FILE *o)
{
	assert(o);
	fprintf(o, "/* SDO_DPS C++ support: automatically generated - do not edit. */\n\n");
}

static void emit_cpp_common_helpers(FILE *o)
{
	fprintf(o,
		"static std::uint64_t sdodps_mask(unsigned bit_length) {\n"
		"\treturn bit_length >= 64u ? 0xffffffffffffffffULL : ((1ULL << bit_length) - 1ULL);\n"
		"}\n\n"
		"static std::uint64_t sdodps_get_bits(std::uint64_t payload, unsigned start, unsigned bit_length) {\n"
		"\treturn (payload >> start) & sdodps_mask(bit_length);\n"
		"}\n\n"
		"static void sdodps_set_bits(std::uint64_t *payload, unsigned start, unsigned bit_length, std::uint64_t value) {\n"
		"\tconst std::uint64_t mask = sdodps_mask(bit_length);\n"
		"\t*payload = (*payload & ~(mask << start)) | ((value & mask) << start);\n"
		"}\n\n"
		"static Frame sdodps_make_frame(std::uint32_t id, Opcode opcode, std::uint16_t var_id, std::uint8_t flags, std::uint64_t value, unsigned bit_length) {\n"
		"\tFrame frame { id, 7u, 0u };\n"
		"\tsdodps_set_bits(&frame.payload, 0u, 8u, static_cast<std::uint8_t>(opcode));\n"
		"\tsdodps_set_bits(&frame.payload, 8u, 10u, var_id);\n"
		"\tsdodps_set_bits(&frame.payload, 18u, 6u, flags);\n"
		"\tsdodps_set_bits(&frame.payload, 24u, bit_length, value);\n"
		"\treturn frame;\n"
		"}\n\n");
}

static void emit_signal_decode_helper(FILE *o, const char *board_file, signal_t *sig)
{
	assert(o);
	assert(board_file);
	assert(sig);
	assert(sig->name);
	const char *type = signal_api_type(sig);
	const bool floating = signal_is_floating(sig);
	char *name = sanitize_identifier(sig->name, false);
	fprintf(o, "static %s sdodps_decode_%s_%s(std::uint64_t payload) {\n", type, board_file, name);
	fprintf(o, "\tstd::uint64_t x = sdodps_get_bits(payload, 24u, %uu);\n", sig->bit_length);
	if (floating) {
		fprintf(o,
			"\tstd::uint32_t raw = static_cast<std::uint32_t>(x);\n"
			"\tfloat unpacked;\n"
			"\tstd::memcpy(&unpacked, &raw, sizeof(unpacked));\n");
		fprintf(o, "\t%s value = static_cast<%s>(unpacked);\n", type, type);
	} else if (sig->is_signed) {
		if (sig->bit_length < 64u) {
			fprintf(o,
				"\tif ((x & (1ULL << %uu)) != 0uLL)\n"
				"\t\tx |= ~sdodps_mask(%uu);\n",
				sig->bit_length - 1u, sig->bit_length);
		}
		fprintf(o, "\t%s value = static_cast<%s>(static_cast<std::int64_t>(x));\n", type, type);
	} else {
		fprintf(o, "\t%s value = static_cast<%s>(x);\n", type, type);
	}
	if (sig->scaling == 0.0)
		error("invalid scaling factor (fix your DBC file)");
	if (sig->scaling != 1.0)
		fprintf(o, "\tvalue *= %g;\n", sig->scaling);
	if (sig->offset != 0.0)
		fprintf(o, "\tvalue += %g;\n", sig->offset);
	fprintf(o, "\treturn value;\n}\n\n");
	free(name);
}

static void emit_signal_encode_helper(FILE *o, const char *board_file, signal_t *sig)
{
	assert(o);
	assert(board_file);
	assert(sig);
	assert(sig->name);
	const char *type = signal_api_type(sig);
	const char *wire_type = signal_wire_type(sig);
	const bool floating = signal_is_floating(sig);
	char *name = sanitize_identifier(sig->name, false);
	fprintf(o, "static std::uint64_t sdodps_encode_%s_%s(%s in) {\n", board_file, name, type);
	if (floating || sig->offset != 0.0 || sig->scaling != 1.0)
		fprintf(o, "\t%s wire = static_cast<%s>(in);\n", wire_type, wire_type);
	if (sig->offset != 0.0)
		fprintf(o, "\twire += %g;\n", -1.0 * sig->offset);
	if (sig->scaling == 0.0)
		error("invalid scaling factor (fix your DBC file)");
	if (sig->scaling != 1.0)
		fprintf(o, "\twire *= %g;\n", 1.0 / sig->scaling);
	if (floating) {
		if (sig->bit_length == 32u) {
			fprintf(o,
				"\tstd::uint32_t raw;\n"
				"\tstd::memcpy(&raw, &wire, sizeof(raw));\n"
				"\treturn static_cast<std::uint64_t>(raw) & sdodps_mask(%uu);\n",
				sig->bit_length);
		} else {
			fprintf(o,
				"\tstd::uint64_t raw;\n"
				"\tstd::memcpy(&raw, &wire, sizeof(raw));\n"
				"\treturn raw & sdodps_mask(%uu);\n",
				sig->bit_length);
		}
	} else if (sig->is_signed) {
		if (sig->offset != 0.0 || sig->scaling != 1.0)
			fprintf(o, "\treturn static_cast<std::uint64_t>(static_cast<std::int64_t>(wire)) & sdodps_mask(%uu);\n", sig->bit_length);
		else
			fprintf(o, "\treturn static_cast<std::uint64_t>(static_cast<std::int64_t>(in)) & sdodps_mask(%uu);\n", sig->bit_length);
	} else {
		if (sig->offset != 0.0 || sig->scaling != 1.0)
			fprintf(o, "\treturn static_cast<std::uint64_t>(wire) & sdodps_mask(%uu);\n", sig->bit_length);
		else
			fprintf(o, "\treturn static_cast<std::uint64_t>(in) & sdodps_mask(%uu);\n", sig->bit_length);
	}
	fprintf(o, "}\n\n");
	free(name);
}

static void emit_board_signal_helpers(FILE *o, can_msg_t *msg)
{
	assert(o);
	assert(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	assert(var_id && var_id->val_list);
	char *board_file = board_file_name(msg);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		assert(sig);
		validate_supported_signal_type(sig);
		emit_signal_decode_helper(o, board_file, sig);
		emit_signal_encode_helper(o, board_file, sig);
	}
	free(board_file);
}

static void emit_master_header_boards(FILE *o, can_msg_t **msgs, size_t count)
{
	for (size_t i = 0; i < count; i++) {
		can_msg_t *msg = msgs[i];
		char *board = board_type_name(msg);
		char *enum_name = format_alloc("%sVar", board);
		fprintf(o, "static constexpr std::uint32_t SDO%s_CAN_ID = %" PRIu64 "u;\n",
			board, (uint64_t)msg->id);
		fprintf(o, "enum class %s : std::uint16_t {\n", enum_name);
		signal_t *var_id = find_signal_by_name(msg, "var_id");
		assert(var_id && var_id->val_list);
		uint64_t var_count = 0;
		for (size_t j = 0; j < var_id->val_list->val_list_item_count; j++) {
			val_list_item_t *item = var_id->val_list->val_list_items[j];
			char *name = sanitize_identifier(item->name, false);
			fprintf(o, "\t%s = %uu,\n", name, item->value);
			if ((uint64_t)item->value >= var_count)
				var_count = (uint64_t)item->value + 1u;
			free(name);
		}
		fprintf(o, "};\n");
		fprintf(o, "static constexpr std::size_t %sCount = %" PRIu64 "u;\n",
			enum_name, var_count);
		fprintf(o, "const char *to_string(%s value);\n\n", enum_name);
		free(enum_name);
		free(board);
	}
}

static void emit_master_header_class_methods(FILE *o, can_msg_t **msgs, size_t count)
{
	for (size_t i = 0; i < count; i++) {
		can_msg_t *msg = msgs[i];
		char *board_file = board_file_name(msg);
		char *board_type = board_type_name(msg);
		signal_t *var_id = find_signal_by_name(msg, "var_id");
		fprintf(o, "\tvoid set_expected_%s_hash(std::uint32_t expected);\n", board_file);
		fprintf(o, "\tbool %s_hash_verified() const;\n", board_file);
		fprintf(o, "\tstatic unsigned %s_bit_length(%sVar var);\n", board_file, board_type);
		fprintf(o, "\tbool request_%s(%sVar var);\n", board_file, board_type);
		fprintf(o, "\tbool has_%s_value(%sVar var) const;\n", board_file, board_type);
		for (size_t j = 0; j < var_id->val_list->val_list_item_count; j++) {
			val_list_item_t *item = var_id->val_list->val_list_items[j];
			signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
			char *name = sanitize_identifier(item->name, false);
			fprintf(o, "\tbool set_%s_%s(%s value);\n", board_file, name, signal_api_type(sig));
			fprintf(o, "\tbool take_%s_%s(%s *out);\n", board_file, name, signal_api_type(sig));
			free(name);
		}
		free(board_type);
		free(board_file);
	}
}

static void emit_master_header_board_state(FILE *o, can_msg_t *msg)
{
	char *board_type = board_type_name(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	fprintf(o, "\tstruct %sState {\n", board_type);
	fprintf(o, "\t\tstd::uint32_t expected_hash = 0u;\n");
	fprintf(o, "\t\tbool has_expected_hash = false;\n");
	fprintf(o, "\t\tbool hash_verified = false;\n");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "\t\t%s %s = {};\n", signal_api_type(sig), name);
		fprintf(o, "\t\tbool has_new_%s = false;\n", name);
		free(name);
	}
	fprintf(o, "\t};\n\n");
	free(board_type);
}

static void emit_master_header_class_private(FILE *o, can_msg_t **msgs, size_t count)
{
	fprintf(o,
		"\tTxCallback tx_ = nullptr;\n"
		"\tValueHook value_hook_ = nullptr;\n\n");
	for (size_t i = 0; i < count; i++)
		emit_master_header_board_state(o, msgs[i]);
	for (size_t i = 0; i < count; i++) {
		char *board_file = board_file_name(msgs[i]);
		char *board_type = board_type_name(msgs[i]);
		fprintf(o, "\t%sState %s_;\n", board_type, board_file);
		fprintf(o, "\tbool process_%s_response(std::uint32_t id, std::uint64_t payload);\n", board_file);
		free(board_type);
		free(board_file);
	}
	fprintf(o,
		"\n\tbool send(std::uint32_t id, Opcode opcode, std::uint16_t var_id, std::uint64_t raw_value, unsigned bit_length);\n");
}

static void generate_master_hpp(can_msg_t **msgs, size_t count, const char *outdir)
{
	char *file_name = format_alloc("%s/sdodps_master.hpp", outdir);
	FILE *o = fopen_or_die(file_name, "wb");
	emit_generated_banner(o);
	fprintf(o,
		"#ifndef SDODPS_MASTER_HPP\n"
		"#define SDODPS_MASTER_HPP\n\n"
		"#include <cstddef>\n"
		"#include <cstdint>\n\n"
		"namespace sdodps {\n\n"
		"enum class Opcode : std::uint8_t {\n"
		"\tGET_REQ = 1u,\n"
		"\tSET_REQ = 2u,\n"
		"\tGET_ALL_REQ = 3u,\n"
		"\tRES = 128u,\n"
		"\tERR_OUT_OF_RANGE = 253u,\n"
		"\tERR_WRITE_RO = 254u,\n"
		"\tERR = 255u,\n"
		"};\n\n"
		"enum class Status : std::uint8_t {\n"
		"\tok,\n"
		"\tunknown_variable,\n"
		"\tread_only,\n"
		"\tno_value,\n"
		"\ttx_missing,\n"
		"\tbad_frame,\n"
		"};\n\n"
		"struct Frame {\n"
		"\tstd::uint32_t id;\n"
		"\tstd::uint8_t dlc;\n"
		"\tstd::uint64_t payload;\n"
		"};\n\n"
		"using TxCallback = bool (*)(std::uint32_t id, std::uint8_t dlc, std::uint64_t payload);\n"
		"using ValueHook = void (*)(std::uint32_t id, std::uint16_t var_id);\n\n");
	emit_master_header_boards(o, msgs, count);
	fprintf(o,
		"class Master {\n"
		"public:\n"
		"\tMaster();\n"
		"\tvoid set_tx_callback(TxCallback cb);\n"
		"\tvoid set_value_hook(ValueHook cb);\n"
		"\tbool process(std::uint32_t id, std::uint64_t payload);\n");
	emit_master_header_class_methods(o, msgs, count);
	fprintf(o, "\nprivate:\n");
	emit_master_header_class_private(o, msgs, count);
	fprintf(o,
		"};\n\n"
		"} // namespace sdodps\n\n"
		"#endif\n");
	fclose(o);
	free(file_name);
}

static void emit_master_cpp_to_string(FILE *o, can_msg_t *msg)
{
	char *board = board_type_name(msg);
	fprintf(o, "const char *to_string(%sVar value) {\n", board);
	fprintf(o, "\tswitch (value) {\n");
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "\tcase %sVar::%s: return \"%s\";\n", board, name, item->name);
		free(name);
	}
	fprintf(o, "\t}\n\treturn \"unknown\";\n}\n\n");
	free(board);
}

static void emit_master_cpp_board_methods(FILE *o, can_msg_t *msg)
{
	char *board_file = board_file_name(msg);
	char *board_type = board_type_name(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");

	fprintf(o, "void Master::set_expected_%s_hash(std::uint32_t expected) {\n", board_file);
	fprintf(o, "\t%s_.expected_hash = expected;\n", board_file);
	fprintf(o, "\t%s_.has_expected_hash = true;\n", board_file);
	fprintf(o, "\t%s_.hash_verified = false;\n", board_file);
	fprintf(o, "}\n\n");

	fprintf(o, "bool Master::%s_hash_verified() const {\n", board_file);
	fprintf(o, "\treturn %s_.hash_verified;\n", board_file);
	fprintf(o, "}\n\n");

	fprintf(o, "unsigned Master::%s_bit_length(%sVar var) {\n", board_file, board_type);
	fprintf(o, "\tswitch (var) {\n");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "\tcase %sVar::%s: return %uu;\n",
			board_type, name, sdo_value_bit_length(msg, item->value));
		free(name);
	}
	fprintf(o, "\t}\n\treturn 0u;\n}\n\n");

	fprintf(o, "bool Master::request_%s(%sVar var) {\n", board_file, board_type);
	fprintf(o, "\tif (var != %sVar::dbc_hash && !%s_.hash_verified) return false;\n", board_type, board_file);
	fprintf(o, "\treturn send(SDO%s_CAN_ID, Opcode::GET_REQ, static_cast<std::uint16_t>(var), 0u, %s_bit_length(var));\n",
		board_type, board_file);
	fprintf(o, "}\n\n");

	fprintf(o, "bool Master::has_%s_value(%sVar var) const {\n", board_file, board_type);
	fprintf(o, "\tif (var != %sVar::dbc_hash && !%s_.hash_verified) return false;\n", board_type, board_file);
	fprintf(o, "\tswitch (var) {\n");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "\tcase %sVar::%s: return %s_.has_new_%s;\n", board_type, name, board_file, name);
		free(name);
	}
	fprintf(o, "\t}\n\treturn false;\n}\n\n");

	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "bool Master::set_%s_%s(%s value) {\n", board_file, name, signal_api_type(sig));
		fprintf(o, "\treturn send(SDO%s_CAN_ID, Opcode::SET_REQ, %uu, sdodps_encode_%s_%s(value), %uu);\n",
			board_type, item->value, board_file, name, sig->bit_length);
		fprintf(o, "}\n\n");

		fprintf(o, "bool Master::take_%s_%s(%s *out) {\n", board_file, name, signal_api_type(sig));
		if (item->value != 0u)
			fprintf(o, "\tif (!%s_.hash_verified) return false;\n", board_file);
		fprintf(o, "\tif (!out || !%s_.has_new_%s) return false;\n", board_file, name);
		fprintf(o, "\t*out = %s_.%s;\n", board_file, name);
		fprintf(o, "\t%s_.has_new_%s = false;\n", board_file, name);
		if (item->value == 0u)
			fprintf(o, "\t%s_.hash_verified = %s_.has_expected_hash && (*out == %s_.expected_hash);\n", board_file, board_file, board_file);
		fprintf(o, "\treturn true;\n}\n\n");
		free(name);
	}

	free(board_type);
	free(board_file);
}

static void emit_master_cpp_process_helper(FILE *o, can_msg_t *msg)
{
	char *board_file = board_file_name(msg);
	char *board_type = board_type_name(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");

	fprintf(o, "bool Master::process_%s_response(std::uint32_t id, std::uint64_t payload) {\n", board_file);
	fprintf(o, "\tconst %sVar var = static_cast<%sVar>(sdodps_get_bits(payload, 8u, 10u));\n", board_type, board_type);
	fprintf(o, "\tswitch (var) {\n");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "\tcase %sVar::%s:\n", board_type, name);
		fprintf(o, "\t\t%s_.%s = sdodps_decode_%s_%s(payload);\n", board_file, name, board_file, name);
		fprintf(o, "\t\t%s_.has_new_%s = true;\n", board_file, name);
		if (item->value == 0u)
			fprintf(o, "\t\t%s_.hash_verified = false;\n", board_file);
		fprintf(o, "\t\tif (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));\n");
		fprintf(o, "\t\treturn true;\n");
		free(name);
	}
	fprintf(o, "\t}\n\treturn false;\n}\n\n");

	free(board_type);
	free(board_file);
}

static void generate_master_cpp(can_msg_t **msgs, size_t count, const char *outdir)
{
	char *file_name = format_alloc("%s/sdodps_master.cpp", outdir);
	FILE *o = fopen_or_die(file_name, "wb");
	emit_generated_banner(o);
	fprintf(o,
		"#include \"sdodps_master.hpp\"\n\n"
		"#include <cstring>\n\n"
		"namespace sdodps {\n\n");
	emit_cpp_common_helpers(o);
	for (size_t i = 0; i < count; i++)
		emit_master_cpp_to_string(o, msgs[i]);
	for (size_t i = 0; i < count; i++)
		emit_board_signal_helpers(o, msgs[i]);
	fprintf(o,
		"Master::Master() = default;\n\n"
		"void Master::set_tx_callback(TxCallback cb) {\n"
		"\ttx_ = cb;\n"
		"}\n\n"
		"void Master::set_value_hook(ValueHook cb) {\n"
		"\tvalue_hook_ = cb;\n"
		"}\n\n"
		"bool Master::send(std::uint32_t id, Opcode opcode, std::uint16_t var_id, std::uint64_t raw_value, unsigned bit_length) {\n"
		"\tif (!tx_) return false;\n"
		"\tconst Frame frame = sdodps_make_frame(id, opcode, var_id, 0u, raw_value, bit_length);\n"
		"\treturn tx_(frame.id, frame.dlc, frame.payload);\n"
		"}\n\n");
	for (size_t i = 0; i < count; i++)
		emit_master_cpp_board_methods(o, msgs[i]);
	for (size_t i = 0; i < count; i++)
		emit_master_cpp_process_helper(o, msgs[i]);
	fprintf(o,
		"bool Master::process(std::uint32_t id, std::uint64_t payload) {\n"
		"\tif (static_cast<Opcode>(sdodps_get_bits(payload, 0u, 8u)) != Opcode::RES) return false;\n"
		"\tswitch (id) {\n");
	for (size_t i = 0; i < count; i++) {
		char *board_file = board_file_name(msgs[i]);
		char *board_type = board_type_name(msgs[i]);
		fprintf(o, "\tcase SDO%s_CAN_ID: return process_%s_response(id, payload);\n", board_type, board_file);
		free(board_type);
		free(board_file);
	}
	fprintf(o, "\t}\n\treturn false;\n}\n\n} // namespace sdodps\n");
	fclose(o);
	free(file_name);
}

static void emit_slave_header_callback_types(FILE *o, can_msg_t *msg)
{
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		const char *prefix = callback_type_prefix(sig);
		if (signal_type_seen_before(msg, i, sig))
			continue;
		fprintf(o, "\tusing %sReadCallback = bool (*)(%s *out);\n", prefix, signal_api_type(sig));
		fprintf(o, "\tusing %sWriteCallback = bool (*)(%s value);\n", prefix, signal_api_type(sig));
	}
	fprintf(o, "\n");
}

static void emit_slave_header_methods(FILE *o, can_msg_t *msg)
{
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		const char *prefix = callback_type_prefix(sig);
		fprintf(o, "\tstatic void set_%s_reader(%sReadCallback cb);\n", name, prefix);
		fprintf(o, "\tstatic void set_%s_writer(%sWriteCallback cb);\n", name, prefix);
		fprintf(o, "\tstatic Status read_%s(%s *out);\n", name, signal_api_type(sig));
		fprintf(o, "\tstatic Status write_%s(%s value);\n", name, signal_api_type(sig));
		free(name);
	}
}

static void emit_slave_header_state(FILE *o, can_msg_t *msg)
{
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	fprintf(o, "\tstruct State {\n");
	fprintf(o, "\t\tTxCallback tx = nullptr;\n");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		const char *prefix = callback_type_prefix(sig);
		fprintf(o, "\t\t%sReadCallback %s_reader = nullptr;\n", prefix, name);
		fprintf(o, "\t\t%sWriteCallback %s_writer = nullptr;\n", prefix, name);
		free(name);
	}
	fprintf(o, "\t};\n\n");
}

static void generate_slave_hpp(can_msg_t *msg, const char *outdir)
{
	char *board_file = board_file_name(msg);
	char *board_type = board_type_name(msg);
	char *guard = sanitize_macro(board_file);
	char *file_name = format_alloc("%s/sdodps_slave_%s.hpp", outdir, board_file);
	FILE *o = fopen_or_die(file_name, "wb");
	emit_generated_banner(o);
	fprintf(o,
		"#ifndef SDODPS_SLAVE_%s_HPP\n"
		"#define SDODPS_SLAVE_%s_HPP\n\n"
		"#include \"sdodps_master.hpp\"\n\n"
		"namespace sdodps {\n\n"
		"class Slave%s {\n"
		"public:\n",
		guard, guard, board_type);
	emit_slave_header_callback_types(o, msg);
	fprintf(o,
		"\tstatic void set_tx_callback(TxCallback cb);\n");
	emit_slave_header_methods(o, msg);
	fprintf(o,
		"\tstatic bool process(std::uint32_t id, std::uint64_t payload);\n"
		"\tstatic bool notify(%sVar var);\n\n"
		"private:\n", board_type);
	emit_slave_header_state(o, msg);
	fprintf(o,
		"\tstatic State &instance();\n"
		"\tstatic bool send_response(Opcode opcode, %sVar var, std::uint64_t raw_value);\n"
		"\tstatic bool process_get(%sVar var);\n"
		"\tstatic bool process_set(%sVar var, std::uint64_t payload);\n"
		"};\n\n"
		"} // namespace sdodps\n\n"
		"#endif\n",
		board_type, board_type, board_type);
	fclose(o);
	free(file_name);
	free(guard);
	free(board_type);
	free(board_file);
}

static void emit_slave_cpp_setters(FILE *o, can_msg_t *msg)
{
	char *board_type = board_type_name(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		const char *prefix = callback_type_prefix(sig);
		fprintf(o, "void Slave%s::set_%s_reader(%sReadCallback cb) {\n", board_type, name, prefix);
		fprintf(o, "\tinstance().%s_reader = cb;\n}\n\n", name);
		fprintf(o, "void Slave%s::set_%s_writer(%sWriteCallback cb) {\n", board_type, name, prefix);
		fprintf(o, "\tinstance().%s_writer = cb;\n}\n\n", name);
		free(name);
	}
	free(board_type);
}

static void emit_slave_cpp_read_write(FILE *o, can_msg_t *msg)
{
	char *board_type = board_type_name(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "Status Slave%s::read_%s(%s *out) {\n", board_type, name, signal_api_type(sig));
		fprintf(o, "\tif (!out) return Status::bad_frame;\n");
		fprintf(o, "\tState &state = instance();\n");
		fprintf(o, "\tif (!state.%s_reader) return Status::no_value;\n", name);
		fprintf(o, "\treturn state.%s_reader(out) ? Status::ok : Status::no_value;\n", name);
		fprintf(o, "}\n\n");

		fprintf(o, "Status Slave%s::write_%s(%s value) {\n", board_type, name, signal_api_type(sig));
		fprintf(o, "\tState &state = instance();\n");
		fprintf(o, "\tif (!state.%s_writer) return Status::read_only;\n", name);
		fprintf(o, "\treturn state.%s_writer(value) ? Status::ok : Status::no_value;\n", name);
		fprintf(o, "}\n\n");
		free(name);
	}
	free(board_type);
}

static void emit_slave_cpp_process_get(FILE *o, can_msg_t *msg)
{
	char *board_type = board_type_name(msg);
	char *board_file = board_file_name(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	fprintf(o, "bool Slave%s::process_get(%sVar var) {\n", board_type, board_type);
	fprintf(o, "\tswitch (var) {\n");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "\tcase %sVar::%s: {\n", board_type, name);
		fprintf(o, "\t\t%s value = {};\n", signal_api_type(sig));
		fprintf(o, "\t\tconst Status status = read_%s(&value);\n", name);
		fprintf(o, "\t\tconst Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;\n");
		fprintf(o, "\t\tconst std::uint64_t raw = status == Status::ok ? sdodps_encode_%s_%s(value) : 0u;\n", board_file, name);
		fprintf(o, "\t\treturn send_response(opcode, var, raw);\n");
		fprintf(o, "\t}\n");
		free(name);
	}
	fprintf(o, "\t}\n\treturn send_response(Opcode::ERR, var, 0u);\n}\n\n");
	free(board_file);
	free(board_type);
}

static void emit_slave_cpp_process_set(FILE *o, can_msg_t *msg)
{
	char *board_type = board_type_name(msg);
	char *board_file = board_file_name(msg);
	signal_t *var_id = find_signal_by_name(msg, "var_id");
	fprintf(o, "bool Slave%s::process_set(%sVar var, std::uint64_t payload) {\n", board_type, board_type);
	fprintf(o, "\tswitch (var) {\n");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_multiplexed_signal_by_value(msg, item->value);
		char *name = sanitize_identifier(item->name, false);
		fprintf(o, "\tcase %sVar::%s: {\n", board_type, name);
		fprintf(o, "\t\tconst %s value = sdodps_decode_%s_%s(payload);\n", signal_api_type(sig), board_file, name);
		fprintf(o, "\t\tconst Status status = write_%s(value);\n", name);
		fprintf(o, "\t\tconst Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);\n");
		fprintf(o, "\t\t%s stored = value;\n", signal_api_type(sig));
		fprintf(o, "\t\tif (status == Status::ok) (void)read_%s(&stored);\n", name);
		fprintf(o, "\t\tconst std::uint64_t raw = status == Status::ok ? sdodps_encode_%s_%s(stored) : 0u;\n", board_file, name);
		fprintf(o, "\t\treturn send_response(opcode, var, raw);\n");
		fprintf(o, "\t}\n");
		free(name);
	}
	fprintf(o, "\t}\n\treturn send_response(Opcode::ERR, var, 0u);\n}\n\n");
	free(board_file);
	free(board_type);
}

static void generate_slave_cpp(can_msg_t *msg, const char *outdir)
{
	char *board_file = board_file_name(msg);
	char *board_type = board_type_name(msg);
	char *file_name = format_alloc("%s/sdodps_slave_%s.cpp", outdir, board_file);
	FILE *o = fopen_or_die(file_name, "wb");
	emit_generated_banner(o);
	fprintf(o,
		"#include \"sdodps_slave_%s.hpp\"\n\n"
		"#include <cstring>\n\n"
		"namespace sdodps {\n\n",
		board_file);
	emit_cpp_common_helpers(o);
	emit_board_signal_helpers(o, msg);
	fprintf(o, "Slave%s::State &Slave%s::instance() {\n", board_type, board_type);
	fprintf(o, "\tstatic State state;\n");
	fprintf(o, "\treturn state;\n}\n\n");

	fprintf(o, "void Slave%s::set_tx_callback(TxCallback cb) {\n", board_type);
	fprintf(o, "\tinstance().tx = cb;\n}\n\n");

	emit_slave_cpp_setters(o, msg);
	emit_slave_cpp_read_write(o, msg);

	fprintf(o, "bool Slave%s::send_response(Opcode opcode, %sVar var, std::uint64_t raw_value) {\n", board_type, board_type);
	fprintf(o, "\tState &state = instance();\n");
	fprintf(o, "\tif (!state.tx) return false;\n");
	fprintf(o, "\tconst Frame frame = sdodps_make_frame(SDO%s_CAN_ID, opcode, static_cast<std::uint16_t>(var), 0u, raw_value, Master::%s_bit_length(var));\n",
		board_type, board_file);
	fprintf(o, "\treturn state.tx(frame.id, frame.dlc, frame.payload);\n");
	fprintf(o, "}\n\n");

	fprintf(o, "bool Slave%s::process(std::uint32_t id, std::uint64_t payload) {\n", board_type);
	fprintf(o, "\tif (id != SDO%s_CAN_ID) return false;\n", board_type);
	fprintf(o, "\tconst Opcode opcode = static_cast<Opcode>(sdodps_get_bits(payload, 0u, 8u));\n");
	fprintf(o, "\tconst %sVar var = static_cast<%sVar>(sdodps_get_bits(payload, 8u, 10u));\n", board_type, board_type);
	fprintf(o, "\tif (opcode == Opcode::GET_REQ) return process_get(var);\n");
	fprintf(o, "\tif (opcode == Opcode::SET_REQ) return process_set(var, payload);\n");
	fprintf(o, "\treturn false;\n}\n\n");

	fprintf(o, "bool Slave%s::notify(%sVar var) {\n", board_type, board_type);
	fprintf(o, "\treturn process_get(var);\n}\n\n");

	emit_slave_cpp_process_get(o, msg);
	emit_slave_cpp_process_set(o, msg);
	fprintf(o, "} // namespace sdodps\n");
	fclose(o);
	free(file_name);
	free(board_type);
	free(board_file);
}

int dbc2sdodps(dbc_t *dbc, const char *dbc_file, const char *outdir)
{
	assert(dbc);
	assert(dbc_file);
	assert(outdir);
	apply_sigval_overrides(dbc, dbc_file);
	if (!check_opcode_valtable(dbc)) {
		warning("SDO_DPS generation skipped: missing or invalid VAL_TABLE_ OPCODES");
		return -1;
	}

	size_t sdo_count = 0;
	can_msg_t **sdo_msgs = filter_sdo_messages(dbc, &sdo_count);
	if (sdo_count == 0) {
		free(sdo_msgs);
		warning("SDO_DPS generation skipped: no valid SDO messages found");
		return -1;
	}

	ensure_dir(outdir);
	generate_master_hpp(sdo_msgs, sdo_count, outdir);
	generate_master_cpp(sdo_msgs, sdo_count, outdir);
	for (size_t i = 0; i < sdo_count; i++) {
		generate_slave_hpp(sdo_msgs[i], outdir);
		generate_slave_cpp(sdo_msgs[i], outdir);
	}

	free(sdo_msgs);
	return 0;
}
