#include "../out/test_c/bitfield_edge.h"
#include "test_2c_common.h"

int test_2c_bitfield_edge(void) {
	can_0x064_EdgePacked_obj_t packed = {0};
	uint16_t unsigned12 = 0;
	uint8_t byte_a = 0, byte_b = 0, byte_c = 0, byte_d = 0;
	int8_t signed8 = 0, signed3 = 0;
	uint8_t unsigned5 = 0, flag0 = 0, flag1 = 0, flag2 = 0, flag3 = 0;

	encode_can_0x064_unsigned12(&packed, 0x0abcu);
	encode_can_0x064_byte_a(&packed, 0x12u);
	encode_can_0x064_byte_b(&packed, 0x34u);
	encode_can_0x064_byte_c(&packed, 0x56u);
	encode_can_0x064_byte_d(&packed, 0x78u);
	encode_can_0x064_signed8(&packed, -17);
	encode_can_0x064_unsigned5(&packed, 0x15u);
	encode_can_0x064_signed3(&packed, -3);
	encode_can_0x064_flag0(&packed, 1u);
	encode_can_0x064_flag1(&packed, 1u);
	encode_can_0x064_flag2(&packed, 0u);
	encode_can_0x064_flag3(&packed, 1u);

	decode_can_0x064_unsigned12(&packed, &unsigned12);
	decode_can_0x064_byte_a(&packed, &byte_a);
	decode_can_0x064_byte_b(&packed, &byte_b);
	decode_can_0x064_byte_c(&packed, &byte_c);
	decode_can_0x064_byte_d(&packed, &byte_d);
	decode_can_0x064_signed8(&packed, &signed8);
	decode_can_0x064_unsigned5(&packed, &unsigned5);
	decode_can_0x064_signed3(&packed, &signed3);
	decode_can_0x064_flag0(&packed, &flag0);
	decode_can_0x064_flag1(&packed, &flag1);
	decode_can_0x064_flag2(&packed, &flag2);
	decode_can_0x064_flag3(&packed, &flag3);

	CHECK(unsigned12 == 0x0abcu);
	CHECK(byte_a == 0x12u);
	CHECK(byte_b == 0x34u);
	CHECK(byte_c == 0x56u);
	CHECK(byte_d == 0x78u);
	CHECK(signed8 == -17);
	CHECK(unsigned5 == 0x15u);
	CHECK(signed3 == -3);
	CHECK(flag0 == 1u);
	CHECK(flag1 == 1u);
	CHECK(flag2 == 0u);
	CHECK(flag3 == 1u);

	can_0x065_EdgeFloat_obj_t fmsg = {0};
	float f32 = 0.0f;
	uint32_t raw32 = 0;

	encode_can_0x065_f32(&fmsg, 12.5f);
	encode_can_0x065_raw32(&fmsg, 0xdeadbeefu);
	decode_can_0x065_f32(&fmsg, &f32);
	decode_can_0x065_raw32(&fmsg, &raw32);
	CHECK(check_float_eq(f32, 12.5f, 1e-6f));
	CHECK(raw32 == 0xdeadbeefu);

	can_0x066_EdgeDouble_obj_t dmsg = {0};
	double d64 = 0.0;

	encode_can_0x066_d64(&dmsg, -1234.5);
	decode_can_0x066_d64(&dmsg, &d64);
	CHECK(check_double_eq(d64, -1234.5, 1e-12));

	can_0x067_EdgeEnums_obj_t emsg = {0};
	can_0x067_EdgeEnums_inline_enum_e inline_enum = CAN_0X067_EDGEENUMS_INLINE_ENUM_ZERO;
	val_table_ModeTable_e mode = VAL_TABLE_MODETABLE_IDLE;
	val_table_SwitchState_e state = VAL_TABLE_SWITCHSTATE_OFF;

	encode_can_0x067_inline_enum(&emsg, CAN_0X067_EDGEENUMS_INLINE_ENUM_TWO);
	encode_can_0x067_mode(&emsg, VAL_TABLE_MODETABLE_FAULT);
	encode_can_0x067_state(&emsg, VAL_TABLE_SWITCHSTATE_ON);
	decode_can_0x067_inline_enum(&emsg, &inline_enum);
	decode_can_0x067_mode(&emsg, &mode);
	decode_can_0x067_state(&emsg, &state);
	CHECK(inline_enum == CAN_0X067_EDGEENUMS_INLINE_ENUM_TWO);
	CHECK(mode == VAL_TABLE_MODETABLE_FAULT);
	CHECK(state == VAL_TABLE_SWITCHSTATE_ON);

	can_0x068_EdgeMux_obj_t mux_a = {0}, mux_b = {0};
	uint8_t mux = 0, muxed = 0;

	encode_can_0x068_mux(&mux_a, 1u);
	encode_can_0x068_muxed_a(&mux_a, 0x5au);
	decode_can_0x068_mux(&mux_a, &mux);
	decode_can_0x068_muxed_a(&mux_a, &muxed);
	CHECK(mux == 1u);
	CHECK(muxed == 0x5au);

	encode_can_0x068_mux(&mux_b, 2u);
	encode_can_0x068_muxed_b(&mux_b, 0xa5u);
	decode_can_0x068_mux(&mux_b, &mux);
	decode_can_0x068_muxed_b(&mux_b, &muxed);
	CHECK(mux == 2u);
	CHECK(muxed == 0xa5u);

	return 0;
}
