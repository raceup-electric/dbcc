/* SDO_DPS C++ support: automatically generated - do not edit. */

#ifndef SDODPS_SLAVE_MCU_HPP
#define SDODPS_SLAVE_MCU_HPP

#include "sdodps_master.hpp"

namespace sdodps {

class SlaveMcu {
public:
	using Uint32ReadCallback = bool (*)(std::uint32_t *out);
	using Uint32WriteCallback = bool (*)(std::uint32_t value);
	using Uint8ReadCallback = bool (*)(std::uint8_t *out);
	using Uint8WriteCallback = bool (*)(std::uint8_t value);
	using FloatReadCallback = bool (*)(float *out);
	using FloatWriteCallback = bool (*)(float value);
	using Uint16ReadCallback = bool (*)(std::uint16_t *out);
	using Uint16WriteCallback = bool (*)(std::uint16_t value);

	static void set_tx_callback(TxCallback cb);
	static void set_dbc_hash_reader(Uint32ReadCallback cb);
	static void set_dbc_hash_writer(Uint32WriteCallback cb);
	static Status read_dbc_hash(std::uint32_t *out);
	static Status write_dbc_hash(std::uint32_t value);
	static void set_is_pos_torque_allowed_reader(Uint8ReadCallback cb);
	static void set_is_pos_torque_allowed_writer(Uint8WriteCallback cb);
	static Status read_is_pos_torque_allowed(std::uint8_t *out);
	static Status write_is_pos_torque_allowed(std::uint8_t value);
	static void set_is_neg_torque_allowed_reader(Uint8ReadCallback cb);
	static void set_is_neg_torque_allowed_writer(Uint8WriteCallback cb);
	static Status read_is_neg_torque_allowed(std::uint8_t *out);
	static Status write_is_neg_torque_allowed(std::uint8_t value);
	static void set_motor_max_torque_reader(FloatReadCallback cb);
	static void set_motor_max_torque_writer(FloatWriteCallback cb);
	static Status read_motor_max_torque(float *out);
	static Status write_motor_max_torque(float value);
	static void set_lim_pos_torque_reader(FloatReadCallback cb);
	static void set_lim_pos_torque_writer(FloatWriteCallback cb);
	static Status read_lim_pos_torque(float *out);
	static Status write_lim_pos_torque(float value);
	static void set_lim_neg_torque_reader(FloatReadCallback cb);
	static void set_lim_neg_torque_writer(FloatWriteCallback cb);
	static Status read_lim_neg_torque(float *out);
	static Status write_lim_neg_torque(float value);
	static void set_lim_rpm_reader(Uint16ReadCallback cb);
	static void set_lim_rpm_writer(Uint16WriteCallback cb);
	static Status read_lim_rpm(std::uint16_t *out);
	static Status write_lim_rpm(std::uint16_t value);
	static void set_speed_limitation_reader(Uint16ReadCallback cb);
	static void set_speed_limitation_writer(Uint16WriteCallback cb);
	static Status read_speed_limitation(std::uint16_t *out);
	static Status write_speed_limitation(std::uint16_t value);
	static void set_scs_active_reader(Uint8ReadCallback cb);
	static void set_scs_active_writer(Uint8WriteCallback cb);
	static Status read_scs_active(std::uint8_t *out);
	static Status write_scs_active(std::uint8_t value);
	static void set_scs_monitor_bmsLv_reader(Uint8ReadCallback cb);
	static void set_scs_monitor_bmsLv_writer(Uint8WriteCallback cb);
	static Status read_scs_monitor_bmsLv(std::uint8_t *out);
	static Status write_scs_monitor_bmsLv(std::uint8_t value);
	static void set_scs_monitor_bmsHv_reader(Uint8ReadCallback cb);
	static void set_scs_monitor_bmsHv_writer(Uint8WriteCallback cb);
	static Status read_scs_monitor_bmsHv(std::uint8_t *out);
	static Status write_scs_monitor_bmsHv(std::uint8_t value);
	static void set_scs_monitor_ebs_reader(Uint8ReadCallback cb);
	static void set_scs_monitor_ebs_writer(Uint8WriteCallback cb);
	static Status read_scs_monitor_ebs(std::uint8_t *out);
	static Status write_scs_monitor_ebs(std::uint8_t value);
	static void set_serial_core_usb_reader(Uint8ReadCallback cb);
	static void set_serial_core_usb_writer(Uint8WriteCallback cb);
	static Status read_serial_core_usb(std::uint8_t *out);
	static Status write_serial_core_usb(std::uint8_t value);
	static bool process(std::uint32_t id, std::uint64_t payload);
	static bool notify(McuVar var);

private:
	struct State {
		TxCallback tx = nullptr;
		Uint32ReadCallback dbc_hash_reader = nullptr;
		Uint32WriteCallback dbc_hash_writer = nullptr;
		Uint8ReadCallback is_pos_torque_allowed_reader = nullptr;
		Uint8WriteCallback is_pos_torque_allowed_writer = nullptr;
		Uint8ReadCallback is_neg_torque_allowed_reader = nullptr;
		Uint8WriteCallback is_neg_torque_allowed_writer = nullptr;
		FloatReadCallback motor_max_torque_reader = nullptr;
		FloatWriteCallback motor_max_torque_writer = nullptr;
		FloatReadCallback lim_pos_torque_reader = nullptr;
		FloatWriteCallback lim_pos_torque_writer = nullptr;
		FloatReadCallback lim_neg_torque_reader = nullptr;
		FloatWriteCallback lim_neg_torque_writer = nullptr;
		Uint16ReadCallback lim_rpm_reader = nullptr;
		Uint16WriteCallback lim_rpm_writer = nullptr;
		Uint16ReadCallback speed_limitation_reader = nullptr;
		Uint16WriteCallback speed_limitation_writer = nullptr;
		Uint8ReadCallback scs_active_reader = nullptr;
		Uint8WriteCallback scs_active_writer = nullptr;
		Uint8ReadCallback scs_monitor_bmsLv_reader = nullptr;
		Uint8WriteCallback scs_monitor_bmsLv_writer = nullptr;
		Uint8ReadCallback scs_monitor_bmsHv_reader = nullptr;
		Uint8WriteCallback scs_monitor_bmsHv_writer = nullptr;
		Uint8ReadCallback scs_monitor_ebs_reader = nullptr;
		Uint8WriteCallback scs_monitor_ebs_writer = nullptr;
		Uint8ReadCallback serial_core_usb_reader = nullptr;
		Uint8WriteCallback serial_core_usb_writer = nullptr;
	};

	static State &instance();
	static bool send_response(Opcode opcode, McuVar var, std::uint64_t raw_value);
	static bool process_get(McuVar var);
	static bool process_set(McuVar var, std::uint64_t payload);
};

} // namespace sdodps

#endif
