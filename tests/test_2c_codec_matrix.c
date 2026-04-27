#include "../out/test_c/codec_matrix.h"
#include "test_2c_common.h"

int test_2c_codec_matrix(void) {
	can_0x0c8_MatrixIntelTypes_obj_t intel_types = {0};
	uint16_t u12 = 0;
	double s12 = 0.0;
	uint8_t u8 = 0;
	int8_t s8 = 0;
	val_table_MatrixState_e state = VAL_TABLE_MATRIXSTATE_OFF;
	can_0x0c8_MatrixIntelTypes_inline_enum_e inline_enum = CAN_0X0C8_MATRIXINTELTYPES_INLINE_ENUM_ZERO;

	encode_can_0x0c8_u8(&intel_types, 0xa5u);
	encode_can_0x0c8_s8(&intel_types, -42);
	encode_can_0x0c8_u12(&intel_types, 0x0bceu);
	encode_can_0x0c8_s12(&intel_types, 112.0);
	encode_can_0x0c8_state(&intel_types, VAL_TABLE_MATRIXSTATE_ERROR);
	encode_can_0x0c8_inline_enum(&intel_types, CAN_0X0C8_MATRIXINTELTYPES_INLINE_ENUM_TWO);

	decode_can_0x0c8_u8(&intel_types, &u8);
	decode_can_0x0c8_s8(&intel_types, &s8);
	decode_can_0x0c8_u12(&intel_types, &u12);
	decode_can_0x0c8_s12(&intel_types, &s12);
	decode_can_0x0c8_state(&intel_types, &state);
	decode_can_0x0c8_inline_enum(&intel_types, &inline_enum);

	CHECK(u8 == 0xa5u);
	CHECK(s8 == -42);
	CHECK(u12 == 0x0bceu);
	CHECK(check_double_eq(s12, 112.0, 1e-12));
	CHECK(state == VAL_TABLE_MATRIXSTATE_ERROR);
	CHECK(inline_enum == CAN_0X0C8_MATRIXINTELTYPES_INLINE_ENUM_TWO);

	can_0x0c9_MatrixIntelScaled_obj_t intel_scaled = {0};
	double scale_0p1 = 0.0;
	double scale_0p01_offset_m40 = 0.0;
	double scale_0p5_offset_1p5 = 0.0;

	encode_can_0x0c9_scale_0p1(&intel_scaled, 123.4);
	encode_can_0x0c9_scale_0p01_offset_m40(&intel_scaled, -12.34);
	encode_can_0x0c9_scale_0p5_offset_1p5(&intel_scaled, 17.5);

	decode_can_0x0c9_scale_0p1(&intel_scaled, &scale_0p1);
	decode_can_0x0c9_scale_0p01_offset_m40(&intel_scaled, &scale_0p01_offset_m40);
	decode_can_0x0c9_scale_0p5_offset_1p5(&intel_scaled, &scale_0p5_offset_1p5);

	CHECK(check_double_eq(scale_0p1, 123.4, 1e-9));
	CHECK(check_double_eq(scale_0p01_offset_m40, -12.34, 1e-9));
	CHECK(check_double_eq(scale_0p5_offset_1p5, 17.5, 1e-12));

	can_0x0ca_MatrixMotorolaTypes_obj_t motorola_types = {0};
	uint16_t u12_be = 0;
	double s12_be = 0.0;
	uint8_t u8_be = 0;
	int8_t s8_be = 0;
	val_table_MatrixState_e state_be = VAL_TABLE_MATRIXSTATE_OFF;
	can_0x0ca_MatrixMotorolaTypes_inline_enum_be_e inline_enum_be = CAN_0X0CA_MATRIXMOTOROLATYPES_INLINE_ENUM_BE_ZERO;

	encode_can_0x0ca_u8_be(&motorola_types, 0x5au);
	encode_can_0x0ca_s8_be(&motorola_types, -17);
	encode_can_0x0ca_u12_be(&motorola_types, 0x0456u);
	encode_can_0x0ca_s12_be(&motorola_types, 87.0);
	encode_can_0x0ca_inline_enum_be(&motorola_types, CAN_0X0CA_MATRIXMOTOROLATYPES_INLINE_ENUM_BE_ONE);
	encode_can_0x0ca_state_be(&motorola_types, VAL_TABLE_MATRIXSTATE_ON);

	decode_can_0x0ca_u8_be(&motorola_types, &u8_be);
	decode_can_0x0ca_s8_be(&motorola_types, &s8_be);
	decode_can_0x0ca_u12_be(&motorola_types, &u12_be);
	decode_can_0x0ca_s12_be(&motorola_types, &s12_be);
	decode_can_0x0ca_inline_enum_be(&motorola_types, &inline_enum_be);
	decode_can_0x0ca_state_be(&motorola_types, &state_be);

	CHECK(u8_be == 0x5au);
	CHECK(s8_be == -17);
	CHECK(u12_be == 0x0456u);
	CHECK(check_double_eq(s12_be, 87.0, 1e-12));
	CHECK(inline_enum_be == CAN_0X0CA_MATRIXMOTOROLATYPES_INLINE_ENUM_BE_ONE);
	CHECK(state_be == VAL_TABLE_MATRIXSTATE_ON);

	can_0x0cb_MatrixMotorolaScaled_obj_t motorola_scaled = {0};
	double scale_0p1_be = 0.0;
	double scale_0p01_offset_m40_be = 0.0;
	double scale_0p5_offset_1p5_be = 0.0;

	encode_can_0x0cb_scale_0p1_be(&motorola_scaled, 321.0);
	encode_can_0x0cb_scale_0p01_offset_m40_be(&motorola_scaled, 23.45);
	encode_can_0x0cb_scale_0p5_offset_1p5_be(&motorola_scaled, 51.5);

	decode_can_0x0cb_scale_0p1_be(&motorola_scaled, &scale_0p1_be);
	decode_can_0x0cb_scale_0p01_offset_m40_be(&motorola_scaled, &scale_0p01_offset_m40_be);
	decode_can_0x0cb_scale_0p5_offset_1p5_be(&motorola_scaled, &scale_0p5_offset_1p5_be);

	CHECK(check_double_eq(scale_0p1_be, 321.0, 1e-9));
	CHECK(check_double_eq(scale_0p01_offset_m40_be, 23.45, 1e-9));
	CHECK(check_double_eq(scale_0p5_offset_1p5_be, 51.5, 1e-12));

	can_0x0cc_MatrixFloat_obj_t float_msg = {0};
	float f32 = 0.0f;
	uint32_t raw32 = 0;

	encode_can_0x0cc_f32(&float_msg, -7.25f);
	encode_can_0x0cc_raw32(&float_msg, 0x89abcdefu);
	decode_can_0x0cc_f32(&float_msg, &f32);
	decode_can_0x0cc_raw32(&float_msg, &raw32);
	CHECK(check_float_eq(f32, -7.25f, 1e-6f));
	CHECK(raw32 == 0x89abcdefu);

	can_0x0cd_MatrixDouble_obj_t double_msg = {0};
	double d64 = 0.0;

	encode_can_0x0cd_d64(&double_msg, 9876.54321);
	decode_can_0x0cd_d64(&double_msg, &d64);
	CHECK(check_double_eq(d64, 9876.54321, 1e-12));

	return 0;
}
