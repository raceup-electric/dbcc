#include "../out/test_c/double_signal.h"
#include "test_2c_common.h"

int test_2c_double_signal(void) {
	can_0x400_NewMessage0_obj_t msg = {0};
	double out = 0.0;

	encode_0x400_double_signal_0(&msg, 12345.6789);
	decode_0x400_double_signal_0(&msg, &out);
	CHECK(check_double_eq(out, 12345.6789, 1e-12));

	return 0;
}
