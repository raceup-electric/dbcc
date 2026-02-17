#ifndef _2ROS_H
#define _2ROS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "can.h"
#include <stdbool.h>

typedef struct {
    bool generate_bools;
    bool add_prefix_to_constants;
    bool generate_legacy_subscriber;
} dbc2ros_options_t;

int dbc2ros(const dbc_t *dbc, const char *outdir, const char *package_name, dbc2ros_options_t *rosopts);

#ifdef __cplusplus
}
#endif

#endif
