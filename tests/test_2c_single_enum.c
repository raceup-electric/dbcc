#include "../out/test_c/single_enum.h"
#include "test_2c_common.h"

int test_2c_single_enum(void) {
	CHECK(CAN_DLC_ENUM1 == 8u);
	CHECK(CAN_DLC_IVTSLEEPACK == 1u);
	CHECK(message_dlc_can2(CAN_ID_ENUM1) == 8);
	CHECK(message_dlc_can2(CAN_ID_IVTSLEEPACK) == 1);

	can_0x001_Enum1_obj_t enum1 = {0};
	can_0x003_IVTCtrl_obj_t ivtctrl = {0};
	can_0x004_Enum2_obj_t enum2 = {0};
	can_0x122_IVTSleepAck_obj_t ack = {0};
	can_0x001_Enum1_state_e enum1_out = CAN_0X001_ENUM1_STATE_INACTIVE;
	uint8_t fuse_out = 0, enum2_out = 0;
	int8_t ack_out = 0;

	encode_0x001_state(&enum1, CAN_0X001_ENUM1_STATE_ACTIVE);
	decode_0x001_state(&enum1, &enum1_out);
	CHECK(enum1_out == CAN_0X001_ENUM1_STATE_ACTIVE);

	encode_0x003_ivt_ctrl_fuse_state(&ivtctrl, 1u);
	decode_0x003_ivt_ctrl_fuse_state(&ivtctrl, &fuse_out);
	CHECK(fuse_out == 1u);

	encode_0x004_state(&enum2, 3u);
	decode_0x004_state(&enum2, &enum2_out);
	CHECK(enum2_out == 3u);

	encode_0x122_ivt_sleep_ack(&ack, 5);
	decode_0x122_ivt_sleep_ack(&ack, &ack_out);
	CHECK(ack_out == 5);

	return 0;
}
