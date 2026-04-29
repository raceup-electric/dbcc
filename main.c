/**@file main.c
 * @brief dbcc - produce serialization and deserialization code for CAN DBC files
 * @copyright Richard James Howe, SUBLEQ LTD (2025)
 * @license MIT */
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdarg.h>
#include "mpc.h"
#include "util.h"
#include "can.h"
#include "parse.h"
#include "2c.h"
#include "2xml.h"
#include "2csv.h"
#include "2bsm.h"
#include "2json.h"
#include "2ros.h"
#include "options.h"

#ifndef NELEMS
#define NELEMS(X) (sizeof(X) / sizeof((X)[0]))
#endif

typedef enum {
	CONVERT_TO_C,
	CONVERT_TO_XML,
	CONVERT_TO_CSV,
	CONVERT_TO_BSM,
	CONVERT_TO_JSON,
	CONVERT_TO_ROS,
} conversion_type_e;

static bool string_in_list(char **items, size_t count, const char *value)
{
	assert(value);
	for (size_t i = 0; i < count; i++) {
		if (!strcmp(items[i], value))
			return true;
	}
	return false;
}

static void add_unique_string(char ***items, size_t *count, const char *value)
{
	assert(items);
	assert(count);
	assert(value);
	if (string_in_list(*items, *count, value))
		return;
	*items = reallocator(*items, sizeof(**items) * (*count + 1));
	(*items)[(*count)++] = (char *)value;
}

static size_t dbc_signal_count(const dbc_t *dbc)
{
	assert(dbc);
	size_t count = 0;
	for (size_t i = 0; i < dbc->message_count; i++)
		count += dbc->messages[i]->signal_count;
	return count;
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
	assert(s);
	return hash32_update_bytes(hash, s, strlen(s));
}

static uint32_t hash32_update_format(uint32_t hash, const char *fmt, ...)
{
	assert(fmt);
	va_list ap;
	va_start(ap, fmt);
	va_list ap_copy;
	va_copy(ap_copy, ap);
	int needed = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);
	if (needed < 0)
		error("vsnprintf failed while computing node hash");
	char *buf = allocate((size_t)needed + 1);
	vsnprintf(buf, (size_t)needed + 1, fmt, ap_copy);
	va_end(ap_copy);
	hash = hash32_update_bytes(hash, buf, (size_t)needed);
	free(buf);
	return hash;
}

static bool node_matches_signal(const signal_t *sig, const char *node)
{
	assert(sig);
	assert(node);
	for (size_t i = 0; i < sig->ecu_count; i++) {
		if (!strcmp(sig->ecus[i], node))
			return true;
	}
	return false;
}

static bool node_matches_message_tx(const can_msg_t *msg, const char *node)
{
	assert(msg);
	assert(node);
	for (size_t i = 0; i < msg->ecu_count; i++) {
		if (!strcmp(msg->ecus[i], node))
			return true;
	}
	return false;
}

static bool node_matches_message(const can_msg_t *msg, const char *node)
{
	assert(msg);
	assert(node);
	if (node_matches_message_tx(msg, node))
		return true;
	for (size_t i = 0; i < msg->signal_count; i++) {
		if (node_matches_signal(msg->sigs[i], node))
			return true;
	}
	return false;
}

static uint32_t hash_val_list(uint32_t hash, const val_list_t *val_list)
{
	if (!val_list)
		return hash32_update_cstr(hash, "VAL:none\n");

	hash = hash32_update_format(hash, "VAL:%s:%u:%d:",
		val_list->name ? val_list->name : "",
		val_list->id,
		(int)val_list->is_val_table_reference);
	if (val_list->val_table_name)
		hash = hash32_update_format(hash, "table=%s:", val_list->val_table_name);
	for (size_t i = 0; i < val_list->val_list_item_count; i++) {
		val_list_item_t *item = val_list->val_list_items[i];
		hash = hash32_update_format(hash, "%u=%s;", item->value, item->name);
	}
	return hash32_update_cstr(hash, "\n");
}

static uint32_t hash_mul_ranges(uint32_t hash, const signal_t *sig)
{
	assert(sig);
	hash = hash32_update_format(hash, "MUX:%d:%d:%u:%zu:",
		(int)sig->is_multiplexor,
		(int)sig->is_multiplexed,
		sig->switchval,
		sig->mul_num);
	if (sig->mux_parent)
		hash = hash32_update_format(hash, "parent=%s:", sig->mux_parent->name);
	for (size_t i = 0; i < sig->mul_num; i++) {
		mul_val_list_t *mv = sig->mux_vals[i];
		hash = hash32_update_format(hash, "%s:", sig->muxed[i]->name);
		if (mv) {
			hash = hash32_update_format(hash, "%s:%s:",
				mv->multiplexed ? mv->multiplexed : "",
				mv->multiplexor ? mv->multiplexor : "");
			for (size_t j = 0; j < mv->range_num; j++) {
				hash = hash32_update_format(hash, "%u-%u,",
					mv->ranges[j]->min_value, mv->ranges[j]->max_value);
			}
		}
		hash = hash32_update_cstr(hash, ";");
	}
	return hash32_update_cstr(hash, "\n");
}

static uint32_t hash_signal(uint32_t hash, const signal_t *sig)
{
	assert(sig);
	hash = hash32_update_format(hash,
		"SIG:%s:%u:%u:%d:%d:%d:%u:%.17g:%.17g:%.17g:%.17g:%s:",
		sig->name,
		sig->start_bit,
		sig->bit_length,
		(int)sig->endianess,
		(int)sig->is_signed,
		(int)sig->is_floating,
		sig->sigval,
		sig->scaling,
		sig->offset,
		sig->minimum,
		sig->maximum,
		sig->units ? sig->units : "");
	for (size_t i = 0; i < sig->ecu_count; i++)
		hash = hash32_update_format(hash, "%s,", sig->ecus[i]);
	hash = hash32_update_cstr(hash, "\n");
	hash = hash_mul_ranges(hash, sig);
	hash = hash_val_list(hash, sig->val_list);
	hash = hash32_update_format(hash, "COMMENT:%s\n", sig->comment ? sig->comment : "");
	return hash;
}

static uint32_t hash_message(uint32_t hash, const can_msg_t *msg)
{
	assert(msg);
	hash = hash32_update_format(hash, "MSG:%s:%lu:%u:%d:",
		msg->name, msg->id, msg->dlc, (int)msg->is_extended);
	for (size_t i = 0; i < msg->ecu_count; i++)
		hash = hash32_update_format(hash, "%s,", msg->ecus[i]);
	hash = hash32_update_cstr(hash, "\n");
	hash = hash32_update_format(hash, "COMMENT:%s\n", msg->comment ? msg->comment : "");
	for (size_t i = 0; i < msg->signal_count; i++)
		hash = hash_signal(hash, msg->sigs[i]);
	return hash;
}

static uint32_t dbc_node_hash32(const dbc_t *dbc, const char *node)
{
	assert(dbc);
	assert(node);
	uint32_t hash = 2166136261u;
	hash = hash32_update_format(hash, "NODE:%s\n", node);
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		if (node_matches_message(msg, node))
			hash = hash_message(hash, msg);
	}
	return hash;
}

static uint32_t dbc_hash32(const dbc_t *dbc)
{
	assert(dbc);
	uint32_t hash = 2166136261u;
	hash = hash32_update_cstr(hash, "DBC\n");
	for (size_t i = 0; i < dbc->message_count; i++)
		hash = hash_message(hash, dbc->messages[i]);
	return hash;
}

static void print_dbc_summary_block(const dbc_t *dbc, const char *file_name)
{
	assert(dbc);
	assert(file_name);
	char **nodes = NULL;
	size_t count = 0;

	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		for (size_t j = 0; j < msg->ecu_count; j++)
			add_unique_string(&nodes, &count, msg->ecus[j]);
		for (size_t j = 0; j < msg->signal_count; j++) {
			signal_t *sig = msg->sigs[j];
			for (size_t k = 0; k < sig->ecu_count; k++)
				add_unique_string(&nodes, &count, sig->ecus[k]);
		}
	}

	fprintf(stdout, "##########\n");
	fprintf(stdout, "%s\n", file_name);
	fprintf(stdout, "%-24s%zu\n", "nodes", count);
	fprintf(stdout, "%-24s%zu\n", "messages", dbc->message_count);
	fprintf(stdout, "%-24s%zu\n", "signals", dbc_signal_count(dbc));
	fprintf(stdout, "%-24s0x%08" PRIx32 "\n", "hash DBC", dbc_hash32(dbc));
	for (size_t i = 0; i < count; i++) {
		char label[256] = {0};
		snprintf(label, sizeof(label), "hash %s", nodes[i]);
		fprintf(stdout, "%-24s0x%08" PRIx32 "\n",
			label, dbc_node_hash32(dbc, nodes[i]));
	}
	fprintf(stdout, "\n");

	free(nodes);
}

static void usage(const char *arg0)
{
	assert(arg0);
	fprintf(stderr, "%s: [-] [-hvjgtxpkuDC] [-o dir] file*\n", arg0);
}

static void help(void)
{
	static const char *msg = "\
dbcc - compile CAN DBC files to C code\n\
Author: Richard James Howe\n\
License: MIT\n\
Email: hello.operator.co.uk@gmail.com\n\
Repo: https://github.com/howerj/dbcc\n\
\n\
Please consider donating to the project, if you require paid support\n\
then please email \"hello.operator.co.uk@gmail.com\" to raise an inquiry.\n\
\n\
Options:\n\
\t-      stop processing command line arguments\n\
\t-h     print out a help message and exit\n\
\t-v     make the program more verbose\n\
\t-g     print out the grammar used to parse the DBC files\n\
\t-t     add timestamps to the generated files\n\
\t-x     convert output to XML instead of the default C code\n\
\t-C     convert output to CSV instead of the default C code\n\
\t-b     convert output to BSM (beSTORM) instead of the default C code\n\
\t-j     convert output to JSON instead of the default C code\n\
\t-r     convert output to ROS2 package instead of the default C code\n\
\t-o dir set the output directory\n\
\t-D     use 'double' for the encode/decode type messages (C code)\n\
\t-p     generate only print code (C code)\n\
\t-k     generate only pack code (C code)\n\
\t-u     generate only unpack code (C code)\n\
\t-s     disable assert generation (C code)\n\
\t-O     prefix all public C symbols with the output filename basename\n\
\t-n [version] specify the version of the generated output. Defaults to the latest. (C code)\n\
\t-B     use bool type for 1 bit long unsigned signals (ROS code)\n\
\t-L     generate legacy subscriber for backwards compatibility with raceup_msgs (ROS code)\n\
\t-P     always add signal as prefix to constants. Default is only with name collision (ROS code)\n\
\t-W [ecu] add ECU to whitelist. Only whitelisted ECUs messages are kept\n\
\tfile   process a DBC file\n\
\n\
Files must come after the arguments have been processed.\n\
\n\
The parser combinator library (mpc) used in this program is licensed from\n\
Daniel Holden, Copyright (c) 2013, under the BSD3 license\n\
(see https://github.com/orangeduck/mpc/).\n\
\n\
dbcc itself is licensed under the MIT license, Copyright (c) 2024, Richard\n\
Howe. (see https://github.com/howerj/dbcc for the full program source).\n";
	fputs(msg, stderr);
}
// TODO: More option processing, allow key=val to be specified

static char *replace_file_type(const char *file, const char *suffix)
{
	assert(file);
	assert(suffix);
	char *name = duplicate(file);
	char *dot = strrchr(name, '.');
	if (*dot)
		*dot = '\0';
	if (*suffix) {
		size_t name_size = strlen(name) + strlen(suffix) + 2;
		name = reallocator(name, name_size); /* + 1 for '.', + 1 for '\0' */
		strcat(name, ".");
		strcat(name, suffix);
	} else {
		size_t name_size = strlen(name) + 1;
		name = reallocator(name, name_size); /* + 1 for '\0' */
	}
	return name;
}

static int dbc2cWrapper(dbc_t *dbc, const char *dbc_file, const char *file_only, dbc2c_options_t *copts)
{
	assert(dbc);
	assert(dbc_file);
	assert(file_only);
	char *cname = replace_file_type(dbc_file,  "c");
	char *hname = replace_file_type(dbc_file,  "h");
	char *fname = replace_file_type(file_only, "h");
	FILE *c = fopen_or_die(cname, "wb");
	FILE *h = fopen_or_die(hname, "wb");
	const int r = dbc2c(dbc, c, h, fname, copts);
	fclose(c);
	fclose(h);
	free(cname);
	free(hname);
	free(fname);
	return r;
}

static int dbc2xmlWrapper(dbc_t *dbc, const char *dbc_file, bool use_time_stamps)
{
	assert(dbc);
	assert(dbc_file);
	char *name = replace_file_type(dbc_file, "xml");
	FILE *o = fopen_or_die(name, "wb");
	const int r = dbc2xml(dbc, o, use_time_stamps);
	fclose(o);
	free(name);
	return r;
}

static int dbc2csvWrapper(dbc_t *dbc, const char *dbc_file)
{
	assert(dbc);
	assert(dbc_file);
	char *name = replace_file_type(dbc_file, "csv");
	FILE *o = fopen_or_die(name, "wb");
	const int r = dbc2csv(dbc, o);
	fclose(o);
	free(name);
	return r;
}

static int dbc2bsmWrapper(dbc_t *dbc, const char *dbc_file, bool use_time_stamps)
{
	assert(dbc);
	assert(dbc_file);
	char *name = replace_file_type(dbc_file, "bsm");
	FILE *o = fopen_or_die(name, "wb");
	const int r = dbc2bsm(dbc, o, use_time_stamps);
	fclose(o);
	free(name);
	return r;
}

static int dbc2jsonWrapper(dbc_t *dbc, const char *dbc_file, bool use_time_stamps)
{
	assert(dbc);
	assert(dbc_file);
	char *name = replace_file_type(dbc_file, "json");
	FILE *o = fopen_or_die(name, "wb");
	const int r = dbc2json(dbc, o, use_time_stamps);
	fclose(o);
	free(name);
	return r;
}

static int dbc2rosWrapper(dbc_t *dbc, const char *dbc_file, const char *file_only, dbc2ros_options_t *rosopts)
{
	assert(dbc);
	assert(dbc_file);
	char *dname = replace_file_type(dbc_file,  "");
	char *fname = replace_file_type(file_only,  "");
	int r = dbc2ros(dbc, dname, fname, rosopts);
	free(fname);
	free(dname);
	return r;
}

// TODO: Formatting, new printing functions
int main(int argc, char **argv)
{
	log_level_e log_level = get_log_level();
	conversion_type_e convert = CONVERT_TO_C;
	const char *outdir = NULL;
	char **ecu_whitelist = NULL;
	size_t ecu_whitelist_length = 0;
	// TODO: Copy copts to dbc_t, use that version threaded throughout
	// system instead.
	dbc2c_options_t copts = {
		.use_id_in_name            =  true,
		.namespace_from_filename   =  false,
		.use_time_stamps           =  false,
		.use_doubles_for_encoding  =  false,
		.generate_print            =  false,
		.generate_pack             =  false,
		.generate_unpack           =  false,
		.generate_asserts          =  true,
		.symbol_namespace          =  NULL,
		.macro_namespace           =  NULL,
		.version                   =  3,
	};
	dbc2ros_options_t rosopts = {
		.generate_bools             = false,
		.add_prefix_to_constants    = false,
		.generate_legacy_subscriber = false,
		.ecu_whitelist              = NULL,
		.ecu_whitelist_length       = 0,
	};
	int opt = 0;

	while ((opt = dbcc_getopt(argc, argv, "hVvbjgxCrNtDpukso:n:OBLPW:")) != -1) {
		switch (opt) {
		case 'h':
			usage(argv[0]);
			help();
			break;
		case 'V':
			if (fprintf(stderr, "%s\n", DBCC_VERSION) < 0) return 1;
			break;
		case 'v':
			set_log_level(++log_level);
			debug("log level: %u", log_level);
			break;
		case 'g':
			return printf("DBCC Grammar =>\n%s\n", parse_get_grammar()) < 0;
		case 'b':
			convert = CONVERT_TO_BSM;
			break;
		case 'j':
			convert = CONVERT_TO_JSON;
			break;
		case 'x':
			convert = CONVERT_TO_XML;
			break;
		case 'C':
			convert = CONVERT_TO_CSV;
			break;
		case 'r':
			convert = CONVERT_TO_ROS;
			break;
		case 'N':
			copts.use_id_in_name = false;
			break;
		case 't':
			copts.use_time_stamps = true;
			debug("using time stamps");
			break;
		case 'D':
			copts.use_doubles_for_encoding = true;
			debug("using doubles for encoding");
			break;
		case 'p':
			copts.generate_print = true;
			debug("generate code for print");
			break;
		case 'u':
			copts.generate_unpack = true;
			debug("generate code for unpack");
			break;
		case 'k':
			copts.generate_pack = true;
			debug("generate code for pack");
			break;
		case 'o':
			outdir = dbcc_optarg;
			debug("output directory: %s", outdir);
			break;
		case 'O':
			copts.namespace_from_filename = true;
			debug("prefix public C symbols with output filename basename");
			break;
		case 's':
			copts.generate_asserts = false;
			debug("asserts disabled - apparently you think silent corruption is a good thing");
			break;
		case 'n': {
			copts.version = strtol(dbcc_optarg, NULL, 10);
			if (errno == ERANGE)
				error("Could not parse version string: %s", dbcc_optarg);

			const int min = 1, max = 3;
			if (copts.version < min || copts.version > max)
				error("Invalid version requested: %d. Version should be greater than %d and less than %d.", copts.version, min, max);
			break;
		}
		case 'B':
			rosopts.generate_bools = true;
			debug("generate ROS bools");
			break;
		case 'P':
			rosopts.add_prefix_to_constants = true;
			debug("always add signals as prefix to ROS constants");
			break;
		case 'L':
			rosopts.generate_legacy_subscriber = true;
			debug("generate legacy ROS subscriber (with dependency from raceup_msgs)");
			break;
		case 'W':
			ecu_whitelist = reallocator(ecu_whitelist, sizeof(*ecu_whitelist) * ++ecu_whitelist_length);
			ecu_whitelist[ecu_whitelist_length-1] = dbcc_optarg;
			rosopts.ecu_whitelist = ecu_whitelist;
			rosopts.ecu_whitelist_length = ecu_whitelist_length;
			debug("%s added to whitelist", dbcc_optarg);
			break;
		default:
			if (fprintf(stderr, "invalid options\n") < 0) return 1;
			usage(argv[0]);
			help();
			break;
		}
	}

	debug("using version %d of output", copts.version);

	if (!copts.generate_unpack && !copts.generate_pack && !copts.generate_print) {
		copts.generate_pack   = true;
		copts.generate_unpack = true;
	}

	for (int i = dbcc_optind; i < argc; i++) {
		debug("reading => %s", argv[i]);
		mpc_ast_t *ast = parse_dbc_file_by_name(argv[i]);
		if (!ast) {
			warning("could not parse file '%s'", argv[i]);
			continue;
		}
		if (verbose(LOG_DEBUG))
			mpc_ast_print(ast);

		dbc_t *dbc = ast2dbc(ast);
		if (!dbc) {
			return 1;
		}
		dbc->version = copts.version;
		whitelist_filter_dbc(dbc, ecu_whitelist, ecu_whitelist_length);
		print_dbc_summary_block(dbc, argv[i]);

		char *outpath = dbcc_basename(argv[i]);
		if (outdir) {
			outpath = allocate(strlen(outpath) + strlen(outdir) + 2 /* '/' + '\0'*/);
			strcat(outpath, outdir);
			strcat(outpath, "/");
			strcat(outpath, dbcc_basename(argv[i]));
		}

		int r = 0;
		switch (convert) {
		case CONVERT_TO_C:
			r = dbc2cWrapper(dbc, outpath, dbcc_basename(argv[i]), &copts);
			break;
		case CONVERT_TO_XML:
			r = dbc2xmlWrapper(dbc, outpath, copts.use_time_stamps);
			break;
		case CONVERT_TO_CSV:
			if (copts.use_time_stamps)
				error("Cannot use time stamps when specifying CSV option");
			r = dbc2csvWrapper(dbc, outpath);
			break;
		case CONVERT_TO_BSM:
			r = dbc2bsmWrapper(dbc, outpath, copts.use_time_stamps);
			break;
		case CONVERT_TO_JSON:
			r = dbc2jsonWrapper(dbc, outpath, copts.use_time_stamps);
			break;
		case CONVERT_TO_ROS:
			r = dbc2rosWrapper(dbc, outpath, dbcc_basename(argv[i]), &rosopts);
			break;
		default:
			error("invalid conversion type: %d", convert);
		}
		if (r < 0)
			warning("conversion process failed: %u/%u", r, convert);

		if (outdir)
			free(outpath);
		dbc_delete(dbc);
		mpc_ast_delete(ast);
	}
	free(ecu_whitelist);

	return 0;
}
