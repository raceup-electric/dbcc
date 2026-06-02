#include "../out/test_c/ex1.h"
#include "test_2c_common.h"

int test_2c_ex1(void) {
	can_0x028_FrameFaultCommand_obj_t command = {0};
	int32_t command_value = 0;
	uint32_t command_code = 0;

	encode_0x028_FrameFaultCommandValue(&command, -123456);
	encode_0x028_FrameFaultCommandCode(&command, 0x12345678u);
	decode_0x028_FrameFaultCommandValue(&command, &command_value);
	decode_0x028_FrameFaultCommandCode(&command, &command_code);
	CHECK(command_value == -123456);
	CHECK(command_code == 0x12345678u);

	can_0x031_CANMirrorHeatbeart_obj_t heartbeat = {0};
	uint8_t overflow = 0, timeout = 0, can_error = 0, can_status = 0;

	encode_0x031_CANMirrorOverflowCounter(&heartbeat, 42u);
	encode_0x031_Timeout(&heartbeat, 1u);
	encode_0x031_Mirror_can_error(&heartbeat, 1u);
	encode_0x031_Mirror_CANa_Status(&heartbeat, 1u);
	decode_0x031_CANMirrorOverflowCounter(&heartbeat, &overflow);
	decode_0x031_Timeout(&heartbeat, &timeout);
	decode_0x031_Mirror_can_error(&heartbeat, &can_error);
	decode_0x031_Mirror_CANa_Status(&heartbeat, &can_status);
	CHECK(overflow == 42u);
	CHECK(timeout == 1u);
	CHECK(can_error == 1u);
	CHECK(can_status == 1u);

	can_0x29b_MESSAGE_NAME_obj_t motorola_small = {0};
	uint8_t nonsense = 0;

	encode_0x29b_NonsenseSignal(&motorola_small, 5u);
	decode_0x29b_NonsenseSignal(&motorola_small, &nonsense);
	CHECK(nonsense == 5u);

	can_0x402_BusMeasurement_obj_t bus = {0};
	float bus_voltage = 0.0f, bus_current = 0.0f;

	encode_0x402_BusVoltage(&bus, 321.25f);
	encode_0x402_BusCurrent(&bus, -12.75f);
	decode_0x402_BusVoltage(&bus, &bus_voltage);
	decode_0x402_BusCurrent(&bus, &bus_current);
	CHECK(check_float_eq(bus_voltage, 321.25f, 1e-6f));
	CHECK(check_float_eq(bus_current, -12.75f, 1e-6f));

	can_0x501_MotorDriveCommand_obj_t drive = {0};
	float motor_velocity = 0.0f, motor_current = 0.0f;

	encode_0x501_MotorVelocityCommand(&drive, 1024.5f);
	encode_0x501_MotorCurrentCommand(&drive, 0.75f);
	decode_0x501_MotorVelocityCommand(&drive, &motor_velocity);
	decode_0x501_MotorCurrentCommand(&drive, &motor_current);
	CHECK(check_float_eq(motor_velocity, 1024.5f, 1e-6f));
	CHECK(check_float_eq(motor_current, 0.75f, 1e-6f));

	can_0x8501930_Odometer_Velocity_obj_t odometer = {0};
	int32_t odometer_velocity = 0;

	encode_0x8501930_Odometer_Velocity(&odometer, 123456789);
	decode_0x8501930_Odometer_Velocity(&odometer, &odometer_velocity);
	CHECK(odometer_velocity == 123456789);

	can_0xcc0016e_MagicCanNode1RHeartbeat_obj_t ext_hb = {0};
	uint16_t flags = 0;

	encode_0xcc0016e_MagicNode1Flags(&ext_hb, 0xa55au);
	decode_0xcc0016e_MagicNode1Flags(&ext_hb, &flags);
	CHECK(flags == 0xa55au);

	return 0;
}
