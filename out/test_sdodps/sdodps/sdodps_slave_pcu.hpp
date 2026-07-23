/* SDO_DPS C++ support: automatically generated - do not edit. */

#ifndef SDODPS_SLAVE_PCU_HPP
#define SDODPS_SLAVE_PCU_HPP

#include "sdodps_master.hpp"

namespace sdodps {

class SlavePcu {
public:
	using Uint32ReadCallback = bool (*)(std::uint32_t *out);
	using Uint32WriteCallback = bool (*)(std::uint32_t value);
	using Uint8ReadCallback = bool (*)(std::uint8_t *out);
	using Uint8WriteCallback = bool (*)(std::uint8_t value);
	using FloatReadCallback = bool (*)(float *out);
	using FloatWriteCallback = bool (*)(float value);

	static void set_tx_callback(TxCallback cb);
	static void set_dbc_hash_reader(Uint32ReadCallback cb);
	static void set_dbc_hash_writer(Uint32WriteCallback cb);
	static Status read_dbc_hash(std::uint32_t *out);
	static Status write_dbc_hash(std::uint32_t value);
	static void set_send_asms_reader(Uint8ReadCallback cb);
	static void set_send_asms_writer(Uint8WriteCallback cb);
	static Status read_send_asms(std::uint8_t *out);
	static Status write_send_asms(std::uint8_t value);
	static void set_Kp_batt_reader(FloatReadCallback cb);
	static void set_Kp_batt_writer(FloatWriteCallback cb);
	static Status read_Kp_batt(float *out);
	static Status write_Kp_batt(float value);
	static void set_Ki_batt_reader(FloatReadCallback cb);
	static void set_Ki_batt_writer(FloatWriteCallback cb);
	static Status read_Ki_batt(float *out);
	static Status write_Ki_batt(float value);
	static void set_T_0_batt_reader(FloatReadCallback cb);
	static void set_T_0_batt_writer(FloatWriteCallback cb);
	static Status read_T_0_batt(float *out);
	static Status write_T_0_batt(float value);
	static void set_T_100_batt_reader(FloatReadCallback cb);
	static void set_T_100_batt_writer(FloatWriteCallback cb);
	static Status read_T_100_batt(float *out);
	static Status write_T_100_batt(float value);
	static void set_droni_perf_reader(Uint8ReadCallback cb);
	static void set_droni_perf_writer(Uint8WriteCallback cb);
	static Status read_droni_perf(std::uint8_t *out);
	static Status write_droni_perf(std::uint8_t value);
	static void set_pump_l_max_reader(Uint8ReadCallback cb);
	static void set_pump_l_max_writer(Uint8WriteCallback cb);
	static Status read_pump_l_max(std::uint8_t *out);
	static Status write_pump_l_max(std::uint8_t value);
	static void set_pump_r_max_reader(Uint8ReadCallback cb);
	static void set_pump_r_max_writer(Uint8WriteCallback cb);
	static Status read_pump_r_max(std::uint8_t *out);
	static Status write_pump_r_max(std::uint8_t value);
	static void set_rain_mode_reader(Uint8ReadCallback cb);
	static void set_rain_mode_writer(Uint8WriteCallback cb);
	static Status read_rain_mode(std::uint8_t *out);
	static Status write_rain_mode(std::uint8_t value);
	static void set_limit_fan_curr_reader(Uint8ReadCallback cb);
	static void set_limit_fan_curr_writer(Uint8WriteCallback cb);
	static Status read_limit_fan_curr(std::uint8_t *out);
	static Status write_limit_fan_curr(std::uint8_t value);
	static void set_debug_sense_reader(Uint8ReadCallback cb);
	static void set_debug_sense_writer(Uint8WriteCallback cb);
	static Status read_debug_sense(std::uint8_t *out);
	static Status write_debug_sense(std::uint8_t value);
	static bool process(std::uint32_t id, std::uint64_t payload);
	static bool notify(PcuVar var);

private:
	struct State {
		TxCallback tx = nullptr;
		Uint32ReadCallback dbc_hash_reader = nullptr;
		Uint32WriteCallback dbc_hash_writer = nullptr;
		Uint8ReadCallback send_asms_reader = nullptr;
		Uint8WriteCallback send_asms_writer = nullptr;
		FloatReadCallback Kp_batt_reader = nullptr;
		FloatWriteCallback Kp_batt_writer = nullptr;
		FloatReadCallback Ki_batt_reader = nullptr;
		FloatWriteCallback Ki_batt_writer = nullptr;
		FloatReadCallback T_0_batt_reader = nullptr;
		FloatWriteCallback T_0_batt_writer = nullptr;
		FloatReadCallback T_100_batt_reader = nullptr;
		FloatWriteCallback T_100_batt_writer = nullptr;
		Uint8ReadCallback droni_perf_reader = nullptr;
		Uint8WriteCallback droni_perf_writer = nullptr;
		Uint8ReadCallback pump_l_max_reader = nullptr;
		Uint8WriteCallback pump_l_max_writer = nullptr;
		Uint8ReadCallback pump_r_max_reader = nullptr;
		Uint8WriteCallback pump_r_max_writer = nullptr;
		Uint8ReadCallback rain_mode_reader = nullptr;
		Uint8WriteCallback rain_mode_writer = nullptr;
		Uint8ReadCallback limit_fan_curr_reader = nullptr;
		Uint8WriteCallback limit_fan_curr_writer = nullptr;
		Uint8ReadCallback debug_sense_reader = nullptr;
		Uint8WriteCallback debug_sense_writer = nullptr;
	};

	static State &instance();
	static bool send_response(Opcode opcode, PcuVar var, std::uint64_t raw_value);
	static bool process_get(PcuVar var);
	static bool process_set(PcuVar var, std::uint64_t payload);
};

} // namespace sdodps

#endif
