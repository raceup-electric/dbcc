#include "../out/test_c/enum.h"
#include "test_2c_common.h"

int test_2c_enum(void) {
	can_0x001_Enum1_obj_t enum1 = {0};
	can_0x003_IVTCtrl_obj_t ivtctrl = {0};
	can_0x004_Enum2_obj_t enum2 = {0};
	can_0x122_IVTSleepAck_obj_t ack = {0};
	can_0x001_Enum1_state_e enum1_out = CAN_0X001_ENUM1_STATE_INACTIVE;
	can_0x003_IVTCtrl_ivt_ctrl_fuse_state_e fuse_out = CAN_0X003_IVTCTRL_IVT_CTRL_FUSE_STATE_FUSE_OR_FUSE_OPEN;
	uint8_t enum2_out = 0;
	can_0x122_IVTSleepAck_ivt_sleep_ack_e ack_out = CAN_0X122_IVTSLEEPACK_IVT_SLEEP_ACK_SLEEP_REQUEST_NOT_ACKNOWLEDGED;

	CHECK(sizeof(enum1.payload) == 8u);
	CHECK(sizeof(can_0x001_Enum1_obj_t) == 8u);
	CHECK(sizeof(ack.payload) == 1u);
	CHECK(sizeof(can_0x122_IVTSleepAck_obj_t) == 1u);

	encode_can_0x001_state(&enum1, CAN_0X001_ENUM1_STATE_ACTIVE);
	decode_can_0x001_state(&enum1, &enum1_out);
	CHECK(enum1_out == CAN_0X001_ENUM1_STATE_ACTIVE);

	encode_can_0x003_ivt_ctrl_fuse_state(&ivtctrl, CAN_0X003_IVTCTRL_IVT_CTRL_FUSE_STATE_FUSE_AND_FUSE_CLOSED);
	decode_can_0x003_ivt_ctrl_fuse_state(&ivtctrl, &fuse_out);
	CHECK(fuse_out == CAN_0X003_IVTCTRL_IVT_CTRL_FUSE_STATE_FUSE_AND_FUSE_CLOSED);

	encode_can_0x004_state(&enum2, 7u);
	decode_can_0x004_state(&enum2, &enum2_out);
	CHECK(enum2_out == 7u);

	encode_can_0x122_ivt_sleep_ack(&ack, CAN_0X122_IVTSLEEPACK_IVT_SLEEP_ACK_SLEEP_REQUEST_ACKNOWLEDGED);
	decode_can_0x122_ivt_sleep_ack(&ack, &ack_out);
	CHECK(ack_out == CAN_0X122_IVTSLEEPACK_IVT_SLEEP_ACK_SLEEP_REQUEST_ACKNOWLEDGED);

	return 0;
}
