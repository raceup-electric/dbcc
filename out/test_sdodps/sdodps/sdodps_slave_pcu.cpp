/* SDO_DPS C++ support: automatically generated - do not edit. */

#include "sdodps_slave_pcu.hpp"

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

SlavePcu::State &SlavePcu::instance() {
	static State state;
	return state;
}

void SlavePcu::set_tx_callback(TxCallback cb) {
	instance().tx = cb;
}

void SlavePcu::set_dbc_hash_reader(Uint32ReadCallback cb) {
	instance().dbc_hash_reader = cb;
}

void SlavePcu::set_dbc_hash_writer(Uint32WriteCallback cb) {
	instance().dbc_hash_writer = cb;
}

void SlavePcu::set_send_asms_reader(Uint8ReadCallback cb) {
	instance().send_asms_reader = cb;
}

void SlavePcu::set_send_asms_writer(Uint8WriteCallback cb) {
	instance().send_asms_writer = cb;
}

void SlavePcu::set_Kp_batt_reader(FloatReadCallback cb) {
	instance().Kp_batt_reader = cb;
}

void SlavePcu::set_Kp_batt_writer(FloatWriteCallback cb) {
	instance().Kp_batt_writer = cb;
}

void SlavePcu::set_Ki_batt_reader(FloatReadCallback cb) {
	instance().Ki_batt_reader = cb;
}

void SlavePcu::set_Ki_batt_writer(FloatWriteCallback cb) {
	instance().Ki_batt_writer = cb;
}

void SlavePcu::set_T_0_batt_reader(FloatReadCallback cb) {
	instance().T_0_batt_reader = cb;
}

void SlavePcu::set_T_0_batt_writer(FloatWriteCallback cb) {
	instance().T_0_batt_writer = cb;
}

void SlavePcu::set_T_100_batt_reader(FloatReadCallback cb) {
	instance().T_100_batt_reader = cb;
}

void SlavePcu::set_T_100_batt_writer(FloatWriteCallback cb) {
	instance().T_100_batt_writer = cb;
}

void SlavePcu::set_droni_perf_reader(Uint8ReadCallback cb) {
	instance().droni_perf_reader = cb;
}

void SlavePcu::set_droni_perf_writer(Uint8WriteCallback cb) {
	instance().droni_perf_writer = cb;
}

void SlavePcu::set_pump_l_max_reader(Uint8ReadCallback cb) {
	instance().pump_l_max_reader = cb;
}

void SlavePcu::set_pump_l_max_writer(Uint8WriteCallback cb) {
	instance().pump_l_max_writer = cb;
}

void SlavePcu::set_pump_r_max_reader(Uint8ReadCallback cb) {
	instance().pump_r_max_reader = cb;
}

void SlavePcu::set_pump_r_max_writer(Uint8WriteCallback cb) {
	instance().pump_r_max_writer = cb;
}

void SlavePcu::set_rain_mode_reader(Uint8ReadCallback cb) {
	instance().rain_mode_reader = cb;
}

void SlavePcu::set_rain_mode_writer(Uint8WriteCallback cb) {
	instance().rain_mode_writer = cb;
}

void SlavePcu::set_limit_fan_curr_reader(Uint8ReadCallback cb) {
	instance().limit_fan_curr_reader = cb;
}

void SlavePcu::set_limit_fan_curr_writer(Uint8WriteCallback cb) {
	instance().limit_fan_curr_writer = cb;
}

void SlavePcu::set_debug_sense_reader(Uint8ReadCallback cb) {
	instance().debug_sense_reader = cb;
}

void SlavePcu::set_debug_sense_writer(Uint8WriteCallback cb) {
	instance().debug_sense_writer = cb;
}

Status SlavePcu::read_dbc_hash(std::uint32_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.dbc_hash_reader) return Status::no_value;
	return state.dbc_hash_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_dbc_hash(std::uint32_t value) {
	State &state = instance();
	if (!state.dbc_hash_writer) return Status::read_only;
	return state.dbc_hash_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_send_asms(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.send_asms_reader) return Status::no_value;
	return state.send_asms_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_send_asms(std::uint8_t value) {
	State &state = instance();
	if (!state.send_asms_writer) return Status::read_only;
	return state.send_asms_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_Kp_batt(float *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.Kp_batt_reader) return Status::no_value;
	return state.Kp_batt_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_Kp_batt(float value) {
	State &state = instance();
	if (!state.Kp_batt_writer) return Status::read_only;
	return state.Kp_batt_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_Ki_batt(float *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.Ki_batt_reader) return Status::no_value;
	return state.Ki_batt_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_Ki_batt(float value) {
	State &state = instance();
	if (!state.Ki_batt_writer) return Status::read_only;
	return state.Ki_batt_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_T_0_batt(float *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.T_0_batt_reader) return Status::no_value;
	return state.T_0_batt_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_T_0_batt(float value) {
	State &state = instance();
	if (!state.T_0_batt_writer) return Status::read_only;
	return state.T_0_batt_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_T_100_batt(float *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.T_100_batt_reader) return Status::no_value;
	return state.T_100_batt_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_T_100_batt(float value) {
	State &state = instance();
	if (!state.T_100_batt_writer) return Status::read_only;
	return state.T_100_batt_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_droni_perf(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.droni_perf_reader) return Status::no_value;
	return state.droni_perf_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_droni_perf(std::uint8_t value) {
	State &state = instance();
	if (!state.droni_perf_writer) return Status::read_only;
	return state.droni_perf_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_pump_l_max(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.pump_l_max_reader) return Status::no_value;
	return state.pump_l_max_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_pump_l_max(std::uint8_t value) {
	State &state = instance();
	if (!state.pump_l_max_writer) return Status::read_only;
	return state.pump_l_max_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_pump_r_max(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.pump_r_max_reader) return Status::no_value;
	return state.pump_r_max_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_pump_r_max(std::uint8_t value) {
	State &state = instance();
	if (!state.pump_r_max_writer) return Status::read_only;
	return state.pump_r_max_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_rain_mode(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.rain_mode_reader) return Status::no_value;
	return state.rain_mode_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_rain_mode(std::uint8_t value) {
	State &state = instance();
	if (!state.rain_mode_writer) return Status::read_only;
	return state.rain_mode_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_limit_fan_curr(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.limit_fan_curr_reader) return Status::no_value;
	return state.limit_fan_curr_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_limit_fan_curr(std::uint8_t value) {
	State &state = instance();
	if (!state.limit_fan_curr_writer) return Status::read_only;
	return state.limit_fan_curr_writer(value) ? Status::ok : Status::no_value;
}

Status SlavePcu::read_debug_sense(std::uint8_t *out) {
	if (!out) return Status::bad_frame;
	State &state = instance();
	if (!state.debug_sense_reader) return Status::no_value;
	return state.debug_sense_reader(out) ? Status::ok : Status::no_value;
}

Status SlavePcu::write_debug_sense(std::uint8_t value) {
	State &state = instance();
	if (!state.debug_sense_writer) return Status::read_only;
	return state.debug_sense_writer(value) ? Status::ok : Status::no_value;
}

bool SlavePcu::send_response(Opcode opcode, PcuVar var, std::uint64_t raw_value) {
	State &state = instance();
	if (!state.tx) return false;
	const Frame frame = sdodps_make_frame(SDOPcu_CAN_ID, opcode, static_cast<std::uint16_t>(var), 0u, raw_value, Master::pcu_bit_length(var));
	return state.tx(frame.id, frame.dlc, frame.payload);
}

bool SlavePcu::process(std::uint32_t id, std::uint64_t payload) {
	if (id != SDOPcu_CAN_ID) return false;
	const Opcode opcode = static_cast<Opcode>(sdodps_get_bits(payload, 0u, 8u));
	const PcuVar var = static_cast<PcuVar>(sdodps_get_bits(payload, 8u, 10u));
	if (opcode == Opcode::GET_REQ) return process_get(var);
	if (opcode == Opcode::SET_REQ) return process_set(var, payload);
	return false;
}

bool SlavePcu::notify(PcuVar var) {
	return process_get(var);
}

bool SlavePcu::process_get(PcuVar var) {
	switch (var) {
	case PcuVar::dbc_hash: {
		std::uint32_t value = {};
		const Status status = read_dbc_hash(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_dbc_hash(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::send_asms: {
		std::uint8_t value = {};
		const Status status = read_send_asms(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_send_asms(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::Kp_batt: {
		float value = {};
		const Status status = read_Kp_batt(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_Kp_batt(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::Ki_batt: {
		float value = {};
		const Status status = read_Ki_batt(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_Ki_batt(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::T_0_batt: {
		float value = {};
		const Status status = read_T_0_batt(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_T_0_batt(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::T_100_batt: {
		float value = {};
		const Status status = read_T_100_batt(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_T_100_batt(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::droni_perf: {
		std::uint8_t value = {};
		const Status status = read_droni_perf(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_droni_perf(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::pump_l_max: {
		std::uint8_t value = {};
		const Status status = read_pump_l_max(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_pump_l_max(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::pump_r_max: {
		std::uint8_t value = {};
		const Status status = read_pump_r_max(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_pump_r_max(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::rain_mode: {
		std::uint8_t value = {};
		const Status status = read_rain_mode(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_rain_mode(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::limit_fan_curr: {
		std::uint8_t value = {};
		const Status status = read_limit_fan_curr(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_limit_fan_curr(value) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::debug_sense: {
		std::uint8_t value = {};
		const Status status = read_debug_sense(&value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : Opcode::ERR;
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_debug_sense(value) : 0u;
		return send_response(opcode, var, raw);
	}
	}
	return send_response(Opcode::ERR, var, 0u);
}

bool SlavePcu::process_set(PcuVar var, std::uint64_t payload) {
	switch (var) {
	case PcuVar::dbc_hash: {
		const std::uint32_t value = sdodps_decode_pcu_dbc_hash(payload);
		const Status status = write_dbc_hash(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint32_t stored = value;
		if (status == Status::ok) (void)read_dbc_hash(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_dbc_hash(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::send_asms: {
		const std::uint8_t value = sdodps_decode_pcu_send_asms(payload);
		const Status status = write_send_asms(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint8_t stored = value;
		if (status == Status::ok) (void)read_send_asms(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_send_asms(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::Kp_batt: {
		const float value = sdodps_decode_pcu_Kp_batt(payload);
		const Status status = write_Kp_batt(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		float stored = value;
		if (status == Status::ok) (void)read_Kp_batt(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_Kp_batt(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::Ki_batt: {
		const float value = sdodps_decode_pcu_Ki_batt(payload);
		const Status status = write_Ki_batt(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		float stored = value;
		if (status == Status::ok) (void)read_Ki_batt(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_Ki_batt(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::T_0_batt: {
		const float value = sdodps_decode_pcu_T_0_batt(payload);
		const Status status = write_T_0_batt(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		float stored = value;
		if (status == Status::ok) (void)read_T_0_batt(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_T_0_batt(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::T_100_batt: {
		const float value = sdodps_decode_pcu_T_100_batt(payload);
		const Status status = write_T_100_batt(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		float stored = value;
		if (status == Status::ok) (void)read_T_100_batt(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_T_100_batt(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::droni_perf: {
		const std::uint8_t value = sdodps_decode_pcu_droni_perf(payload);
		const Status status = write_droni_perf(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint8_t stored = value;
		if (status == Status::ok) (void)read_droni_perf(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_droni_perf(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::pump_l_max: {
		const std::uint8_t value = sdodps_decode_pcu_pump_l_max(payload);
		const Status status = write_pump_l_max(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint8_t stored = value;
		if (status == Status::ok) (void)read_pump_l_max(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_pump_l_max(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::pump_r_max: {
		const std::uint8_t value = sdodps_decode_pcu_pump_r_max(payload);
		const Status status = write_pump_r_max(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint8_t stored = value;
		if (status == Status::ok) (void)read_pump_r_max(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_pump_r_max(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::rain_mode: {
		const std::uint8_t value = sdodps_decode_pcu_rain_mode(payload);
		const Status status = write_rain_mode(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint8_t stored = value;
		if (status == Status::ok) (void)read_rain_mode(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_rain_mode(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::limit_fan_curr: {
		const std::uint8_t value = sdodps_decode_pcu_limit_fan_curr(payload);
		const Status status = write_limit_fan_curr(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint8_t stored = value;
		if (status == Status::ok) (void)read_limit_fan_curr(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_limit_fan_curr(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	case PcuVar::debug_sense: {
		const std::uint8_t value = sdodps_decode_pcu_debug_sense(payload);
		const Status status = write_debug_sense(value);
		const Opcode opcode = status == Status::ok ? Opcode::RES : (status == Status::read_only ? Opcode::ERR_WRITE_RO : Opcode::ERR);
		std::uint8_t stored = value;
		if (status == Status::ok) (void)read_debug_sense(&stored);
		const std::uint64_t raw = status == Status::ok ? sdodps_encode_pcu_debug_sense(stored) : 0u;
		return send_response(opcode, var, raw);
	}
	}
	return send_response(Opcode::ERR, var, 0u);
}

} // namespace sdodps
