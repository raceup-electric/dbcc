/* @copyright SUBLEQ LTD. (2025), RaceUP (2026)
 * @license MIT */
#ifndef _2RUST_H
#define _2RUST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "can.h"
#include <stdio.h>

/*
 * Generate a dependency-free Rust module containing the complete DBC codec
 * and, when valid SDO_DPS messages are present, the SDO master/slave API.
 */
int dbc2rust(dbc_t *dbc, FILE *output, const char *name, const char *dbc_file);

#ifdef __cplusplus
}
#endif

#endif
