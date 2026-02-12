#ifndef _2ROS_H
#define _2ROS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "can.h"

int dbc2ros(const dbc_t *dbc, const char *outdir, const char *name);

#ifdef __cplusplus
}
#endif

#endif
