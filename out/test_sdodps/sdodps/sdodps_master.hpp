/* SDO_DPS C++ support: automatically generated - do not edit. */

#ifndef SDODPS_MASTER_HPP
#define SDODPS_MASTER_HPP

#include <cstddef>
#include <cstdint>

namespace sdodps {

enum class Opcode : std::uint8_t {
	GET_REQ = 1u,
	SET_REQ = 2u,
	GET_ALL_REQ = 3u,
	RES = 128u,
	ERR_OUT_OF_RANGE = 253u,
	ERR_WRITE_RO = 254u,
	ERR = 255u,
};

enum class Status : std::uint8_t {
	ok,
	unknown_variable,
	read_only,
	no_value,
	tx_missing,
	bad_frame,
};

struct Frame {
	std::uint32_t id;
	std::uint8_t dlc;
	std::uint64_t payload;
};

using TxCallback = bool (*)(std::uint32_t id, std::uint8_t dlc, std::uint64_t payload);
using ValueHook = void (*)(std::uint32_t id, std::uint16_t var_id);

static constexpr std::uint32_t SDOPcu_CAN_ID = 512u;
enum class PcuVar : std::uint16_t {
	dbc_hash = 0u,
	send_asms = 1u,
	Kp_batt = 2u,
	Ki_batt = 3u,
	T_0_batt = 4u,
	T_100_batt = 5u,
	droni_perf = 6u,
	pump_l_max = 7u,
	pump_r_max = 8u,
	rain_mode = 9u,
	limit_fan_curr = 10u,
	debug_sense = 11u,
};
static constexpr std::size_t PcuVarCount = 12u;
const char *to_string(PcuVar value);

static constexpr std::uint32_t SDOMcu_CAN_ID = 513u;
enum class McuVar : std::uint16_t {
	dbc_hash = 0u,
	is_pos_torque_allowed = 1u,
	is_neg_torque_allowed = 2u,
	motor_max_torque = 3u,
	lim_pos_torque = 4u,
	lim_neg_torque = 5u,
	lim_rpm = 6u,
	speed_limitation = 7u,
	scs_active = 8u,
	scs_monitor_bmsLv = 9u,
	scs_monitor_bmsHv = 10u,
	scs_monitor_ebs = 11u,
	serial_core_usb = 12u,
};
static constexpr std::size_t McuVarCount = 13u;
const char *to_string(McuVar value);

class Master {
public:
	Master();
	void set_tx_callback(TxCallback cb);
	void set_value_hook(ValueHook cb);
	bool process(std::uint32_t id, std::uint64_t payload);
	void set_expected_pcu_hash(std::uint32_t expected);
	bool pcu_hash_verified() const;
	static unsigned pcu_bit_length(PcuVar var);
	bool request_pcu(PcuVar var);
	bool has_pcu_value(PcuVar var) const;
	bool set_pcu_dbc_hash(std::uint32_t value);
	bool take_pcu_dbc_hash(std::uint32_t *out);
	bool set_pcu_send_asms(std::uint8_t value);
	bool take_pcu_send_asms(std::uint8_t *out);
	bool set_pcu_Kp_batt(float value);
	bool take_pcu_Kp_batt(float *out);
	bool set_pcu_Ki_batt(float value);
	bool take_pcu_Ki_batt(float *out);
	bool set_pcu_T_0_batt(float value);
	bool take_pcu_T_0_batt(float *out);
	bool set_pcu_T_100_batt(float value);
	bool take_pcu_T_100_batt(float *out);
	bool set_pcu_droni_perf(std::uint8_t value);
	bool take_pcu_droni_perf(std::uint8_t *out);
	bool set_pcu_pump_l_max(std::uint8_t value);
	bool take_pcu_pump_l_max(std::uint8_t *out);
	bool set_pcu_pump_r_max(std::uint8_t value);
	bool take_pcu_pump_r_max(std::uint8_t *out);
	bool set_pcu_rain_mode(std::uint8_t value);
	bool take_pcu_rain_mode(std::uint8_t *out);
	bool set_pcu_limit_fan_curr(std::uint8_t value);
	bool take_pcu_limit_fan_curr(std::uint8_t *out);
	bool set_pcu_debug_sense(std::uint8_t value);
	bool take_pcu_debug_sense(std::uint8_t *out);
	void set_expected_mcu_hash(std::uint32_t expected);
	bool mcu_hash_verified() const;
	static unsigned mcu_bit_length(McuVar var);
	bool request_mcu(McuVar var);
	bool has_mcu_value(McuVar var) const;
	bool set_mcu_dbc_hash(std::uint32_t value);
	bool take_mcu_dbc_hash(std::uint32_t *out);
	bool set_mcu_is_pos_torque_allowed(std::uint8_t value);
	bool take_mcu_is_pos_torque_allowed(std::uint8_t *out);
	bool set_mcu_is_neg_torque_allowed(std::uint8_t value);
	bool take_mcu_is_neg_torque_allowed(std::uint8_t *out);
	bool set_mcu_motor_max_torque(float value);
	bool take_mcu_motor_max_torque(float *out);
	bool set_mcu_lim_pos_torque(float value);
	bool take_mcu_lim_pos_torque(float *out);
	bool set_mcu_lim_neg_torque(float value);
	bool take_mcu_lim_neg_torque(float *out);
	bool set_mcu_lim_rpm(std::uint16_t value);
	bool take_mcu_lim_rpm(std::uint16_t *out);
	bool set_mcu_speed_limitation(std::uint16_t value);
	bool take_mcu_speed_limitation(std::uint16_t *out);
	bool set_mcu_scs_active(std::uint8_t value);
	bool take_mcu_scs_active(std::uint8_t *out);
	bool set_mcu_scs_monitor_bmsLv(std::uint8_t value);
	bool take_mcu_scs_monitor_bmsLv(std::uint8_t *out);
	bool set_mcu_scs_monitor_bmsHv(std::uint8_t value);
	bool take_mcu_scs_monitor_bmsHv(std::uint8_t *out);
	bool set_mcu_scs_monitor_ebs(std::uint8_t value);
	bool take_mcu_scs_monitor_ebs(std::uint8_t *out);
	bool set_mcu_serial_core_usb(std::uint8_t value);
	bool take_mcu_serial_core_usb(std::uint8_t *out);

private:
	TxCallback tx_ = nullptr;
	ValueHook value_hook_ = nullptr;

	struct PcuState {
		std::uint32_t expected_hash = 0u;
		bool has_expected_hash = false;
		bool hash_verified = false;
		std::uint32_t dbc_hash = {};
		bool has_new_dbc_hash = false;
		std::uint8_t send_asms = {};
		bool has_new_send_asms = false;
		float Kp_batt = {};
		bool has_new_Kp_batt = false;
		float Ki_batt = {};
		bool has_new_Ki_batt = false;
		float T_0_batt = {};
		bool has_new_T_0_batt = false;
		float T_100_batt = {};
		bool has_new_T_100_batt = false;
		std::uint8_t droni_perf = {};
		bool has_new_droni_perf = false;
		std::uint8_t pump_l_max = {};
		bool has_new_pump_l_max = false;
		std::uint8_t pump_r_max = {};
		bool has_new_pump_r_max = false;
		std::uint8_t rain_mode = {};
		bool has_new_rain_mode = false;
		std::uint8_t limit_fan_curr = {};
		bool has_new_limit_fan_curr = false;
		std::uint8_t debug_sense = {};
		bool has_new_debug_sense = false;
	};

	struct McuState {
		std::uint32_t expected_hash = 0u;
		bool has_expected_hash = false;
		bool hash_verified = false;
		std::uint32_t dbc_hash = {};
		bool has_new_dbc_hash = false;
		std::uint8_t is_pos_torque_allowed = {};
		bool has_new_is_pos_torque_allowed = false;
		std::uint8_t is_neg_torque_allowed = {};
		bool has_new_is_neg_torque_allowed = false;
		float motor_max_torque = {};
		bool has_new_motor_max_torque = false;
		float lim_pos_torque = {};
		bool has_new_lim_pos_torque = false;
		float lim_neg_torque = {};
		bool has_new_lim_neg_torque = false;
		std::uint16_t lim_rpm = {};
		bool has_new_lim_rpm = false;
		std::uint16_t speed_limitation = {};
		bool has_new_speed_limitation = false;
		std::uint8_t scs_active = {};
		bool has_new_scs_active = false;
		std::uint8_t scs_monitor_bmsLv = {};
		bool has_new_scs_monitor_bmsLv = false;
		std::uint8_t scs_monitor_bmsHv = {};
		bool has_new_scs_monitor_bmsHv = false;
		std::uint8_t scs_monitor_ebs = {};
		bool has_new_scs_monitor_ebs = false;
		std::uint8_t serial_core_usb = {};
		bool has_new_serial_core_usb = false;
	};

	PcuState pcu_;
	bool process_pcu_response(std::uint32_t id, std::uint64_t payload);
	McuState mcu_;
	bool process_mcu_response(std::uint32_t id, std::uint64_t payload);

	bool send(std::uint32_t id, Opcode opcode, std::uint16_t var_id, std::uint64_t raw_value, unsigned bit_length);
};

} // namespace sdodps

#endif
