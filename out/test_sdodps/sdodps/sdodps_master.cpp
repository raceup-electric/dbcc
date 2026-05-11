/* SDO_DPS C++ support: automatically generated - do not edit. */

#include "sdodps_master.hpp"

#include <cstring>

namespace sdodps {

static std::uint64_t sdodps_mask(unsigned bit_length) {
	return bit_length >= 64u ? 0xffffffffffffffffULL : ((1ULL << bit_length) - 1ULL);
}

static std::uint64_t sdodps_get_bits(std::uint64_t payload, unsigned start, unsigned bit_length) {
	return (payload >> start) & sdodps_mask(bit_length);
}

static void sdodps_set_bits(std::uint64_t *payload, unsigned start, unsigned bit_length, std::uint64_t value) {
	const std::uint64_t mask = sdodps_mask(bit_length);
	*payload = (*payload & ~(mask << start)) | ((value & mask) << start);
}

static Frame sdodps_make_frame(std::uint32_t id, Opcode opcode, std::uint16_t var_id, std::uint8_t flags, std::uint64_t value, unsigned bit_length) {
	Frame frame { id, 7u, 0u };
	sdodps_set_bits(&frame.payload, 0u, 8u, static_cast<std::uint8_t>(opcode));
	sdodps_set_bits(&frame.payload, 8u, 10u, var_id);
	sdodps_set_bits(&frame.payload, 18u, 6u, flags);
	sdodps_set_bits(&frame.payload, 24u, bit_length, value);
	return frame;
}

const char *to_string(PcuVar value) {
	switch (value) {
	case PcuVar::dbc_hash: return "dbc_hash";
	case PcuVar::send_asms: return "send_asms";
	case PcuVar::Kp_batt: return "Kp_batt";
	case PcuVar::Ki_batt: return "Ki_batt";
	case PcuVar::T_0_batt: return "T_0_batt";
	case PcuVar::T_100_batt: return "T_100_batt";
	case PcuVar::droni_perf: return "droni_perf";
	case PcuVar::pump_l_max: return "pump_l_max";
	case PcuVar::pump_r_max: return "pump_r_max";
	case PcuVar::rain_mode: return "rain_mode";
	case PcuVar::limit_fan_curr: return "limit_fan_curr";
	case PcuVar::debug_sense: return "debug_sense";
	}
	return "unknown";
}

const char *to_string(McuVar value) {
	switch (value) {
	case McuVar::dbc_hash: return "dbc_hash";
	case McuVar::is_pos_torque_allowed: return "is_pos_torque_allowed";
	case McuVar::is_neg_torque_allowed: return "is_neg_torque_allowed";
	case McuVar::motor_max_torque: return "motor_max_torque";
	case McuVar::lim_pos_torque: return "lim_pos_torque";
	case McuVar::lim_neg_torque: return "lim_neg_torque";
	case McuVar::lim_rpm: return "lim_rpm";
	case McuVar::speed_limitation: return "speed_limitation";
	case McuVar::scs_active: return "scs_active";
	case McuVar::scs_monitor_bmsLv: return "scs_monitor_bmsLv";
	case McuVar::scs_monitor_bmsHv: return "scs_monitor_bmsHv";
	case McuVar::scs_monitor_ebs: return "scs_monitor_ebs";
	case McuVar::serial_core_usb: return "serial_core_usb";
	}
	return "unknown";
}

static std::uint32_t sdodps_decode_pcu_dbc_hash(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t value = static_cast<std::uint32_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_dbc_hash(std::uint32_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(32u);
}

static std::uint8_t sdodps_decode_pcu_send_asms(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_send_asms(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static float sdodps_decode_pcu_Kp_batt(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t raw = static_cast<std::uint32_t>(x);
	float unpacked;
	std::memcpy(&unpacked, &raw, sizeof(unpacked));
	float value = static_cast<float>(unpacked);
	return value;
}

static std::uint64_t sdodps_encode_pcu_Kp_batt(float in) {
	float wire = static_cast<float>(in);
	std::uint32_t raw;
	std::memcpy(&raw, &wire, sizeof(raw));
	return static_cast<std::uint64_t>(raw) & sdodps_mask(32u);
}

static float sdodps_decode_pcu_Ki_batt(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t raw = static_cast<std::uint32_t>(x);
	float unpacked;
	std::memcpy(&unpacked, &raw, sizeof(unpacked));
	float value = static_cast<float>(unpacked);
	return value;
}

static std::uint64_t sdodps_encode_pcu_Ki_batt(float in) {
	float wire = static_cast<float>(in);
	std::uint32_t raw;
	std::memcpy(&raw, &wire, sizeof(raw));
	return static_cast<std::uint64_t>(raw) & sdodps_mask(32u);
}

static float sdodps_decode_pcu_T_0_batt(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t raw = static_cast<std::uint32_t>(x);
	float unpacked;
	std::memcpy(&unpacked, &raw, sizeof(unpacked));
	float value = static_cast<float>(unpacked);
	return value;
}

static std::uint64_t sdodps_encode_pcu_T_0_batt(float in) {
	float wire = static_cast<float>(in);
	std::uint32_t raw;
	std::memcpy(&raw, &wire, sizeof(raw));
	return static_cast<std::uint64_t>(raw) & sdodps_mask(32u);
}

static float sdodps_decode_pcu_T_100_batt(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t raw = static_cast<std::uint32_t>(x);
	float unpacked;
	std::memcpy(&unpacked, &raw, sizeof(unpacked));
	float value = static_cast<float>(unpacked);
	return value;
}

static std::uint64_t sdodps_encode_pcu_T_100_batt(float in) {
	float wire = static_cast<float>(in);
	std::uint32_t raw;
	std::memcpy(&raw, &wire, sizeof(raw));
	return static_cast<std::uint64_t>(raw) & sdodps_mask(32u);
}

static std::uint8_t sdodps_decode_pcu_droni_perf(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 8u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_droni_perf(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(8u);
}

static std::uint8_t sdodps_decode_pcu_pump_l_max(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 8u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_pump_l_max(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(8u);
}

static std::uint8_t sdodps_decode_pcu_pump_r_max(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 8u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_pump_r_max(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(8u);
}

static std::uint8_t sdodps_decode_pcu_rain_mode(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_rain_mode(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint8_t sdodps_decode_pcu_limit_fan_curr(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_limit_fan_curr(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint8_t sdodps_decode_pcu_debug_sense(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_pcu_debug_sense(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint32_t sdodps_decode_mcu_dbc_hash(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t value = static_cast<std::uint32_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_dbc_hash(std::uint32_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(32u);
}

static std::uint8_t sdodps_decode_mcu_is_pos_torque_allowed(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_is_pos_torque_allowed(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint8_t sdodps_decode_mcu_is_neg_torque_allowed(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_is_neg_torque_allowed(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static float sdodps_decode_mcu_motor_max_torque(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t raw = static_cast<std::uint32_t>(x);
	float unpacked;
	std::memcpy(&unpacked, &raw, sizeof(unpacked));
	float value = static_cast<float>(unpacked);
	return value;
}

static std::uint64_t sdodps_encode_mcu_motor_max_torque(float in) {
	float wire = static_cast<float>(in);
	std::uint32_t raw;
	std::memcpy(&raw, &wire, sizeof(raw));
	return static_cast<std::uint64_t>(raw) & sdodps_mask(32u);
}

static float sdodps_decode_mcu_lim_pos_torque(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t raw = static_cast<std::uint32_t>(x);
	float unpacked;
	std::memcpy(&unpacked, &raw, sizeof(unpacked));
	float value = static_cast<float>(unpacked);
	return value;
}

static std::uint64_t sdodps_encode_mcu_lim_pos_torque(float in) {
	float wire = static_cast<float>(in);
	std::uint32_t raw;
	std::memcpy(&raw, &wire, sizeof(raw));
	return static_cast<std::uint64_t>(raw) & sdodps_mask(32u);
}

static float sdodps_decode_mcu_lim_neg_torque(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 32u);
	std::uint32_t raw = static_cast<std::uint32_t>(x);
	float unpacked;
	std::memcpy(&unpacked, &raw, sizeof(unpacked));
	float value = static_cast<float>(unpacked);
	return value;
}

static std::uint64_t sdodps_encode_mcu_lim_neg_torque(float in) {
	float wire = static_cast<float>(in);
	std::uint32_t raw;
	std::memcpy(&raw, &wire, sizeof(raw));
	return static_cast<std::uint64_t>(raw) & sdodps_mask(32u);
}

static std::uint16_t sdodps_decode_mcu_lim_rpm(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 16u);
	std::uint16_t value = static_cast<std::uint16_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_lim_rpm(std::uint16_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(16u);
}

static std::uint16_t sdodps_decode_mcu_speed_limitation(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 16u);
	std::uint16_t value = static_cast<std::uint16_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_speed_limitation(std::uint16_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(16u);
}

static std::uint8_t sdodps_decode_mcu_scs_active(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_scs_active(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint8_t sdodps_decode_mcu_scs_monitor_bmsLv(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_scs_monitor_bmsLv(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint8_t sdodps_decode_mcu_scs_monitor_bmsHv(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_scs_monitor_bmsHv(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint8_t sdodps_decode_mcu_scs_monitor_ebs(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 1u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_scs_monitor_ebs(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(1u);
}

static std::uint8_t sdodps_decode_mcu_serial_core_usb(std::uint64_t payload) {
	std::uint64_t x = sdodps_get_bits(payload, 24u, 8u);
	std::uint8_t value = static_cast<std::uint8_t>(x);
	return value;
}

static std::uint64_t sdodps_encode_mcu_serial_core_usb(std::uint8_t in) {
	return static_cast<std::uint64_t>(in) & sdodps_mask(8u);
}

Master::Master() = default;

void Master::set_tx_callback(TxCallback cb) {
	tx_ = cb;
}

void Master::set_value_hook(ValueHook cb) {
	value_hook_ = cb;
}

bool Master::send(std::uint32_t id, Opcode opcode, std::uint16_t var_id, std::uint64_t raw_value, unsigned bit_length) {
	if (!tx_) return false;
	const Frame frame = sdodps_make_frame(id, opcode, var_id, 0u, raw_value, bit_length);
	return tx_(frame.id, frame.dlc, frame.payload);
}

void Master::set_expected_pcu_hash(std::uint32_t expected) {
	pcu_.expected_hash = expected;
	pcu_.has_expected_hash = true;
	pcu_.hash_verified = false;
}

bool Master::pcu_hash_verified() const {
	return pcu_.hash_verified;
}

unsigned Master::pcu_bit_length(PcuVar var) {
	switch (var) {
	case PcuVar::dbc_hash: return 32u;
	case PcuVar::send_asms: return 1u;
	case PcuVar::Kp_batt: return 32u;
	case PcuVar::Ki_batt: return 32u;
	case PcuVar::T_0_batt: return 32u;
	case PcuVar::T_100_batt: return 32u;
	case PcuVar::droni_perf: return 8u;
	case PcuVar::pump_l_max: return 8u;
	case PcuVar::pump_r_max: return 8u;
	case PcuVar::rain_mode: return 1u;
	case PcuVar::limit_fan_curr: return 1u;
	case PcuVar::debug_sense: return 1u;
	}
	return 0u;
}

bool Master::request_pcu(PcuVar var) {
	if (var != PcuVar::dbc_hash && !pcu_.hash_verified) return false;
	return send(SDOPcu_CAN_ID, Opcode::GET_REQ, static_cast<std::uint16_t>(var), 0u, pcu_bit_length(var));
}

bool Master::has_pcu_value(PcuVar var) const {
	if (var != PcuVar::dbc_hash && !pcu_.hash_verified) return false;
	switch (var) {
	case PcuVar::dbc_hash: return pcu_.has_new_dbc_hash;
	case PcuVar::send_asms: return pcu_.has_new_send_asms;
	case PcuVar::Kp_batt: return pcu_.has_new_Kp_batt;
	case PcuVar::Ki_batt: return pcu_.has_new_Ki_batt;
	case PcuVar::T_0_batt: return pcu_.has_new_T_0_batt;
	case PcuVar::T_100_batt: return pcu_.has_new_T_100_batt;
	case PcuVar::droni_perf: return pcu_.has_new_droni_perf;
	case PcuVar::pump_l_max: return pcu_.has_new_pump_l_max;
	case PcuVar::pump_r_max: return pcu_.has_new_pump_r_max;
	case PcuVar::rain_mode: return pcu_.has_new_rain_mode;
	case PcuVar::limit_fan_curr: return pcu_.has_new_limit_fan_curr;
	case PcuVar::debug_sense: return pcu_.has_new_debug_sense;
	}
	return false;
}

bool Master::set_pcu_dbc_hash(std::uint32_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 0u, sdodps_encode_pcu_dbc_hash(value), 32u);
}

bool Master::take_pcu_dbc_hash(std::uint32_t *out) {
	if (!out || !pcu_.has_new_dbc_hash) return false;
	*out = pcu_.dbc_hash;
	pcu_.has_new_dbc_hash = false;
	pcu_.hash_verified = pcu_.has_expected_hash && (*out == pcu_.expected_hash);
	return true;
}

bool Master::set_pcu_send_asms(std::uint8_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 1u, sdodps_encode_pcu_send_asms(value), 1u);
}

bool Master::take_pcu_send_asms(std::uint8_t *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_send_asms) return false;
	*out = pcu_.send_asms;
	pcu_.has_new_send_asms = false;
	return true;
}

bool Master::set_pcu_Kp_batt(float value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 2u, sdodps_encode_pcu_Kp_batt(value), 32u);
}

bool Master::take_pcu_Kp_batt(float *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_Kp_batt) return false;
	*out = pcu_.Kp_batt;
	pcu_.has_new_Kp_batt = false;
	return true;
}

bool Master::set_pcu_Ki_batt(float value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 3u, sdodps_encode_pcu_Ki_batt(value), 32u);
}

bool Master::take_pcu_Ki_batt(float *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_Ki_batt) return false;
	*out = pcu_.Ki_batt;
	pcu_.has_new_Ki_batt = false;
	return true;
}

bool Master::set_pcu_T_0_batt(float value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 4u, sdodps_encode_pcu_T_0_batt(value), 32u);
}

bool Master::take_pcu_T_0_batt(float *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_T_0_batt) return false;
	*out = pcu_.T_0_batt;
	pcu_.has_new_T_0_batt = false;
	return true;
}

bool Master::set_pcu_T_100_batt(float value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 5u, sdodps_encode_pcu_T_100_batt(value), 32u);
}

bool Master::take_pcu_T_100_batt(float *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_T_100_batt) return false;
	*out = pcu_.T_100_batt;
	pcu_.has_new_T_100_batt = false;
	return true;
}

bool Master::set_pcu_droni_perf(std::uint8_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 6u, sdodps_encode_pcu_droni_perf(value), 8u);
}

bool Master::take_pcu_droni_perf(std::uint8_t *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_droni_perf) return false;
	*out = pcu_.droni_perf;
	pcu_.has_new_droni_perf = false;
	return true;
}

bool Master::set_pcu_pump_l_max(std::uint8_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 7u, sdodps_encode_pcu_pump_l_max(value), 8u);
}

bool Master::take_pcu_pump_l_max(std::uint8_t *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_pump_l_max) return false;
	*out = pcu_.pump_l_max;
	pcu_.has_new_pump_l_max = false;
	return true;
}

bool Master::set_pcu_pump_r_max(std::uint8_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 8u, sdodps_encode_pcu_pump_r_max(value), 8u);
}

bool Master::take_pcu_pump_r_max(std::uint8_t *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_pump_r_max) return false;
	*out = pcu_.pump_r_max;
	pcu_.has_new_pump_r_max = false;
	return true;
}

bool Master::set_pcu_rain_mode(std::uint8_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 9u, sdodps_encode_pcu_rain_mode(value), 1u);
}

bool Master::take_pcu_rain_mode(std::uint8_t *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_rain_mode) return false;
	*out = pcu_.rain_mode;
	pcu_.has_new_rain_mode = false;
	return true;
}

bool Master::set_pcu_limit_fan_curr(std::uint8_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 10u, sdodps_encode_pcu_limit_fan_curr(value), 1u);
}

bool Master::take_pcu_limit_fan_curr(std::uint8_t *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_limit_fan_curr) return false;
	*out = pcu_.limit_fan_curr;
	pcu_.has_new_limit_fan_curr = false;
	return true;
}

bool Master::set_pcu_debug_sense(std::uint8_t value) {
	return send(SDOPcu_CAN_ID, Opcode::SET_REQ, 11u, sdodps_encode_pcu_debug_sense(value), 1u);
}

bool Master::take_pcu_debug_sense(std::uint8_t *out) {
	if (!pcu_.hash_verified) return false;
	if (!out || !pcu_.has_new_debug_sense) return false;
	*out = pcu_.debug_sense;
	pcu_.has_new_debug_sense = false;
	return true;
}

void Master::set_expected_mcu_hash(std::uint32_t expected) {
	mcu_.expected_hash = expected;
	mcu_.has_expected_hash = true;
	mcu_.hash_verified = false;
}

bool Master::mcu_hash_verified() const {
	return mcu_.hash_verified;
}

unsigned Master::mcu_bit_length(McuVar var) {
	switch (var) {
	case McuVar::dbc_hash: return 32u;
	case McuVar::is_pos_torque_allowed: return 1u;
	case McuVar::is_neg_torque_allowed: return 1u;
	case McuVar::motor_max_torque: return 32u;
	case McuVar::lim_pos_torque: return 32u;
	case McuVar::lim_neg_torque: return 32u;
	case McuVar::lim_rpm: return 16u;
	case McuVar::speed_limitation: return 16u;
	case McuVar::scs_active: return 1u;
	case McuVar::scs_monitor_bmsLv: return 1u;
	case McuVar::scs_monitor_bmsHv: return 1u;
	case McuVar::scs_monitor_ebs: return 1u;
	case McuVar::serial_core_usb: return 8u;
	}
	return 0u;
}

bool Master::request_mcu(McuVar var) {
	if (var != McuVar::dbc_hash && !mcu_.hash_verified) return false;
	return send(SDOMcu_CAN_ID, Opcode::GET_REQ, static_cast<std::uint16_t>(var), 0u, mcu_bit_length(var));
}

bool Master::has_mcu_value(McuVar var) const {
	if (var != McuVar::dbc_hash && !mcu_.hash_verified) return false;
	switch (var) {
	case McuVar::dbc_hash: return mcu_.has_new_dbc_hash;
	case McuVar::is_pos_torque_allowed: return mcu_.has_new_is_pos_torque_allowed;
	case McuVar::is_neg_torque_allowed: return mcu_.has_new_is_neg_torque_allowed;
	case McuVar::motor_max_torque: return mcu_.has_new_motor_max_torque;
	case McuVar::lim_pos_torque: return mcu_.has_new_lim_pos_torque;
	case McuVar::lim_neg_torque: return mcu_.has_new_lim_neg_torque;
	case McuVar::lim_rpm: return mcu_.has_new_lim_rpm;
	case McuVar::speed_limitation: return mcu_.has_new_speed_limitation;
	case McuVar::scs_active: return mcu_.has_new_scs_active;
	case McuVar::scs_monitor_bmsLv: return mcu_.has_new_scs_monitor_bmsLv;
	case McuVar::scs_monitor_bmsHv: return mcu_.has_new_scs_monitor_bmsHv;
	case McuVar::scs_monitor_ebs: return mcu_.has_new_scs_monitor_ebs;
	case McuVar::serial_core_usb: return mcu_.has_new_serial_core_usb;
	}
	return false;
}

bool Master::set_mcu_dbc_hash(std::uint32_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 0u, sdodps_encode_mcu_dbc_hash(value), 32u);
}

bool Master::take_mcu_dbc_hash(std::uint32_t *out) {
	if (!out || !mcu_.has_new_dbc_hash) return false;
	*out = mcu_.dbc_hash;
	mcu_.has_new_dbc_hash = false;
	mcu_.hash_verified = mcu_.has_expected_hash && (*out == mcu_.expected_hash);
	return true;
}

bool Master::set_mcu_is_pos_torque_allowed(std::uint8_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 1u, sdodps_encode_mcu_is_pos_torque_allowed(value), 1u);
}

bool Master::take_mcu_is_pos_torque_allowed(std::uint8_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_is_pos_torque_allowed) return false;
	*out = mcu_.is_pos_torque_allowed;
	mcu_.has_new_is_pos_torque_allowed = false;
	return true;
}

bool Master::set_mcu_is_neg_torque_allowed(std::uint8_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 2u, sdodps_encode_mcu_is_neg_torque_allowed(value), 1u);
}

bool Master::take_mcu_is_neg_torque_allowed(std::uint8_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_is_neg_torque_allowed) return false;
	*out = mcu_.is_neg_torque_allowed;
	mcu_.has_new_is_neg_torque_allowed = false;
	return true;
}

bool Master::set_mcu_motor_max_torque(float value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 3u, sdodps_encode_mcu_motor_max_torque(value), 32u);
}

bool Master::take_mcu_motor_max_torque(float *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_motor_max_torque) return false;
	*out = mcu_.motor_max_torque;
	mcu_.has_new_motor_max_torque = false;
	return true;
}

bool Master::set_mcu_lim_pos_torque(float value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 4u, sdodps_encode_mcu_lim_pos_torque(value), 32u);
}

bool Master::take_mcu_lim_pos_torque(float *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_lim_pos_torque) return false;
	*out = mcu_.lim_pos_torque;
	mcu_.has_new_lim_pos_torque = false;
	return true;
}

bool Master::set_mcu_lim_neg_torque(float value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 5u, sdodps_encode_mcu_lim_neg_torque(value), 32u);
}

bool Master::take_mcu_lim_neg_torque(float *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_lim_neg_torque) return false;
	*out = mcu_.lim_neg_torque;
	mcu_.has_new_lim_neg_torque = false;
	return true;
}

bool Master::set_mcu_lim_rpm(std::uint16_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 6u, sdodps_encode_mcu_lim_rpm(value), 16u);
}

bool Master::take_mcu_lim_rpm(std::uint16_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_lim_rpm) return false;
	*out = mcu_.lim_rpm;
	mcu_.has_new_lim_rpm = false;
	return true;
}

bool Master::set_mcu_speed_limitation(std::uint16_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 7u, sdodps_encode_mcu_speed_limitation(value), 16u);
}

bool Master::take_mcu_speed_limitation(std::uint16_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_speed_limitation) return false;
	*out = mcu_.speed_limitation;
	mcu_.has_new_speed_limitation = false;
	return true;
}

bool Master::set_mcu_scs_active(std::uint8_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 8u, sdodps_encode_mcu_scs_active(value), 1u);
}

bool Master::take_mcu_scs_active(std::uint8_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_scs_active) return false;
	*out = mcu_.scs_active;
	mcu_.has_new_scs_active = false;
	return true;
}

bool Master::set_mcu_scs_monitor_bmsLv(std::uint8_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 9u, sdodps_encode_mcu_scs_monitor_bmsLv(value), 1u);
}

bool Master::take_mcu_scs_monitor_bmsLv(std::uint8_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_scs_monitor_bmsLv) return false;
	*out = mcu_.scs_monitor_bmsLv;
	mcu_.has_new_scs_monitor_bmsLv = false;
	return true;
}

bool Master::set_mcu_scs_monitor_bmsHv(std::uint8_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 10u, sdodps_encode_mcu_scs_monitor_bmsHv(value), 1u);
}

bool Master::take_mcu_scs_monitor_bmsHv(std::uint8_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_scs_monitor_bmsHv) return false;
	*out = mcu_.scs_monitor_bmsHv;
	mcu_.has_new_scs_monitor_bmsHv = false;
	return true;
}

bool Master::set_mcu_scs_monitor_ebs(std::uint8_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 11u, sdodps_encode_mcu_scs_monitor_ebs(value), 1u);
}

bool Master::take_mcu_scs_monitor_ebs(std::uint8_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_scs_monitor_ebs) return false;
	*out = mcu_.scs_monitor_ebs;
	mcu_.has_new_scs_monitor_ebs = false;
	return true;
}

bool Master::set_mcu_serial_core_usb(std::uint8_t value) {
	return send(SDOMcu_CAN_ID, Opcode::SET_REQ, 12u, sdodps_encode_mcu_serial_core_usb(value), 8u);
}

bool Master::take_mcu_serial_core_usb(std::uint8_t *out) {
	if (!mcu_.hash_verified) return false;
	if (!out || !mcu_.has_new_serial_core_usb) return false;
	*out = mcu_.serial_core_usb;
	mcu_.has_new_serial_core_usb = false;
	return true;
}

bool Master::process_pcu_response(std::uint32_t id, std::uint64_t payload) {
	const PcuVar var = static_cast<PcuVar>(sdodps_get_bits(payload, 8u, 10u));
	switch (var) {
	case PcuVar::dbc_hash:
		pcu_.dbc_hash = sdodps_decode_pcu_dbc_hash(payload);
		pcu_.has_new_dbc_hash = true;
		pcu_.hash_verified = false;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::send_asms:
		pcu_.send_asms = sdodps_decode_pcu_send_asms(payload);
		pcu_.has_new_send_asms = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::Kp_batt:
		pcu_.Kp_batt = sdodps_decode_pcu_Kp_batt(payload);
		pcu_.has_new_Kp_batt = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::Ki_batt:
		pcu_.Ki_batt = sdodps_decode_pcu_Ki_batt(payload);
		pcu_.has_new_Ki_batt = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::T_0_batt:
		pcu_.T_0_batt = sdodps_decode_pcu_T_0_batt(payload);
		pcu_.has_new_T_0_batt = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::T_100_batt:
		pcu_.T_100_batt = sdodps_decode_pcu_T_100_batt(payload);
		pcu_.has_new_T_100_batt = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::droni_perf:
		pcu_.droni_perf = sdodps_decode_pcu_droni_perf(payload);
		pcu_.has_new_droni_perf = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::pump_l_max:
		pcu_.pump_l_max = sdodps_decode_pcu_pump_l_max(payload);
		pcu_.has_new_pump_l_max = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::pump_r_max:
		pcu_.pump_r_max = sdodps_decode_pcu_pump_r_max(payload);
		pcu_.has_new_pump_r_max = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::rain_mode:
		pcu_.rain_mode = sdodps_decode_pcu_rain_mode(payload);
		pcu_.has_new_rain_mode = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::limit_fan_curr:
		pcu_.limit_fan_curr = sdodps_decode_pcu_limit_fan_curr(payload);
		pcu_.has_new_limit_fan_curr = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case PcuVar::debug_sense:
		pcu_.debug_sense = sdodps_decode_pcu_debug_sense(payload);
		pcu_.has_new_debug_sense = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	}
	return false;
}

bool Master::process_mcu_response(std::uint32_t id, std::uint64_t payload) {
	const McuVar var = static_cast<McuVar>(sdodps_get_bits(payload, 8u, 10u));
	switch (var) {
	case McuVar::dbc_hash:
		mcu_.dbc_hash = sdodps_decode_mcu_dbc_hash(payload);
		mcu_.has_new_dbc_hash = true;
		mcu_.hash_verified = false;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::is_pos_torque_allowed:
		mcu_.is_pos_torque_allowed = sdodps_decode_mcu_is_pos_torque_allowed(payload);
		mcu_.has_new_is_pos_torque_allowed = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::is_neg_torque_allowed:
		mcu_.is_neg_torque_allowed = sdodps_decode_mcu_is_neg_torque_allowed(payload);
		mcu_.has_new_is_neg_torque_allowed = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::motor_max_torque:
		mcu_.motor_max_torque = sdodps_decode_mcu_motor_max_torque(payload);
		mcu_.has_new_motor_max_torque = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::lim_pos_torque:
		mcu_.lim_pos_torque = sdodps_decode_mcu_lim_pos_torque(payload);
		mcu_.has_new_lim_pos_torque = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::lim_neg_torque:
		mcu_.lim_neg_torque = sdodps_decode_mcu_lim_neg_torque(payload);
		mcu_.has_new_lim_neg_torque = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::lim_rpm:
		mcu_.lim_rpm = sdodps_decode_mcu_lim_rpm(payload);
		mcu_.has_new_lim_rpm = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::speed_limitation:
		mcu_.speed_limitation = sdodps_decode_mcu_speed_limitation(payload);
		mcu_.has_new_speed_limitation = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::scs_active:
		mcu_.scs_active = sdodps_decode_mcu_scs_active(payload);
		mcu_.has_new_scs_active = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::scs_monitor_bmsLv:
		mcu_.scs_monitor_bmsLv = sdodps_decode_mcu_scs_monitor_bmsLv(payload);
		mcu_.has_new_scs_monitor_bmsLv = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::scs_monitor_bmsHv:
		mcu_.scs_monitor_bmsHv = sdodps_decode_mcu_scs_monitor_bmsHv(payload);
		mcu_.has_new_scs_monitor_bmsHv = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::scs_monitor_ebs:
		mcu_.scs_monitor_ebs = sdodps_decode_mcu_scs_monitor_ebs(payload);
		mcu_.has_new_scs_monitor_ebs = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	case McuVar::serial_core_usb:
		mcu_.serial_core_usb = sdodps_decode_mcu_serial_core_usb(payload);
		mcu_.has_new_serial_core_usb = true;
		if (value_hook_) value_hook_(id, static_cast<std::uint16_t>(var));
		return true;
	}
	return false;
}

bool Master::process(std::uint32_t id, std::uint64_t payload) {
	if (static_cast<Opcode>(sdodps_get_bits(payload, 0u, 8u)) != Opcode::RES) return false;
	switch (id) {
	case SDOPcu_CAN_ID: return process_pcu_response(id, payload);
	case SDOMcu_CAN_ID: return process_mcu_response(id, payload);
	}
	return false;
}

} // namespace sdodps
