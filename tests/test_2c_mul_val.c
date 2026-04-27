#include "../out/test_c/mul_val.h"
#include "test_2c_common.h"

int test_2c_mul_val(void) {
	can_0x000_extended_multiplex_w_ranges_obj_t ranges = {0};
	uint8_t muxer_w_ranges = 0;
	int8_t muxed_w_ranges = 0;

	encode_can_0x000_muxer_w_multiple_ranges(&ranges, 66u);
	encode_can_0x000_muxed_w_ranges(&ranges, -12);
	decode_can_0x000_muxer_w_multiple_ranges(&ranges, &muxer_w_ranges);
	decode_can_0x000_muxed_w_ranges(&ranges, &muxed_w_ranges);
	CHECK(muxer_w_ranges == 66u);
	CHECK(muxed_w_ranges == -12);

	can_0x692_extended_multiplex_obj_t mux1 = {0};
	uint16_t simple_muxer = 0;
	uint8_t muxed_muxer = 0, sig3 = 0, sig1 = 0;
	double sig2 = 0.0;
	uint32_t muxed1 = 0;

	encode_can_0x692_simple_muxer(&mux1, 9216u);
	encode_can_0x692_muxed_muxer(&mux1, 1u);
	encode_can_0x692_muxed1(&mux1, 0x89abcdefu);
	encode_can_0x692_sig3(&mux1, 9u);
	encode_can_0x692_sig1(&mux1, 2u);
	encode_can_0x692_sig2(&mux1, 3.0);
	decode_can_0x692_simple_muxer(&mux1, &simple_muxer);
	decode_can_0x692_muxed_muxer(&mux1, &muxed_muxer);
	decode_can_0x692_muxed1(&mux1, &muxed1);
	decode_can_0x692_sig3(&mux1, &sig3);
	decode_can_0x692_sig1(&mux1, &sig1);
	decode_can_0x692_sig2(&mux1, &sig2);
	CHECK(simple_muxer == 9216u);
	CHECK(muxed_muxer == 1u);
	CHECK(muxed1 == 0x89abcdefu);
	CHECK(sig3 == 9u);
	CHECK(sig1 == 2u);
	CHECK(check_double_eq(sig2, 3.0, 1e-12));

	can_0x692_extended_multiplex_obj_t mux2 = {0};
	uint32_t muxed2 = 0;

	encode_can_0x692_simple_muxer(&mux2, 9216u);
	encode_can_0x692_muxed_muxer(&mux2, 4u);
	encode_can_0x692_muxed2(&mux2, 0x12345678u);
	decode_can_0x692_muxed2(&mux2, &muxed2);
	CHECK(muxed2 == 0x12345678u);

	return 0;
}
