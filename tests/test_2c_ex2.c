#include "../out/test_c/ex2.h"
#include "test_2c_common.h"

int test_2c_ex2(void) {
	CHECK(CAN_DLC_DYNLOC == 8u);
	CHECK(CAN_DLC_DYNOCOOLANTFLOW == 4u);
	CHECK(message_dlc_can2(CAN_ID_DYNLOC) == 8);
	CHECK(message_dlc_can2(CAN_ID_DYNOCOOLANTFLOW) == 4);

	can_0x064_DynLoc_obj_t dynloc = {0};
	float speed = 0.0f, torque = 0.0f;

	encode_can_0x064_speed(&dynloc, 87.5f);
	encode_can_0x064_torque(&dynloc, -13.25f);
	decode_can_0x064_speed(&dynloc, &speed);
	decode_can_0x064_torque(&dynloc, &torque);
	CHECK(check_float_eq(speed, 87.5f, 1e-6f));
	CHECK(check_float_eq(torque, -13.25f, 1e-6f));

	can_0x401_WS200Status_obj_t status = {0};
	uint16_t limit_flags = 0, error_flags = 0, active_motor = 0;
	uint8_t tx_errors = 0, rx_errors = 0;

	encode_can_0x401_limit_flags(&status, 0x0123u);
	encode_can_0x401_error_flags(&status, 0x0456u);
	encode_can_0x401_active_motor(&status, 2u);
	encode_can_0x401_transmit_error_count(&status, 7u);
	encode_can_0x401_receive_error_count(&status, 9u);
	decode_can_0x401_limit_flags(&status, &limit_flags);
	decode_can_0x401_error_flags(&status, &error_flags);
	decode_can_0x401_active_motor(&status, &active_motor);
	decode_can_0x401_transmit_error_count(&status, &tx_errors);
	decode_can_0x401_receive_error_count(&status, &rx_errors);
	CHECK(limit_flags == 0x0123u);
	CHECK(error_flags == 0x0456u);
	CHECK(active_motor == 2u);
	CHECK(tx_errors == 7u);
	CHECK(rx_errors == 9u);

	can_0x402_WS200BusMeasurement_obj_t bus = {0};
	float bus_voltage = 0.0f, bus_current = 0.0f;

	encode_can_0x402_bus_voltage(&bus, 410.75f);
	encode_can_0x402_bus_current(&bus, 15.5f);
	decode_can_0x402_bus_voltage(&bus, &bus_voltage);
	decode_can_0x402_bus_current(&bus, &bus_current);
	CHECK(check_float_eq(bus_voltage, 410.75f, 1e-6f));
	CHECK(check_float_eq(bus_current, 15.5f, 1e-6f));

	can_0x417_WS200SlipSpeed_obj_t slip = {0};
	float slip_speed = 0.0f, reserved_2 = 0.0f;

	encode_can_0x417_slip_speed(&slip, 1.5f);
	encode_can_0x417_reserved_2(&slip, -0.5f);
	decode_can_0x417_slip_speed(&slip, &slip_speed);
	decode_can_0x417_reserved_2(&slip, &reserved_2);
	CHECK(check_float_eq(slip_speed, 1.5f, 1e-6f));
	CHECK(check_float_eq(reserved_2, -0.5f, 1e-6f));

	return 0;
}
