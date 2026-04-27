/**
 * @copyright SUBLEQ LTD (2025)
 * @license MIT
 * @note Error checking is not done in this file, or if it is done it should be
 * done with assertions, the parser does the validation and processing of the
 * input, if a returned object is not checked it is because it *must* exist (or
 * there is a bug in the grammar).
 * @note most values will be converted to doubles and then to integers, which
 * is fine for 32 bit values, but fails for large integers. */
#include "can.h"
#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

static signal_t *signal_new(void)
{
	return allocate(sizeof(signal_t));
}

static void signal_delete(signal_t *signal)
{
	if (!signal)
		return;
	for (size_t i = 0; i < signal->ecu_count; i++)
		free(signal->ecus[i]);
	free(signal->name);
	free(signal->ecus);
	free(signal->units);
	free(signal->muxed);
	free(signal->mux_vals);
	free(signal->comment);
	free(signal);
}

static can_msg_t *can_msg_new(void)
{
	return allocate(sizeof(can_msg_t));
}

static void can_msg_delete(can_msg_t *msg)
{
	if (!msg)
		return;
	for (size_t i = 0; i < msg->signal_count; i++)
		signal_delete(msg->sigs[i]);
	for (size_t i = 0; i < msg->ecu_count; i++)
		free(msg->ecus[i]);
	free(msg->ecus);
	free(msg->sigs);
	free(msg->name);
	free(msg->ecu);
	free(msg->comment);
	free(msg);
}

static void val_delete(val_list_t *val)
{
	if (!val)
		return;
	for (size_t i = 0; i < val->val_list_item_count; i++) {
		free(val->val_list_items[i]->name);
		free(val->val_list_items[i]);
	}
	free(val->val_list_items);
	free(val->name);
	free(val->val_table_name);
	free(val);
}

static void mul_val_delete(mul_val_list_t *mul_val)
{
	if (!mul_val)
		return;
	free(mul_val->multiplexed);
	free(mul_val->multiplexor);
	for (size_t i = 0; i < mul_val->range_num; i++) {
		free(mul_val->ranges[i]);
	}
	free(mul_val->ranges);
	free(mul_val);
}

static void y_mx_c(mpc_ast_t *ast, signal_t *sig)
{
	assert(ast && sig);
	mpc_ast_t *scalar = ast->children[1];
	mpc_ast_t *offset = ast->children[3];
	int r = sscanf(scalar->contents, "%lf", &sig->scaling);
	assert(r == 1);
	r = sscanf(offset->contents, "%lf", &sig->offset);
	assert(r == 1);
}

static void range(mpc_ast_t *ast, signal_t *sig)
{
	assert(ast && sig);
	mpc_ast_t *min = ast->children[1];
	mpc_ast_t *max = ast->children[3];
	int r = sscanf(min->contents, "%lf", &sig->minimum);
	assert(r == 1);
	r = sscanf(max->contents, "%lf", &sig->maximum);
	assert(r == 1);
}

static void units(mpc_ast_t *ast, signal_t *sig)
{
	assert(ast && sig);
	mpc_ast_t *unit = mpc_ast_get_child(ast, "regex");
	sig->units = duplicate(unit->contents);
}

static void nodes(mpc_ast_t *sig_ast, signal_t *sig)
{
	assert(sig_ast && sig);

	mpc_ast_t *single_node = mpc_ast_get_child(sig_ast, "nodes|node|ident|regex");
	if (single_node) {
		sig->ecus = allocate(sizeof(*sig->ecus));
		sig->ecus[0] = duplicate(single_node->contents);
		sig->ecu_count = 1;
		return;
	}
	
	mpc_ast_t *multiple_nodes = mpc_ast_get_child(sig_ast, "nodes|>");
	char **nodes = NULL;
	size_t len = 0;
	for (int i = 0; i >= 0;) {
		i = mpc_ast_get_index_lb(multiple_nodes, "node|ident|regex", i);
		if (i >= 0) {
			mpc_ast_t *node_ast = mpc_ast_get_child_lb(multiple_nodes, "node|ident|regex", i);
			nodes = reallocator(nodes, sizeof(*nodes)*++len);
			nodes[len-1] = duplicate(node_ast->contents);
			i++;
		}
	}
	sig->ecus = nodes;
	sig->ecu_count = len;
}

static void message_nodes(mpc_ast_t *msg_ast, can_msg_t *msg)
{
	assert(msg_ast && msg);

	mpc_ast_t *single_node = mpc_ast_get_child(msg_ast, "nodes|node|ident|regex");
	if (single_node) {
		msg->ecus = allocate(sizeof(*msg->ecus));
		msg->ecus[0] = duplicate(single_node->contents);
		msg->ecu_count = 1;
		msg->ecu = duplicate(single_node->contents);
		return;
	}

	mpc_ast_t *multiple_nodes = mpc_ast_get_child(msg_ast, "nodes|>");
	char **nodes = NULL;
	size_t len = 0;
	for (int i = 0; i >= 0;) {
		i = mpc_ast_get_index_lb(multiple_nodes, "node|ident|regex", i);
		if (i >= 0) {
			mpc_ast_t *node_ast = mpc_ast_get_child_lb(multiple_nodes, "node|ident|regex", i);
			nodes = reallocator(nodes, sizeof(*nodes) * ++len);
			nodes[len - 1] = duplicate(node_ast->contents);
			i++;
		}
	}
	msg->ecus = nodes;
	msg->ecu_count = len;
	if (len)
		msg->ecu = duplicate(nodes[0]);
}

static int sigval(mpc_ast_t *top, unsigned id, const char *signal)
{
	assert(top);
	assert(signal);
	for (int i = 0; i >= 0;) {
		i = mpc_ast_get_index_lb(top, "sigval|>", i);
		if (i >= 0) {
			mpc_ast_t *sv   = mpc_ast_get_child_lb(top, "sigval|>", i);
			mpc_ast_t *name = mpc_ast_get_child(sv,     "name|ident|regex");
			mpc_ast_t *svid = mpc_ast_get_child(sv,     "id|integer|regex");
			assert(name);
			assert(svid);
			unsigned svidd = 0;
			sscanf(svid->contents, "%u", &svidd);
			if (id == svidd && !strcmp(signal, name->contents)) {
				unsigned typed = 0;
				mpc_ast_t *type = mpc_ast_get_child(sv, "sigtype|integer|regex");
				sscanf(type->contents, "%u", &typed);
				debug("floating -> %s:%u:%u\n", name->contents, id, typed);
				return typed;
			}
			i++;
		}
	}
	return -1;
}

static signal_t *ast2signal(mpc_ast_t *top, mpc_ast_t *ast, unsigned can_id)
{
	assert(ast);
	signal_t *sig = signal_new();
	mpc_ast_t *name   = mpc_ast_get_child(ast, "name|ident|regex");
	mpc_ast_t *start  = mpc_ast_get_child(ast, "startbit|integer|regex");
	mpc_ast_t *length = mpc_ast_get_child(ast, "length|regex");
	mpc_ast_t *endianess = mpc_ast_get_child(ast, "endianess|char");
	mpc_ast_t *sign   = mpc_ast_get_child(ast, "sign|char");
	sig->name = duplicate(name->contents);
	sig->val_list = NULL;
	int r = sscanf(start->contents, "%u", &sig->start_bit);
	/* BUG: Minor-medium bug, an error should be returned here instead,
	 * using `assert` for error handling is something of faux pas in
	 * more civilized circles. Here, were are barbarians, lazy ones. */
	assert(r == 1 && sig->start_bit <= 64);
	r = sscanf(length->contents, "%u", &sig->bit_length);
	assert(r == 1 && sig->bit_length <= 64);
	char endchar = endianess->contents[0];
	assert(endchar == '0' || endchar == '1');
	sig->endianess = endchar == '0' ?
		endianess_motorola_e :
		endianess_intel_e ;
	char signchar = sign->contents[0];
	assert(signchar == '+' || signchar == '-');
	sig->is_signed = signchar == '-';

	y_mx_c(mpc_ast_get_child(ast, "y_mx_c|>"), sig);
	range(mpc_ast_get_child(ast, "range|>"), sig);
	units(mpc_ast_get_child(ast, "unit|string|>"), sig);
	nodes(ast, sig);

	/* process multiplexed values, if present */
	sig->mul_num = 0;
	sig->muxed = NULL;
	sig->mux_vals = NULL;
	sig->mux_parent = NULL;
	mpc_ast_t *multiplex = mpc_ast_get_child(ast, "multiplexor|>");
	if (multiplex) {
		sig->is_multiplexed = true;
		sig->switchval = atol(multiplex->children[1]->contents);
		mpc_ast_t *elem = mpc_ast_get_child_lb(multiplex, "char", 1);
		if(elem && *elem->contents == 'M') {
			sig->is_multiplexor = true;
		}
	}

	if (mpc_ast_get_child(ast, "multiplexor|char")) {
		assert(!sig->is_multiplexed);
		sig->is_multiplexor = true;
	}

	sig->sigval = sigval(top, can_id, sig->name);
	if (sig->sigval == 1 || sig->sigval == 2)
		sig->is_floating = true;

	debug("\tname => %s; start %u length %u %s %s %s",
			sig->name, sig->start_bit, sig->bit_length, sig->units,
			sig->endianess ? "intel" : "motorola",
			sig->is_signed ? "signed " : "unsigned");
	return sig;
}

static void sort_val_items(val_list_t *val)
{
	assert(val);

	if (val->val_list_item_count) {
		bool bFlip = false;
		do {
			bFlip = false;
			for (size_t i = 0; i < val->val_list_item_count - 1; i++) {
				if (val->val_list_items[i]->value > val->val_list_items[i + 1]->value) {
					val_list_item_t *tmp = val->val_list_items[i];
					val->val_list_items[i] = val->val_list_items[i + 1];
					val->val_list_items[i + 1] = tmp;
					bFlip = true;
				}
			}
		} while (bFlip);
	}
}

static void ast2val_items(mpc_ast_t *ast, val_list_t *val)
{
	assert(ast);
	assert(val);
	val_list_item_t **items = allocate(sizeof(*items) * (ast->children_num + 1));
	size_t j = 0;
	for (int i = 0; i >= 0;) {
		i = mpc_ast_get_index_lb(ast, "val_item|>", i);
		if (i >= 0) {
			val_list_item_t *item = allocate(sizeof(val_list_item_t));
			mpc_ast_t *val_item_ast = mpc_ast_get_child_lb(ast, "val_item|>", i);

			mpc_ast_t *val_item_index = mpc_ast_get_child(val_item_ast, "integer|regex");
			int r = sscanf(val_item_index->contents, "%u", &item->value);
			assert(r == 1);

			mpc_ast_t *val_item_name = mpc_ast_get_child(val_item_ast, "string|>");
			val_item_name = mpc_ast_get_child_lb(val_item_name, "regex", 1);
			item->name = duplicate(val_item_name->contents);
			items[j++] = item;
			i++;
		}
	}

	val->val_list_item_count = j;
	val->val_list_items = items;
	sort_val_items(val);
}

static val_list_t *find_val_table(dbc_t *dbc, const char *name)
{
	assert(dbc);
	assert(name);

	for (size_t i = 0; i < dbc->val_table_count; i++)
		if (!strcmp(dbc->val_tables[i]->name, name))
			return dbc->val_tables[i];

	return NULL;
}

static mpc_ast_t *child_with_tag(mpc_ast_t *ast, const char *tag)
{
	assert(ast);
	assert(tag);

	for (int i = 0; i < ast->children_num; i++)
		if (!strcmp(ast->children[i]->tag, tag))
			return ast->children[i];

	return NULL;
}

static void copy_val_items(val_list_t *dst, const val_list_t *src)
{
	assert(dst);
	assert(src);

	dst->val_list_item_count = src->val_list_item_count;
	dst->val_list_items = allocate(sizeof(*dst->val_list_items) * (src->val_list_item_count + 1));

	for (size_t i = 0; i < src->val_list_item_count; i++) {
		val_list_item_t *item = allocate(sizeof(*item));
		item->name = duplicate(src->val_list_items[i]->name);
		item->value = src->val_list_items[i]->value;
		dst->val_list_items[i] = item;
	}
}

static val_list_t *ast2val(mpc_ast_t *top, mpc_ast_t *ast, dbc_t *dbc)
{
	assert(top);
	assert(ast);
	assert(dbc);
	val_list_t *val = allocate(sizeof(val_list_t));

	mpc_ast_t *id = mpc_ast_get_child(ast, "id|integer|regex");
	int r = sscanf(id->contents, "%u", &val->id);
	assert(r == 1);

	mpc_ast_t *name = mpc_ast_get_child(ast, "name|ident|regex");
	val->name = duplicate(name->contents);

	mpc_ast_t *table_ref = child_with_tag(ast, "val_table_ref|>");
	if (table_ref) {
		mpc_ast_t *table_name = child_with_tag(table_ref, "name|ident|regex");
		assert(table_name);
		val_list_t *table = find_val_table(dbc, table_name->contents);
		if (!table)
			error("unknown VAL_TABLE_ reference '%s' for signal %s", table_name->contents, val->name);
		copy_val_items(val, table);
		val->is_val_table_reference = true;
		val->val_table_name = duplicate(table_name->contents);
	} else {
		ast2val_items(ast, val);
	}

	return val;
}

static val_list_t *ast2val_table(mpc_ast_t *ast)
{
	assert(ast);
	val_list_t *val = allocate(sizeof(val_list_t));

	mpc_ast_t *name = mpc_ast_get_child(ast, "name|ident|regex");
	val->name = duplicate(name->contents);
	ast2val_items(ast, val);

	return val;
}

static mul_val_list_t *ast2mul_val(mpc_ast_t *top, mpc_ast_t *ast)
{
	assert(top);
	assert(ast);
	mul_val_list_t *mul_val = allocate(sizeof(mul_val_list_t));

	mpc_ast_t *id   = mpc_ast_get_child(ast, "id|integer|regex");
	int r = sscanf(id->contents,  "%u",  &mul_val->id);
	assert(r == 1);

	int i =0;
	i = mpc_ast_get_index_lb(ast, "name|ident|regex", i);
	mpc_ast_t *multiplexed = mpc_ast_get_child_lb(ast, "name|ident|regex", i);
	mul_val->multiplexed = duplicate(multiplexed->contents);

	mpc_ast_t *multiplexor = mpc_ast_get_child_lb(ast, "name|ident|regex", i+1);
	mul_val->multiplexor = duplicate(multiplexor->contents);

	mpc_ast_t *mul_ranges_ast = mpc_ast_get_child_lb(ast, "mul_ranges|>", 0);
	if (mul_ranges_ast && mul_ranges_ast->children_num) {
		mul_val_range_pair **ranges = allocate(sizeof(*ranges) * (mul_ranges_ast->children_num+1));
		int j = 0;
		for (int i = 0; i >= 0;) {
			mpc_ast_t *mul_range = mpc_ast_get_child_lb(mul_ranges_ast, "mul_range|>", i);
			if (mul_range) {
				mul_val_range_pair *range = allocate(sizeof(mul_val_range_pair));

				int k = 0;
				k = mpc_ast_get_index_lb(mul_range, "integer|regex", 0);
				mpc_ast_t *first_value = mpc_ast_get_child_lb(mul_range, "integer|regex", k);
				r = sscanf(first_value->contents,  "%u",  &range->min_value);
				assert(r == 1);

				mpc_ast_t *second_value = mpc_ast_get_child_lb(mul_range, "integer|regex", k+1);
				r = sscanf(second_value->contents,  "%u",  &range->max_value);
				assert(r == 1);

				// swap inverted values
				if (range->min_value > range->max_value) {
					int tmp = range->min_value;
					range->min_value = range->max_value;
					range->max_value = tmp;
				}

				ranges[j++] = range;
				i++;
			} else {
				break;
			}
		}
		mul_val->range_num = j;
		mul_val->ranges = ranges;
	} else {
		mpc_ast_t *mul_range = mpc_ast_get_child_lb(ast, "mul_ranges|mul_range|>", 0);
		if (mul_range) {
			mul_val->range_num = 1;
			mul_val_range_pair *range = allocate(sizeof(mul_val_range_pair));

			int k = 0;
			k = mpc_ast_get_index_lb(mul_range, "integer|regex", 0);
			mpc_ast_t *first_value = mpc_ast_get_child_lb(mul_range, "integer|regex", k);
			r = sscanf(first_value->contents,  "%u",  &range->min_value);
			assert(r == 1);

			mpc_ast_t *second_value = mpc_ast_get_child_lb(mul_range, "integer|regex", k+1);
			r = sscanf(second_value->contents,  "%u",  &range->max_value);
			assert(r == 1);

			// swap inverted values
			if (range->min_value > range->max_value) {
				int tmp = range->min_value;
				range->min_value = range->max_value;
				range->max_value = tmp;
			}

			mul_val->ranges = allocate(sizeof(mul_val_range_pair*));
			mul_val->ranges[0] = range;
		}
	}

	return mul_val;
}

static can_msg_t *ast2msg(mpc_ast_t *top, mpc_ast_t *ast, dbc_t *dbc)
{
	assert(top);
	assert(ast);
	can_msg_t *c = can_msg_new();
	mpc_ast_t *name = mpc_ast_get_child(ast, "name|ident|regex");
	mpc_ast_t *dlc  = mpc_ast_get_child(ast, "dlc|integer|regex");
	mpc_ast_t *id   = mpc_ast_get_child(ast, "id|integer|regex");
	c->name = duplicate(name->contents);
	int r = sscanf(dlc->contents, "%u", &c->dlc);
	assert(r == 1);
	r = sscanf(id->contents,  "%lu", &c->id);
	assert(r == 1);
	message_nodes(ast, c);

	/* Extended CAN messages use the top most bit (which should
	 * not normally be set) to indicate that they are extended
	 * and not normal messages. */

	// TODO: Handle version generation
	//if (copt->version >= 3 || copt->feature_mask_ids) {
		const uint32_t msk = 0x80000000u;
		if (c->id & 0x80000000u) {
			c->is_extended = true;
			c->id &= ~msk;
		}
	//}

	signal_t **signal_s = allocate(sizeof(*signal_s));
	size_t len = 1, j = 0;
	for (int i = 0; i >= 0;) {
		i = mpc_ast_get_index_lb(ast, "signal|>", i);
		if (i >= 0) {
			mpc_ast_t *sig_ast = mpc_ast_get_child_lb(ast, "signal|>", i);
			signal_s = reallocator(signal_s, sizeof(*signal_s)*++len);
			signal_s[j++] = ast2signal(top, sig_ast, c->id);
			i++;
		}
	}

	c->sigs = signal_s;
	c->signal_count = j;

	// assign val-s to the signals
	for (size_t i = 0; i < c->signal_count; i++) {
		for (size_t j = 0; j<dbc->val_count; j++) {
			if (dbc->vals[j]->id == (c->id | (unsigned long)c->is_extended << 31) && strcmp(dbc->vals[j]->name, c->sigs[i]->name) == 0) {
				c->sigs[i]->val_list = dbc->vals[j];
				break;
			}
		}
	}

	// assign multiplexed signals to multiplexors
	for (size_t i = 0; i < c->signal_count; i++) {
		for (size_t j = 0; j<dbc->mul_val_count; j++) {
			if (dbc->mul_vals[j]->id == (c->id | (unsigned long)c->is_extended << 31) && strcmp(dbc->mul_vals[j]->multiplexed, c->sigs[i]->name) == 0) {
				bool muxMatch = false;
				for (size_t k = 0; k<dbc->mul_vals[j]->range_num; k++) {
					if (dbc->mul_vals[j]->ranges[k]->min_value <= c->sigs[i]->switchval && c->sigs[i]->switchval <= dbc->mul_vals[j]->ranges[k]->max_value) {
						muxMatch = true;
						break;
					}
				}
				if (!muxMatch)
					error("The multiplex value is wrong on message %s for signal %s (fix your DBC file)", c->name, c->sigs[i]->name);

				c->sigs[i]->is_multiplexed = true;
				for(size_t k = 0; k < c->signal_count; k++) {
					if (strcmp(c->sigs[k]->name, dbc->mul_vals[j]->multiplexor) == 0) {
						size_t last = c->sigs[k]->mul_num++;
							c->sigs[k]->muxed = reallocator(c->sigs[k]->muxed, sizeof(signal_t*) * c->sigs[k]->mul_num);
							c->sigs[k]->mux_vals = reallocator(c->sigs[k]->mux_vals, sizeof(mul_val_list_t*) * c->sigs[k]->mul_num);
							c->sigs[k]->muxed[last] = c->sigs[i];
							c->sigs[k]->mux_vals[last] = dbc->mul_vals[j];
							c->sigs[i]->mux_parent = c->sigs[k];
							break; // I assume a signal can be multiplexed by only one signal
						}
					}
			}
		}
	}

	if (c->signal_count > 1) { // Lets sort the signals so that their start_bit is asc (lowest number first)
		bool bFlip = false;
		do {
			bFlip = false;
			for (size_t i = 0; i < c->signal_count - 1; i++) {
				if (c->sigs[i]->start_bit > c->sigs[i + 1]->start_bit) {
					signal_t *tmp = c->sigs[i];
					c->sigs[i] = c->sigs[i + 1];
					c->sigs[i + 1] = tmp;
					bFlip = true;
				}
			}
		} while (bFlip);
	}

	debug("%s id:%u dlc:%u signals:%zu ecu:%s tx_count:%zu", c->name, c->id, c->dlc, c->signal_count, c->ecu, c->ecu_count);
	return c;
}

dbc_t *dbc_new(void)
{
	return allocate(sizeof(dbc_t));
}

void dbc_delete(dbc_t *dbc)
{
	if (!dbc)
		return;
	for (size_t i = 0; i < dbc->message_count; i++)
		can_msg_delete(dbc->messages[i]);
	free(dbc->messages);

	for (size_t i = 0; i < dbc->val_count; i++)
		val_delete(dbc->vals[i]);
	free(dbc->vals);

	for (size_t i = 0; i < dbc->val_table_count; i++)
		val_delete(dbc->val_tables[i]);
	free(dbc->val_tables);

	for (size_t i = 0; i < dbc->mul_val_count; i++)
		mul_val_delete(dbc->mul_vals[i]);
	free(dbc->mul_vals);

	free(dbc);
}

void assign_comment_to_signal(dbc_t *dbc, const char *comment, unsigned message_id, const char * signal_name)
{
	for (size_t i = 0; i<dbc->message_count; i++) {
		if (dbc->messages[i]->id == message_id) {
			for (size_t j = 0; j<dbc->messages[i]->signal_count; j++) {
				if (strcmp(dbc->messages[i]->sigs[j]->name, signal_name) == 0) {
					dbc->messages[i]->sigs[j]->comment = duplicate(comment);
					return;
				}
			}
		}
	}
}

void assign_comment_to_message(dbc_t *dbc, const char *comment, unsigned message_id)
{
	for (size_t i = 0; i<dbc->message_count; i++) {
		if (dbc->messages[i]->id == message_id) {
			dbc->messages[i]->comment = duplicate(comment);
			return;
		}
	}
}

dbc_t *ast2dbc(mpc_ast_t *ast)
{
	dbc_t *d = dbc_new();

	/* find and store global VAL_TABLE_ definitions */
	size_t len = 0;
	for (int i = 0; i >= 0;) {
		i = mpc_ast_get_index_lb(ast, "values|value_table|>", i);
		if (i >= 0) {
			len++;
			i++;
		}
	}

	if (len) {
		d->val_tables = allocate(sizeof(*d->val_tables) * (len + 1));
		d->val_table_count = len;
		size_t j = 0;
		for (int i = 0; i >= 0;) {
			i = mpc_ast_get_index_lb(ast, "values|value_table|>", i);
			if (i >= 0) {
				mpc_ast_t *val_table_ast = mpc_ast_get_child_lb(ast, "values|value_table|>", i);
				d->val_tables[j++] = ast2val_table(val_table_ast);
				i++;
			}
		}
	}

	/* find and store the vals into the dbc: they will be assigned to
	signals later */
	mpc_ast_t *vals_ast = mpc_ast_get_child_lb(ast, "vals|>", 0);
	if (vals_ast) {
		d->val_count = vals_ast->children_num;
		d->vals = allocate(sizeof(*d->vals) * (d->val_count+1));
		if (d->val_count) {
			int j = 0;
			for (int i = 0; i >= 0;) {
				i = mpc_ast_get_index_lb(vals_ast, "val|>", i);
				if (i >= 0) {
					mpc_ast_t *val_ast = mpc_ast_get_child_lb(vals_ast, "val|>", i);
					d->vals[j++] = ast2val(ast, val_ast, d);
					i++;
				}
			}
		}
	} else {
		mpc_ast_t *val_ast = mpc_ast_get_child_lb(ast, "vals|val|>", 0);
		if (val_ast) {
			d->vals = allocate(sizeof(*d->vals) * (d->val_count+1));
			d->val_count = 1;
			d->vals[0] = ast2val(ast, val_ast, d);
		}
	}

	/* find and store the multiplexed vals into the dbc: they will be assigned
	to signals later */
	mpc_ast_t *mul_vals_ast = mpc_ast_get_child_lb(ast, "mul_vals|>", 0);
	if (mul_vals_ast) {
		d->mul_val_count = mul_vals_ast->children_num;
		d->mul_vals = allocate(sizeof(*d->mul_vals) * (d->mul_val_count));
		if (d->mul_val_count) {
			int j = 0;
			for (int i = 0; i >= 0;) {
				i = mpc_ast_get_index_lb(mul_vals_ast, "mul_val|>", i);
				if (i >= 0) {
					mpc_ast_t *mul_val_ast = mpc_ast_get_child_lb(mul_vals_ast, "mul_val|>", i);
					d->mul_vals[j++] = ast2mul_val(ast, mul_val_ast);
					i++;
				}
			}
		}
	} else {
		mpc_ast_t *mul_val_ast = mpc_ast_get_child_lb(ast, "mul_vals|mul_val|>", 0);
		if (mul_val_ast) {
			d->mul_val_count = 1;
			d->mul_vals = allocate(sizeof(*d->mul_vals));
			d->mul_vals[0] = ast2mul_val(ast, mul_val_ast);
		}
	}

	int index     = mpc_ast_get_index_lb(ast, "messages|>", 0);
	mpc_ast_t *msgs_ast = mpc_ast_get_child_lb(ast, "messages|>", 0);
	if (index < 0) {
		warning("no messages found");
		return NULL;
	}

	int n = msgs_ast->children_num;
	if (n <= 0) {
		warning("messages has no children");
		return NULL;
	}

	can_msg_t **r = allocate(sizeof(*r) * (n+1));
	int j = 0;
	for (int i = 0; i >= 0;) {
		i = mpc_ast_get_index_lb(msgs_ast, "message|>", i);
		if (i >= 0) {
			mpc_ast_t *msg_ast = mpc_ast_get_child_lb(msgs_ast, "message|>", i);
			r[j++] = ast2msg(ast, msg_ast, d);
			i++;
		}
	}
	d->message_count = j;
	d->messages = r;

	int i = mpc_ast_get_index_lb(ast, "sigval|>", 0);
	if (i >= 0)
		d->use_float = true;

	// find and store the vals into the dbc: they will be assigned to
	// signals later
	mpc_ast_t *comments_ast = mpc_ast_get_child_lb(ast, "comments|>", 0);
	if (comments_ast && comments_ast->children_num) {
		for (int i = 0; i >= 0;) {
			i = mpc_ast_get_index_lb(comments_ast, "comment|>", i);
			if (i >= 0) {
				mpc_ast_t *comment_ast = mpc_ast_get_child_lb(comments_ast, "comment|>", i);
				if (comments_ast && comments_ast->children_num > 3) {
					bool to_message = strcmp(comment_ast->children[2]->contents, "BO_") == 0;
					bool to_signal = strcmp(comment_ast->children[2]->contents, "SG_") == 0;
					if (to_signal || to_message) {
						mpc_ast_t *id   = mpc_ast_get_child(comment_ast, "id|integer|regex");
						unsigned message_id;
						int r = sscanf(id->contents, "%u", &message_id);
						assert(r == 1);
						mpc_ast_t *comment = mpc_ast_get_child(comment_ast, "comment_string|string|>");
						if (to_signal) {
							mpc_ast_t *signal_name = mpc_ast_get_child(comment_ast, "name|ident|regex");
							assign_comment_to_signal(d, comment->children[1]->contents, message_id, signal_name->contents);
						} else  {
							assign_comment_to_message(d, comment->children[1]->contents, message_id);
						}
					}
				}
				i++;
			}
		}
	}

	return d;
}


static bool is_whitelisted_ecu(const char* ecu, char **ecu_whitelist, size_t ecu_whitelist_length) {
	for (size_t i = 0; i <ecu_whitelist_length; i++) {
		if (strcmp(ecu, ecu_whitelist[i]) == 0) {
			return true;
		}
	}
	return false;
}

void whitelist_filter_dbc(dbc_t *dbc, char **ecu_whitelist, size_t ecu_whitelist_length)
{
	if (ecu_whitelist_length == 0)
		return;

	size_t write_index = 0;

	for (size_t read_index = 0; read_index < dbc->message_count; read_index++) {

		can_msg_t *msg = dbc->messages[read_index];
		int keep = 0;

		// message ECU is whitelisted
		for (size_t j = 0; j < msg->ecu_count && !keep; j++) {
			if (is_whitelisted_ecu(msg->ecus[j], ecu_whitelist, ecu_whitelist_length)) {
				keep = 1;
			}
		}
		if (!keep) {
			// any signal has a whitelisted ECU
			for (size_t j = 0; j < msg->signal_count && !keep; j++) {
				signal_t *sig = msg->sigs[j];
				for (size_t k = 0; k < sig->ecu_count; k++) {
					if (is_whitelisted_ecu(sig->ecus[k], ecu_whitelist, ecu_whitelist_length)) {
						keep = 1;
						break;
					}
				}
			}
		}

		if (keep) {
			dbc->messages[write_index++] = msg;
		} else {
			can_msg_delete(msg);
		}
	}

	dbc->message_count = write_index;
}
