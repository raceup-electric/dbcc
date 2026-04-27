#include <stdio.h>

int test_2c_single_enum(void);

int main(void) {
	if (test_2c_single_enum() != 0)
		return 1;
	puts("2.c single_enum round-trip tests passed");
	return 0;
}
