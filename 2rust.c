/**@file 2rust.c
 * @brief Convert a parsed DBC into a dependency-free Rust module.
 * @copyright SUBLEQ LTD. (2025), RaceUP (2026)
 * @license MIT
 */
#include "2rust.h"
#include "util.h"

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH (512u)

static char *format_alloc(const char *fmt, ...)
{
	assert(fmt);
	va_list ap;
	va_start(ap, fmt);
	va_list copy;
	va_copy(copy, ap);
	const int needed = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);
	if (needed < 0)
		error("vsnprintf failed");
	char *result = allocate((size_t)needed + 1u);
	vsnprintf(result, (size_t)needed + 1u, fmt, copy);
	va_end(copy);
	return result;
}

static bool rust_keyword(const char *name)
{
	static const char *const words[] = {
		"as", "break", "const", "continue", "crate", "else", "enum",
		"extern", "false", "fn", "for", "if", "impl", "in", "let",
		"loop", "match", "mod", "move", "mut", "pub", "ref", "return",
		"self", "Self", "static", "struct", "super", "trait", "true",
		"type", "unsafe", "use", "where", "while", "async", "await",
		"dyn", "abstract", "become", "box", "do", "final", "macro",
		"override", "priv", "typeof", "unsized", "virtual", "yield",
		"try",
	};
	for (size_t i = 0; i < sizeof(words) / sizeof(words[0]); i++)
		if (!strcmp(name, words[i]))
			return true;
	return false;
}

static char *rust_snake(const char *name)
{
	assert(name);
	const size_t len = strlen(name);
	char *out = allocate(len + 3u);
	size_t j = 0;
	if (!len || (!isalpha((unsigned char)name[0]) && name[0] != '_'))
		out[j++] = '_';
	for (size_t i = 0; i < len; i++) {
		const unsigned char ch = (unsigned char)name[i];
		out[j++] = isalnum(ch) || ch == '_' ? (char)tolower(ch) : '_';
	}
	out[j] = '\0';
	if (rust_keyword(out)) {
		out[j++] = '_';
		out[j] = '\0';
	}
	return out;
}

static char *rust_pascal(const char *name)
{
	assert(name);
	const size_t len = strlen(name);
	char *out = allocate(len + 4u);
	size_t j = 0;
	for (size_t i = 0; i < len;) {
		while (i < len && !isalnum((unsigned char)name[i]))
			i++;
		if (i == len)
			break;
		const size_t begin = i;
		while (i < len && isalnum((unsigned char)name[i]))
			i++;
		bool all_upper = true;
		for (size_t k = begin; k < i; k++)
			if (isalpha((unsigned char)name[k]) &&
			    islower((unsigned char)name[k]))
				all_upper = false;
		for (size_t k = begin; k < i; k++) {
			unsigned char ch = (unsigned char)name[k];
			if (k == begin)
				ch = (unsigned char)toupper(ch);
			else if (all_upper)
				ch = (unsigned char)tolower(ch);
			out[j++] = (char)ch;
		}
		if (i < len) {
			while (i < len && !isalnum((unsigned char)name[i]))
				i++;
			continue;
		}
	}
	if (!j || !isalpha((unsigned char)out[0])) {
		memmove(out + 1, out, j);
		out[0] = 'N';
		j++;
	}
	out[j] = '\0';
	return out;
}

static char *rust_upper(const char *name)
{
	char *out = rust_snake(name);
	for (size_t i = 0; out[i]; i++)
		out[i] = (char)toupper((unsigned char)out[i]);
	return out;
}

static void emit_rust_string(FILE *o, const char *s)
{
	assert(o);
	fputc('"', o);
	if (s) {
		for (size_t i = 0; s[i]; i++) {
			const unsigned char ch = (unsigned char)s[i];
			switch (ch) {
			case '\\': fputs("\\\\", o); break;
			case '"': fputs("\\\"", o); break;
			case '\n': fputs("\\n", o); break;
			case '\r': fputs("\\r", o); break;
			case '\t': fputs("\\t", o); break;
			default:
				if (ch < 0x20u)
					fprintf(o, "\\u{%02x}", ch);
				else
					fputc(ch, o);
				break;
			}
		}
	}
	fputc('"', o);
}

static unsigned fixed_start(const signal_t *sig)
{
	assert(sig);
	if (sig->endianess == endianess_motorola_e)
		return (8u * (7u - (sig->start_bit / 8u))) +
			(sig->start_bit % 8u) - (sig->bit_length - 1u);
	return sig->start_bit;
}

static const char *rust_unsigned_type(unsigned bits)
{
	if (bits <= 8u) return "u8";
	if (bits <= 16u) return "u16";
	if (bits <= 32u) return "u32";
	return "u64";
}

static const char *rust_signed_type(unsigned bits)
{
	if (bits <= 8u) return "i8";
	if (bits <= 16u) return "i16";
	if (bits <= 32u) return "i32";
	return "i64";
}

static bool signal_has_enum(const signal_t *sig)
{
	return sig->val_list && sig->val_list->val_list_item_count > 0u;
}

static char *message_type_name(const can_msg_t *msg)
{
	return rust_pascal(msg->name);
}

static bool rust_type_matches_message(const dbc_t *dbc, const char *type_name)
{
	for (size_t i = 0; i < dbc->message_count; i++) {
		char *message = message_type_name(dbc->messages[i]);
		const bool matches = !strcmp(message, type_name);
		free(message);
		if (matches)
			return true;
	}
	return false;
}

static char *val_table_enum_name(const dbc_t *dbc, const char *table_name)
{
	char *name = rust_pascal(table_name);
	if (!rust_type_matches_message(dbc, name))
		return name;
	char *unique = format_alloc("%sValue", name);
	free(name);
	return unique;
}

static char *signal_enum_name(const dbc_t *dbc, const can_msg_t *msg,
	const signal_t *sig)
{
	if (sig->val_list && sig->val_list->is_val_table_reference &&
	    sig->val_list->val_table_name)
		return val_table_enum_name(dbc, sig->val_list->val_table_name);
	char *message = message_type_name(msg);
	char *signal = rust_pascal(sig->name);
	char *name = format_alloc("%s%sValue", message, signal);
	free(signal);
	free(message);
	return name;
}

static char *signal_api_type(const dbc_t *dbc, const can_msg_t *msg,
	const signal_t *sig)
{
	if (signal_has_enum(sig))
		return signal_enum_name(dbc, msg, sig);
	if (sig->is_floating)
		return duplicate(sig->bit_length == 64u ? "f64" : "f32");
	if (sig->scaling != 1.0 || sig->offset != 0.0)
		return duplicate(sig->bit_length <= 32u ? "f32" : "f64");
	return duplicate(sig->is_signed ?
		rust_signed_type(sig->bit_length) :
		rust_unsigned_type(sig->bit_length));
}

static signal_t *signal_mux_parent(can_msg_t *msg, signal_t *sig)
{
	if (sig->mux_parent)
		return sig->mux_parent;
	if (!sig->is_multiplexed)
		return NULL;
	signal_t *fallback = NULL;
	for (size_t i = 0; i < msg->signal_count; i++) {
		signal_t *candidate = msg->sigs[i];
		if (!candidate->is_multiplexor)
			continue;
		if (!fallback)
			fallback = candidate;
		for (size_t j = 0; j < candidate->mul_num; j++)
			if (candidate->muxed[j] == sig)
				return candidate;
	}
	return fallback;
}

static uint32_t hash32_update_bytes(uint32_t hash, const void *data, size_t size)
{
	const unsigned char *bytes = data;
	for (size_t i = 0; i < size; i++) {
		hash ^= bytes[i];
		hash *= 16777619u;
	}
	return hash;
}

static uint32_t hash32_update_cstr(uint32_t hash, const char *s)
{
	return hash32_update_bytes(hash, s, strlen(s));
}

static uint32_t hash32_update_format(uint32_t hash, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	va_list copy;
	va_copy(copy, ap);
	const int needed = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);
	if (needed < 0)
		error("vsnprintf failed while computing Rust DBC hash");
	char *buf = allocate((size_t)needed + 1u);
	vsnprintf(buf, (size_t)needed + 1u, fmt, copy);
	va_end(copy);
	hash = hash32_update_bytes(hash, buf, (size_t)needed);
	free(buf);
	return hash;
}

static uint32_t hash_val_list(uint32_t hash, const val_list_t *list)
{
	if (!list)
		return hash32_update_cstr(hash, "VAL:none\n");
	hash = hash32_update_format(hash, "VAL:%s:%u:%d:",
		list->name ? list->name : "", list->id,
		(int)list->is_val_table_reference);
	if (list->val_table_name)
		hash = hash32_update_format(hash, "table=%s:", list->val_table_name);
	for (size_t i = 0; i < list->val_list_item_count; i++)
		hash = hash32_update_format(hash, "%u=%s;",
			list->val_list_items[i]->value,
			list->val_list_items[i]->name);
	return hash32_update_cstr(hash, "\n");
}

static uint32_t hash_signal(uint32_t hash, const signal_t *sig)
{
	hash = hash32_update_format(hash,
		"SIG:%s:%u:%u:%d:%d:%d:%u:%.17g:%.17g:%.17g:%.17g:%s:",
		sig->name, sig->start_bit, sig->bit_length, (int)sig->endianess,
		(int)sig->is_signed, (int)sig->is_floating, sig->sigval,
		sig->scaling, sig->offset, sig->minimum, sig->maximum,
		sig->units ? sig->units : "");
	for (size_t i = 0; i < sig->ecu_count; i++)
		hash = hash32_update_format(hash, "%s,", sig->ecus[i]);
	hash = hash32_update_cstr(hash, "\n");
	hash = hash32_update_format(hash, "MUX:%d:%d:%u:%zu:",
		(int)sig->is_multiplexor, (int)sig->is_multiplexed,
		sig->switchval, sig->mul_num);
	if (sig->mux_parent)
		hash = hash32_update_format(hash, "parent=%s:", sig->mux_parent->name);
	for (size_t i = 0; i < sig->mul_num; i++) {
		mul_val_list_t *mv = sig->mux_vals[i];
		hash = hash32_update_format(hash, "%s:", sig->muxed[i]->name);
		if (mv) {
			hash = hash32_update_format(hash, "%s:%s:",
				mv->multiplexed ? mv->multiplexed : "",
				mv->multiplexor ? mv->multiplexor : "");
			for (size_t j = 0; j < mv->range_num; j++)
				hash = hash32_update_format(hash, "%u-%u,",
					mv->ranges[j]->min_value, mv->ranges[j]->max_value);
		}
		hash = hash32_update_cstr(hash, ";");
	}
	hash = hash32_update_cstr(hash, "\n");
	hash = hash_val_list(hash, sig->val_list);
	return hash32_update_format(hash, "COMMENT:%s\n",
		sig->comment ? sig->comment : "");
}

static uint32_t hash_message(uint32_t hash, const can_msg_t *msg)
{
	hash = hash32_update_format(hash, "MSG:%s:%lu:%u:%d:",
		msg->name, msg->id, msg->dlc, (int)msg->is_extended);
	for (size_t i = 0; i < msg->ecu_count; i++)
		hash = hash32_update_format(hash, "%s,", msg->ecus[i]);
	hash = hash32_update_cstr(hash, "\n");
	if (msg->has_cycle_time)
		hash = hash32_update_format(hash, "CYCLETIME:%u\n", msg->cycle_time);
	hash = hash32_update_format(hash, "COMMENT:%s\n",
		msg->comment ? msg->comment : "");
	for (size_t i = 0; i < msg->signal_count; i++)
		hash = hash_signal(hash, msg->sigs[i]);
	return hash;
}

static uint32_t dbc_hash32(const dbc_t *dbc)
{
	uint32_t hash = hash32_update_cstr(2166136261u, "DBC\n");
	for (size_t i = 0; i < dbc->message_count; i++)
		hash = hash_message(hash, dbc->messages[i]);
	return hash;
}

static bool node_in_list(char **items, size_t count, const char *node)
{
	for (size_t i = 0; i < count; i++)
		if (!strcmp(items[i], node))
			return true;
	return false;
}

static void add_node(char ***items, size_t *count, const char *node)
{
	if (node_in_list(*items, *count, node))
		return;
	*items = reallocator(*items, (*count + 1u) * sizeof(**items));
	(*items)[(*count)++] = (char *)node;
}

static bool node_matches_signal(const signal_t *sig, const char *node)
{
	for (size_t i = 0; i < sig->ecu_count; i++)
		if (!strcmp(sig->ecus[i], node))
			return true;
	return false;
}

static bool node_matches_message(const can_msg_t *msg, const char *node)
{
	for (size_t i = 0; i < msg->ecu_count; i++)
		if (!strcmp(msg->ecus[i], node))
			return true;
	for (size_t i = 0; i < msg->signal_count; i++)
		if (node_matches_signal(msg->sigs[i], node))
			return true;
	return false;
}

static uint32_t node_hash32(const dbc_t *dbc, const char *node)
{
	uint32_t hash = hash32_update_format(2166136261u, "NODE:%s\n", node);
	for (size_t i = 0; i < dbc->message_count; i++)
		if (node_matches_message(dbc->messages[i], node))
			hash = hash_message(hash, dbc->messages[i]);
	return hash;
}

static void emit_prelude(FILE *o, const dbc_t *dbc, const char *name)
{
	fputs(
		"//! CAN DBC encoder/decoder generated by dbcc. Do not edit.\n"
		"//! The module is dependency-free and can be used in `no_std` crates.\n"
		"#![allow(non_camel_case_types, non_snake_case, non_upper_case_globals)]\n\n",
		o);
	fprintf(o, "pub const DBCC_GENERATOR_VERSION: u32 = %du32;\n", dbc->version);
	fprintf(o, "pub const DBCC_HASH: u32 = 0x%08" PRIx32 "u32;\n", dbc_hash32(dbc));
	fputs("pub const DBCC_MODULE_NAME: &str = ", o);
	emit_rust_string(o, name);
	fputs(";\n", o);

	char **nodes = NULL;
	size_t count = 0;
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		for (size_t j = 0; j < msg->ecu_count; j++)
			add_node(&nodes, &count, msg->ecus[j]);
		for (size_t j = 0; j < msg->signal_count; j++)
			for (size_t k = 0; k < msg->sigs[j]->ecu_count; k++)
				add_node(&nodes, &count, msg->sigs[j]->ecus[k]);
	}
	char **emitted_node_names = NULL;
	size_t emitted_node_count = 0;
	for (size_t i = 0; i < count; i++) {
		char *upper = rust_upper(nodes[i]);
		if (node_in_list(emitted_node_names, emitted_node_count, upper)) {
			char *base = duplicate(upper);
			size_t suffix = 2u;
			do {
				free(upper);
				upper = format_alloc("%s_%zu", base, suffix++);
			} while (node_in_list(emitted_node_names, emitted_node_count, upper));
			free(base);
		}
		fprintf(o, "pub const DBCC_NODE_HASH_%s: u32 = 0x%08" PRIx32 "u32;\n",
			upper, node_hash32(dbc, nodes[i]));
		emitted_node_names = reallocator(emitted_node_names,
			(emitted_node_count + 1u) * sizeof(*emitted_node_names));
		emitted_node_names[emitted_node_count++] = upper;
	}
	for (size_t i = 0; i < emitted_node_count; i++)
		free(emitted_node_names[i]);
	free(emitted_node_names);
	free(nodes);

	fputs(
		"\n#[derive(Debug, Clone, Copy, PartialEq, Eq)]\n"
		"pub enum DbccError {\n"
		"    UnknownMessage { id: u32 },\n"
		"    InvalidDlc { id: u32, expected: u8, actual: u8 },\n"
		"    InactiveMultiplexedSignal { signal: &'static str, mux: u64 },\n"
		"    OutOfRange { signal: &'static str },\n"
		"    InvalidEnumValue { signal: &'static str, value: u64 },\n"
		"}\n\n"
		"#[derive(Debug, Clone, Copy, PartialEq, Eq)]\n"
		"pub struct CanFrame { pub id: u32, pub dlc: u8, pub payload: u64 }\n\n"
		"#[derive(Debug, Clone, Copy, PartialEq)]\n"
		"pub struct SignalInfo {\n"
		"    pub name: &'static str,\n"
		"    pub start_bit: u16,\n"
		"    pub bit_length: u16,\n"
		"    pub little_endian: bool,\n"
		"    pub signed: bool,\n"
		"    pub floating: bool,\n"
		"    pub scaling: f64,\n"
		"    pub offset: f64,\n"
		"    pub minimum: f64,\n"
		"    pub maximum: f64,\n"
		"    pub units: &'static str,\n"
		"    pub multiplexor: bool,\n"
		"    pub multiplexed: bool,\n"
		"    pub switch_value: Option<u64>,\n"
		"}\n\n"
		"#[derive(Debug, Clone, Copy, PartialEq)]\n"
		"pub struct MessageInfo {\n"
		"    pub id: u32,\n"
		"    pub dlc: u8,\n"
		"    pub name: &'static str,\n"
		"    pub is_extended: bool,\n"
		"    pub cycle_time_ms: Option<u32>,\n"
		"    pub signals: &'static [SignalInfo],\n"
		"}\n\n"
		"#[inline]\n"
		"const fn dbcc_mask(bits: u32) -> u64 {\n"
		"    if bits >= 64 { u64::MAX } else { (1u64 << bits) - 1u64 }\n"
		"}\n\n"
		"#[inline]\n"
		"fn dbcc_extract(payload: u64, start: u32, bits: u32, motorola: bool) -> u64 {\n"
		"    let lane = if motorola { payload.swap_bytes() } else { payload };\n"
		"    (lane >> start) & dbcc_mask(bits)\n"
		"}\n\n"
		"#[inline]\n"
		"fn dbcc_insert(payload: &mut u64, start: u32, bits: u32, motorola: bool, value: u64) {\n"
		"    let mask = dbcc_mask(bits);\n"
		"    let mut lane = if motorola { payload.swap_bytes() } else { *payload };\n"
		"    lane = (lane & !(mask << start)) | ((value & mask) << start);\n"
		"    *payload = if motorola { lane.swap_bytes() } else { lane };\n"
		"}\n\n",
		o);
}

static bool enum_table_emitted_before(const dbc_t *dbc, size_t upto,
	const val_list_t *list)
{
	for (size_t i = 0; i < upto; i++)
		if (dbc->val_tables[i] == list ||
		    (dbc->val_tables[i]->name && list->name &&
		     !strcmp(dbc->val_tables[i]->name, list->name)))
			return true;
	return false;
}

static size_t enum_value_first_index(const val_list_t *list, size_t index)
{
	for (size_t i = 0; i < index; i++)
		if (list->val_list_items[i]->value ==
		    list->val_list_items[index]->value)
			return i;
	return index;
}

static void emit_enum(FILE *o, const char *type_name, const val_list_t *list)
{
	if (!list || list->val_list_item_count == 0u)
		return;
	fprintf(o,
		"#[repr(u64)]\n"
		"#[derive(Debug, Clone, Copy, PartialEq, Eq)]\n"
		"pub enum %s {\n",
		type_name);
	for (size_t i = 0; i < list->val_list_item_count; i++) {
		if (enum_value_first_index(list, i) != i)
			continue;
		val_list_item_t *item = list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		fprintf(o, "    %s = %" PRIu64 "u64,\n",
			variant, (uint64_t)item->value);
		free(variant);
	}
	fprintf(o,
		"}\n\n"
		"impl %s {\n",
		type_name);
	for (size_t i = 0; i < list->val_list_item_count; i++) {
		const size_t first = enum_value_first_index(list, i);
		if (first == i)
			continue;
		char *alias = rust_pascal(list->val_list_items[i]->name);
		char *canonical = rust_pascal(list->val_list_items[first]->name);
		if (strcmp(alias, canonical))
			fprintf(o,
				"    #[allow(non_upper_case_globals)]\n"
				"    pub const %s: Self = Self::%s;\n",
				alias, canonical);
		free(canonical);
		free(alias);
	}
	fprintf(o,
		"    pub const fn raw(self) -> u64 { self as u64 }\n"
		"    pub const fn name(self) -> &'static str {\n"
		"        match self {\n");
	for (size_t i = 0; i < list->val_list_item_count; i++) {
		if (enum_value_first_index(list, i) != i)
			continue;
		val_list_item_t *item = list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		fprintf(o, "            Self::%s => ", variant);
		emit_rust_string(o, item->name);
		fputs(",\n", o);
		free(variant);
	}
	fputs(
		"        }\n"
		"    }\n"
		"}\n\n",
		o);
	fprintf(o,
		"impl core::convert::TryFrom<u64> for %s {\n"
		"    type Error = u64;\n"
		"    fn try_from(value: u64) -> Result<Self, u64> {\n"
		"        match value {\n",
		type_name);
	for (size_t i = 0; i < list->val_list_item_count; i++) {
		if (enum_value_first_index(list, i) != i)
			continue;
		val_list_item_t *item = list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		fprintf(o, "            %" PRIu64 "u64 => Ok(Self::%s),\n",
			(uint64_t)item->value, variant);
		free(variant);
	}
	fputs(
		"            other => Err(other),\n"
		"        }\n"
		"    }\n"
		"}\n\n",
		o);
}

static void emit_enums(FILE *o, const dbc_t *dbc)
{
	for (size_t i = 0; i < dbc->val_table_count; i++) {
		val_list_t *list = dbc->val_tables[i];
		if (!list || !list->name || list->val_list_item_count == 0u ||
		    enum_table_emitted_before(dbc, i, list))
			continue;
		char *name = val_table_enum_name(dbc, list->name);
		emit_enum(o, name, list);
		free(name);
	}
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		for (size_t j = 0; j < msg->signal_count; j++) {
			signal_t *sig = msg->sigs[j];
			if (!signal_has_enum(sig) || sig->val_list->is_val_table_reference)
				continue;
			char *name = signal_enum_name(dbc, msg, sig);
			emit_enum(o, name, sig->val_list);
			free(name);
		}
	}
}

static void emit_mux_check(FILE *o, can_msg_t *msg, signal_t *sig)
{
	if (!sig->is_multiplexed)
		return;
	signal_t *parent = signal_mux_parent(msg, sig);
	if (!parent)
		return;
	fprintf(o,
		"        let mux = dbcc_extract(self.payload, %uu32, %uu32, %s);\n"
		"        if !(",
		fixed_start(parent), parent->bit_length,
		parent->endianess == endianess_motorola_e ? "true" : "false");
	bool have_range = false;
	for (size_t i = 0; i < parent->mul_num; i++) {
		if (parent->muxed[i] != sig || !parent->mux_vals[i])
			continue;
		mul_val_list_t *mv = parent->mux_vals[i];
		for (size_t r = 0; r < mv->range_num; r++) {
			if (have_range)
				fputs(" || ", o);
			if (mv->ranges[r]->min_value == 0u)
				fprintf(o, "(mux <= %uu64)",
					mv->ranges[r]->max_value);
			else
				fprintf(o, "(mux >= %uu64 && mux <= %uu64)",
					mv->ranges[r]->min_value,
					mv->ranges[r]->max_value);
			have_range = true;
		}
	}
	if (!have_range)
		fprintf(o, "mux == %uu64", sig->switchval);
	fputs(
		") {\n"
		"            return Err(DbccError::InactiveMultiplexedSignal { signal: ",
		o);
	emit_rust_string(o, sig->name);
	fputs(", mux });\n        }\n", o);
}

static void emit_range_check(FILE *o, const signal_t *sig, const char *value)
{
	if (sig->minimum == sig->maximum)
		return;
	fprintf(o, "        if (%s as f64) < %.17g_f64 || (%s as f64) > %.17g_f64 {\n",
		value, sig->minimum, value, sig->maximum);
	fputs("            return Err(DbccError::OutOfRange { signal: ", o);
	emit_rust_string(o, sig->name);
	fputs(" });\n        }\n", o);
}

static void emit_signal_getter(FILE *o, const dbc_t *dbc, can_msg_t *msg,
	signal_t *sig)
{
	char *method = rust_snake(sig->name);
	char *type = signal_api_type(dbc, msg, sig);
	fprintf(o, "    pub fn get_%s(&self) -> Result<%s, DbccError> {\n", method, type);
	emit_mux_check(o, msg, sig);
	fprintf(o,
		"        let raw = dbcc_extract(self.payload, %uu32, %uu32, %s);\n",
		fixed_start(sig), sig->bit_length,
		sig->endianess == endianess_motorola_e ? "true" : "false");
	if (signal_has_enum(sig)) {
		fprintf(o,
			"        <%s as core::convert::TryFrom<u64>>::try_from(raw)\n"
			"            .map_err(|value| DbccError::InvalidEnumValue { signal: ",
			type);
		emit_rust_string(o, sig->name);
		fputs(", value })\n", o);
	} else if (sig->is_floating && sig->bit_length == 32u) {
		fputs("        let value = f32::from_bits(raw as u32);\n", o);
		if (sig->scaling != 1.0)
			fprintf(o, "        let value = value * %.17g_f32;\n", sig->scaling);
		if (sig->offset != 0.0)
			fprintf(o, "        let value = value + %.17g_f32;\n", sig->offset);
		emit_range_check(o, sig, "value");
		fputs("        Ok(value)\n", o);
	} else if (sig->is_floating && sig->bit_length == 64u) {
		fputs("        let value = f64::from_bits(raw);\n", o);
		if (sig->scaling != 1.0)
			fprintf(o, "        let value = value * %.17g_f64;\n", sig->scaling);
		if (sig->offset != 0.0)
			fprintf(o, "        let value = value + %.17g_f64;\n", sig->offset);
		emit_range_check(o, sig, "value");
		fputs("        Ok(value)\n", o);
	} else if (sig->is_signed) {
		if (sig->bit_length < 64u)
			fprintf(o,
				"        let signed = if raw & (1u64 << %uu32) != 0 {\n"
				"            (raw | !dbcc_mask(%uu32)) as i64\n"
				"        } else { raw as i64 };\n",
				sig->bit_length - 1u, sig->bit_length);
		else
			fputs("        let signed = raw as i64;\n", o);
		if (sig->scaling != 1.0 || sig->offset != 0.0) {
			fprintf(o, "        let value = signed as %s", type);
			if (sig->scaling != 1.0)
				fprintf(o, " * %.17g_%s", sig->scaling, type);
			if (sig->offset != 0.0)
				fprintf(o, " + %.17g_%s", sig->offset, type);
			fputs(";\n", o);
		} else {
			fprintf(o, "        let value = signed as %s;\n", type);
		}
		emit_range_check(o, sig, "value");
		fputs("        Ok(value)\n", o);
	} else {
		if (sig->scaling != 1.0 || sig->offset != 0.0) {
			fprintf(o, "        let value = raw as %s", type);
			if (sig->scaling != 1.0)
				fprintf(o, " * %.17g_%s", sig->scaling, type);
			if (sig->offset != 0.0)
				fprintf(o, " + %.17g_%s", sig->offset, type);
			fputs(";\n", o);
		} else {
			fprintf(o, "        let value = raw as %s;\n", type);
		}
		emit_range_check(o, sig, "value");
		fputs("        Ok(value)\n", o);
	}
	fputs("    }\n\n", o);
	free(type);
	free(method);
}

static void emit_signal_setter(FILE *o, const dbc_t *dbc, can_msg_t *msg,
	signal_t *sig)
{
	char *method = rust_snake(sig->name);
	char *type = signal_api_type(dbc, msg, sig);
	fprintf(o, "    pub fn set_%s(&mut self, value: %s) -> Result<(), DbccError> {\n",
		method, type);
	emit_mux_check(o, msg, sig);
	if (!signal_has_enum(sig))
		emit_range_check(o, sig, "value");
	if (signal_has_enum(sig)) {
		fputs("        let raw = value.raw();\n", o);
	} else if (sig->is_floating && sig->bit_length == 32u) {
		fprintf(o, "        let %swire = value;\n",
			(sig->offset != 0.0 || sig->scaling != 1.0) ? "mut " : "");
		if (sig->offset != 0.0)
			fprintf(o, "        wire -= %.17g_f32;\n", sig->offset);
		if (sig->scaling != 1.0)
			fprintf(o, "        wire /= %.17g_f32;\n", sig->scaling);
		fputs("        let raw = wire.to_bits() as u64;\n", o);
	} else if (sig->is_floating && sig->bit_length == 64u) {
		fprintf(o, "        let %swire = value;\n",
			(sig->offset != 0.0 || sig->scaling != 1.0) ? "mut " : "");
		if (sig->offset != 0.0)
			fprintf(o, "        wire -= %.17g_f64;\n", sig->offset);
		if (sig->scaling != 1.0)
			fprintf(o, "        wire /= %.17g_f64;\n", sig->scaling);
		fputs("        let raw = wire.to_bits();\n", o);
	} else if (sig->scaling != 1.0 || sig->offset != 0.0) {
		fputs("        let mut wire = value as f64;\n", o);
		if (sig->offset != 0.0)
			fprintf(o, "        wire -= %.17g_f64;\n", sig->offset);
		if (sig->scaling != 1.0)
			fprintf(o, "        wire /= %.17g_f64;\n", sig->scaling);
		if (sig->is_signed)
			fputs("        let raw = (wire.round() as i64) as u64;\n", o);
		else
			fputs("        let raw = wire.round() as u64;\n", o);
	} else if (sig->is_signed) {
		fputs("        let raw = (value as i64) as u64;\n", o);
	} else {
		fputs("        let raw = value as u64;\n", o);
	}
	fprintf(o,
		"        dbcc_insert(&mut self.payload, %uu32, %uu32, %s, raw);\n"
		"        Ok(())\n"
		"    }\n\n",
		fixed_start(sig), sig->bit_length,
		sig->endianess == endianess_motorola_e ? "true" : "false");
	free(type);
	free(method);
}

static void emit_message(FILE *o, const dbc_t *dbc, can_msg_t *msg)
{
	char *type = message_type_name(msg);
	char *upper = rust_upper(msg->name);
	fprintf(o, "pub const CAN_ID_%s: u32 = %" PRIu64 "u32;\n",
		upper, (uint64_t)msg->id);
	fprintf(o, "pub const CAN_DLC_%s: u8 = %uu8;\n", upper, msg->dlc);
	if (msg->has_cycle_time)
		fprintf(o, "pub const CAN_CYCLETIME_%s: u32 = %uu32;\n",
			upper, msg->cycle_time);
	for (size_t i = 0; i < msg->signal_count; i++) {
		signal_t *sig = msg->sigs[i];
		char *signal_upper = rust_upper(sig->name);
		fprintf(o,
			"pub const %s_%s_MIN: f64 = %.17g_f64;\n"
			"pub const %s_%s_MAX: f64 = %.17g_f64;\n"
			"pub const %s_%s_SCALING: f64 = %.17g_f64;\n"
			"pub const %s_%s_OFFSET: f64 = %.17g_f64;\n",
			upper, signal_upper, sig->minimum,
			upper, signal_upper, sig->maximum,
			upper, signal_upper, sig->scaling,
			upper, signal_upper, sig->offset);
		free(signal_upper);
	}
	fprintf(o,
		"\n#[derive(Debug, Clone, Copy, Default, PartialEq, Eq)]\n"
		"pub struct %s { payload: u64 }\n\n"
		"impl %s {\n"
		"    pub const ID: u32 = CAN_ID_%s;\n"
		"    pub const DLC: u8 = CAN_DLC_%s;\n"
		"    pub const fn new() -> Self { Self { payload: 0 } }\n"
		"    pub const fn from_payload(payload: u64) -> Self { Self { payload } }\n"
		"    pub const fn payload(&self) -> u64 { self.payload }\n"
		"    pub fn set_payload(&mut self, payload: u64) { self.payload = payload; }\n"
		"    pub const fn frame(&self) -> CanFrame {\n"
		"        CanFrame { id: Self::ID, dlc: Self::DLC, payload: self.payload }\n"
		"    }\n\n",
		type, type, upper, upper);
	for (size_t i = 0; i < msg->signal_count; i++) {
		emit_signal_getter(o, dbc, msg, msg->sigs[i]);
		emit_signal_setter(o, dbc, msg, msg->sigs[i]);
	}
	fputs("}\n\n", o);

	for (size_t i = 0; i < msg->signal_count; i++) {
		signal_t *sig = msg->sigs[i];
		char *method = rust_snake(sig->name);
		char *api = signal_api_type(dbc, msg, sig);
		fprintf(o,
			"pub fn decode_0x%03" PRIx64 "_%s(message: &%s) -> Result<%s, DbccError> {\n"
			"    message.get_%s()\n"
			"}\n\n"
			"pub fn encode_0x%03" PRIx64 "_%s(message: &mut %s, value: %s) -> Result<(), DbccError> {\n"
			"    message.set_%s(value)\n"
			"}\n\n",
			(uint64_t)msg->id, method, type, api, method,
			(uint64_t)msg->id, method, type, api, method);
		free(api);
		free(method);
	}
	free(upper);
	free(type);
}

static void emit_database_api(FILE *o, const dbc_t *dbc)
{
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		char *upper = rust_upper(msg->name);
		fprintf(o, "pub static SIGNALS_%s: &[SignalInfo] = &[\n", upper);
		for (size_t j = 0; j < msg->signal_count; j++) {
			signal_t *sig = msg->sigs[j];
			fputs("    SignalInfo { name: ", o);
			emit_rust_string(o, sig->name);
			fprintf(o,
				", start_bit: %uu16, bit_length: %uu16, little_endian: %s, signed: %s, floating: %s, scaling: %.17g_f64, offset: %.17g_f64, minimum: %.17g_f64, maximum: %.17g_f64, units: ",
				sig->start_bit, sig->bit_length,
				sig->endianess == endianess_intel_e ? "true" : "false",
				sig->is_signed ? "true" : "false",
				sig->is_floating ? "true" : "false",
				sig->scaling, sig->offset, sig->minimum, sig->maximum);
			emit_rust_string(o, sig->units ? sig->units : "");
			fprintf(o,
				", multiplexor: %s, multiplexed: %s, switch_value: ",
				sig->is_multiplexor ? "true" : "false",
				sig->is_multiplexed ? "true" : "false");
			if (sig->is_multiplexed)
				fprintf(o, "Some(%uu64)", sig->switchval);
			else
				fputs("None", o);
			fputs(" },\n", o);
		}
		fputs("];\n\n", o);
		free(upper);
	}
	fputs("pub static ALL_MESSAGES: &[MessageInfo] = &[\n", o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		char *upper = rust_upper(msg->name);
		fprintf(o,
			"    MessageInfo { id: CAN_ID_%s, dlc: CAN_DLC_%s, name: ",
			upper, upper);
		emit_rust_string(o, msg->name);
		fprintf(o, ", is_extended: %s, cycle_time_ms: ",
			msg->is_extended ? "true" : "false");
		if (msg->has_cycle_time)
			fprintf(o, "Some(%uu32)", msg->cycle_time);
		else
			fputs("None", o);
		fprintf(o, ", signals: SIGNALS_%s },\n", upper);
		free(upper);
	}
	fputs(
		"];\n\n"
		"/// Return metadata for every CAN message in the DBC.\n"
		"pub const fn get_all_mess() -> &'static [MessageInfo] { ALL_MESSAGES }\n\n"
		"pub fn get_message(id: u32) -> Option<&'static MessageInfo> {\n"
		"    ALL_MESSAGES.iter().find(|message| message.id == id)\n"
		"}\n\n"
		"pub fn get_all_signals(id: u32) -> Option<&'static [SignalInfo]> {\n"
		"    get_message(id).map(|message| message.signals)\n"
		"}\n\n"
		"pub fn get_signal(id: u32, name: &str) -> Option<&'static SignalInfo> {\n"
		"    get_all_signals(id)?.iter().find(|signal| signal.name == name)\n"
		"}\n\n"
		"pub fn message_dlc(id: u32) -> Option<u8> { get_message(id).map(|m| m.dlc) }\n\n"
		"#[derive(Debug, Clone, Copy, PartialEq, Eq)]\n"
		"pub enum Message {\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		char *type = message_type_name(dbc->messages[i]);
		fprintf(o, "    %s(%s),\n", type, type);
		free(type);
	}
	fputs("}\n\nimpl Message {\n", o);
	fputs("    pub const fn id(&self) -> u32 {\n        match self {\n", o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		char *type = message_type_name(dbc->messages[i]);
		fprintf(o, "            Self::%s(_) => %s::ID,\n", type, type);
		free(type);
	}
	fputs("        }\n    }\n\n", o);
	fputs("    pub const fn dlc(&self) -> u8 {\n        match self {\n", o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		char *type = message_type_name(dbc->messages[i]);
		fprintf(o, "            Self::%s(_) => %s::DLC,\n", type, type);
		free(type);
	}
	fputs("        }\n    }\n\n", o);
	fputs("    pub const fn payload(&self) -> u64 {\n        match self {\n", o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		char *type = message_type_name(dbc->messages[i]);
		fprintf(o, "            Self::%s(message) => message.payload(),\n", type);
		free(type);
	}
	fputs(
		"        }\n"
		"    }\n\n"
		"    pub const fn frame(&self) -> CanFrame {\n"
		"        CanFrame { id: self.id(), dlc: self.dlc(), payload: self.payload() }\n"
		"    }\n\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		char *type = message_type_name(msg);
		char *method = rust_snake(msg->name);
		if (dbc->message_count == 1u) {
			fprintf(o,
				"    pub const fn get_%s(&self) -> Option<&%s> {\n"
				"        let Self::%s(message) = self; Some(message)\n"
				"    }\n\n"
				"    pub fn get_%s_mut(&mut self) -> Option<&mut %s> {\n"
				"        let Self::%s(message) = self; Some(message)\n"
				"    }\n\n",
				method, type, type, method, type, type);
		} else {
			fprintf(o,
				"    pub const fn get_%s(&self) -> Option<&%s> {\n"
				"        match self { Self::%s(message) => Some(message), _ => None }\n"
				"    }\n\n"
				"    pub fn get_%s_mut(&mut self) -> Option<&mut %s> {\n"
				"        match self { Self::%s(message) => Some(message), _ => None }\n"
				"    }\n\n",
				method, type, type, method, type, type);
		}
		free(method);
		free(type);
	}
	fputs("}\n\n", o);
	fputs(
		"pub fn decode_message(id: u32, payload: u64, dlc: u8) -> Result<Message, DbccError> {\n"
		"    match id {\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		char *type = message_type_name(msg);
		char *upper = rust_upper(msg->name);
		fprintf(o,
			"        CAN_ID_%s => {\n"
			"            if dlc != CAN_DLC_%s {\n"
			"                return Err(DbccError::InvalidDlc { id, expected: CAN_DLC_%s, actual: dlc });\n"
			"            }\n"
			"            Ok(Message::%s(%s::from_payload(payload)))\n"
			"        }\n",
			upper, upper, upper, type, type);
		free(upper);
		free(type);
	}
	fputs(
		"        _ => Err(DbccError::UnknownMessage { id }),\n"
		"    }\n"
		"}\n\n",
		o);
}

/*
 * SDO_DPS generation is kept in this file so `-R` emits one module that can be
 * copied directly into firmware or the GUI. The validator intentionally
 * matches 2sdodps.c.
 */
static signal_t *find_signal(can_msg_t *msg, const char *name)
{
	for (size_t i = 0; i < msg->signal_count; i++)
		if (!strcmp(msg->sigs[i]->name, name))
			return msg->sigs[i];
	return NULL;
}

static signal_t *find_mux_value(can_msg_t *msg, unsigned value)
{
	for (size_t i = 0; i < msg->signal_count; i++)
		if (msg->sigs[i]->is_multiplexed &&
		    msg->sigs[i]->switchval == value)
			return msg->sigs[i];
	return NULL;
}

static bool valid_sdo_message(can_msg_t *msg)
{
	if (!msg->name || strncmp(msg->name, "SDO", 3u))
		return false;
	signal_t *opcode = find_signal(msg, "opcode");
	signal_t *var_id = find_signal(msg, "var_id");
	signal_t *flags = find_signal(msg, "flags");
	signal_t *dbc_hash = find_signal(msg, "dbc_hash");
	if (!opcode || !var_id || !flags || !dbc_hash || !var_id->is_multiplexor ||
	    !opcode->val_list || !opcode->val_list->is_val_table_reference ||
	    !opcode->val_list->val_table_name ||
	    strcmp(opcode->val_list->val_table_name, "OPCODES") ||
	    !var_id->val_list || !var_id->val_list->val_list_item_count)
		return false;
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_mux_value(msg, item->value);
		if (!sig || strcmp(sig->name, item->name) ||
		    sig->start_bit != 24u || sig->bit_length == 0u)
			return false;
	}
	return true;
}

static bool has_valid_sdo(const dbc_t *dbc)
{
	for (size_t i = 0; i < dbc->message_count; i++)
		if (valid_sdo_message(dbc->messages[i]))
			return true;
	return false;
}

static char *sdo_board_type(can_msg_t *msg)
{
	return rust_pascal(msg->name + 3u);
}

static char *sdo_board_snake(can_msg_t *msg)
{
	return rust_snake(msg->name + 3u);
}

static char *sdo_api_type(const signal_t *sig)
{
	if (sig->is_floating)
		return duplicate(sig->bit_length == 64u ? "f64" : "f32");
	if (sig->scaling != 1.0 || sig->offset != 0.0)
		return duplicate(sig->bit_length <= 32u ? "f32" : "f64");
	return duplicate(sig->is_signed ?
		rust_signed_type(sig->bit_length) :
		rust_unsigned_type(sig->bit_length));
}

static void emit_sdo_common(FILE *o)
{
	fputs(
		"#[repr(u8)]\n"
		"#[derive(Debug, Clone, Copy, PartialEq, Eq)]\n"
		"pub enum SdoOpcode {\n"
		"    GetReq = 1, SetReq = 2, GetAllReq = 3, Response = 128,\n"
		"    ErrOutOfRange = 253, ErrWriteReadOnly = 254, Error = 255,\n"
		"}\n\n"
		"#[derive(Debug, Clone, Copy, PartialEq, Eq)]\n"
		"pub enum SdoStatus { Ok, UnknownVariable, ReadOnly, NoValue, OutOfRange, TxMissing, BadFrame }\n\n"
		"pub type SdoTxCallback = fn(u32, u8, u64) -> bool;\n"
		"pub type SdoValueHook = fn(u32, u16);\n\n"
		"pub fn sdo_frame(id: u32, opcode: SdoOpcode, var_id: u16, raw: u64, bits: u32) -> CanFrame {\n"
		"    let mut payload = 0u64;\n"
		"    dbcc_insert(&mut payload, 0, 8, false, opcode as u64);\n"
		"    dbcc_insert(&mut payload, 8, 10, false, var_id as u64);\n"
		"    dbcc_insert(&mut payload, 24, bits, false, raw);\n"
		"    CanFrame { id, dlc: 7, payload }\n"
		"}\n\n",
		o);
}

static void emit_sdo_board_enum(FILE *o, can_msg_t *msg)
{
	char *board = sdo_board_type(msg);
	signal_t *var_id = find_signal(msg, "var_id");
	fprintf(o,
		"#[repr(u16)]\n"
		"#[derive(Debug, Clone, Copy, PartialEq, Eq)]\n"
		"pub enum %sVar {\n",
		board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		fprintf(o, "    %s = %uu16,\n", variant, item->value);
		free(variant);
	}
	fputs("}\n\n", o);
	fprintf(o, "impl %sVar {\n", board);
	fputs("    pub const ALL: &'static [Self] = &[\n", o);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		char *variant = rust_pascal(var_id->val_list->val_list_items[i]->name);
		fprintf(o, "        Self::%s,\n", variant);
		free(variant);
	}
	fputs("    ];\n", o);
	fputs("    pub const fn bit_length(self) -> u32 {\n        match self {\n", o);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_mux_value(msg, item->value);
		char *variant = rust_pascal(item->name);
		fprintf(o, "            Self::%s => %uu32,\n", variant, sig->bit_length);
		free(variant);
	}
	fputs("        }\n    }\n", o);
	fputs("    pub const fn name(self) -> &'static str {\n        match self {\n", o);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		fprintf(o, "            Self::%s => ", variant);
		emit_rust_string(o, item->name);
		fputs(",\n", o);
		free(variant);
	}
	fputs("        }\n    }\n}\n\n", o);
	fprintf(o,
		"impl core::convert::TryFrom<u16> for %sVar {\n"
		"    type Error = u16;\n"
		"    fn try_from(value: u16) -> Result<Self, Self::Error> {\n"
		"        match value {\n",
		board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		fprintf(o, "            %uu16 => Ok(Self::%s),\n", item->value, variant);
		free(variant);
	}
	fputs("            other => Err(other),\n        }\n    }\n}\n\n", o);
	free(board);
}

static void emit_sdo_raw_helpers(FILE *o, can_msg_t *msg)
{
	char *board = sdo_board_snake(msg);
	signal_t *var_id = find_signal(msg, "var_id");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_mux_value(msg, item->value);
		char *name = rust_snake(item->name);
		char *api = sdo_api_type(sig);
		fprintf(o, "fn sdo_decode_%s_%s(payload: u64) -> %s {\n",
			board, name, api);
		fprintf(o, "    let raw = dbcc_extract(payload, 24, %u, false);\n",
			sig->bit_length);
		if (sig->is_floating && sig->bit_length == 32u) {
			fputs("    let value = f32::from_bits(raw as u32);\n", o);
		} else if (sig->is_floating && sig->bit_length == 64u) {
			fputs("    let value = f64::from_bits(raw);\n", o);
		} else if (sig->is_signed) {
			if (sig->bit_length < 64u)
				fprintf(o,
					"    let value = if raw & (1u64 << %u) != 0 { (raw | !dbcc_mask(%u)) as i64 } else { raw as i64 };\n",
					sig->bit_length - 1u, sig->bit_length);
			else
				fputs("    let value = raw as i64;\n", o);
			fprintf(o, "    let value = value as %s;\n", api);
		} else {
			fprintf(o, "    let value = raw as %s;\n", api);
		}
		if (sig->scaling != 1.0)
			fprintf(o, "    let value = value * %.17g_%s;\n", sig->scaling, api);
		if (sig->offset != 0.0)
			fprintf(o, "    let value = value + %.17g_%s;\n", sig->offset, api);
		fputs("    value\n}\n\n", o);

		fprintf(o, "fn sdo_encode_%s_%s(value: %s) -> u64 {\n",
			board, name, api);
		if (sig->is_floating) {
			fprintf(o, "    let %swire = value;\n",
				(sig->offset != 0.0 || sig->scaling != 1.0) ? "mut " : "");
			if (sig->offset != 0.0)
				fprintf(o, "    wire -= %.17g_%s;\n", sig->offset, api);
			if (sig->scaling != 1.0)
				fprintf(o, "    wire /= %.17g_%s;\n", sig->scaling, api);
			if (sig->bit_length == 32u)
				fputs("    wire.to_bits() as u64\n", o);
			else
				fputs("    wire.to_bits()\n", o);
		} else if (sig->scaling != 1.0 || sig->offset != 0.0) {
			fputs("    let mut wire = value as f64;\n", o);
			if (sig->offset != 0.0)
				fprintf(o, "    wire -= %.17g_f64;\n", sig->offset);
			if (sig->scaling != 1.0)
				fprintf(o, "    wire /= %.17g_f64;\n", sig->scaling);
			if (sig->is_signed)
				fputs("    (wire.round() as i64) as u64\n", o);
			else
				fputs("    wire.round() as u64\n", o);
		} else if (sig->is_signed) {
			fputs("    (value as i64) as u64\n", o);
		} else {
			fputs("    value as u64\n", o);
		}
		fputs("}\n\n", o);
		free(api);
		free(name);
	}
	free(board);
}

static void emit_sdo_master_state(FILE *o, can_msg_t *msg)
{
	char *board = sdo_board_type(msg);
	char *board_snake = sdo_board_snake(msg);
	signal_t *var_id = find_signal(msg, "var_id");
	fprintf(o,
		"#[derive(Debug, Clone, Copy, Default)]\n"
		"struct %sSdoState {\n"
		"    expected_hash: u32,\n"
		"    has_expected_hash: bool,\n"
		"    hash_verified: bool,\n",
		board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_mux_value(msg, item->value);
		char *name = rust_snake(item->name);
		char *api = sdo_api_type(sig);
		fprintf(o, "    %s: %s,\n    has_new_%s: bool,\n", name, api, name);
		free(api);
		free(name);
	}
	fputs("}\n\n", o);
	(void)board_snake;
	free(board_snake);
	free(board);
}

static void emit_sdo_master_board_methods(FILE *o, can_msg_t *msg)
{
	char *board = sdo_board_type(msg);
	char *board_snake = sdo_board_snake(msg);
	char *msg_upper = rust_upper(msg->name);
	signal_t *var_id = find_signal(msg, "var_id");
	fprintf(o,
		"    pub fn set_expected_%s_hash(&mut self, expected: u32) {\n"
		"        self.%s.expected_hash = expected;\n"
		"        self.%s.has_expected_hash = true;\n"
		"        self.%s.hash_verified = false;\n"
		"    }\n\n"
		"    pub const fn %s_hash_verified(&self) -> bool { self.%s.hash_verified }\n\n"
		"    pub fn request_%s(&mut self, var: %sVar) -> bool {\n"
		"        if var as u16 != 0 && !self.%s.hash_verified { return false; }\n"
		"        self.send(CAN_ID_%s, SdoOpcode::GetReq, var as u16, 0, var.bit_length())\n"
		"    }\n\n"
		"    /// Request every variable from this SDO slave.\n"
		"    pub fn request_all_%s(&mut self) -> bool {\n"
		"        self.send(CAN_ID_%s, SdoOpcode::GetAllReq, 0, 0, 0)\n"
		"    }\n\n"
		"    /// Compatibility alias for request_all_%s.\n"
		"    pub fn get_all_%s(&mut self) -> bool { self.request_all_%s() }\n\n"
		"    pub const fn has_%s_value(&self, var: %sVar) -> bool {\n"
		"        match var {\n",
		board_snake, board_snake, board_snake, board_snake,
		board_snake, board_snake,
		board_snake, board, board_snake, msg_upper,
		board_snake, msg_upper,
		board_snake, board_snake, board_snake,
		board_snake, board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		char *name = rust_snake(item->name);
		fprintf(o, "            %sVar::%s => self.%s.has_new_%s,\n",
			board, variant, board_snake, name);
		free(name);
		free(variant);
	}
	fputs("        }\n    }\n\n", o);

	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_mux_value(msg, item->value);
		char *name = rust_snake(item->name);
		char *api = sdo_api_type(sig);
		fprintf(o,
			"    pub fn set_%s_%s(&mut self, value: %s) -> bool {\n"
			"        self.send(CAN_ID_%s, SdoOpcode::SetReq, %uu16, sdo_encode_%s_%s(value), %uu32)\n"
			"    }\n\n"
			"    /// Non-destructive getter for the latest received value.\n"
			"    pub fn get_%s_%s(&self) -> Option<%s> {\n"
			"        if %s && !self.%s.hash_verified { return None; }\n"
			"        self.%s.has_new_%s.then_some(self.%s.%s)\n"
			"    }\n\n"
			"    pub fn take_%s_%s(&mut self) -> Option<%s> {\n"
			"        let value = self.get_%s_%s()?;\n"
			"        self.%s.has_new_%s = false;\n"
			"        Some(value)\n"
			"    }\n\n",
			board_snake, name, api, msg_upper, item->value,
			board_snake, name, sig->bit_length,
			board_snake, name, api,
			item->value == 0u ? "false" : "true", board_snake,
			board_snake, name, board_snake, name,
			board_snake, name, api, board_snake, name,
			board_snake, name);
		free(api);
		free(name);
	}

	fprintf(o,
		"    fn process_%s_response(&mut self, id: u32, payload: u64) -> bool {\n"
		"        let raw_var = dbcc_extract(payload, 8, 10, false) as u16;\n"
		"        let Ok(var) = <%sVar as core::convert::TryFrom<u16>>::try_from(raw_var) else { return false; };\n"
		"        match var {\n",
		board_snake, board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		char *name = rust_snake(item->name);
		fprintf(o,
			"            %sVar::%s => {\n"
			"                self.%s.%s = sdo_decode_%s_%s(payload);\n"
			"                self.%s.has_new_%s = true;\n",
			board, variant, board_snake, name, board_snake, name,
			board_snake, name);
		if (item->value == 0u)
			fprintf(o,
				"                self.%s.hash_verified = self.%s.has_expected_hash && self.%s.%s == self.%s.expected_hash;\n",
				board_snake, board_snake, board_snake, name, board_snake);
		fputs(
			"                if let Some(hook) = self.value_hook { hook(id, raw_var); }\n"
			"                true\n"
			"            }\n",
			o);
		free(name);
		free(variant);
	}
	fputs("        }\n    }\n\n", o);
	free(msg_upper);
	free(board_snake);
	free(board);
}

static void emit_sdo_master(FILE *o, const dbc_t *dbc)
{
	for (size_t i = 0; i < dbc->message_count; i++)
		if (valid_sdo_message(dbc->messages[i]))
			emit_sdo_master_state(o, dbc->messages[i]);

	fputs(
		"#[derive(Debug, Clone, Copy)]\n"
		"pub struct SdoMaster {\n"
		"    tx: Option<SdoTxCallback>,\n"
		"    value_hook: Option<SdoValueHook>,\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		if (!valid_sdo_message(dbc->messages[i]))
			continue;
		char *board = sdo_board_type(dbc->messages[i]);
		char *snake = sdo_board_snake(dbc->messages[i]);
		fprintf(o, "    %s: %sSdoState,\n", snake, board);
		free(snake);
		free(board);
	}
	fputs("}\n\n", o);
	fputs(
		"impl Default for SdoMaster { fn default() -> Self { Self::new() } }\n\n"
		"impl SdoMaster {\n"
		"    pub const fn new() -> Self {\n"
		"        Self { tx: None, value_hook: None,\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		if (!valid_sdo_message(dbc->messages[i]))
			continue;
		char *board = sdo_board_type(dbc->messages[i]);
		char *snake = sdo_board_snake(dbc->messages[i]);
		fprintf(o, "            %s: %sSdoState {\n", snake, board);
		fputs(
			"                expected_hash: 0, has_expected_hash: false, hash_verified: false,\n",
			o);
		signal_t *var_id = find_signal(dbc->messages[i], "var_id");
		for (size_t j = 0; j < var_id->val_list->val_list_item_count; j++) {
			char *name = rust_snake(var_id->val_list->val_list_items[j]->name);
			fprintf(o, "                %s: 0 as _, has_new_%s: false,\n", name, name);
			free(name);
		}
		fputs("            },\n", o);
		free(snake);
		free(board);
	}
	fputs(
		"        }\n"
		"    }\n\n"
		"    pub fn set_tx_callback(&mut self, callback: SdoTxCallback) { self.tx = Some(callback); }\n"
		"    pub fn clear_tx_callback(&mut self) { self.tx = None; }\n"
		"    pub fn set_value_hook(&mut self, hook: SdoValueHook) { self.value_hook = Some(hook); }\n"
		"    pub fn clear_value_hook(&mut self) { self.value_hook = None; }\n\n"
		"    fn send(&mut self, id: u32, opcode: SdoOpcode, var_id: u16, raw: u64, bits: u32) -> bool {\n"
		"        let Some(tx) = self.tx else { return false; };\n"
		"        let frame = sdo_frame(id, opcode, var_id, raw, bits);\n"
		"        tx(frame.id, frame.dlc, frame.payload)\n"
		"    }\n\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++)
		if (valid_sdo_message(dbc->messages[i]))
			emit_sdo_master_board_methods(o, dbc->messages[i]);

	fputs(
		"    /// Send GET_ALL_REQ to every SDO board in the DBC.\n"
		"    pub fn get_all_mess(&mut self) -> bool {\n"
		"        let mut sent = true;\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		if (!valid_sdo_message(dbc->messages[i]))
			continue;
		char *snake = sdo_board_snake(dbc->messages[i]);
		fprintf(o, "        sent = self.request_all_%s() && sent;\n", snake);
		free(snake);
	}
	fputs("        sent\n    }\n\n", o);
	fputs(
		"    pub fn process(&mut self, id: u32, payload: u64) -> bool {\n"
		"        if dbcc_extract(payload, 0, 8, false) != SdoOpcode::Response as u64 { return false; }\n"
		"        match id {\n",
		o);
	for (size_t i = 0; i < dbc->message_count; i++) {
		if (!valid_sdo_message(dbc->messages[i]))
			continue;
		char *upper = rust_upper(dbc->messages[i]->name);
		char *snake = sdo_board_snake(dbc->messages[i]);
		fprintf(o, "            CAN_ID_%s => self.process_%s_response(id, payload),\n",
			upper, snake);
		free(snake);
		free(upper);
	}
	fputs("            _ => false,\n        }\n    }\n}\n\n", o);
}

static void emit_sdo_slave_fields(FILE *o, can_msg_t *msg)
{
	signal_t *var_id = find_signal(msg, "var_id");
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_mux_value(msg, item->value);
		char *name = rust_snake(item->name);
		char *api = sdo_api_type(sig);
		fprintf(o,
			"    %s_reader: Option<fn() -> Option<%s>>,\n"
			"    %s_writer: Option<fn(%s) -> bool>,\n",
			name, api, name, api);
		free(api);
		free(name);
	}
}

static void emit_sdo_slave_board(FILE *o, can_msg_t *msg)
{
	char *board = sdo_board_type(msg);
	char *snake = sdo_board_snake(msg);
	char *upper = rust_upper(msg->name);
	signal_t *var_id = find_signal(msg, "var_id");
	fprintf(o,
		"pub struct %sSdoSlave {\n"
		"    tx: Option<SdoTxCallback>,\n",
		board);
	emit_sdo_slave_fields(o, msg);
	fputs("}\n\n", o);
	fprintf(o, "impl Default for %sSdoSlave { fn default() -> Self { Self::new() } }\n\n", board);
	fprintf(o,
		"impl %sSdoSlave {\n"
		"    pub const fn new() -> Self {\n"
		"        Self { tx: None,\n",
		board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		char *name = rust_snake(var_id->val_list->val_list_items[i]->name);
		fprintf(o, "            %s_reader: None, %s_writer: None,\n", name, name);
		free(name);
	}
	fputs(
		"        }\n"
		"    }\n\n"
		"    pub fn set_tx_callback(&mut self, callback: SdoTxCallback) { self.tx = Some(callback); }\n"
		"    pub fn clear_tx_callback(&mut self) { self.tx = None; }\n\n",
		o);

	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		signal_t *sig = find_mux_value(msg, item->value);
		char *name = rust_snake(item->name);
		char *api = sdo_api_type(sig);
		fprintf(o,
			"    pub fn set_%s_reader(&mut self, callback: fn() -> Option<%s>) { self.%s_reader = Some(callback); }\n"
			"    pub fn clear_%s_reader(&mut self) { self.%s_reader = None; }\n"
			"    pub fn set_%s_writer(&mut self, callback: fn(%s) -> bool) { self.%s_writer = Some(callback); }\n"
			"    pub fn clear_%s_writer(&mut self) { self.%s_writer = None; }\n\n"
			"    pub fn get_%s(&self) -> Result<%s, SdoStatus> {\n"
			"        self.%s_reader.and_then(|reader| reader()).ok_or(SdoStatus::NoValue)\n"
			"    }\n\n"
			"    pub fn set_%s(&mut self, value: %s) -> SdoStatus {\n",
			name, api, name, name, name,
			name, api, name, name, name,
			name, api, name, name, api);
		if (sig->minimum != sig->maximum)
			fprintf(o,
				"        if (value as f64) < %.17g_f64 || (value as f64) > %.17g_f64 { return SdoStatus::OutOfRange; }\n",
				sig->minimum, sig->maximum);
		fprintf(o,
			"        match self.%s_writer { Some(writer) if writer(value) => SdoStatus::Ok, Some(_) => SdoStatus::NoValue, None => SdoStatus::ReadOnly }\n"
			"    }\n\n",
			name);
		free(api);
		free(name);
	}

	/*
	 * SdoStatus::OutOfRange is emitted below by replacing the common enum;
	 * keeping the wire opcode distinction makes GET/SET diagnostics useful.
	 */
	fprintf(o,
		"    fn send_response(&self, opcode: SdoOpcode, var: %sVar, raw: u64) -> bool {\n"
		"        let Some(tx) = self.tx else { return false; };\n"
		"        let frame = sdo_frame(CAN_ID_%s, opcode, var as u16, raw, var.bit_length());\n"
		"        tx(frame.id, frame.dlc, frame.payload)\n"
		"    }\n\n"
		"    fn process_get(&self, var: %sVar) -> bool {\n"
		"        match var {\n",
		board, upper, board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		char *name = rust_snake(item->name);
		fprintf(o,
			"            %sVar::%s => match self.get_%s() {\n"
			"                Ok(value) => self.send_response(SdoOpcode::Response, var, sdo_encode_%s_%s(value)),\n"
			"                Err(_) => self.send_response(SdoOpcode::Error, var, 0),\n"
			"            },\n",
			board, variant, name, snake, name);
		free(name);
		free(variant);
	}
	fputs("        }\n    }\n\n", o);

	fprintf(o,
		"    fn process_set(&mut self, var: %sVar, payload: u64) -> bool {\n"
		"        match var {\n",
		board);
	for (size_t i = 0; i < var_id->val_list->val_list_item_count; i++) {
		val_list_item_t *item = var_id->val_list->val_list_items[i];
		char *variant = rust_pascal(item->name);
		char *name = rust_snake(item->name);
		fprintf(o,
			"            %sVar::%s => {\n"
			"                let value = sdo_decode_%s_%s(payload);\n"
			"                let status = self.set_%s(value);\n"
			"                let opcode = match status { SdoStatus::Ok => SdoOpcode::Response, SdoStatus::ReadOnly => SdoOpcode::ErrWriteReadOnly, SdoStatus::OutOfRange => SdoOpcode::ErrOutOfRange, _ => SdoOpcode::Error };\n"
			"                let stored = self.get_%s().unwrap_or(value);\n"
			"                self.send_response(opcode, var, if status == SdoStatus::Ok { sdo_encode_%s_%s(stored) } else { 0 })\n"
			"            }\n",
			board, variant, snake, name, name, name, snake, name);
		free(name);
		free(variant);
	}
	fputs("        }\n    }\n\n", o);

	fprintf(o,
		"    pub fn process(&mut self, id: u32, payload: u64) -> bool {\n"
		"        if id != CAN_ID_%s { return false; }\n"
		"        let opcode = dbcc_extract(payload, 0, 8, false);\n"
		"        if opcode == SdoOpcode::GetAllReq as u64 {\n"
		"            let mut sent = true;\n"
		"            for &var in %sVar::ALL { sent = self.process_get(var) && sent; }\n"
		"            return sent;\n"
		"        }\n"
		"        let raw_var = dbcc_extract(payload, 8, 10, false) as u16;\n"
		"        let Ok(var) = <%sVar as core::convert::TryFrom<u16>>::try_from(raw_var) else { return false; };\n"
		"        if opcode == SdoOpcode::GetReq as u64 { self.process_get(var) }\n"
		"        else if opcode == SdoOpcode::SetReq as u64 { self.process_set(var, payload) }\n"
		"        else { false }\n"
		"    }\n\n"
		"    pub fn notify(&self, var: %sVar) -> bool { self.process_get(var) }\n"
		"}\n\n",
		upper, board, board, board);
	free(upper);
	free(snake);
	free(board);
}

static void emit_sdo_slaves(FILE *o, const dbc_t *dbc)
{
	for (size_t i = 0; i < dbc->message_count; i++)
		if (valid_sdo_message(dbc->messages[i]))
			emit_sdo_slave_board(o, dbc->messages[i]);
}

static void emit_sdo(FILE *o, const dbc_t *dbc)
{
	if (!has_valid_sdo(dbc))
		return;
	emit_sdo_common(o);
	for (size_t i = 0; i < dbc->message_count; i++)
		if (valid_sdo_message(dbc->messages[i])) {
			emit_sdo_board_enum(o, dbc->messages[i]);
			emit_sdo_raw_helpers(o, dbc->messages[i]);
		}
	emit_sdo_master(o, dbc);
	emit_sdo_slaves(o, dbc);
}

static void apply_sigval_overrides(dbc_t *dbc, const char *dbc_file)
{
	FILE *input = fopen(dbc_file, "rb");
	if (!input)
		error("error opening '%s': %s", dbc_file, emsg());
	char line[1024];
	while (fgets(line, sizeof(line), input)) {
		unsigned long id = 0;
		unsigned typed = 0;
		char signal_name[MAX_NAME_LENGTH] = {0};
		if (sscanf(line, " SIG_VALTYPE_ %lu %511s : %u ;",
		    &id, signal_name, &typed) != 3)
			continue;
		for (size_t i = 0; i < dbc->message_count; i++) {
			can_msg_t *msg = dbc->messages[i];
			if (msg->id != id)
				continue;
			signal_t *sig = find_signal(msg, signal_name);
			if (sig) {
				sig->sigval = typed;
				sig->is_floating = typed == 1u || typed == 2u;
			}
			break;
		}
	}
	fclose(input);
}

int dbc2rust(dbc_t *dbc, FILE *output, const char *name, const char *dbc_file)
{
	assert(dbc);
	assert(output);
	assert(name);
	assert(dbc_file);
	apply_sigval_overrides(dbc, dbc_file);
	emit_prelude(output, dbc, name);
	emit_enums(output, dbc);
	for (size_t i = 0; i < dbc->message_count; i++)
		emit_message(output, dbc, dbc->messages[i]);
	emit_database_api(output, dbc);
	emit_sdo(output, dbc);
	return ferror(output) ? -1 : 0;
}
