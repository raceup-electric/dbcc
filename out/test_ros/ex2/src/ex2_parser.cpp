/* CAN message encoder/decoder: automatically generated - do not edit. */

#include <rclcpp/rclcpp.hpp>
#include <cstring>
#include <cstdint>
#include <can_msgs/msg/frame.hpp>

#include <ex2/msg/ws200_id_info.hpp>
#include <ex2/msg/ws200_status.hpp>
#include <ex2/msg/ws200_bus_measurement.hpp>
#include <ex2/msg/velocity_measurement.hpp>
#include <ex2/msg/phase_current.hpp>
#include <ex2/msg/motor_voltage.hpp>
#include <ex2/msg/motor_current.hpp>
#include <ex2/msg/motor_back_emf.hpp>
#include <ex2/msg/ws200_rail15_v.hpp>
#include <ex2/msg/ws200_low_rail.hpp>
#include <ex2/msg/ws200_motor_temp.hpp>
#include <ex2/msg/ws200_dsp_board_temp.hpp>
#include <ex2/msg/ws200_phase_c_temp.hpp>
#include <ex2/msg/ws200_bus_amp_hours.hpp>
#include <ex2/msg/ws200_slip_speed.hpp>


static inline uint32_t pack754_32(const float f) {
	uint32_t i;
	std::memcpy(&i, &f, sizeof(i));
	return i;
}

static inline uint64_t pack754_64(const double d) {
	uint64_t i;
	std::memcpy(&i, &d, sizeof(i));
	return i;
}

static inline float unpack754_32(const uint32_t i) {
	float f;
	std::memcpy(&f, &i, sizeof(f));
	return f;
}

static inline double unpack754_64(const uint64_t i) {
	double d;
	std::memcpy(&d, &i, sizeof(d));
	return d;
}

static inline uint64_t reverse_byte_order(uint64_t x) {
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
	return x;
}

class Ex2Parser : public rclcpp::Node {
public:
	Ex2Parser() : Node("ex2_parser", "/ex2") {
		createPublishers();
		createSubscriptions();
	}

private:
	void createSubscriptions() {
		auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort().durability_volatile();

		/* 0x400: WS200IDInfo */
		ws200_id_info_sub_ = this->create_subscription<ex2::msg::WS200IDInfo>(
			"ws200_id_info", qos, [this](const ex2::msg::WS200IDInfo::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* tritium_id: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->tritium_id))) & 0xffffffff;
				i |= x;
				/* serial_number: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->serial_number))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1024);
			}
		);

		/* 0x401: WS200Status */
		ws200_status_sub_ = this->create_subscription<ex2::msg::WS200Status>(
			"ws200_status", qos, [this](const ex2::msg::WS200Status::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* limit_flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->limit_flags))) & 0xffff;
				i |= x;
				/* error_flags: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->error_flags))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* active_motor: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->active_motor))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* transmit_error_count: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->transmit_error_count))) & 0xff;
				x <<= 48; 
				i |= x;
				/* receive_error_count: start-bit 56, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->receive_error_count))) & 0xff;
				x <<= 56; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1025);
			}
		);

		/* 0x402: WS200BusMeasurement */
		ws200_bus_measurement_sub_ = this->create_subscription<ex2::msg::WS200BusMeasurement>(
			"ws200_bus_measurement", qos, [this](const ex2::msg::WS200BusMeasurement::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bus_voltage: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->bus_voltage))) & 0xffffffff;
				i |= x;
				/* bus_current: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->bus_current))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1026);
			}
		);

		/* 0x403: VelocityMeasurement */
		velocity_measurement_sub_ = this->create_subscription<ex2::msg::VelocityMeasurement>(
			"velocity_measurement", qos, [this](const ex2::msg::VelocityMeasurement::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motor_velocity: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motor_velocity))) & 0xffffffff;
				i |= x;
				/* vehicle_velocity: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->vehicle_velocity))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1027);
			}
		);

		/* 0x404: PhaseCurrent */
		phase_current_sub_ = this->create_subscription<ex2::msg::PhaseCurrent>(
			"phase_current", qos, [this](const ex2::msg::PhaseCurrent::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* phase_current_b: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->phase_current_b))) & 0xffffffff;
				i |= x;
				/* phase_current_c: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->phase_current_c))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1028);
			}
		);

		/* 0x405: MotorVoltage */
		motor_voltage_sub_ = this->create_subscription<ex2::msg::MotorVoltage>(
			"motor_voltage", qos, [this](const ex2::msg::MotorVoltage::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* vq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->vq))) & 0xffffffff;
				i |= x;
				/* vd: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->vd))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1029);
			}
		);

		/* 0x406: MotorCurrent */
		motor_current_sub_ = this->create_subscription<ex2::msg::MotorCurrent>(
			"motor_current", qos, [this](const ex2::msg::MotorCurrent::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* iq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->iq))) & 0xffffffff;
				i |= x;
				/* id: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->id))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1030);
			}
		);

		/* 0x407: MotorBackEMF */
		motor_back_emf_sub_ = this->create_subscription<ex2::msg::MotorBackEMF>(
			"motor_back_emf", qos, [this](const ex2::msg::MotorBackEMF::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bemf_q: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->bemf_q))) & 0xffffffff;
				i |= x;
				/* bemf_d: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->bemf_d))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1031);
			}
		);

		/* 0x408: WS200Rail15V */
		ws200_rail15_v_sub_ = this->create_subscription<ex2::msg::WS200Rail15V>(
			"ws200_rail15_v", qos, [this](const ex2::msg::WS200Rail15V::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* supply_15v: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->supply_15v))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1032);
			}
		);

		/* 0x409: WS200LowRail */
		ws200_low_rail_sub_ = this->create_subscription<ex2::msg::WS200LowRail>(
			"ws200_low_rail", qos, [this](const ex2::msg::WS200LowRail::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* rail_2v: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->rail_2v))) & 0xffffffff;
				i |= x;
				/* rail_3v: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->rail_3v))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1033);
			}
		);

		/* 0x40b: WS200MotorTemp */
		ws200_motor_temp_sub_ = this->create_subscription<ex2::msg::WS200MotorTemp>(
			"ws200_motor_temp", qos, [this](const ex2::msg::WS200MotorTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motor_temp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motor_temp))) & 0xffffffff;
				i |= x;
				/* ipm_phase_a_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->ipm_phase_a_temp))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1035);
			}
		);

		/* 0x40c: WS200DSPBoardTemp */
		ws200_dsp_board_temp_sub_ = this->create_subscription<ex2::msg::WS200DSPBoardTemp>(
			"ws200_dsp_board_temp", qos, [this](const ex2::msg::WS200DSPBoardTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* ipm_phase_b_temp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->ipm_phase_b_temp))) & 0xffffffff;
				i |= x;
				/* dsp_board_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->dsp_board_temp))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1036);
			}
		);

		/* 0x40d: WS200PhaseCTemp */
		ws200_phase_c_temp_sub_ = this->create_subscription<ex2::msg::WS200PhaseCTemp>(
			"ws200_phase_c_temp", qos, [this](const ex2::msg::WS200PhaseCTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* reserved_1: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->reserved_1))) & 0xffffffff;
				i |= x;
				/* ipm_phase_c_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->ipm_phase_c_temp))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1037);
			}
		);

		/* 0x40e: WS200BusAmpHours */
		ws200_bus_amp_hours_sub_ = this->create_subscription<ex2::msg::WS200BusAmpHours>(
			"ws200_bus_amp_hours", qos, [this](const ex2::msg::WS200BusAmpHours::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* odometer: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->odometer))) & 0xffffffff;
				i |= x;
				/* dc_bus_amp_hours: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->dc_bus_amp_hours))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1038);
			}
		);

		/* 0x417: WS200SlipSpeed */
		ws200_slip_speed_sub_ = this->create_subscription<ex2::msg::WS200SlipSpeed>(
			"ws200_slip_speed", qos, [this](const ex2::msg::WS200SlipSpeed::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* slip_speed: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->slip_speed))) & 0xffffffff;
				i |= x;
				/* reserved_2: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->reserved_2))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1047);
			}
		);

		frame_subscription_ = this->create_subscription<can_msgs::msg::Frame>(
			"/can/ex2/read", qos, [this](const can_msgs::msg::Frame::SharedPtr msg) {
				if (msg->is_error || msg->is_extended || msg->is_rtr) return;
				uint64_t data;
				std::memcpy(&data, msg->data.data(), msg->dlc);
				decodeMessage(data, msg->dlc, msg->id, msg->header.stamp);
			}
		);

	}

	void publishFrame(uint64_t data, uint8_t dlc, uint32_t id) {
		can_msgs::msg::Frame msg;
		msg.dlc = dlc;
		msg.id = id;
		std::memcpy(msg.data.data(), &data, dlc);
		frame_publisher_->publish(msg);
	}

	void createPublishers() {
		auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort().durability_volatile();

		ws200_id_info_pub_ = this->create_publisher<ex2::msg::WS200IDInfo>("ws200_id_info", qos);
		ws200_status_pub_ = this->create_publisher<ex2::msg::WS200Status>("ws200_status", qos);
		ws200_bus_measurement_pub_ = this->create_publisher<ex2::msg::WS200BusMeasurement>("ws200_bus_measurement", qos);
		velocity_measurement_pub_ = this->create_publisher<ex2::msg::VelocityMeasurement>("velocity_measurement", qos);
		phase_current_pub_ = this->create_publisher<ex2::msg::PhaseCurrent>("phase_current", qos);
		motor_voltage_pub_ = this->create_publisher<ex2::msg::MotorVoltage>("motor_voltage", qos);
		motor_current_pub_ = this->create_publisher<ex2::msg::MotorCurrent>("motor_current", qos);
		motor_back_emf_pub_ = this->create_publisher<ex2::msg::MotorBackEMF>("motor_back_emf", qos);
		ws200_rail15_v_pub_ = this->create_publisher<ex2::msg::WS200Rail15V>("ws200_rail15_v", qos);
		ws200_low_rail_pub_ = this->create_publisher<ex2::msg::WS200LowRail>("ws200_low_rail", qos);
		ws200_motor_temp_pub_ = this->create_publisher<ex2::msg::WS200MotorTemp>("ws200_motor_temp", qos);
		ws200_dsp_board_temp_pub_ = this->create_publisher<ex2::msg::WS200DSPBoardTemp>("ws200_dsp_board_temp", qos);
		ws200_phase_c_temp_pub_ = this->create_publisher<ex2::msg::WS200PhaseCTemp>("ws200_phase_c_temp", qos);
		ws200_bus_amp_hours_pub_ = this->create_publisher<ex2::msg::WS200BusAmpHours>("ws200_bus_amp_hours", qos);
		ws200_slip_speed_pub_ = this->create_publisher<ex2::msg::WS200SlipSpeed>("ws200_slip_speed", qos);
		frame_publisher_ = this->create_publisher<can_msgs::msg::Frame>("/can/ex2/write", qos);
	}

	void decodeMessage(uint64_t data, uint8_t dlc, uint32_t id, const rclcpp::Time& timestamp) {
		switch(id) {
			case 1024: { /* 0x400: WS200IDInfo */
				if (dlc < 8) return;
				ex2::msg::WS200IDInfo msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* tritium_id: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.tritium_id = (uint32_t)(x);
				/* serial_number: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.serial_number = (uint32_t)(x);
				ws200_id_info_pub_->publish(msg);
				break;
			}
			case 1025: { /* 0x401: WS200Status */
				if (dlc < 8) return;
				ex2::msg::WS200Status msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* limit_flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.limit_flags = (uint16_t)(x);
				/* error_flags: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.error_flags = (uint16_t)(x);
				/* active_motor: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.active_motor = (uint16_t)(x);
				/* transmit_error_count: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xff;
				msg.transmit_error_count = (uint8_t)(x);
				/* receive_error_count: start-bit 56, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 56) & 0xff;
				msg.receive_error_count = (uint8_t)(x);
				ws200_status_pub_->publish(msg);
				break;
			}
			case 1026: { /* 0x402: WS200BusMeasurement */
				if (dlc < 8) return;
				ex2::msg::WS200BusMeasurement msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bus_voltage: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.bus_voltage = unpack754_32(x);
				/* bus_current: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.bus_current = unpack754_32(x);
				ws200_bus_measurement_pub_->publish(msg);
				break;
			}
			case 1027: { /* 0x403: VelocityMeasurement */
				if (dlc < 8) return;
				ex2::msg::VelocityMeasurement msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motor_velocity: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motor_velocity = unpack754_32(x);
				/* vehicle_velocity: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.vehicle_velocity = unpack754_32(x);
				velocity_measurement_pub_->publish(msg);
				break;
			}
			case 1028: { /* 0x404: PhaseCurrent */
				if (dlc < 8) return;
				ex2::msg::PhaseCurrent msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* phase_current_b: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.phase_current_b = unpack754_32(x);
				/* phase_current_c: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.phase_current_c = unpack754_32(x);
				phase_current_pub_->publish(msg);
				break;
			}
			case 1029: { /* 0x405: MotorVoltage */
				if (dlc < 8) return;
				ex2::msg::MotorVoltage msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* vq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.vq = unpack754_32(x);
				/* vd: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.vd = unpack754_32(x);
				motor_voltage_pub_->publish(msg);
				break;
			}
			case 1030: { /* 0x406: MotorCurrent */
				if (dlc < 8) return;
				ex2::msg::MotorCurrent msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* iq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.iq = unpack754_32(x);
				/* id: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.id = unpack754_32(x);
				motor_current_pub_->publish(msg);
				break;
			}
			case 1031: { /* 0x407: MotorBackEMF */
				if (dlc < 8) return;
				ex2::msg::MotorBackEMF msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bemf_q: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.bemf_q = unpack754_32(x);
				/* bemf_d: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.bemf_d = unpack754_32(x);
				motor_back_emf_pub_->publish(msg);
				break;
			}
			case 1032: { /* 0x408: WS200Rail15V */
				if (dlc < 8) return;
				ex2::msg::WS200Rail15V msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* supply_15v: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.supply_15v = unpack754_32(x);
				ws200_rail15_v_pub_->publish(msg);
				break;
			}
			case 1033: { /* 0x409: WS200LowRail */
				if (dlc < 8) return;
				ex2::msg::WS200LowRail msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* rail_2v: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.rail_2v = unpack754_32(x);
				/* rail_3v: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.rail_3v = unpack754_32(x);
				ws200_low_rail_pub_->publish(msg);
				break;
			}
			case 1035: { /* 0x40b: WS200MotorTemp */
				if (dlc < 8) return;
				ex2::msg::WS200MotorTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motor_temp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motor_temp = unpack754_32(x);
				/* ipm_phase_a_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.ipm_phase_a_temp = unpack754_32(x);
				ws200_motor_temp_pub_->publish(msg);
				break;
			}
			case 1036: { /* 0x40c: WS200DSPBoardTemp */
				if (dlc < 8) return;
				ex2::msg::WS200DSPBoardTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* ipm_phase_b_temp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.ipm_phase_b_temp = unpack754_32(x);
				/* dsp_board_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.dsp_board_temp = unpack754_32(x);
				ws200_dsp_board_temp_pub_->publish(msg);
				break;
			}
			case 1037: { /* 0x40d: WS200PhaseCTemp */
				if (dlc < 8) return;
				ex2::msg::WS200PhaseCTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* reserved_1: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.reserved_1 = unpack754_32(x);
				/* ipm_phase_c_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.ipm_phase_c_temp = unpack754_32(x);
				ws200_phase_c_temp_pub_->publish(msg);
				break;
			}
			case 1038: { /* 0x40e: WS200BusAmpHours */
				if (dlc < 8) return;
				ex2::msg::WS200BusAmpHours msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* odometer: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.odometer = unpack754_32(x);
				/* dc_bus_amp_hours: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.dc_bus_amp_hours = unpack754_32(x);
				ws200_bus_amp_hours_pub_->publish(msg);
				break;
			}
			case 1047: { /* 0x417: WS200SlipSpeed */
				if (dlc < 8) return;
				ex2::msg::WS200SlipSpeed msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* slip_speed: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.slip_speed = unpack754_32(x);
				/* reserved_2: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.reserved_2 = unpack754_32(x);
				ws200_slip_speed_pub_->publish(msg);
				break;
			}
		}
	}

	rclcpp::Subscription<ex2::msg::WS200IDInfo>::SharedPtr ws200_id_info_sub_;
	rclcpp::Publisher<ex2::msg::WS200IDInfo>::SharedPtr ws200_id_info_pub_;
	rclcpp::Subscription<ex2::msg::WS200Status>::SharedPtr ws200_status_sub_;
	rclcpp::Publisher<ex2::msg::WS200Status>::SharedPtr ws200_status_pub_;
	rclcpp::Subscription<ex2::msg::WS200BusMeasurement>::SharedPtr ws200_bus_measurement_sub_;
	rclcpp::Publisher<ex2::msg::WS200BusMeasurement>::SharedPtr ws200_bus_measurement_pub_;
	rclcpp::Subscription<ex2::msg::VelocityMeasurement>::SharedPtr velocity_measurement_sub_;
	rclcpp::Publisher<ex2::msg::VelocityMeasurement>::SharedPtr velocity_measurement_pub_;
	rclcpp::Subscription<ex2::msg::PhaseCurrent>::SharedPtr phase_current_sub_;
	rclcpp::Publisher<ex2::msg::PhaseCurrent>::SharedPtr phase_current_pub_;
	rclcpp::Subscription<ex2::msg::MotorVoltage>::SharedPtr motor_voltage_sub_;
	rclcpp::Publisher<ex2::msg::MotorVoltage>::SharedPtr motor_voltage_pub_;
	rclcpp::Subscription<ex2::msg::MotorCurrent>::SharedPtr motor_current_sub_;
	rclcpp::Publisher<ex2::msg::MotorCurrent>::SharedPtr motor_current_pub_;
	rclcpp::Subscription<ex2::msg::MotorBackEMF>::SharedPtr motor_back_emf_sub_;
	rclcpp::Publisher<ex2::msg::MotorBackEMF>::SharedPtr motor_back_emf_pub_;
	rclcpp::Subscription<ex2::msg::WS200Rail15V>::SharedPtr ws200_rail15_v_sub_;
	rclcpp::Publisher<ex2::msg::WS200Rail15V>::SharedPtr ws200_rail15_v_pub_;
	rclcpp::Subscription<ex2::msg::WS200LowRail>::SharedPtr ws200_low_rail_sub_;
	rclcpp::Publisher<ex2::msg::WS200LowRail>::SharedPtr ws200_low_rail_pub_;
	rclcpp::Subscription<ex2::msg::WS200MotorTemp>::SharedPtr ws200_motor_temp_sub_;
	rclcpp::Publisher<ex2::msg::WS200MotorTemp>::SharedPtr ws200_motor_temp_pub_;
	rclcpp::Subscription<ex2::msg::WS200DSPBoardTemp>::SharedPtr ws200_dsp_board_temp_sub_;
	rclcpp::Publisher<ex2::msg::WS200DSPBoardTemp>::SharedPtr ws200_dsp_board_temp_pub_;
	rclcpp::Subscription<ex2::msg::WS200PhaseCTemp>::SharedPtr ws200_phase_c_temp_sub_;
	rclcpp::Publisher<ex2::msg::WS200PhaseCTemp>::SharedPtr ws200_phase_c_temp_pub_;
	rclcpp::Subscription<ex2::msg::WS200BusAmpHours>::SharedPtr ws200_bus_amp_hours_sub_;
	rclcpp::Publisher<ex2::msg::WS200BusAmpHours>::SharedPtr ws200_bus_amp_hours_pub_;
	rclcpp::Subscription<ex2::msg::WS200SlipSpeed>::SharedPtr ws200_slip_speed_sub_;
	rclcpp::Publisher<ex2::msg::WS200SlipSpeed>::SharedPtr ws200_slip_speed_pub_;
	rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr frame_subscription_;
	rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr frame_publisher_;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::executors::StaticSingleThreadedExecutor executor;
	auto node = std::make_shared<Ex2Parser>();
	executor.add_node(node);
	executor.spin();
	rclcpp::shutdown();
	return 0;
}
