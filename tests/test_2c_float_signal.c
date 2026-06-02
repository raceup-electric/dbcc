#include "../out/test_c/float_signal.h"
#include "test_2c_common.h"

int test_2c_float_signal(void) {
	can_0x400_NewMessage0_obj_t msg = {0};
	float out0 = 0.0f, out1 = 0.0f;

	encode_0x400_float_signal_0(&msg, 1.25f);
	encode_0x400_float_signal_1(&msg, -9.5f);
	decode_0x400_float_signal_0(&msg, &out0);
	decode_0x400_float_signal_1(&msg, &out1);
	CHECK(check_float_eq(out0, 1.25f, 1e-6f));
	CHECK(check_float_eq(out1, -9.5f, 1e-6f));

	return 0;
}
