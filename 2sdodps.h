/* @copyright SUBLEQ LTD. (2025)
 * @license MIT */
#ifndef _2SDODPS_H
#define _2SDODPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "can.h"

int dbc2sdodps(dbc_t *dbc, const char *dbc_file, const char *outdir);

#ifdef __cplusplus
}
#endif

#endif
