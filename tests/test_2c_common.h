#ifndef TEST_2C_COMMON_H
#define TEST_2C_COMMON_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK(expr) \
	do { \
		if (!(expr)) { \
			fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #expr); \
			return 1; \
		} \
	} while (0)

static inline int check_float_eq(float a, float b, float tol) {
	return fabsf(a - b) <= tol;
}

static inline int check_double_eq(double a, double b, double tol) {
	return fabs(a - b) <= tol;
}

#endif
