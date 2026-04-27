#include <stdio.h>

int test_2c_bitfield_edge(void);
int test_2c_codec_matrix(void);
int test_2c_double_signal(void);
int test_2c_enum(void);
int test_2c_ex1(void);
int test_2c_ex2(void);
int test_2c_float_signal(void);
int test_2c_mul_val(void);

int main(void) {
	if (test_2c_bitfield_edge() != 0)
		return 1;
	if (test_2c_codec_matrix() != 0)
		return 1;
	if (test_2c_double_signal() != 0)
		return 1;
	if (test_2c_enum() != 0)
		return 1;
	if (test_2c_ex1() != 0)
		return 1;
	if (test_2c_ex2() != 0)
		return 1;
	if (test_2c_float_signal() != 0)
		return 1;
	if (test_2c_mul_val() != 0)
		return 1;
	puts("2.c round-trip tests passed");
	return 0;
}
