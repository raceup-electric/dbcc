/* SDO_DPS C++ support: automatically generated - do not edit. */

#include "sdodps_slave_mcu.hpp"

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

SlaveMcu::State &SlaveMcu::instance() {
	static State state;
	return state;
}

void SlaveMcu::set_tx_callback(TxCallback cb) {
	instance().tx = cb;
}

void SlaveMcu::set_dbc_hash_reader(Uint32ReadCallback cb) {
	instance().dbc_hash_reader = cb;
}

void SlaveMcu::set_dbc_hash_writer(Uint32WriteCallback cb) {
	instance().dbc_hash_writer = cb;
}

void SlaveMcu::set_is_pos_torque_allowed_reader(Uint8ReadCallback cb) {
	instance().is_pos_torque_allowed_reader = cb;
}

void SlaveMcu::set_is_pos_torque_allowed_writer(Uint8WriteCallback cb) {
	instance().is_pos_torque_allowed_writer = cb;
}

void SlaveMcu::set_is_neg_torque_allowed_reader(Uint8ReadCallback cb) {
	instance().is_neg_torque_allowed_reader = cb;
}

void SlaveMcu::set_is_neg_torque_allowed_writer(Uint8WriteCallback cb) {
	instance().is_neg_torque_allowed_writer = cb;
}

void SlaveMcu::set_motor_max_torque_reader(FloatReadCallback cb) {
	instance().motor_max_torque_reader = cb;
}

void SlaveMcu::set_motor_max_torque_writer(FloatWriteCallback cb) {
	instance().motor_max_torque_writer = cb;
}

void SlaveMcu::set_lim_pos_torque_reader(FloatReadCallback cb) {
	instance().lim_pos_torque_reader = cb;
}

void SlaveMcu::set_lim_pos_torque_writer(FloatWriteCallback cb) {
	instance().lim_pos_torque_writer = cb;
}

void SlaveMcu::set_lim_neg_torque_reader(FloatReadCallback cb) {
	instance().lim_neg_torque_reader = cb;
}

void SlaveMcu::set_lim_neg_torque_writer(FloatWriteCallback cb) {
	instance().lim_neg_torque_writer = cb;
}

void SlaveMcu::set_lim_rpm_reader(Uint16ReadCallback cb) {
	instance().lim_rpm_reader = cb;
}

void SlaveMcu::set_lim_rpm_writer(Uint16WriteCallback cb) {
	instance().lim_rpm_writer = cb;
}

void SlaveMcu::set_speed_limitation_reader(Uint16ReadCallback cb) {
	instance().speed_limitation_reader = cb;
}

void SlaveMcu::set_speed_limitation_writer(Uint16WriteCallback cb) {
	instance().speed_limitation_writer = cb;
}

void SlaveMcu::set_scs_active_reader(Uint8ReadCallback cb) {
	instance().scs_active_reader = cb;
}

void SlaveMcu::set_scs_active_writer(Uint8WriteCallback cb) {
	instance().scs_active_writer = cb;
}

void SlaveMcu::set_scs_monitor_bmsLv_reader(Uint8ReadCallback cb) {
	instance().scs_monitor_bmsLv_reader = cb;
}

void SlaveMcu::set_scs_monitor_bmsLv_writer(Uint8WriteCallback cb) {
	instance().scs_monitor_bmsLv_writer = cb;
}

void SlaveMcu::set_scs_monitor_bmsHv_reader(Uint8ReadCallback cb) {
	instance().scs_monitor_bmsHv_reader = cb;
}

void SlaveMcu::set_scs_monitor_bmsHv_writer(Uint8WriteCallback cb) {
	instance().scs_monitor_bmsHv_writer = cb;
}

void SlaveMcu::set_scs_monitor_ebs_reader(Uint8ReadCallback cb) {
	instance().scs_monitor_ebs_reader = cb;
}

void SlaveMcu::set_scs_monitor_ebs_writer(Uint8WriteCallback cb) {
	instance().scs_monitor_ebs_writer = cb;
}

void SlaveMcu::set_serial_core_usb_reader(Uint8ReadCallback cb) {
	instance().serial_core_usb_reader = cb;
}

void SlaveMcu::set_serial_core_usb_writer(Uint8WriteCallback cb) {
	instance().serial_core_usb_writer = cb;
}

Status SlaveMcu::read_dbc_hash(std::uint32_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.dbc_hash_reader) return Status::no_value;
	return state.dbc_hash_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_dbc_hash(std::uint32_t value) {
	State &state = instance();
	if (!state.dbc_hash_writer) return Status::read_only;
	return state.dbc_hash_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_is_pos_torque_allowed(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.is_pos_torque_allowed_reader) return Status::no_value;
	return state.is_pos_torque_allowed_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_is_pos_torque_allowed(std::uint8_t value) {
	State &state = instance();
	if (!state.is_pos_torque_allowed_writer) return Status::read_only;
	return state.is_pos_torque_allowed_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_is_neg_torque_allowed(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.is_neg_torque_allowed_reader) return Status::no_value;
	return state.is_neg_torque_allowed_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_is_neg_torque_allowed(std::uint8_t value) {
	State &state = instance();
	if (!state.is_neg_torque_allowed_writer) return Status::read_only;
	return state.is_neg_torque_allowed_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_motor_max_torque(float *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.motor_max_torque_reader) return Status::no_value;
	return state.motor_max_torque_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_motor_max_torque(float value) {
	State &state = instance();
	if (!state.motor_max_torque_writer) return Status::read_only;
	return state.motor_max_torque_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_lim_pos_torque(float *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.lim_pos_torque_reader) return Status::no_value;
	return state.lim_pos_torque_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_lim_pos_torque(float value) {
	State &state = instance();
	if (!state.lim_pos_torque_writer) return Status::read_only;
	return state.lim_pos_torque_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_lim_neg_torque(float *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.lim_neg_torque_reader) return Status::no_value;
	return state.lim_neg_torque_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_lim_neg_torque(float value) {
	State &state = instance();
	if (!state.lim_neg_torque_writer) return Status::read_only;
	return state.lim_neg_torque_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_lim_rpm(std::uint16_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.lim_rpm_reader) return Status::no_value;
	return state.lim_rpm_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_lim_rpm(std::uint16_t value) {
	State &state = instance();
	if (!state.lim_rpm_writer) return Status::read_only;
	return state.lim_rpm_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_speed_limitation(std::uint16_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.speed_limitation_reader) return Status::no_value;
	return state.speed_limitation_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_speed_limitation(std::uint16_t value) {
	State &state = instance();
	if (!state.speed_limitation_writer) return Status::read_only;
	return state.speed_limitation_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_scs_active(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.scs_active_reader) return Status::no_value;
	return state.scs_active_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_scs_active(std::uint8_t value) {
	State &state = instance();
	if (!state.scs_active_writer) return Status::read_only;
	return state.scs_active_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_scs_monitor_bmsLv(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.scs_monitor_bmsLv_reader) return Status::no_value;
	return state.scs_monitor_bmsLv_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_scs_monitor_bmsLv(std::uint8_t value) {
	State &state = instance();
	if (!state.scs_monitor_bmsLv_writer) return Status::read_only;
	return state.scs_monitor_bmsLv_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_scs_monitor_bmsHv(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.scs_monitor_bmsHv_reader) return Status::no_value;
	return state.scs_monitor_bmsHv_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_scs_monitor_bmsHv(std::uint8_t value) {
	State &state = instance();
	if (!state.scs_monitor_bmsHv_writer) return Status::read_only;
	return state.scs_monitor_bmsHv_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_scs_monitor_ebs(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.scs_monitor_ebs_reader) return Status::no_value;
	return state.scs_monitor_ebs_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_scs_monitor_ebs(std::uint8_t value) {
	State &state = instance();
	if (!state.scs_monitor_ebs_writer) return Status::read_only;
	return state.scs_monitor_ebs_writer(value) ? Status::ok : Status::no_value;
}

Status SlaveMcu::read_serial_core_usb(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.serial_core_usb_reader) return Status::no_value;
	return state.serial_core_usb_reader(out) ? Status::ok : Status::no_value;
}

Status SlaveMcu::write_serial_core_usb(std::uint8_t value) {
	State &state = instance();
	if (!state.serial_core_usb_writer) return Status::read_only;
	return state.serial_core_usb_writer(value) ? Status::ok : Status::no_value;
}

bool SlaveMcu::send_response(Opcode opcode, McuVar var, std::uint64_t raw_value) {
	State &state = instance();
	if (!state.tx) return false;
	const Frame frame = sdodps_make_frame(SDOMcu_CAN_ID, opcode, static_cast<std::uint16_t>(var), 0u, raw_value, Master::mcu_bit_length(var));
	return state.tx(frame.id, frame.dlc, frame.payload);
}

bool SlaveMcu::process(std::uint32_t id, std::uint64_t payload) {
	if (id != SDOMcu_CAN_ID) return false;
	const Opcode opcode = static_cast<Opcode>(sdodps_get_bits(payload, 0u, 8u));
	const McuVar var = static_cast<McuVar>(sdodps_get_bits(payload, 8u, 10u));
	if (opcode == Opcode::GET_REQ) return process_get(var);
	if (opcode == Opcode::SET_REQ) return process_set(var, payload);
	return false;
}

bool SlaveMcu::process_get(McuVar var) {
	switch (var) {
	case McuVar::dbc_hash: {
		std::uint32_t value = {};
		const Status status = read_dbc_hash(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_dbc_hash(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::is_pos_torque_allowed: {
		std::uint8_t value = {};
		const Status status = read_is_pos_torque_allowed(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_is_pos_torque_allowed(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::is_neg_torque_allowed: {
		std::uint8_t value = {};
		const Status status = read_is_neg_torque_allowed(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_is_neg_torque_allowed(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::motor_max_torque: {
		float value = {};
		const Status status = read_motor_max_torque(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_motor_max_torque(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::lim_pos_torque: {
		float value = {};
		const Status status = read_lim_pos_torque(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_lim_pos_torque(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::lim_neg_torque: {
		float value = {};
		const Status status = read_lim_neg_torque(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_lim_neg_torque(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::lim_rpm: {
		std::uint16_t value = {};
		const Status status = read_lim_rpm(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_lim_rpm(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::speed_limitation: {
		std::uint16_t value = {};
		const Status status = read_speed_limitation(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_speed_limitation(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_active: {
		std::uint8_t value = {};
		const Status status = read_scs_active(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_active(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_monitor_bmsLv: {
		std::uint8_t value = {};
		const Status status = read_scs_monitor_bmsLv(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_monitor_bmsLv(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_monitor_bmsHv: {
		std::uint8_t value = {};
		const Status status = read_scs_monitor_bmsHv(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_monitor_bmsHv(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_monitor_ebs: {
		std::uint8_t value = {};
		const Status status = read_scs_monitor_ebs(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_monitor_ebs(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::serial_core_usb: {
		std::uint8_t value = {};
		const Status status = read_serial_core_usb(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_serial_core_usb(value) : 0u;
		return send_response(opcode, var, raw);
	}
	}
	return send_response(Opcode::ERR, var, 0u);
}

bool SlaveMcu::process_set(McuVar var, std::uint64_t payload) {
	switch (var) {
	case McuVar::dbc_hash: {
		const std::uint32_t value = sdodps_decode_mcu_dbc_hash(payload);
		const Status status = write_dbc_hash(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_dbc_hash(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::is_pos_torque_allowed: {
		const std::uint8_t value = sdodps_decode_mcu_is_pos_torque_allowed(payload);
		const Status status = write_is_pos_torque_allowed(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_is_pos_torque_allowed(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::is_neg_torque_allowed: {
		const std::uint8_t value = sdodps_decode_mcu_is_neg_torque_allowed(payload);
		const Status status = write_is_neg_torque_allowed(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_is_neg_torque_allowed(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::motor_max_torque: {
		const float value = sdodps_decode_mcu_motor_max_torque(payload);
		const Status status = write_motor_max_torque(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_motor_max_torque(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::lim_pos_torque: {
		const float value = sdodps_decode_mcu_lim_pos_torque(payload);
		const Status status = write_lim_pos_torque(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_lim_pos_torque(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::lim_neg_torque: {
		const float value = sdodps_decode_mcu_lim_neg_torque(payload);
		const Status status = write_lim_neg_torque(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_lim_neg_torque(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::lim_rpm: {
		const std::uint16_t value = sdodps_decode_mcu_lim_rpm(payload);
		const Status status = write_lim_rpm(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_lim_rpm(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::speed_limitation: {
		const std::uint16_t value = sdodps_decode_mcu_speed_limitation(payload);
		const Status status = write_speed_limitation(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_speed_limitation(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_active: {
		const std::uint8_t value = sdodps_decode_mcu_scs_active(payload);
		const Status status = write_scs_active(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_active(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_monitor_bmsLv: {
		const std::uint8_t value = sdodps_decode_mcu_scs_monitor_bmsLv(payload);
		const Status status = write_scs_monitor_bmsLv(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_monitor_bmsLv(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_monitor_bmsHv: {
		const std::uint8_t value = sdodps_decode_mcu_scs_monitor_bmsHv(payload);
		const Status status = write_scs_monitor_bmsHv(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_monitor_bmsHv(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::scs_monitor_ebs: {
		const std::uint8_t value = sdodps_decode_mcu_scs_monitor_ebs(payload);
		const Status status = write_scs_monitor_ebs(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_scs_monitor_ebs(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case McuVar::serial_core_usb: {
		const std::uint8_t value = sdodps_decode_mcu_serial_core_usb(payload);
		const Status status = write_serial_core_usb(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_mcu_serial_core_usb(value) : 0u;
		return send_response(opcode, var, raw);
	}
	}
	return send_response(Opcode::ERR, var, 0u);
}

} // namespace sdodps
