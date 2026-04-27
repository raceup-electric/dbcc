/* CAN message encoder/decoder: automatically generated - do not edit. */

#include <rclcpp/rclcpp.hpp>
#include <cstring>
#include <can_msgs/msg/frame.hpp>

#include <ex1/msg/magic_can_node1_r_heartbeat.hpp>
#include <ex1/msg/magic_can_node2_heartbeat.hpp>
#include <ex1/msg/magic_can_node3_heartbeat.hpp>
#include <ex1/msg/frame_fault_heartbeat.hpp>
#include <ex1/msg/drive_controls_heartbeat.hpp>
#include <ex1/msg/can_mirror_heatbeart.hpp>
#include <ex1/msg/rider_display_heartbeat.hpp>
#include <ex1/msg/bim1_heartbeat.hpp>
#include <ex1/msg/bim2_heartbeat.hpp>
#include <ex1/msg/bim3_heartbeat.hpp>
#include <ex1/msg/bim4_heartbeat.hpp>
#include <ex1/msg/frame_fault_detection_status.hpp>
#include <ex1/msg/front_brake_pressure.hpp>
#include <ex1/msg/rear_brake_pressure.hpp>
#include <ex1/msg/front_suspension_travel.hpp>
#include <ex1/msg/rear_suspension_travel.hpp>
#include <ex1/msg/bus_voltage12_v.hpp>
#include <ex1/msg/post_motor_coolant_temp.hpp>
#include <ex1/msg/post_controller_coolant_temp.hpp>
#include <ex1/msg/radiator_cool_side_coolant_temp.hpp>
#include <ex1/msg/ambient_temp.hpp>
#include <ex1/msg/gps_lat_and_validity_status.hpp>
#include <ex1/msg/gps_longitude.hpp>
#include <ex1/msg/gps_altitude_and_accuracy.hpp>
#include <ex1/msg/current_time.hpp>
#include <ex1/msg/imu_acceleration_measurement.hpp>
#include <ex1/msg/imu_gyro_measurement.hpp>
#include <ex1/msg/motor_plate_temp.hpp>
#include <ex1/msg/bim1_cell_statistics1.hpp>
#include <ex1/msg/bim1_cell_statistics2.hpp>
#include <ex1/msg/bim2_cell_statisitcs1.hpp>
#include <ex1/msg/bim2_cell_statistics2.hpp>
#include <ex1/msg/bim3_cell_statisitcs1.hpp>
#include <ex1/msg/bim3_cell_statistics2.hpp>
#include <ex1/msg/bim4_cell_statistics1.hpp>
#include <ex1/msg/bim4_cell_statistics2.hpp>
#include <ex1/msg/cells14.hpp>
#include <ex1/msg/cells58.hpp>
#include <ex1/msg/cells912.hpp>
#include <ex1/msg/odometer_velocity.hpp>
#include <ex1/msg/cells1316.hpp>
#include <ex1/msg/cells1720.hpp>
#include <ex1/msg/cells2124.hpp>
#include <ex1/msg/cells2528.hpp>
#include <ex1/msg/cells2932.hpp>
#include <ex1/msg/cells3336.hpp>
#include <ex1/msg/cells3740.hpp>
#include <ex1/msg/cells4144.hpp>
#include <ex1/msg/cells4548.hpp>
#include <ex1/msg/cells4952.hpp>
#include <ex1/msg/cells5354.hpp>
#include <ex1/msg/cells5558.hpp>
#include <ex1/msg/cells5962.hpp>
#include <ex1/msg/cells6366.hpp>
#include <ex1/msg/cells6770.hpp>
#include <ex1/msg/cells7174.hpp>
#include <ex1/msg/cells7578.hpp>
#include <ex1/msg/cells7982.hpp>
#include <ex1/msg/cells8386.hpp>
#include <ex1/msg/cells8790.hpp>
#include <ex1/msg/cells9194.hpp>
#include <ex1/msg/cells9598.hpp>
#include <ex1/msg/cells99102.hpp>
#include <ex1/msg/cells103106.hpp>
#include <ex1/msg/cells107110.hpp>
#include <ex1/msg/pack_temperatures1_thru4.hpp>
#include <ex1/msg/pack_tempeartures5_thru8.hpp>
#include <ex1/msg/pack_temperatures9_thru14.hpp>
#include <ex1/msg/pack_temperatures13_thru14.hpp>
#include <ex1/msg/pack_temperatures15_thru18.hpp>
#include <ex1/msg/pack_temperatures19_thru22.hpp>
#include <ex1/msg/pack_temperatures23_thru26.hpp>
#include <ex1/msg/pack_temperatures27_thru30.hpp>
#include <ex1/msg/pack_temperatures31_thru34.hpp>
#include <ex1/msg/pack_temperatures35_thru38.hpp>
#include <ex1/msg/pack_temperatures39_thru42.hpp>
#include <ex1/msg/motor_drive_command.hpp>
#include <ex1/msg/motor_power_command.hpp>
#include <ex1/msg/status_information.hpp>
#include <ex1/msg/bus_measurement.hpp>
#include <ex1/msg/velocity_measurment.hpp>
#include <ex1/msg/phase_current_measurment.hpp>
#include <ex1/msg/motor_voltage.hpp>
#include <ex1/msg/motor_current.hpp>
#include <ex1/msg/motor_phase_a_temperature.hpp>
#include <ex1/msg/odometeramphours.hpp>
#include <ex1/msg/back_emf.hpp>
#include <ex1/msg/rail15v.hpp>
#include <ex1/msg/rail3v31v9.hpp>
#include <ex1/msg/phase_bdsptemprature.hpp>
#include <ex1/msg/magic_can_node1_r_bootloader_address.hpp>
#include <ex1/msg/magic_can_node2_m_bootloader_address.hpp>
#include <ex1/msg/magic_can_node3_f_bootloader_address.hpp>
#include <ex1/msg/frame_fault_bootloader_addres.hpp>
#include <ex1/msg/frame_fault_command.hpp>
#include <ex1/msg/drive_controls_bootloader.hpp>
#include <ex1/msg/drive_controls_command.hpp>
#include <ex1/msg/can_mirror_bootloader_address.hpp>
#include <ex1/msg/can_mirror_command.hpp>
#include <ex1/msg/rider_display_bootloader_address.hpp>
#include <ex1/msg/rider_display_command.hpp>
#include <ex1/msg/bim1_bootloader_address.hpp>
#include <ex1/msg/bim2_bootloader_address.hpp>
#include <ex1/msg/bim3_bootloader_address.hpp>
#include <ex1/msg/bim4_bootloader_address.hpp>
#include <ex1/msg/magic_can_node1_r_command.hpp>
#include <ex1/msg/magic_can_node2_m_command.hpp>
#include <ex1/msg/magic_can_node3_f_command.hpp>
#include <ex1/msg/ca_ncorder_heartbeat.hpp>
#include <ex1/msg/bim1_command.hpp>
#include <ex1/msg/bim2_command.hpp>
#include <ex1/msg/bim3_command.hpp>
#include <ex1/msg/bim4_command.hpp>
#include <ex1/msg/motor_scoop.hpp>
#include <ex1/msg/imu1.hpp>
#include <ex1/msg/imu2.hpp>
#include <ex1/msg/imu3.hpp>
#include <ex1/msg/imu4.hpp>
#include <ex1/msg/imu5.hpp>
#include <ex1/msg/messagename.hpp>
#include <ex1/msg/messagename2.hpp>


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

class Ex1Parser : public rclcpp::Node {
public:
	Ex1Parser() : Node("ex1_parser", "/ex1") {
		createPublishers();
		createSubscriptions();
	}

private:
	void createSubscriptions() {
		auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort().durability_volatile();

		/* 0xcc0016e: MagicCanNode1RHeartbeat */
		magic_can_node1_r_heartbeat_sub_ = this->create_subscription<ex1::msg::MagicCanNode1RHeartbeat>(
			"magic_can_node1_r_heartbeat", qos, [this](const ex1::msg::MagicCanNode1RHeartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magicnode1flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->magicnode1flags))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 213909870);
			}
		);

		/* 0x023: MagicCanNode2Heartbeat */
		magic_can_node2_heartbeat_sub_ = this->create_subscription<ex1::msg::MagicCanNode2Heartbeat>(
			"magic_can_node2_heartbeat", qos, [this](const ex1::msg::MagicCanNode2Heartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magicnode2flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->magicnode2flags))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 35);
			}
		);

		/* 0x025: MagicCanNode3Heartbeat */
		magic_can_node3_heartbeat_sub_ = this->create_subscription<ex1::msg::MagicCanNode3Heartbeat>(
			"magic_can_node3_heartbeat", qos, [this](const ex1::msg::MagicCanNode3Heartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magicnode3flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->magicnode3flags))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 37);
			}
		);

		/* 0x027: FrameFaultHeartbeat */
		frame_fault_heartbeat_sub_ = this->create_subscription<ex1::msg::FrameFaultHeartbeat>(
			"frame_fault_heartbeat", qos, [this](const ex1::msg::FrameFaultHeartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* framefaultflags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->framefaultflags))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 39);
			}
		);

		/* 0x02e: DriveControlsHeartbeat */
		drive_controls_heartbeat_sub_ = this->create_subscription<ex1::msg::DriveControlsHeartbeat>(
			"drive_controls_heartbeat", qos, [this](const ex1::msg::DriveControlsHeartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* drivecontroltritiumerror: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->drivecontroltritiumerror))) & 0x1;
				x <<= 1; 
				i |= x;
				/* drivecontrolmaxerror: start-bit 2, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->drivecontrolmaxerror))) & 0x1;
				x <<= 2; 
				i |= x;
				/* drivecontrolminerror: start-bit 3, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->drivecontrolminerror))) & 0x1;
				x <<= 3; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 46);
			}
		);

		/* 0x031: CANMirrorHeatbeart */
		can_mirror_heatbeart_sub_ = this->create_subscription<ex1::msg::CANMirrorHeatbeart>(
			"can_mirror_heatbeart", qos, [this](const ex1::msg::CANMirrorHeatbeart::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* canmirroroverflowcounter: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->canmirroroverflowcounter))) & 0xff;
				i |= x;
				/* timeout: start-bit 8, length 6, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->timeout))) & 0x3f;
				x <<= 8; 
				i |= x;
				/* mirror_can_error: start-bit 14, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->mirror_can_error))) & 0x1;
				x <<= 14; 
				i |= x;
				/* mirror_cana_status: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->mirror_cana_status))) & 0x1;
				x <<= 15; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 49);
			}
		);

		/* 0x034: RiderDisplayHeartbeat */
		rider_display_heartbeat_sub_ = this->create_subscription<ex1::msg::RiderDisplayHeartbeat>(
			"rider_display_heartbeat", qos, [this](const ex1::msg::RiderDisplayHeartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* riderdisplayflags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->riderdisplayflags))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 52);
			}
		);

		/* 0x03a: BIM1Heartbeat */
		bim1_heartbeat_sub_ = this->create_subscription<ex1::msg::BIM1Heartbeat>(
			"bim1_heartbeat", qos, [this](const ex1::msg::BIM1Heartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim1init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim1init))) & 0x1;
				i |= x;
				/* bim1spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim1spi))) & 0x1;
				x <<= 1; 
				i |= x;
				/* bim1bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim1bq))) & 0x3f;
				x <<= 2; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 58);
			}
		);

		/* 0x03c: BIM2Heartbeat */
		bim2_heartbeat_sub_ = this->create_subscription<ex1::msg::BIM2Heartbeat>(
			"bim2_heartbeat", qos, [this](const ex1::msg::BIM2Heartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim2init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim2init))) & 0x1;
				i |= x;
				/* bim2spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim2spi))) & 0x1;
				x <<= 1; 
				i |= x;
				/* bim2bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim2bq))) & 0x3f;
				x <<= 2; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 60);
			}
		);

		/* 0x03e: BIM3Heartbeat */
		bim3_heartbeat_sub_ = this->create_subscription<ex1::msg::BIM3Heartbeat>(
			"bim3_heartbeat", qos, [this](const ex1::msg::BIM3Heartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim3init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim3init))) & 0x1;
				i |= x;
				/* bim3spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim3spi))) & 0x1;
				x <<= 1; 
				i |= x;
				/* bim3bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim3bq))) & 0x3f;
				x <<= 2; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 62);
			}
		);

		/* 0x040: BIM4Heartbeat */
		bim4_heartbeat_sub_ = this->create_subscription<ex1::msg::BIM4Heartbeat>(
			"bim4_heartbeat", qos, [this](const ex1::msg::BIM4Heartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim4init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim4init))) & 0x1;
				i |= x;
				/* bim4spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim4spi))) & 0x1;
				x <<= 1; 
				i |= x;
				/* bim4bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim4bq))) & 0x3f;
				x <<= 2; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 64);
			}
		);

		/* 0x100: FrameFaultDetectionStatus */
		frame_fault_detection_status_sub_ = this->create_subscription<ex1::msg::FrameFaultDetectionStatus>(
			"frame_fault_detection_status", qos, [this](const ex1::msg::FrameFaultDetectionStatus::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* estimatedpackframeresistance: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->estimatedpackframeresistance))) & 0xffffffff;
				i |= x;
				/* faultstatus: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->faultstatus))) & 0xffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 6, 256);
			}
		);

		/* 0x101: FrontBrakePressure */
		front_brake_pressure_sub_ = this->create_subscription<ex1::msg::FrontBrakePressure>(
			"front_brake_pressure", qos, [this](const ex1::msg::FrontBrakePressure::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* frontbrakepressure: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->frontbrakepressure))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 257);
			}
		);

		/* 0x102: RearBrakePressure */
		rear_brake_pressure_sub_ = this->create_subscription<ex1::msg::RearBrakePressure>(
			"rear_brake_pressure", qos, [this](const ex1::msg::RearBrakePressure::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* rearbrakepressure: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->rearbrakepressure))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 258);
			}
		);

		/* 0x103: FrontSuspensionTravel */
		front_suspension_travel_sub_ = this->create_subscription<ex1::msg::FrontSuspensionTravel>(
			"front_suspension_travel", qos, [this](const ex1::msg::FrontSuspensionTravel::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* frontsuspensionposition: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->frontsuspensionposition))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 259);
			}
		);

		/* 0x104: RearSuspensionTravel */
		rear_suspension_travel_sub_ = this->create_subscription<ex1::msg::RearSuspensionTravel>(
			"rear_suspension_travel", qos, [this](const ex1::msg::RearSuspensionTravel::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* rearsuspensionposition: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->rearsuspensionposition))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 260);
			}
		);

		/* 0x106: BusVoltage12V */
		bus_voltage12_v_sub_ = this->create_subscription<ex1::msg::BusVoltage12V>(
			"bus_voltage12_v", qos, [this](const ex1::msg::BusVoltage12V::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* busvoltage12v: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->busvoltage12v))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 262);
			}
		);

		/* 0x107: PostMotorCoolantTemp */
		post_motor_coolant_temp_sub_ = this->create_subscription<ex1::msg::PostMotorCoolantTemp>(
			"post_motor_coolant_temp", qos, [this](const ex1::msg::PostMotorCoolantTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* postmotorcoolanttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->postmotorcoolanttemp))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 263);
			}
		);

		/* 0x108: PostControllerCoolantTemp */
		post_controller_coolant_temp_sub_ = this->create_subscription<ex1::msg::PostControllerCoolantTemp>(
			"post_controller_coolant_temp", qos, [this](const ex1::msg::PostControllerCoolantTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* postcontrollercoolanttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->postcontrollercoolanttemp))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 264);
			}
		);

		/* 0x109: RadiatorCoolSideCoolantTemp */
		radiator_cool_side_coolant_temp_sub_ = this->create_subscription<ex1::msg::RadiatorCoolSideCoolantTemp>(
			"radiator_cool_side_coolant_temp", qos, [this](const ex1::msg::RadiatorCoolSideCoolantTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* radiatorcoolsidecoolanttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->radiatorcoolsidecoolanttemp))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 265);
			}
		);

		/* 0x10a: AmbientTemp */
		ambient_temp_sub_ = this->create_subscription<ex1::msg::AmbientTemp>(
			"ambient_temp", qos, [this](const ex1::msg::AmbientTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* ambienttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->ambienttemp))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 266);
			}
		);

		/* 0x10b: GPSLatAndValidityStatus */
		gps_lat_and_validity_status_sub_ = this->create_subscription<ex1::msg::GPSLatAndValidityStatus>(
			"gps_lat_and_validity_status", qos, [this](const ex1::msg::GPSLatAndValidityStatus::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* gpslatitude: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->gpslatitude))) & 0xffffffff;
				i |= x;
				/* gpsvaliditystatus: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->gpsvaliditystatus))) & 0xff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 5, 267);
			}
		);

		/* 0x10c: GPSLongitude */
		gps_longitude_sub_ = this->create_subscription<ex1::msg::GPSLongitude>(
			"gps_longitude", qos, [this](const ex1::msg::GPSLongitude::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* gpslongitude: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->gpslongitude))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 268);
			}
		);

		/* 0x10d: GPSAltitudeAndAccuracy */
		gps_altitude_and_accuracy_sub_ = this->create_subscription<ex1::msg::GPSAltitudeAndAccuracy>(
			"gps_altitude_and_accuracy", qos, [this](const ex1::msg::GPSAltitudeAndAccuracy::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* gpsaltitude: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->gpsaltitude))) & 0xffffffff;
				i |= x;
				/* positiondop: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->positiondop))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 269);
			}
		);

		/* 0x10e: CurrentTime */
		current_time_sub_ = this->create_subscription<ex1::msg::CurrentTime>(
			"current_time", qos, [this](const ex1::msg::CurrentTime::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* years: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->years))) & 0xffff;
				i |= x;
				/* month: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->month))) & 0xff;
				x <<= 16; 
				i |= x;
				/* day: start-bit 24, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->day))) & 0xff;
				x <<= 24; 
				i |= x;
				/* hours: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->hours))) & 0xff;
				x <<= 32; 
				i |= x;
				/* minutes: start-bit 40, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->minutes))) & 0xff;
				x <<= 40; 
				i |= x;
				/* seconds: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->seconds))) & 0xff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 7, 270);
			}
		);

		/* 0x10f: IMUAccelerationMeasurement */
		imu_acceleration_measurement_sub_ = this->create_subscription<ex1::msg::IMUAccelerationMeasurement>(
			"imu_acceleration_measurement", qos, [this](const ex1::msg::IMUAccelerationMeasurement::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* xaxisacceleration: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->xaxisacceleration))) & 0xffff;
				i |= x;
				/* yaxisacceleration: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->yaxisacceleration))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* zaxisacceleration: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->zaxisacceleration))) & 0xffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 6, 271);
			}
		);

		/* 0x110: IMUGyroMeasurement */
		imu_gyro_measurement_sub_ = this->create_subscription<ex1::msg::IMUGyroMeasurement>(
			"imu_gyro_measurement", qos, [this](const ex1::msg::IMUGyroMeasurement::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* xaxisroll: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->xaxisroll))) & 0xffff;
				i |= x;
				/* yaxisroll: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->yaxisroll))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* zaxisroll: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->zaxisroll))) & 0xffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 6, 272);
			}
		);

		/* 0x111: MotorPlateTemp */
		motor_plate_temp_sub_ = this->create_subscription<ex1::msg::MotorPlateTemp>(
			"motor_plate_temp", qos, [this](const ex1::msg::MotorPlateTemp::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motorplatetemp1: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorplatetemp1))) & 0xffffffff;
				i |= x;
				/* motorplatetemp2: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorplatetemp2))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 273);
			}
		);

		/* 0x300: BIM1CellStatistics1 */
		bim1_cell_statistics1_sub_ = this->create_subscription<ex1::msg::BIM1CellStatistics1>(
			"bim1_cell_statistics1", qos, [this](const ex1::msg::BIM1CellStatistics1::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim1maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim1maxcellvoltage))) & 0xffff;
				i |= x;
				/* bim1maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim1maxcellnumber))) & 0xff;
				x <<= 16; 
				i |= x;
				/* bim1mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim1mincellvoltage))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* bim1mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim1mincellnumber))) & 0xff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 7, 768);
			}
		);

		/* 0x301: BIM1CellStatistics2 */
		bim1_cell_statistics2_sub_ = this->create_subscription<ex1::msg::BIM1CellStatistics2>(
			"bim1_cell_statistics2", qos, [this](const ex1::msg::BIM1CellStatistics2::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim1avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim1avgcellvoltage))) & 0xffff;
				i |= x;
				/* bim1stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim1stdevcellvoltage))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* bim1numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim1numberbalancingcells))) & 0xff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 5, 769);
			}
		);

		/* 0x302: BIM2CellStatisitcs1 */
		bim2_cell_statisitcs1_sub_ = this->create_subscription<ex1::msg::BIM2CellStatisitcs1>(
			"bim2_cell_statisitcs1", qos, [this](const ex1::msg::BIM2CellStatisitcs1::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim2maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim2maxcellvoltage))) & 0xffff;
				i |= x;
				/* bim2maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim2maxcellnumber))) & 0xff;
				x <<= 16; 
				i |= x;
				/* bim2mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim2mincellvoltage))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* bim2mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim2mincellnumber))) & 0xff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 7, 770);
			}
		);

		/* 0x303: BIM2CellStatistics2 */
		bim2_cell_statistics2_sub_ = this->create_subscription<ex1::msg::BIM2CellStatistics2>(
			"bim2_cell_statistics2", qos, [this](const ex1::msg::BIM2CellStatistics2::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim2avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim2avgcellvoltage))) & 0xffff;
				i |= x;
				/* bim2stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim2stdevcellvoltage))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* bim2numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim2numberbalancingcells))) & 0xff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 5, 771);
			}
		);

		/* 0x304: BIM3CellStatisitcs1 */
		bim3_cell_statisitcs1_sub_ = this->create_subscription<ex1::msg::BIM3CellStatisitcs1>(
			"bim3_cell_statisitcs1", qos, [this](const ex1::msg::BIM3CellStatisitcs1::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim3maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim3maxcellvoltage))) & 0xffff;
				i |= x;
				/* bim3maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim3maxcellnumber))) & 0xff;
				x <<= 16; 
				i |= x;
				/* bim3mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim3mincellvoltage))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* bim3mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim3mincellnumber))) & 0xff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 7, 772);
			}
		);

		/* 0x305: BIM3CellStatistics2 */
		bim3_cell_statistics2_sub_ = this->create_subscription<ex1::msg::BIM3CellStatistics2>(
			"bim3_cell_statistics2", qos, [this](const ex1::msg::BIM3CellStatistics2::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim3avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim3avgcellvoltage))) & 0xffff;
				i |= x;
				/* bim3stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim3stdevcellvoltage))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* bim3numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim3numberbalancingcells))) & 0xff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 5, 773);
			}
		);

		/* 0x306: BIM4CellStatistics1 */
		bim4_cell_statistics1_sub_ = this->create_subscription<ex1::msg::BIM4CellStatistics1>(
			"bim4_cell_statistics1", qos, [this](const ex1::msg::BIM4CellStatistics1::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim4maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim4maxcellvoltage))) & 0xffff;
				i |= x;
				/* bim4maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim4maxcellnumber))) & 0xff;
				x <<= 16; 
				i |= x;
				/* bim4mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim4mincellvoltage))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* bim4mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim4mincellnumber))) & 0xff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 6, 774);
			}
		);

		/* 0x307: BIM4CellStatistics2 */
		bim4_cell_statistics2_sub_ = this->create_subscription<ex1::msg::BIM4CellStatistics2>(
			"bim4_cell_statistics2", qos, [this](const ex1::msg::BIM4CellStatistics2::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim4avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim4avgcellvoltage))) & 0xffff;
				i |= x;
				/* bim4stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim4stdevcellvoltage))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* bim4numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->bim4numberbalancingcells))) & 0xff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 5, 775);
			}
		);

		/* 0x310: Cells14 */
		cells14_sub_ = this->create_subscription<ex1::msg::Cells14>(
			"cells14", qos, [this](const ex1::msg::Cells14::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell1: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell1))) & 0x7fff;
				i |= x;
				/* cell1_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell1_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell2: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell2))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell2_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell2_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell3: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell3))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell3_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell3_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell4: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell4))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell4_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell4_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 784);
			}
		);

		/* 0x311: Cells58 */
		cells58_sub_ = this->create_subscription<ex1::msg::Cells58>(
			"cells58", qos, [this](const ex1::msg::Cells58::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell5: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell5))) & 0x7fff;
				i |= x;
				/* cell5_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell5_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell6: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell6))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell6_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell6_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell7: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell7))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell7_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell7_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell8: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell8))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell8_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell8_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 785);
			}
		);

		/* 0x312: Cells912 */
		cells912_sub_ = this->create_subscription<ex1::msg::Cells912>(
			"cells912", qos, [this](const ex1::msg::Cells912::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell9: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell9))) & 0x7fff;
				i |= x;
				/* cell9_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell9_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell10: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell10))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell10_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell10_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell11: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell11))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell11_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell11_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell12: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell12))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell12_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell12_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 786);
			}
		);

		/* 0x8501930: OdometerVelocity */
		odometer_velocity_sub_ = this->create_subscription<ex1::msg::OdometerVelocity>(
			"odometer_velocity", qos, [this](const ex1::msg::OdometerVelocity::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t m = 0;
				/* odometer_velocity: start-bit 7, length 32, endianess motorola, scaling 1, offset 0 */
				x = ((uint32_t)((msg->odometer_velocity))) & 0xffffffff;
				x <<= 32; 
				m |= x;
				uint64_t data = reverse_byte_order(m);
				publishFrame(data, 6, 139467056);
			}
		);

		/* 0x313: Cells1316 */
		cells1316_sub_ = this->create_subscription<ex1::msg::Cells1316>(
			"cells1316", qos, [this](const ex1::msg::Cells1316::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell13: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell13))) & 0x7fff;
				i |= x;
				/* cell13_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell13_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell14: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell14))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell14_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell14_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell15: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell15))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell15_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell15_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell16: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell16))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell16_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell16_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 787);
			}
		);

		/* 0x314: Cells1720 */
		cells1720_sub_ = this->create_subscription<ex1::msg::Cells1720>(
			"cells1720", qos, [this](const ex1::msg::Cells1720::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell17: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell17))) & 0x7fff;
				i |= x;
				/* cell17_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell17_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell18: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell18))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell18_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell18_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell19: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell19))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell19_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell19_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell20: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell20))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell20_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell20_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 788);
			}
		);

		/* 0x315: Cells2124 */
		cells2124_sub_ = this->create_subscription<ex1::msg::Cells2124>(
			"cells2124", qos, [this](const ex1::msg::Cells2124::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell21: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell21))) & 0x7fff;
				i |= x;
				/* cell21_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell21_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell22: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell22))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell22_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell22_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell23: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell23))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell23_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell23_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell24: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell24))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell24_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell24_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 789);
			}
		);

		/* 0x316: Cells2528 */
		cells2528_sub_ = this->create_subscription<ex1::msg::Cells2528>(
			"cells2528", qos, [this](const ex1::msg::Cells2528::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell25: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell25))) & 0x7fff;
				i |= x;
				/* cell25_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell25_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell26: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell26))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell26_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell26_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell27: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell27))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell27_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell27_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell28: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell28))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell28_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell28_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 790);
			}
		);

		/* 0x317: Cells2932 */
		cells2932_sub_ = this->create_subscription<ex1::msg::Cells2932>(
			"cells2932", qos, [this](const ex1::msg::Cells2932::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell29: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell29))) & 0x7fff;
				i |= x;
				/* cell29_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell29_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell30: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell30))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell30_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell30_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell31: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell31))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell31_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell31_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell32: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell32))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell32_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell32_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 791);
			}
		);

		/* 0x318: Cells3336 */
		cells3336_sub_ = this->create_subscription<ex1::msg::Cells3336>(
			"cells3336", qos, [this](const ex1::msg::Cells3336::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell33: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell33))) & 0x7fff;
				i |= x;
				/* cell33_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell33_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell34: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell34))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell34_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell34_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell35: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell35))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell35_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell35_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell36: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell36))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell36_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell36_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 792);
			}
		);

		/* 0x319: Cells3740 */
		cells3740_sub_ = this->create_subscription<ex1::msg::Cells3740>(
			"cells3740", qos, [this](const ex1::msg::Cells3740::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell37: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell37))) & 0x7fff;
				i |= x;
				/* cell37_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell37_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell38: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell38))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell38_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell38_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell39: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell39))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell39_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell39_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell40: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell40))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell40_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell40_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 793);
			}
		);

		/* 0x31a: Cells4144 */
		cells4144_sub_ = this->create_subscription<ex1::msg::Cells4144>(
			"cells4144", qos, [this](const ex1::msg::Cells4144::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell41: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell41))) & 0x7fff;
				i |= x;
				/* cell41_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell41_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell42: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell42))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell42_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell42_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell43: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell43))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell43_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell43_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell44: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell44))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell44_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell44_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 794);
			}
		);

		/* 0x31b: Cells4548 */
		cells4548_sub_ = this->create_subscription<ex1::msg::Cells4548>(
			"cells4548", qos, [this](const ex1::msg::Cells4548::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell45: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell45))) & 0x7fff;
				i |= x;
				/* cell45_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell45_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell46: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell46))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell46_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell46_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell47: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell47))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell47_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell47_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell48: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell48))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell48_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell48_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 795);
			}
		);

		/* 0x31c: Cells4952 */
		cells4952_sub_ = this->create_subscription<ex1::msg::Cells4952>(
			"cells4952", qos, [this](const ex1::msg::Cells4952::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell49: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell49))) & 0x7fff;
				i |= x;
				/* cell49_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell49_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell50: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell50))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell50_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell50_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell51: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell51))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell51_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell51_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell52: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell52))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell52_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell52_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 796);
			}
		);

		/* 0x31d: Cells5354 */
		cells5354_sub_ = this->create_subscription<ex1::msg::Cells5354>(
			"cells5354", qos, [this](const ex1::msg::Cells5354::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell53: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell53))) & 0x7fff;
				i |= x;
				/* cell53_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell53_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell54: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell54))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell54_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell54_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 797);
			}
		);

		/* 0x31e: Cells5558 */
		cells5558_sub_ = this->create_subscription<ex1::msg::Cells5558>(
			"cells5558", qos, [this](const ex1::msg::Cells5558::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell55: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell55))) & 0x7fff;
				i |= x;
				/* cell55_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell55_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell56: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell56))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell56_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell56_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell57: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell57))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell57_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell57_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell58: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell58))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell58_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell58_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 798);
			}
		);

		/* 0x31f: Cells5962 */
		cells5962_sub_ = this->create_subscription<ex1::msg::Cells5962>(
			"cells5962", qos, [this](const ex1::msg::Cells5962::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell59: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell59))) & 0x7fff;
				i |= x;
				/* cell59_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell59_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell60: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell60))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell60_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell60_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell61: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell61))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell61_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell61_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell62: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell62))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell62_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell62_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 799);
			}
		);

		/* 0x320: Cells6366 */
		cells6366_sub_ = this->create_subscription<ex1::msg::Cells6366>(
			"cells6366", qos, [this](const ex1::msg::Cells6366::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell63: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell63))) & 0x7fff;
				i |= x;
				/* cell63_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell63_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell64: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell64))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell64_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell64_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell65: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell65))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell65_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell65_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell66: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell66))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell66_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell66_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 800);
			}
		);

		/* 0x321: Cells6770 */
		cells6770_sub_ = this->create_subscription<ex1::msg::Cells6770>(
			"cells6770", qos, [this](const ex1::msg::Cells6770::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell67: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell67))) & 0x7fff;
				i |= x;
				/* cell67_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell67_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell68: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell68))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell68_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell68_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell69: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell69))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell69_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell69_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell70: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell70))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell70_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell70_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 801);
			}
		);

		/* 0x322: Cells7174 */
		cells7174_sub_ = this->create_subscription<ex1::msg::Cells7174>(
			"cells7174", qos, [this](const ex1::msg::Cells7174::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell71: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell71))) & 0x7fff;
				i |= x;
				/* cell71_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell71_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell72: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell72))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell72_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell72_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell73: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell73))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell73_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell73_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell74: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell74))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell74_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell74_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 802);
			}
		);

		/* 0x323: Cells7578 */
		cells7578_sub_ = this->create_subscription<ex1::msg::Cells7578>(
			"cells7578", qos, [this](const ex1::msg::Cells7578::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell75: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell75))) & 0x7fff;
				i |= x;
				/* cell75_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell75_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell76: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell76))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell76_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell76_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell77: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell77))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell77_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell77_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell78: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell78))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell78_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell78_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 803);
			}
		);

		/* 0x324: Cells7982 */
		cells7982_sub_ = this->create_subscription<ex1::msg::Cells7982>(
			"cells7982", qos, [this](const ex1::msg::Cells7982::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell79: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell79))) & 0x7fff;
				i |= x;
				/* cell79_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell79_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell80: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell80))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell80_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell80_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell81: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell81))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell81_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell81_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell82: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell82))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell82_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell82_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 804);
			}
		);

		/* 0x325: Cells8386 */
		cells8386_sub_ = this->create_subscription<ex1::msg::Cells8386>(
			"cells8386", qos, [this](const ex1::msg::Cells8386::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell83: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell83))) & 0x7fff;
				i |= x;
				/* cell83_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell83_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell84: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell84))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell84_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell84_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell85: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell85))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell85_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell85_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell86: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell86))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell86_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell86_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 805);
			}
		);

		/* 0x326: Cells8790 */
		cells8790_sub_ = this->create_subscription<ex1::msg::Cells8790>(
			"cells8790", qos, [this](const ex1::msg::Cells8790::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell87: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell87))) & 0x7fff;
				i |= x;
				/* cell87_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell87_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell88: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell88))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell88_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell88_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell89: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell89))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell89_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell89_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell90: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell90))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell90_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell90_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 806);
			}
		);

		/* 0x327: Cells9194 */
		cells9194_sub_ = this->create_subscription<ex1::msg::Cells9194>(
			"cells9194", qos, [this](const ex1::msg::Cells9194::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell91: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell91))) & 0x7fff;
				i |= x;
				/* cell91_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell91_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell92: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell92))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell92_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell92_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell93: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell93))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell93_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell93_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell94: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell94))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell94_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell94_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 807);
			}
		);

		/* 0x328: Cells9598 */
		cells9598_sub_ = this->create_subscription<ex1::msg::Cells9598>(
			"cells9598", qos, [this](const ex1::msg::Cells9598::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell95: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell95))) & 0x7fff;
				i |= x;
				/* cell95_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell95_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell96: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell96))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell96_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell96_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell97: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell97))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell97_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell97_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell98: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell98))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell98_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell98_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 808);
			}
		);

		/* 0x329: Cells99102 */
		cells99102_sub_ = this->create_subscription<ex1::msg::Cells99102>(
			"cells99102", qos, [this](const ex1::msg::Cells99102::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell99: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell99))) & 0x7fff;
				i |= x;
				/* cell99_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell99_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell100: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell100))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell100_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell100_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell101: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell101))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell101_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell101_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell102: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell102))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell102_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell102_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 809);
			}
		);

		/* 0x32a: Cells103106 */
		cells103106_sub_ = this->create_subscription<ex1::msg::Cells103106>(
			"cells103106", qos, [this](const ex1::msg::Cells103106::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell103: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell103))) & 0x7fff;
				i |= x;
				/* cell103_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell103_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell104: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell104))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell104_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell104_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell105: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell105))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell105_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell105_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell106: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell106))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell106_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell106_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 810);
			}
		);

		/* 0x32b: Cells107110 */
		cells107110_sub_ = this->create_subscription<ex1::msg::Cells107110>(
			"cells107110", qos, [this](const ex1::msg::Cells107110::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cell107: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell107))) & 0x7fff;
				i |= x;
				/* cell107_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell107_bal))) & 0x1;
				x <<= 15; 
				i |= x;
				/* cell108: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell108))) & 0x7fff;
				x <<= 16; 
				i |= x;
				/* cell108_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell108_bal))) & 0x1;
				x <<= 31; 
				i |= x;
				/* cell109: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell109))) & 0x7fff;
				x <<= 32; 
				i |= x;
				/* cell109_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell109_bal))) & 0x1;
				x <<= 47; 
				i |= x;
				/* cell110: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cell110))) & 0x7fff;
				x <<= 48; 
				i |= x;
				/* cell110_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->cell110_bal))) & 0x1;
				x <<= 63; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 811);
			}
		);

		/* 0x335: PackTemperatures1Thru4 */
		pack_temperatures1_thru4_sub_ = this->create_subscription<ex1::msg::PackTemperatures1Thru4>(
			"pack_temperatures1_thru4", qos, [this](const ex1::msg::PackTemperatures1Thru4::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp1: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp1))) & 0xffff;
				i |= x;
				/* temp2: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp2))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp3: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp3))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temp4: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp4))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 821);
			}
		);

		/* 0x336: PackTempeartures5Thru8 */
		pack_tempeartures5_thru8_sub_ = this->create_subscription<ex1::msg::PackTempeartures5Thru8>(
			"pack_tempeartures5_thru8", qos, [this](const ex1::msg::PackTempeartures5Thru8::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp5: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp5))) & 0xffff;
				i |= x;
				/* temp6: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp6))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp7: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp7))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temp8: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp8))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 822);
			}
		);

		/* 0x337: PackTemperatures9Thru14 */
		pack_temperatures9_thru14_sub_ = this->create_subscription<ex1::msg::PackTemperatures9Thru14>(
			"pack_temperatures9_thru14", qos, [this](const ex1::msg::PackTemperatures9Thru14::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp9: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp9))) & 0xffff;
				i |= x;
				/* temp10: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp10))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp11: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp11))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temp12: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp12))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 823);
			}
		);

		/* 0x338: PackTemperatures13Thru14 */
		pack_temperatures13_thru14_sub_ = this->create_subscription<ex1::msg::PackTemperatures13Thru14>(
			"pack_temperatures13_thru14", qos, [this](const ex1::msg::PackTemperatures13Thru14::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp13: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp13))) & 0xffff;
				i |= x;
				/* temp14: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp14))) & 0xffff;
				x <<= 16; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 824);
			}
		);

		/* 0x339: PackTemperatures15Thru18 */
		pack_temperatures15_thru18_sub_ = this->create_subscription<ex1::msg::PackTemperatures15Thru18>(
			"pack_temperatures15_thru18", qos, [this](const ex1::msg::PackTemperatures15Thru18::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp15: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp15))) & 0xffff;
				i |= x;
				/* temp16: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp16))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp17: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp17))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temo18: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temo18))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 825);
			}
		);

		/* 0x33a: PackTemperatures19Thru22 */
		pack_temperatures19_thru22_sub_ = this->create_subscription<ex1::msg::PackTemperatures19Thru22>(
			"pack_temperatures19_thru22", qos, [this](const ex1::msg::PackTemperatures19Thru22::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp19: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp19))) & 0xffff;
				i |= x;
				/* temp20: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp20))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp21: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp21))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temo22: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temo22))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 826);
			}
		);

		/* 0x33b: PackTemperatures23Thru26 */
		pack_temperatures23_thru26_sub_ = this->create_subscription<ex1::msg::PackTemperatures23Thru26>(
			"pack_temperatures23_thru26", qos, [this](const ex1::msg::PackTemperatures23Thru26::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp23: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp23))) & 0xffff;
				i |= x;
				/* temp24: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp24))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp25: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp25))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temo26: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temo26))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 827);
			}
		);

		/* 0x33c: PackTemperatures27Thru30 */
		pack_temperatures27_thru30_sub_ = this->create_subscription<ex1::msg::PackTemperatures27Thru30>(
			"pack_temperatures27_thru30", qos, [this](const ex1::msg::PackTemperatures27Thru30::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp27: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp27))) & 0xffff;
				i |= x;
				/* temp28: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp28))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp29: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp29))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temo30: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temo30))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 828);
			}
		);

		/* 0x33d: PackTemperatures31Thru34 */
		pack_temperatures31_thru34_sub_ = this->create_subscription<ex1::msg::PackTemperatures31Thru34>(
			"pack_temperatures31_thru34", qos, [this](const ex1::msg::PackTemperatures31Thru34::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp31: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp31))) & 0xffff;
				i |= x;
				/* temp32: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp32))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp33: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp33))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temo34: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temo34))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 829);
			}
		);

		/* 0x33e: PackTemperatures35Thru38 */
		pack_temperatures35_thru38_sub_ = this->create_subscription<ex1::msg::PackTemperatures35Thru38>(
			"pack_temperatures35_thru38", qos, [this](const ex1::msg::PackTemperatures35Thru38::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp35: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp35))) & 0xffff;
				i |= x;
				/* temp36: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp36))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp37: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp37))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temo38: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temo38))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 830);
			}
		);

		/* 0x33f: PackTemperatures39Thru42 */
		pack_temperatures39_thru42_sub_ = this->create_subscription<ex1::msg::PackTemperatures39Thru42>(
			"pack_temperatures39_thru42", qos, [this](const ex1::msg::PackTemperatures39Thru42::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* temp39: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp39))) & 0xffff;
				i |= x;
				/* temp40: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp40))) & 0xffff;
				x <<= 16; 
				i |= x;
				/* temp41: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temp41))) & 0xffff;
				x <<= 32; 
				i |= x;
				/* temo42: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->temo42))) & 0xffff;
				x <<= 48; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 831);
			}
		);

		/* 0x501: MotorDriveCommand */
		motor_drive_command_sub_ = this->create_subscription<ex1::msg::MotorDriveCommand>(
			"motor_drive_command", qos, [this](const ex1::msg::MotorDriveCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motorvelocitycommand: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorvelocitycommand))) & 0xffffffff;
				i |= x;
				/* motorcurrentcommand: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorcurrentcommand))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1281);
			}
		);

		/* 0x502: MotorPowerCommand */
		motor_power_command_sub_ = this->create_subscription<ex1::msg::MotorPowerCommand>(
			"motor_power_command", qos, [this](const ex1::msg::MotorPowerCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* buscurrentcommand: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->buscurrentcommand))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1282);
			}
		);

		/* 0x401: StatusInformation */
		status_information_sub_ = this->create_subscription<ex1::msg::StatusInformation>(
			"status_information", qos, [this](const ex1::msg::StatusInformation::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* limit_outputvolt_pwm: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->limit_outputvolt_pwm))) & 0x1;
				i |= x;
				/* limit_motor_current: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->limit_motor_current))) & 0x1;
				x <<= 1; 
				i |= x;
				/* limit_velocity: start-bit 2, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->limit_velocity))) & 0x1;
				x <<= 2; 
				i |= x;
				/* limit_bus_current: start-bit 3, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->limit_bus_current))) & 0x1;
				x <<= 3; 
				i |= x;
				/* limit_bus_volt_upper: start-bit 4, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->limit_bus_volt_upper))) & 0x1;
				x <<= 4; 
				i |= x;
				/* limit_bus_volt_lower: start-bit 5, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->limit_bus_volt_lower))) & 0x1;
				x <<= 5; 
				i |= x;
				/* limit_temp: start-bit 6, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->limit_temp))) & 0x1;
				x <<= 6; 
				i |= x;
				/* reserved_limit: start-bit 7, length 9, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->reserved_limit))) & 0x1ff;
				x <<= 7; 
				i |= x;
				/* error_hardware_over_current: start-bit 16, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_hardware_over_current))) & 0x1;
				x <<= 16; 
				i |= x;
				/* error_software_over_current: start-bit 17, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_software_over_current))) & 0x1;
				x <<= 17; 
				i |= x;
				/* error_dc_over_volt: start-bit 18, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_dc_over_volt))) & 0x1;
				x <<= 18; 
				i |= x;
				/* error_bad_position: start-bit 19, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_bad_position))) & 0x1;
				x <<= 19; 
				i |= x;
				/* error_watchdog: start-bit 20, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_watchdog))) & 0x1;
				x <<= 20; 
				i |= x;
				/* error_configread: start-bit 21, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_configread))) & 0x1;
				x <<= 21; 
				i |= x;
				/* error_15v_under_volt: start-bit 22, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_15v_under_volt))) & 0x1;
				x <<= 22; 
				i |= x;
				/* error_desaturation: start-bit 23, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->error_desaturation))) & 0x1;
				x <<= 23; 
				i |= x;
				/* reserved_error: start-bit 24, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->reserved_error))) & 0xff;
				x <<= 24; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1025);
			}
		);

		/* 0x402: BusMeasurement */
		bus_measurement_sub_ = this->create_subscription<ex1::msg::BusMeasurement>(
			"bus_measurement", qos, [this](const ex1::msg::BusMeasurement::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* busvoltage: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->busvoltage))) & 0xffffffff;
				i |= x;
				/* buscurrent: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->buscurrent))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1026);
			}
		);

		/* 0x403: VelocityMeasurment */
		velocity_measurment_sub_ = this->create_subscription<ex1::msg::VelocityMeasurment>(
			"velocity_measurment", qos, [this](const ex1::msg::VelocityMeasurment::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motorvelocity: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorvelocity))) & 0xffffffff;
				i |= x;
				/* vehiclevelocity: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->vehiclevelocity))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1027);
			}
		);

		/* 0x404: PhaseCurrentMeasurment */
		phase_current_measurment_sub_ = this->create_subscription<ex1::msg::PhaseCurrentMeasurment>(
			"phase_current_measurment", qos, [this](const ex1::msg::PhaseCurrentMeasurment::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* phasebcurrent: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->phasebcurrent))) & 0xffffffff;
				i |= x;
				/* phaseccurrent: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->phaseccurrent))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1028);
			}
		);

		/* 0x405: MotorVoltage */
		motor_voltage_sub_ = this->create_subscription<ex1::msg::MotorVoltage>(
			"motor_voltage", qos, [this](const ex1::msg::MotorVoltage::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motorvq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorvq))) & 0xffffffff;
				i |= x;
				/* motorvd: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorvd))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1029);
			}
		);

		/* 0x406: MotorCurrent */
		motor_current_sub_ = this->create_subscription<ex1::msg::MotorCurrent>(
			"motor_current", qos, [this](const ex1::msg::MotorCurrent::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motoriq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motoriq))) & 0xffffffff;
				i |= x;
				/* motorid: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorid))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1030);
			}
		);

		/* 0x40b: MotorPhaseATemperature */
		motor_phase_a_temperature_sub_ = this->create_subscription<ex1::msg::MotorPhaseATemperature>(
			"motor_phase_a_temperature", qos, [this](const ex1::msg::MotorPhaseATemperature::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motortemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motortemp))) & 0xffffffff;
				i |= x;
				/* phaseatemp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->phaseatemp))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1035);
			}
		);

		/* 0x40e: Odometeramphours */
		odometeramphours_sub_ = this->create_subscription<ex1::msg::Odometeramphours>(
			"odometeramphours", qos, [this](const ex1::msg::Odometeramphours::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* odometer: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->odometer))) & 0xffffffff;
				i |= x;
				/* busamphours: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->busamphours))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1038);
			}
		);

		/* 0x407: BackEMF */
		back_emf_sub_ = this->create_subscription<ex1::msg::BackEMF>(
			"back_emf", qos, [this](const ex1::msg::BackEMF::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bemfq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->bemfq))) & 0xffffffff;
				i |= x;
				/* bemfd: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->bemfd))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1031);
			}
		);

		/* 0x408: Rail15v */
		rail15v_sub_ = this->create_subscription<ex1::msg::Rail15v>(
			"rail15v", qos, [this](const ex1::msg::Rail15v::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* supply15v: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->supply15v))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1032);
			}
		);

		/* 0x409: Rail3v31v9 */
		rail3v31v9_sub_ = this->create_subscription<ex1::msg::Rail3v31v9>(
			"rail3v31v9", qos, [this](const ex1::msg::Rail3v31v9::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* supply1v9: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->supply1v9))) & 0xffffffff;
				i |= x;
				/* supply3v3: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->supply3v3))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1033);
			}
		);

		/* 0x40c: PhaseBdsptemprature */
		phase_bdsptemprature_sub_ = this->create_subscription<ex1::msg::PhaseBdsptemprature>(
			"phase_bdsptemprature", qos, [this](const ex1::msg::PhaseBdsptemprature::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* dsp_temp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->dsp_temp))) & 0xffffffff;
				i |= x;
				/* phaseb_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->phaseb_temp))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1036);
			}
		);

		/* 0x020: MagicCanNode1RBootloaderAddress */
		magic_can_node1_r_bootloader_address_sub_ = this->create_subscription<ex1::msg::MagicCanNode1RBootloaderAddress>(
			"magic_can_node1_r_bootloader_address", qos, [this](const ex1::msg::MagicCanNode1RBootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magicnode1r_bladdy: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->magicnode1r_bladdy))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 32);
			}
		);

		/* 0x022: MagicCanNode2MBootloaderAddress */
		magic_can_node2_m_bootloader_address_sub_ = this->create_subscription<ex1::msg::MagicCanNode2MBootloaderAddress>(
			"magic_can_node2_m_bootloader_address", qos, [this](const ex1::msg::MagicCanNode2MBootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magicnode2m_bladdy: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->magicnode2m_bladdy))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 34);
			}
		);

		/* 0x024: MagicCanNode3FBootloaderAddress */
		magic_can_node3_f_bootloader_address_sub_ = this->create_subscription<ex1::msg::MagicCanNode3FBootloaderAddress>(
			"magic_can_node3_f_bootloader_address", qos, [this](const ex1::msg::MagicCanNode3FBootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magicnode3f_bladdy: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->magicnode3f_bladdy))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 36);
			}
		);

		/* 0x026: FrameFaultBootloaderAddres */
		frame_fault_bootloader_addres_sub_ = this->create_subscription<ex1::msg::FrameFaultBootloaderAddres>(
			"frame_fault_bootloader_addres", qos, [this](const ex1::msg::FrameFaultBootloaderAddres::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* framefaultbootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->framefaultbootloaderaddress))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 38);
			}
		);

		/* 0x028: FrameFaultCommand */
		frame_fault_command_sub_ = this->create_subscription<ex1::msg::FrameFaultCommand>(
			"frame_fault_command", qos, [this](const ex1::msg::FrameFaultCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* framefaultcommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->framefaultcommandvalue))) & 0xffffffff;
				i |= x;
				/* framefaultcommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->framefaultcommandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 40);
			}
		);

		/* 0x02c: DriveControlsBootloader */
		drive_controls_bootloader_sub_ = this->create_subscription<ex1::msg::DriveControlsBootloader>(
			"drive_controls_bootloader", qos, [this](const ex1::msg::DriveControlsBootloader::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* drivecontrolsbootloader: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->drivecontrolsbootloader))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 44);
			}
		);

		/* 0x02d: DriveControlsCommand */
		drive_controls_command_sub_ = this->create_subscription<ex1::msg::DriveControlsCommand>(
			"drive_controls_command", qos, [this](const ex1::msg::DriveControlsCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* drivecontrolcommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->drivecontrolcommandvalue))) & 0xffffffff;
				i |= x;
				/* drivecontrolcommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->drivecontrolcommandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 45);
			}
		);

		/* 0x030: CANMirrorBootloaderAddress */
		can_mirror_bootloader_address_sub_ = this->create_subscription<ex1::msg::CANMirrorBootloaderAddress>(
			"can_mirror_bootloader_address", qos, [this](const ex1::msg::CANMirrorBootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* canmirrorbootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->canmirrorbootloaderaddress))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 48);
			}
		);

		/* 0x032: CANMirrorCommand */
		can_mirror_command_sub_ = this->create_subscription<ex1::msg::CANMirrorCommand>(
			"can_mirror_command", qos, [this](const ex1::msg::CANMirrorCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* canmirrorcommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->canmirrorcommandvalue))) & 0xffffffff;
				i |= x;
				/* canmirrorcommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->canmirrorcommandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 50);
			}
		);

		/* 0x033: RiderDisplayBootloaderAddress */
		rider_display_bootloader_address_sub_ = this->create_subscription<ex1::msg::RiderDisplayBootloaderAddress>(
			"rider_display_bootloader_address", qos, [this](const ex1::msg::RiderDisplayBootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* riderdisplaybootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->riderdisplaybootloaderaddress))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 51);
			}
		);

		/* 0x035: RiderDisplayCommand */
		rider_display_command_sub_ = this->create_subscription<ex1::msg::RiderDisplayCommand>(
			"rider_display_command", qos, [this](const ex1::msg::RiderDisplayCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* riderdisplaycommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->riderdisplaycommandvalue))) & 0xffffffff;
				i |= x;
				/* riderdisplaycommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->riderdisplaycommandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 53);
			}
		);

		/* 0x039: BIM1BootloaderAddress */
		bim1_bootloader_address_sub_ = this->create_subscription<ex1::msg::BIM1BootloaderAddress>(
			"bim1_bootloader_address", qos, [this](const ex1::msg::BIM1BootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim1bootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim1bootloaderaddress))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 57);
			}
		);

		/* 0x03b: BIM2BootloaderAddress */
		bim2_bootloader_address_sub_ = this->create_subscription<ex1::msg::BIM2BootloaderAddress>(
			"bim2_bootloader_address", qos, [this](const ex1::msg::BIM2BootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim2bootloaderaddres: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim2bootloaderaddres))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 59);
			}
		);

		/* 0x03d: BIM3BootloaderAddress */
		bim3_bootloader_address_sub_ = this->create_subscription<ex1::msg::BIM3BootloaderAddress>(
			"bim3_bootloader_address", qos, [this](const ex1::msg::BIM3BootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim3bootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim3bootloaderaddress))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 61);
			}
		);

		/* 0x03f: BIM4BootloaderAddress */
		bim4_bootloader_address_sub_ = this->create_subscription<ex1::msg::BIM4BootloaderAddress>(
			"bim4_bootloader_address", qos, [this](const ex1::msg::BIM4BootloaderAddress::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim4bootloaderaddres: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->bim4bootloaderaddres))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 63);
			}
		);

		/* 0x0a0: MagicCanNode1RCommand */
		magic_can_node1_r_command_sub_ = this->create_subscription<ex1::msg::MagicCanNode1RCommand>(
			"magic_can_node1_r_command", qos, [this](const ex1::msg::MagicCanNode1RCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magiccannode1commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->magiccannode1commandvalue))) & 0xffffffff;
				i |= x;
				/* magiccannode1commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->magiccannode1commandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 160);
			}
		);

		/* 0x0a1: MagicCanNode2MCommand */
		magic_can_node2_m_command_sub_ = this->create_subscription<ex1::msg::MagicCanNode2MCommand>(
			"magic_can_node2_m_command", qos, [this](const ex1::msg::MagicCanNode2MCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magiccannode2commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->magiccannode2commandvalue))) & 0xffffffff;
				i |= x;
				/* magiccannode2commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->magiccannode2commandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 161);
			}
		);

		/* 0x0a2: MagicCanNode3FCommand */
		magic_can_node3_f_command_sub_ = this->create_subscription<ex1::msg::MagicCanNode3FCommand>(
			"magic_can_node3_f_command", qos, [this](const ex1::msg::MagicCanNode3FCommand::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* magiccannode3commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->magiccannode3commandvalue))) & 0xffffffff;
				i |= x;
				/* magiccannode3commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->magiccannode3commandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 162);
			}
		);

		/* 0x0aa: CANcorderHeartbeat */
		ca_ncorder_heartbeat_sub_ = this->create_subscription<ex1::msg::CANcorderHeartbeat>(
			"ca_ncorder_heartbeat", qos, [this](const ex1::msg::CANcorderHeartbeat::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* cancorderheartbeat: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->cancorderheartbeat))) & 0xffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 170);
			}
		);

		/* 0x0b0: BIM1Command */
		bim1_command_sub_ = this->create_subscription<ex1::msg::BIM1Command>(
			"bim1_command", qos, [this](const ex1::msg::BIM1Command::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim1commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim1commandvalue))) & 0xffffffff;
				i |= x;
				/* bim1commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim1commandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 176);
			}
		);

		/* 0x0b1: BIM2Command */
		bim2_command_sub_ = this->create_subscription<ex1::msg::BIM2Command>(
			"bim2_command", qos, [this](const ex1::msg::BIM2Command::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim2commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim2commandvalue))) & 0xffffffff;
				i |= x;
				/* bim2commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim2commandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 177);
			}
		);

		/* 0x0b2: BIM3Command */
		bim3_command_sub_ = this->create_subscription<ex1::msg::BIM3Command>(
			"bim3_command", qos, [this](const ex1::msg::BIM3Command::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim3commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim3commandvalue))) & 0xffffffff;
				i |= x;
				/* bim3commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim3commandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 178);
			}
		);

		/* 0x0b3: BIM4Command */
		bim4_command_sub_ = this->create_subscription<ex1::msg::BIM4Command>(
			"bim4_command", qos, [this](const ex1::msg::BIM4Command::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* bim4commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim4commandvalue))) & 0xffffffff;
				i |= x;
				/* bim4commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->bim4commandcode))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 179);
			}
		);

		/* 0x112: MotorScoop */
		motor_scoop_sub_ = this->create_subscription<ex1::msg::MotorScoop>(
			"motor_scoop", qos, [this](const ex1::msg::MotorScoop::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* motorscoop: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->motorscoop))) & 0xffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 274);
			}
		);

		/* 0x113: IMU1 */
		imu1_sub_ = this->create_subscription<ex1::msg::IMU1>(
			"imu1", qos, [this](const ex1::msg::IMU1::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* imuaccelx: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->imuaccelx))) & 0xffffffff;
				i |= x;
				/* imuaceely: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->imuaceely))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 275);
			}
		);

		/* 0x114: IMU2 */
		imu2_sub_ = this->create_subscription<ex1::msg::IMU2>(
			"imu2", qos, [this](const ex1::msg::IMU2::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* imuaccelz: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->imuaccelz))) & 0xffffffff;
				i |= x;
				/* gravityx: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->gravityx))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 276);
			}
		);

		/* 0x115: IMU3 */
		imu3_sub_ = this->create_subscription<ex1::msg::IMU3>(
			"imu3", qos, [this](const ex1::msg::IMU3::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* gravityy: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->gravityy))) & 0xffffffff;
				i |= x;
				/* gravityz: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->gravityz))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 277);
			}
		);

		/* 0x116: IMU4 */
		imu4_sub_ = this->create_subscription<ex1::msg::IMU4>(
			"imu4", qos, [this](const ex1::msg::IMU4::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* yaw: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->yaw))) & 0xffffffff;
				i |= x;
				/* pitch: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->pitch))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 278);
			}
		);

		/* 0x29a: IMU5 */
		imu5_sub_ = this->create_subscription<ex1::msg::IMU5>(
			"imu5", qos, [this](const ex1::msg::IMU5::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* multiplexor: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->multiplexor))) & 0xf;
				i |= x;
				/* multi2a: start-bit 6, length 2, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->multi2a))) & 0x3;
				x <<= 6; 
				i |= x;
				/* multi1: start-bit 8, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->multi1))) & 0xf;
				x <<= 8; 
				i |= x;
				/* multi2b: start-bit 8, length 2, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->multi2b))) & 0x3;
				x <<= 8; 
				i |= x;
				/* multi3: start-bit 8, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->multi3))) & 0xf;
				x <<= 8; 
				i |= x;
				/* multi4: start-bit 8, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->multi4))) & 0xf;
				x <<= 8; 
				i |= x;
				/* normal: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->normal))) & 0xff;
				x <<= 16; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 4, 666);
			}
		);

		/* 0x29b: MESSAGENAME */
		messagename_sub_ = this->create_subscription<ex1::msg::MESSAGENAME>(
			"messagename", qos, [this](const ex1::msg::MESSAGENAME::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t m = 0;
				/* nonsensesignal: start-bit 0, length 3, endianess motorola, scaling 1, offset 0 */
				x = ((uint8_t)((msg->nonsensesignal))) & 0x7;
				x <<= 54; 
				m |= x;
				uint64_t data = reverse_byte_order(m);
				publishFrame(data, 1, 667);
			}
		);

		/* 0x29c: MESSAGENAME2 */
		messagename2_sub_ = this->create_subscription<ex1::msg::MESSAGENAME2>(
			"messagename2", qos, [this](const ex1::msg::MESSAGENAME2::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* placeholdersignal: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->placeholdersignal))) & 0xff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 1, 668);
			}
		);

		frame_subscription_ = this->create_subscription<can_msgs::msg::Frame>(
			"/can/ex1/read", qos, [this](const can_msgs::msg::Frame::SharedPtr msg) {
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

		magic_can_node1_r_heartbeat_pub_ = this->create_publisher<ex1::msg::MagicCanNode1RHeartbeat>("magic_can_node1_r_heartbeat", qos);
		magic_can_node2_heartbeat_pub_ = this->create_publisher<ex1::msg::MagicCanNode2Heartbeat>("magic_can_node2_heartbeat", qos);
		magic_can_node3_heartbeat_pub_ = this->create_publisher<ex1::msg::MagicCanNode3Heartbeat>("magic_can_node3_heartbeat", qos);
		frame_fault_heartbeat_pub_ = this->create_publisher<ex1::msg::FrameFaultHeartbeat>("frame_fault_heartbeat", qos);
		drive_controls_heartbeat_pub_ = this->create_publisher<ex1::msg::DriveControlsHeartbeat>("drive_controls_heartbeat", qos);
		can_mirror_heatbeart_pub_ = this->create_publisher<ex1::msg::CANMirrorHeatbeart>("can_mirror_heatbeart", qos);
		rider_display_heartbeat_pub_ = this->create_publisher<ex1::msg::RiderDisplayHeartbeat>("rider_display_heartbeat", qos);
		bim1_heartbeat_pub_ = this->create_publisher<ex1::msg::BIM1Heartbeat>("bim1_heartbeat", qos);
		bim2_heartbeat_pub_ = this->create_publisher<ex1::msg::BIM2Heartbeat>("bim2_heartbeat", qos);
		bim3_heartbeat_pub_ = this->create_publisher<ex1::msg::BIM3Heartbeat>("bim3_heartbeat", qos);
		bim4_heartbeat_pub_ = this->create_publisher<ex1::msg::BIM4Heartbeat>("bim4_heartbeat", qos);
		frame_fault_detection_status_pub_ = this->create_publisher<ex1::msg::FrameFaultDetectionStatus>("frame_fault_detection_status", qos);
		front_brake_pressure_pub_ = this->create_publisher<ex1::msg::FrontBrakePressure>("front_brake_pressure", qos);
		rear_brake_pressure_pub_ = this->create_publisher<ex1::msg::RearBrakePressure>("rear_brake_pressure", qos);
		front_suspension_travel_pub_ = this->create_publisher<ex1::msg::FrontSuspensionTravel>("front_suspension_travel", qos);
		rear_suspension_travel_pub_ = this->create_publisher<ex1::msg::RearSuspensionTravel>("rear_suspension_travel", qos);
		bus_voltage12_v_pub_ = this->create_publisher<ex1::msg::BusVoltage12V>("bus_voltage12_v", qos);
		post_motor_coolant_temp_pub_ = this->create_publisher<ex1::msg::PostMotorCoolantTemp>("post_motor_coolant_temp", qos);
		post_controller_coolant_temp_pub_ = this->create_publisher<ex1::msg::PostControllerCoolantTemp>("post_controller_coolant_temp", qos);
		radiator_cool_side_coolant_temp_pub_ = this->create_publisher<ex1::msg::RadiatorCoolSideCoolantTemp>("radiator_cool_side_coolant_temp", qos);
		ambient_temp_pub_ = this->create_publisher<ex1::msg::AmbientTemp>("ambient_temp", qos);
		gps_lat_and_validity_status_pub_ = this->create_publisher<ex1::msg::GPSLatAndValidityStatus>("gps_lat_and_validity_status", qos);
		gps_longitude_pub_ = this->create_publisher<ex1::msg::GPSLongitude>("gps_longitude", qos);
		gps_altitude_and_accuracy_pub_ = this->create_publisher<ex1::msg::GPSAltitudeAndAccuracy>("gps_altitude_and_accuracy", qos);
		current_time_pub_ = this->create_publisher<ex1::msg::CurrentTime>("current_time", qos);
		imu_acceleration_measurement_pub_ = this->create_publisher<ex1::msg::IMUAccelerationMeasurement>("imu_acceleration_measurement", qos);
		imu_gyro_measurement_pub_ = this->create_publisher<ex1::msg::IMUGyroMeasurement>("imu_gyro_measurement", qos);
		motor_plate_temp_pub_ = this->create_publisher<ex1::msg::MotorPlateTemp>("motor_plate_temp", qos);
		bim1_cell_statistics1_pub_ = this->create_publisher<ex1::msg::BIM1CellStatistics1>("bim1_cell_statistics1", qos);
		bim1_cell_statistics2_pub_ = this->create_publisher<ex1::msg::BIM1CellStatistics2>("bim1_cell_statistics2", qos);
		bim2_cell_statisitcs1_pub_ = this->create_publisher<ex1::msg::BIM2CellStatisitcs1>("bim2_cell_statisitcs1", qos);
		bim2_cell_statistics2_pub_ = this->create_publisher<ex1::msg::BIM2CellStatistics2>("bim2_cell_statistics2", qos);
		bim3_cell_statisitcs1_pub_ = this->create_publisher<ex1::msg::BIM3CellStatisitcs1>("bim3_cell_statisitcs1", qos);
		bim3_cell_statistics2_pub_ = this->create_publisher<ex1::msg::BIM3CellStatistics2>("bim3_cell_statistics2", qos);
		bim4_cell_statistics1_pub_ = this->create_publisher<ex1::msg::BIM4CellStatistics1>("bim4_cell_statistics1", qos);
		bim4_cell_statistics2_pub_ = this->create_publisher<ex1::msg::BIM4CellStatistics2>("bim4_cell_statistics2", qos);
		cells14_pub_ = this->create_publisher<ex1::msg::Cells14>("cells14", qos);
		cells58_pub_ = this->create_publisher<ex1::msg::Cells58>("cells58", qos);
		cells912_pub_ = this->create_publisher<ex1::msg::Cells912>("cells912", qos);
		odometer_velocity_pub_ = this->create_publisher<ex1::msg::OdometerVelocity>("odometer_velocity", qos);
		cells1316_pub_ = this->create_publisher<ex1::msg::Cells1316>("cells1316", qos);
		cells1720_pub_ = this->create_publisher<ex1::msg::Cells1720>("cells1720", qos);
		cells2124_pub_ = this->create_publisher<ex1::msg::Cells2124>("cells2124", qos);
		cells2528_pub_ = this->create_publisher<ex1::msg::Cells2528>("cells2528", qos);
		cells2932_pub_ = this->create_publisher<ex1::msg::Cells2932>("cells2932", qos);
		cells3336_pub_ = this->create_publisher<ex1::msg::Cells3336>("cells3336", qos);
		cells3740_pub_ = this->create_publisher<ex1::msg::Cells3740>("cells3740", qos);
		cells4144_pub_ = this->create_publisher<ex1::msg::Cells4144>("cells4144", qos);
		cells4548_pub_ = this->create_publisher<ex1::msg::Cells4548>("cells4548", qos);
		cells4952_pub_ = this->create_publisher<ex1::msg::Cells4952>("cells4952", qos);
		cells5354_pub_ = this->create_publisher<ex1::msg::Cells5354>("cells5354", qos);
		cells5558_pub_ = this->create_publisher<ex1::msg::Cells5558>("cells5558", qos);
		cells5962_pub_ = this->create_publisher<ex1::msg::Cells5962>("cells5962", qos);
		cells6366_pub_ = this->create_publisher<ex1::msg::Cells6366>("cells6366", qos);
		cells6770_pub_ = this->create_publisher<ex1::msg::Cells6770>("cells6770", qos);
		cells7174_pub_ = this->create_publisher<ex1::msg::Cells7174>("cells7174", qos);
		cells7578_pub_ = this->create_publisher<ex1::msg::Cells7578>("cells7578", qos);
		cells7982_pub_ = this->create_publisher<ex1::msg::Cells7982>("cells7982", qos);
		cells8386_pub_ = this->create_publisher<ex1::msg::Cells8386>("cells8386", qos);
		cells8790_pub_ = this->create_publisher<ex1::msg::Cells8790>("cells8790", qos);
		cells9194_pub_ = this->create_publisher<ex1::msg::Cells9194>("cells9194", qos);
		cells9598_pub_ = this->create_publisher<ex1::msg::Cells9598>("cells9598", qos);
		cells99102_pub_ = this->create_publisher<ex1::msg::Cells99102>("cells99102", qos);
		cells103106_pub_ = this->create_publisher<ex1::msg::Cells103106>("cells103106", qos);
		cells107110_pub_ = this->create_publisher<ex1::msg::Cells107110>("cells107110", qos);
		pack_temperatures1_thru4_pub_ = this->create_publisher<ex1::msg::PackTemperatures1Thru4>("pack_temperatures1_thru4", qos);
		pack_tempeartures5_thru8_pub_ = this->create_publisher<ex1::msg::PackTempeartures5Thru8>("pack_tempeartures5_thru8", qos);
		pack_temperatures9_thru14_pub_ = this->create_publisher<ex1::msg::PackTemperatures9Thru14>("pack_temperatures9_thru14", qos);
		pack_temperatures13_thru14_pub_ = this->create_publisher<ex1::msg::PackTemperatures13Thru14>("pack_temperatures13_thru14", qos);
		pack_temperatures15_thru18_pub_ = this->create_publisher<ex1::msg::PackTemperatures15Thru18>("pack_temperatures15_thru18", qos);
		pack_temperatures19_thru22_pub_ = this->create_publisher<ex1::msg::PackTemperatures19Thru22>("pack_temperatures19_thru22", qos);
		pack_temperatures23_thru26_pub_ = this->create_publisher<ex1::msg::PackTemperatures23Thru26>("pack_temperatures23_thru26", qos);
		pack_temperatures27_thru30_pub_ = this->create_publisher<ex1::msg::PackTemperatures27Thru30>("pack_temperatures27_thru30", qos);
		pack_temperatures31_thru34_pub_ = this->create_publisher<ex1::msg::PackTemperatures31Thru34>("pack_temperatures31_thru34", qos);
		pack_temperatures35_thru38_pub_ = this->create_publisher<ex1::msg::PackTemperatures35Thru38>("pack_temperatures35_thru38", qos);
		pack_temperatures39_thru42_pub_ = this->create_publisher<ex1::msg::PackTemperatures39Thru42>("pack_temperatures39_thru42", qos);
		motor_drive_command_pub_ = this->create_publisher<ex1::msg::MotorDriveCommand>("motor_drive_command", qos);
		motor_power_command_pub_ = this->create_publisher<ex1::msg::MotorPowerCommand>("motor_power_command", qos);
		status_information_pub_ = this->create_publisher<ex1::msg::StatusInformation>("status_information", qos);
		bus_measurement_pub_ = this->create_publisher<ex1::msg::BusMeasurement>("bus_measurement", qos);
		velocity_measurment_pub_ = this->create_publisher<ex1::msg::VelocityMeasurment>("velocity_measurment", qos);
		phase_current_measurment_pub_ = this->create_publisher<ex1::msg::PhaseCurrentMeasurment>("phase_current_measurment", qos);
		motor_voltage_pub_ = this->create_publisher<ex1::msg::MotorVoltage>("motor_voltage", qos);
		motor_current_pub_ = this->create_publisher<ex1::msg::MotorCurrent>("motor_current", qos);
		motor_phase_a_temperature_pub_ = this->create_publisher<ex1::msg::MotorPhaseATemperature>("motor_phase_a_temperature", qos);
		odometeramphours_pub_ = this->create_publisher<ex1::msg::Odometeramphours>("odometeramphours", qos);
		back_emf_pub_ = this->create_publisher<ex1::msg::BackEMF>("back_emf", qos);
		rail15v_pub_ = this->create_publisher<ex1::msg::Rail15v>("rail15v", qos);
		rail3v31v9_pub_ = this->create_publisher<ex1::msg::Rail3v31v9>("rail3v31v9", qos);
		phase_bdsptemprature_pub_ = this->create_publisher<ex1::msg::PhaseBdsptemprature>("phase_bdsptemprature", qos);
		magic_can_node1_r_bootloader_address_pub_ = this->create_publisher<ex1::msg::MagicCanNode1RBootloaderAddress>("magic_can_node1_r_bootloader_address", qos);
		magic_can_node2_m_bootloader_address_pub_ = this->create_publisher<ex1::msg::MagicCanNode2MBootloaderAddress>("magic_can_node2_m_bootloader_address", qos);
		magic_can_node3_f_bootloader_address_pub_ = this->create_publisher<ex1::msg::MagicCanNode3FBootloaderAddress>("magic_can_node3_f_bootloader_address", qos);
		frame_fault_bootloader_addres_pub_ = this->create_publisher<ex1::msg::FrameFaultBootloaderAddres>("frame_fault_bootloader_addres", qos);
		frame_fault_command_pub_ = this->create_publisher<ex1::msg::FrameFaultCommand>("frame_fault_command", qos);
		drive_controls_bootloader_pub_ = this->create_publisher<ex1::msg::DriveControlsBootloader>("drive_controls_bootloader", qos);
		drive_controls_command_pub_ = this->create_publisher<ex1::msg::DriveControlsCommand>("drive_controls_command", qos);
		can_mirror_bootloader_address_pub_ = this->create_publisher<ex1::msg::CANMirrorBootloaderAddress>("can_mirror_bootloader_address", qos);
		can_mirror_command_pub_ = this->create_publisher<ex1::msg::CANMirrorCommand>("can_mirror_command", qos);
		rider_display_bootloader_address_pub_ = this->create_publisher<ex1::msg::RiderDisplayBootloaderAddress>("rider_display_bootloader_address", qos);
		rider_display_command_pub_ = this->create_publisher<ex1::msg::RiderDisplayCommand>("rider_display_command", qos);
		bim1_bootloader_address_pub_ = this->create_publisher<ex1::msg::BIM1BootloaderAddress>("bim1_bootloader_address", qos);
		bim2_bootloader_address_pub_ = this->create_publisher<ex1::msg::BIM2BootloaderAddress>("bim2_bootloader_address", qos);
		bim3_bootloader_address_pub_ = this->create_publisher<ex1::msg::BIM3BootloaderAddress>("bim3_bootloader_address", qos);
		bim4_bootloader_address_pub_ = this->create_publisher<ex1::msg::BIM4BootloaderAddress>("bim4_bootloader_address", qos);
		magic_can_node1_r_command_pub_ = this->create_publisher<ex1::msg::MagicCanNode1RCommand>("magic_can_node1_r_command", qos);
		magic_can_node2_m_command_pub_ = this->create_publisher<ex1::msg::MagicCanNode2MCommand>("magic_can_node2_m_command", qos);
		magic_can_node3_f_command_pub_ = this->create_publisher<ex1::msg::MagicCanNode3FCommand>("magic_can_node3_f_command", qos);
		ca_ncorder_heartbeat_pub_ = this->create_publisher<ex1::msg::CANcorderHeartbeat>("ca_ncorder_heartbeat", qos);
		bim1_command_pub_ = this->create_publisher<ex1::msg::BIM1Command>("bim1_command", qos);
		bim2_command_pub_ = this->create_publisher<ex1::msg::BIM2Command>("bim2_command", qos);
		bim3_command_pub_ = this->create_publisher<ex1::msg::BIM3Command>("bim3_command", qos);
		bim4_command_pub_ = this->create_publisher<ex1::msg::BIM4Command>("bim4_command", qos);
		motor_scoop_pub_ = this->create_publisher<ex1::msg::MotorScoop>("motor_scoop", qos);
		imu1_pub_ = this->create_publisher<ex1::msg::IMU1>("imu1", qos);
		imu2_pub_ = this->create_publisher<ex1::msg::IMU2>("imu2", qos);
		imu3_pub_ = this->create_publisher<ex1::msg::IMU3>("imu3", qos);
		imu4_pub_ = this->create_publisher<ex1::msg::IMU4>("imu4", qos);
		imu5_pub_ = this->create_publisher<ex1::msg::IMU5>("imu5", qos);
		messagename_pub_ = this->create_publisher<ex1::msg::MESSAGENAME>("messagename", qos);
		messagename2_pub_ = this->create_publisher<ex1::msg::MESSAGENAME2>("messagename2", qos);
		frame_publisher_ = this->create_publisher<can_msgs::msg::Frame>("/can/ex1/write", qos);
	}

	void decodeMessage(uint64_t data, uint8_t dlc, uint32_t id, const rclcpp::Time& timestamp) {
		switch(id) {
			case 213909870: { /* 0xcc0016e: MagicCanNode1RHeartbeat */
				if (dlc < 2) return;
				ex1::msg::MagicCanNode1RHeartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magicnode1flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.magicnode1flags = (uint16_t)(x);
				magic_can_node1_r_heartbeat_pub_->publish(msg);
				break;
			}
			case 35: { /* 0x023: MagicCanNode2Heartbeat */
				if (dlc < 2) return;
				ex1::msg::MagicCanNode2Heartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magicnode2flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.magicnode2flags = (uint16_t)(x);
				magic_can_node2_heartbeat_pub_->publish(msg);
				break;
			}
			case 37: { /* 0x025: MagicCanNode3Heartbeat */
				if (dlc < 2) return;
				ex1::msg::MagicCanNode3Heartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magicnode3flags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.magicnode3flags = (uint16_t)(x);
				magic_can_node3_heartbeat_pub_->publish(msg);
				break;
			}
			case 39: { /* 0x027: FrameFaultHeartbeat */
				if (dlc < 2) return;
				ex1::msg::FrameFaultHeartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* framefaultflags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.framefaultflags = (uint16_t)(x);
				frame_fault_heartbeat_pub_->publish(msg);
				break;
			}
			case 46: { /* 0x02e: DriveControlsHeartbeat */
				if (dlc < 2) return;
				ex1::msg::DriveControlsHeartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* drivecontroltritiumerror: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 1) & 0x1;
				msg.drivecontroltritiumerror = (uint8_t)(x);
				/* drivecontrolmaxerror: start-bit 2, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 2) & 0x1;
				msg.drivecontrolmaxerror = (uint8_t)(x);
				/* drivecontrolminerror: start-bit 3, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 3) & 0x1;
				msg.drivecontrolminerror = (uint8_t)(x);
				drive_controls_heartbeat_pub_->publish(msg);
				break;
			}
			case 49: { /* 0x031: CANMirrorHeatbeart */
				if (dlc < 2) return;
				ex1::msg::CANMirrorHeatbeart msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* canmirroroverflowcounter: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = i & 0xff;
				msg.canmirroroverflowcounter = (uint8_t)(x);
				/* timeout: start-bit 8, length 6, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0x3f;
				msg.timeout = (uint8_t)(x);
				/* mirror_can_error: start-bit 14, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 14) & 0x1;
				msg.mirror_can_error = (uint8_t)(x);
				/* mirror_cana_status: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.mirror_cana_status = (uint8_t)(x);
				can_mirror_heatbeart_pub_->publish(msg);
				break;
			}
			case 52: { /* 0x034: RiderDisplayHeartbeat */
				if (dlc < 2) return;
				ex1::msg::RiderDisplayHeartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* riderdisplayflags: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.riderdisplayflags = (uint16_t)(x);
				rider_display_heartbeat_pub_->publish(msg);
				break;
			}
			case 58: { /* 0x03a: BIM1Heartbeat */
				if (dlc < 2) return;
				ex1::msg::BIM1Heartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim1init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = i & 0x1;
				msg.bim1init = (uint8_t)(x);
				/* bim1spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 1) & 0x1;
				msg.bim1spi = (uint8_t)(x);
				/* bim1bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = (i >> 2) & 0x3f;
				msg.bim1bq = (uint8_t)(x);
				bim1_heartbeat_pub_->publish(msg);
				break;
			}
			case 60: { /* 0x03c: BIM2Heartbeat */
				if (dlc < 2) return;
				ex1::msg::BIM2Heartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim2init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = i & 0x1;
				msg.bim2init = (uint8_t)(x);
				/* bim2spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 1) & 0x1;
				msg.bim2spi = (uint8_t)(x);
				/* bim2bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = (i >> 2) & 0x3f;
				msg.bim2bq = (uint8_t)(x);
				bim2_heartbeat_pub_->publish(msg);
				break;
			}
			case 62: { /* 0x03e: BIM3Heartbeat */
				if (dlc < 2) return;
				ex1::msg::BIM3Heartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim3init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = i & 0x1;
				msg.bim3init = (uint8_t)(x);
				/* bim3spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 1) & 0x1;
				msg.bim3spi = (uint8_t)(x);
				/* bim3bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = (i >> 2) & 0x3f;
				msg.bim3bq = (uint8_t)(x);
				bim3_heartbeat_pub_->publish(msg);
				break;
			}
			case 64: { /* 0x040: BIM4Heartbeat */
				if (dlc < 2) return;
				ex1::msg::BIM4Heartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim4init: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = i & 0x1;
				msg.bim4init = (uint8_t)(x);
				/* bim4spi: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 1) & 0x1;
				msg.bim4spi = (uint8_t)(x);
				/* bim4bq: start-bit 2, length 6, endianess intel, scaling 1, offset 0 */
				x = (i >> 2) & 0x3f;
				msg.bim4bq = (uint8_t)(x);
				bim4_heartbeat_pub_->publish(msg);
				break;
			}
			case 256: { /* 0x100: FrameFaultDetectionStatus */
				if (dlc < 6) return;
				ex1::msg::FrameFaultDetectionStatus msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* estimatedpackframeresistance: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.estimatedpackframeresistance = unpack754_32(x);
				/* faultstatus: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.faultstatus = (uint16_t)(x);
				frame_fault_detection_status_pub_->publish(msg);
				break;
			}
			case 257: { /* 0x101: FrontBrakePressure */
				if (dlc < 4) return;
				ex1::msg::FrontBrakePressure msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* frontbrakepressure: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.frontbrakepressure = unpack754_32(x);
				front_brake_pressure_pub_->publish(msg);
				break;
			}
			case 258: { /* 0x102: RearBrakePressure */
				if (dlc < 4) return;
				ex1::msg::RearBrakePressure msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* rearbrakepressure: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.rearbrakepressure = unpack754_32(x);
				rear_brake_pressure_pub_->publish(msg);
				break;
			}
			case 259: { /* 0x103: FrontSuspensionTravel */
				if (dlc < 4) return;
				ex1::msg::FrontSuspensionTravel msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* frontsuspensionposition: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.frontsuspensionposition = unpack754_32(x);
				front_suspension_travel_pub_->publish(msg);
				break;
			}
			case 260: { /* 0x104: RearSuspensionTravel */
				if (dlc < 4) return;
				ex1::msg::RearSuspensionTravel msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* rearsuspensionposition: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.rearsuspensionposition = unpack754_32(x);
				rear_suspension_travel_pub_->publish(msg);
				break;
			}
			case 262: { /* 0x106: BusVoltage12V */
				if (dlc < 4) return;
				ex1::msg::BusVoltage12V msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* busvoltage12v: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.busvoltage12v = unpack754_32(x);
				bus_voltage12_v_pub_->publish(msg);
				break;
			}
			case 263: { /* 0x107: PostMotorCoolantTemp */
				if (dlc < 4) return;
				ex1::msg::PostMotorCoolantTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* postmotorcoolanttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.postmotorcoolanttemp = unpack754_32(x);
				post_motor_coolant_temp_pub_->publish(msg);
				break;
			}
			case 264: { /* 0x108: PostControllerCoolantTemp */
				if (dlc < 4) return;
				ex1::msg::PostControllerCoolantTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* postcontrollercoolanttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.postcontrollercoolanttemp = unpack754_32(x);
				post_controller_coolant_temp_pub_->publish(msg);
				break;
			}
			case 265: { /* 0x109: RadiatorCoolSideCoolantTemp */
				if (dlc < 4) return;
				ex1::msg::RadiatorCoolSideCoolantTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* radiatorcoolsidecoolanttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.radiatorcoolsidecoolanttemp = unpack754_32(x);
				radiator_cool_side_coolant_temp_pub_->publish(msg);
				break;
			}
			case 266: { /* 0x10a: AmbientTemp */
				if (dlc < 4) return;
				ex1::msg::AmbientTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* ambienttemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.ambienttemp = unpack754_32(x);
				ambient_temp_pub_->publish(msg);
				break;
			}
			case 267: { /* 0x10b: GPSLatAndValidityStatus */
				if (dlc < 5) return;
				ex1::msg::GPSLatAndValidityStatus msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* gpslatitude: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.gpslatitude = unpack754_32(x);
				/* gpsvaliditystatus: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xff;
				msg.gpsvaliditystatus = (uint8_t)(x);
				gps_lat_and_validity_status_pub_->publish(msg);
				break;
			}
			case 268: { /* 0x10c: GPSLongitude */
				if (dlc < 4) return;
				ex1::msg::GPSLongitude msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* gpslongitude: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.gpslongitude = unpack754_32(x);
				gps_longitude_pub_->publish(msg);
				break;
			}
			case 269: { /* 0x10d: GPSAltitudeAndAccuracy */
				if (dlc < 8) return;
				ex1::msg::GPSAltitudeAndAccuracy msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* gpsaltitude: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.gpsaltitude = unpack754_32(x);
				/* positiondop: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.positiondop = unpack754_32(x);
				gps_altitude_and_accuracy_pub_->publish(msg);
				break;
			}
			case 270: { /* 0x10e: CurrentTime */
				if (dlc < 7) return;
				ex1::msg::CurrentTime msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* years: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.years = (uint16_t)(x);
				/* month: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xff;
				msg.month = (uint8_t)(x);
				/* day: start-bit 24, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 24) & 0xff;
				msg.day = (uint8_t)(x);
				/* hours: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xff;
				msg.hours = (uint8_t)(x);
				/* minutes: start-bit 40, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 40) & 0xff;
				msg.minutes = (uint8_t)(x);
				/* seconds: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xff;
				msg.seconds = (uint8_t)(x);
				current_time_pub_->publish(msg);
				break;
			}
			case 271: { /* 0x10f: IMUAccelerationMeasurement */
				if (dlc < 6) return;
				ex1::msg::IMUAccelerationMeasurement msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* xaxisacceleration: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.xaxisacceleration = (int16_t)(x);
				/* yaxisacceleration: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.yaxisacceleration = (int16_t)(x);
				/* zaxisacceleration: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.zaxisacceleration = (int16_t)(x);
				imu_acceleration_measurement_pub_->publish(msg);
				break;
			}
			case 272: { /* 0x110: IMUGyroMeasurement */
				if (dlc < 6) return;
				ex1::msg::IMUGyroMeasurement msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* xaxisroll: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.xaxisroll = (int16_t)(x);
				/* yaxisroll: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.yaxisroll = (int16_t)(x);
				/* zaxisroll: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.zaxisroll = (int16_t)(x);
				imu_gyro_measurement_pub_->publish(msg);
				break;
			}
			case 273: { /* 0x111: MotorPlateTemp */
				if (dlc < 8) return;
				ex1::msg::MotorPlateTemp msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motorplatetemp1: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motorplatetemp1 = unpack754_32(x);
				/* motorplatetemp2: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.motorplatetemp2 = unpack754_32(x);
				motor_plate_temp_pub_->publish(msg);
				break;
			}
			case 768: { /* 0x300: BIM1CellStatistics1 */
				if (dlc < 7) return;
				ex1::msg::BIM1CellStatistics1 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim1maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim1maxcellvoltage = (uint16_t)(x);
				/* bim1maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xff;
				msg.bim1maxcellnumber = (uint8_t)(x);
				/* bim1mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.bim1mincellvoltage = (uint16_t)(x);
				/* bim1mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xff;
				msg.bim1mincellnumber = (uint8_t)(x);
				bim1_cell_statistics1_pub_->publish(msg);
				break;
			}
			case 769: { /* 0x301: BIM1CellStatistics2 */
				if (dlc < 5) return;
				ex1::msg::BIM1CellStatistics2 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim1avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim1avgcellvoltage = (uint16_t)(x);
				/* bim1stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.bim1stdevcellvoltage = (uint16_t)(x);
				/* bim1numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xff;
				msg.bim1numberbalancingcells = (uint8_t)(x);
				bim1_cell_statistics2_pub_->publish(msg);
				break;
			}
			case 770: { /* 0x302: BIM2CellStatisitcs1 */
				if (dlc < 7) return;
				ex1::msg::BIM2CellStatisitcs1 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim2maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim2maxcellvoltage = (uint16_t)(x);
				/* bim2maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xff;
				msg.bim2maxcellnumber = (uint8_t)(x);
				/* bim2mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.bim2mincellvoltage = (uint16_t)(x);
				/* bim2mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xff;
				msg.bim2mincellnumber = (uint8_t)(x);
				bim2_cell_statisitcs1_pub_->publish(msg);
				break;
			}
			case 771: { /* 0x303: BIM2CellStatistics2 */
				if (dlc < 5) return;
				ex1::msg::BIM2CellStatistics2 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim2avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim2avgcellvoltage = (uint16_t)(x);
				/* bim2stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.bim2stdevcellvoltage = (uint16_t)(x);
				/* bim2numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xff;
				msg.bim2numberbalancingcells = (uint8_t)(x);
				bim2_cell_statistics2_pub_->publish(msg);
				break;
			}
			case 772: { /* 0x304: BIM3CellStatisitcs1 */
				if (dlc < 7) return;
				ex1::msg::BIM3CellStatisitcs1 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim3maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim3maxcellvoltage = (uint16_t)(x);
				/* bim3maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xff;
				msg.bim3maxcellnumber = (uint8_t)(x);
				/* bim3mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.bim3mincellvoltage = (uint16_t)(x);
				/* bim3mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xff;
				msg.bim3mincellnumber = (uint8_t)(x);
				bim3_cell_statisitcs1_pub_->publish(msg);
				break;
			}
			case 773: { /* 0x305: BIM3CellStatistics2 */
				if (dlc < 5) return;
				ex1::msg::BIM3CellStatistics2 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim3avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim3avgcellvoltage = (uint16_t)(x);
				/* bim3stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.bim3stdevcellvoltage = (uint16_t)(x);
				/* bim3numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xff;
				msg.bim3numberbalancingcells = (uint8_t)(x);
				bim3_cell_statistics2_pub_->publish(msg);
				break;
			}
			case 774: { /* 0x306: BIM4CellStatistics1 */
				if (dlc < 6) return;
				ex1::msg::BIM4CellStatistics1 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim4maxcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim4maxcellvoltage = (uint16_t)(x);
				/* bim4maxcellnumber: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xff;
				msg.bim4maxcellnumber = (uint8_t)(x);
				/* bim4mincellvoltage: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.bim4mincellvoltage = (uint16_t)(x);
				/* bim4mincellnumber: start-bit 48, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xff;
				msg.bim4mincellnumber = (uint8_t)(x);
				bim4_cell_statistics1_pub_->publish(msg);
				break;
			}
			case 775: { /* 0x307: BIM4CellStatistics2 */
				if (dlc < 5) return;
				ex1::msg::BIM4CellStatistics2 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim4avgcellvoltage: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim4avgcellvoltage = (uint16_t)(x);
				/* bim4stdevcellvoltage: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.bim4stdevcellvoltage = (uint16_t)(x);
				/* bim4numberbalancingcells: start-bit 32, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xff;
				msg.bim4numberbalancingcells = (uint8_t)(x);
				bim4_cell_statistics2_pub_->publish(msg);
				break;
			}
			case 784: { /* 0x310: Cells14 */
				if (dlc < 8) return;
				ex1::msg::Cells14 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell1: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell1 = (int16_t)(x);
				/* cell1_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell1_bal = (uint8_t)(x);
				/* cell2: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell2 = (int16_t)(x);
				/* cell2_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell2_bal = (uint8_t)(x);
				/* cell3: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell3 = (int16_t)(x);
				/* cell3_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell3_bal = (uint8_t)(x);
				/* cell4: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell4 = (int16_t)(x);
				/* cell4_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell4_bal = (uint8_t)(x);
				cells14_pub_->publish(msg);
				break;
			}
			case 785: { /* 0x311: Cells58 */
				if (dlc < 8) return;
				ex1::msg::Cells58 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell5: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell5 = (int16_t)(x);
				/* cell5_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell5_bal = (uint8_t)(x);
				/* cell6: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell6 = (int16_t)(x);
				/* cell6_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell6_bal = (uint8_t)(x);
				/* cell7: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell7 = (int16_t)(x);
				/* cell7_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell7_bal = (uint8_t)(x);
				/* cell8: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell8 = (int16_t)(x);
				/* cell8_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell8_bal = (uint8_t)(x);
				cells58_pub_->publish(msg);
				break;
			}
			case 786: { /* 0x312: Cells912 */
				if (dlc < 8) return;
				ex1::msg::Cells912 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell9: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell9 = (int16_t)(x);
				/* cell9_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell9_bal = (uint8_t)(x);
				/* cell10: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell10 = (int16_t)(x);
				/* cell10_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell10_bal = (uint8_t)(x);
				/* cell11: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell11 = (int16_t)(x);
				/* cell11_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell11_bal = (uint8_t)(x);
				/* cell12: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell12 = (int16_t)(x);
				/* cell12_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell12_bal = (uint8_t)(x);
				cells912_pub_->publish(msg);
				break;
			}
			case 139467056: { /* 0x8501930: OdometerVelocity */
				if (dlc < 6) return;
				ex1::msg::OdometerVelocity msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t m = reverse_byte_order(data);
				/* odometer_velocity: start-bit 7, length 32, endianess motorola, scaling 1, offset 0 */
				x = (m >> 32) & 0xffffffff;
				msg.odometer_velocity = (int32_t)(x);
				odometer_velocity_pub_->publish(msg);
				break;
			}
			case 787: { /* 0x313: Cells1316 */
				if (dlc < 8) return;
				ex1::msg::Cells1316 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell13: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell13 = (int16_t)(x);
				/* cell13_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell13_bal = (uint8_t)(x);
				/* cell14: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell14 = (int16_t)(x);
				/* cell14_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell14_bal = (uint8_t)(x);
				/* cell15: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell15 = (int16_t)(x);
				/* cell15_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell15_bal = (uint8_t)(x);
				/* cell16: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell16 = (int16_t)(x);
				/* cell16_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell16_bal = (uint8_t)(x);
				cells1316_pub_->publish(msg);
				break;
			}
			case 788: { /* 0x314: Cells1720 */
				if (dlc < 8) return;
				ex1::msg::Cells1720 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell17: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell17 = (int16_t)(x);
				/* cell17_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell17_bal = (uint8_t)(x);
				/* cell18: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell18 = (int16_t)(x);
				/* cell18_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell18_bal = (uint8_t)(x);
				/* cell19: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell19 = (int16_t)(x);
				/* cell19_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell19_bal = (uint8_t)(x);
				/* cell20: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell20 = (int16_t)(x);
				/* cell20_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell20_bal = (uint8_t)(x);
				cells1720_pub_->publish(msg);
				break;
			}
			case 789: { /* 0x315: Cells2124 */
				if (dlc < 8) return;
				ex1::msg::Cells2124 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell21: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell21 = (int16_t)(x);
				/* cell21_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell21_bal = (uint8_t)(x);
				/* cell22: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell22 = (int16_t)(x);
				/* cell22_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell22_bal = (uint8_t)(x);
				/* cell23: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell23 = (int16_t)(x);
				/* cell23_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell23_bal = (uint8_t)(x);
				/* cell24: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell24 = (int16_t)(x);
				/* cell24_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell24_bal = (uint8_t)(x);
				cells2124_pub_->publish(msg);
				break;
			}
			case 790: { /* 0x316: Cells2528 */
				if (dlc < 8) return;
				ex1::msg::Cells2528 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell25: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell25 = (int16_t)(x);
				/* cell25_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell25_bal = (uint8_t)(x);
				/* cell26: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell26 = (int16_t)(x);
				/* cell26_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell26_bal = (uint8_t)(x);
				/* cell27: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell27 = (int16_t)(x);
				/* cell27_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell27_bal = (uint8_t)(x);
				/* cell28: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell28 = (int16_t)(x);
				/* cell28_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell28_bal = (uint8_t)(x);
				cells2528_pub_->publish(msg);
				break;
			}
			case 791: { /* 0x317: Cells2932 */
				if (dlc < 8) return;
				ex1::msg::Cells2932 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell29: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell29 = (int16_t)(x);
				/* cell29_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell29_bal = (uint8_t)(x);
				/* cell30: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell30 = (int16_t)(x);
				/* cell30_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell30_bal = (uint8_t)(x);
				/* cell31: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell31 = (int16_t)(x);
				/* cell31_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell31_bal = (uint8_t)(x);
				/* cell32: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell32 = (int16_t)(x);
				/* cell32_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell32_bal = (uint8_t)(x);
				cells2932_pub_->publish(msg);
				break;
			}
			case 792: { /* 0x318: Cells3336 */
				if (dlc < 8) return;
				ex1::msg::Cells3336 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell33: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell33 = (int16_t)(x);
				/* cell33_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell33_bal = (uint8_t)(x);
				/* cell34: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell34 = (int16_t)(x);
				/* cell34_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell34_bal = (uint8_t)(x);
				/* cell35: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell35 = (int16_t)(x);
				/* cell35_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell35_bal = (uint8_t)(x);
				/* cell36: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell36 = (int16_t)(x);
				/* cell36_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell36_bal = (uint8_t)(x);
				cells3336_pub_->publish(msg);
				break;
			}
			case 793: { /* 0x319: Cells3740 */
				if (dlc < 8) return;
				ex1::msg::Cells3740 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell37: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell37 = (int16_t)(x);
				/* cell37_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell37_bal = (uint8_t)(x);
				/* cell38: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell38 = (int16_t)(x);
				/* cell38_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell38_bal = (uint8_t)(x);
				/* cell39: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell39 = (int16_t)(x);
				/* cell39_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell39_bal = (uint8_t)(x);
				/* cell40: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell40 = (int16_t)(x);
				/* cell40_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell40_bal = (uint8_t)(x);
				cells3740_pub_->publish(msg);
				break;
			}
			case 794: { /* 0x31a: Cells4144 */
				if (dlc < 8) return;
				ex1::msg::Cells4144 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell41: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell41 = (int16_t)(x);
				/* cell41_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell41_bal = (uint8_t)(x);
				/* cell42: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell42 = (int16_t)(x);
				/* cell42_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell42_bal = (uint8_t)(x);
				/* cell43: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell43 = (int16_t)(x);
				/* cell43_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell43_bal = (uint8_t)(x);
				/* cell44: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell44 = (int16_t)(x);
				/* cell44_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell44_bal = (uint8_t)(x);
				cells4144_pub_->publish(msg);
				break;
			}
			case 795: { /* 0x31b: Cells4548 */
				if (dlc < 8) return;
				ex1::msg::Cells4548 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell45: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell45 = (int16_t)(x);
				/* cell45_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell45_bal = (uint8_t)(x);
				/* cell46: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell46 = (int16_t)(x);
				/* cell46_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell46_bal = (uint8_t)(x);
				/* cell47: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell47 = (int16_t)(x);
				/* cell47_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell47_bal = (uint8_t)(x);
				/* cell48: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell48 = (int16_t)(x);
				/* cell48_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell48_bal = (uint8_t)(x);
				cells4548_pub_->publish(msg);
				break;
			}
			case 796: { /* 0x31c: Cells4952 */
				if (dlc < 8) return;
				ex1::msg::Cells4952 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell49: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell49 = (int16_t)(x);
				/* cell49_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell49_bal = (uint8_t)(x);
				/* cell50: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell50 = (int16_t)(x);
				/* cell50_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell50_bal = (uint8_t)(x);
				/* cell51: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell51 = (int16_t)(x);
				/* cell51_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell51_bal = (uint8_t)(x);
				/* cell52: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell52 = (int16_t)(x);
				/* cell52_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell52_bal = (uint8_t)(x);
				cells4952_pub_->publish(msg);
				break;
			}
			case 797: { /* 0x31d: Cells5354 */
				if (dlc < 8) return;
				ex1::msg::Cells5354 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell53: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell53 = (int16_t)(x);
				/* cell53_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell53_bal = (uint8_t)(x);
				/* cell54: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell54 = (int16_t)(x);
				/* cell54_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell54_bal = (uint8_t)(x);
				cells5354_pub_->publish(msg);
				break;
			}
			case 798: { /* 0x31e: Cells5558 */
				if (dlc < 8) return;
				ex1::msg::Cells5558 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell55: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell55 = (int16_t)(x);
				/* cell55_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell55_bal = (uint8_t)(x);
				/* cell56: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell56 = (int16_t)(x);
				/* cell56_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell56_bal = (uint8_t)(x);
				/* cell57: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell57 = (int16_t)(x);
				/* cell57_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell57_bal = (uint8_t)(x);
				/* cell58: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell58 = (int16_t)(x);
				/* cell58_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell58_bal = (uint8_t)(x);
				cells5558_pub_->publish(msg);
				break;
			}
			case 799: { /* 0x31f: Cells5962 */
				if (dlc < 8) return;
				ex1::msg::Cells5962 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell59: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell59 = (int16_t)(x);
				/* cell59_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell59_bal = (uint8_t)(x);
				/* cell60: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell60 = (int16_t)(x);
				/* cell60_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell60_bal = (uint8_t)(x);
				/* cell61: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell61 = (int16_t)(x);
				/* cell61_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell61_bal = (uint8_t)(x);
				/* cell62: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell62 = (int16_t)(x);
				/* cell62_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell62_bal = (uint8_t)(x);
				cells5962_pub_->publish(msg);
				break;
			}
			case 800: { /* 0x320: Cells6366 */
				if (dlc < 8) return;
				ex1::msg::Cells6366 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell63: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell63 = (int16_t)(x);
				/* cell63_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell63_bal = (uint8_t)(x);
				/* cell64: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell64 = (int16_t)(x);
				/* cell64_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell64_bal = (uint8_t)(x);
				/* cell65: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell65 = (int16_t)(x);
				/* cell65_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell65_bal = (uint8_t)(x);
				/* cell66: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell66 = (int16_t)(x);
				/* cell66_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell66_bal = (uint8_t)(x);
				cells6366_pub_->publish(msg);
				break;
			}
			case 801: { /* 0x321: Cells6770 */
				if (dlc < 8) return;
				ex1::msg::Cells6770 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell67: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell67 = (int16_t)(x);
				/* cell67_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell67_bal = (uint8_t)(x);
				/* cell68: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell68 = (int16_t)(x);
				/* cell68_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell68_bal = (uint8_t)(x);
				/* cell69: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell69 = (int16_t)(x);
				/* cell69_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell69_bal = (uint8_t)(x);
				/* cell70: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell70 = (int16_t)(x);
				/* cell70_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell70_bal = (uint8_t)(x);
				cells6770_pub_->publish(msg);
				break;
			}
			case 802: { /* 0x322: Cells7174 */
				if (dlc < 8) return;
				ex1::msg::Cells7174 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell71: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell71 = (int16_t)(x);
				/* cell71_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell71_bal = (uint8_t)(x);
				/* cell72: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell72 = (int16_t)(x);
				/* cell72_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell72_bal = (uint8_t)(x);
				/* cell73: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell73 = (int16_t)(x);
				/* cell73_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell73_bal = (uint8_t)(x);
				/* cell74: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell74 = (int16_t)(x);
				/* cell74_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell74_bal = (uint8_t)(x);
				cells7174_pub_->publish(msg);
				break;
			}
			case 803: { /* 0x323: Cells7578 */
				if (dlc < 8) return;
				ex1::msg::Cells7578 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell75: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell75 = (int16_t)(x);
				/* cell75_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell75_bal = (uint8_t)(x);
				/* cell76: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell76 = (int16_t)(x);
				/* cell76_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell76_bal = (uint8_t)(x);
				/* cell77: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell77 = (int16_t)(x);
				/* cell77_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell77_bal = (uint8_t)(x);
				/* cell78: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell78 = (int16_t)(x);
				/* cell78_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell78_bal = (uint8_t)(x);
				cells7578_pub_->publish(msg);
				break;
			}
			case 804: { /* 0x324: Cells7982 */
				if (dlc < 8) return;
				ex1::msg::Cells7982 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell79: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell79 = (int16_t)(x);
				/* cell79_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell79_bal = (uint8_t)(x);
				/* cell80: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell80 = (int16_t)(x);
				/* cell80_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell80_bal = (uint8_t)(x);
				/* cell81: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell81 = (int16_t)(x);
				/* cell81_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell81_bal = (uint8_t)(x);
				/* cell82: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell82 = (int16_t)(x);
				/* cell82_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell82_bal = (uint8_t)(x);
				cells7982_pub_->publish(msg);
				break;
			}
			case 805: { /* 0x325: Cells8386 */
				if (dlc < 8) return;
				ex1::msg::Cells8386 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell83: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell83 = (int16_t)(x);
				/* cell83_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell83_bal = (uint8_t)(x);
				/* cell84: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell84 = (int16_t)(x);
				/* cell84_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell84_bal = (uint8_t)(x);
				/* cell85: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell85 = (int16_t)(x);
				/* cell85_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell85_bal = (uint8_t)(x);
				/* cell86: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell86 = (int16_t)(x);
				/* cell86_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell86_bal = (uint8_t)(x);
				cells8386_pub_->publish(msg);
				break;
			}
			case 806: { /* 0x326: Cells8790 */
				if (dlc < 8) return;
				ex1::msg::Cells8790 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell87: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell87 = (int16_t)(x);
				/* cell87_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell87_bal = (uint8_t)(x);
				/* cell88: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell88 = (int16_t)(x);
				/* cell88_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell88_bal = (uint8_t)(x);
				/* cell89: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell89 = (int16_t)(x);
				/* cell89_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell89_bal = (uint8_t)(x);
				/* cell90: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell90 = (int16_t)(x);
				/* cell90_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell90_bal = (uint8_t)(x);
				cells8790_pub_->publish(msg);
				break;
			}
			case 807: { /* 0x327: Cells9194 */
				if (dlc < 8) return;
				ex1::msg::Cells9194 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell91: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell91 = (int16_t)(x);
				/* cell91_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell91_bal = (uint8_t)(x);
				/* cell92: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell92 = (int16_t)(x);
				/* cell92_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell92_bal = (uint8_t)(x);
				/* cell93: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell93 = (int16_t)(x);
				/* cell93_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell93_bal = (uint8_t)(x);
				/* cell94: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell94 = (int16_t)(x);
				/* cell94_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell94_bal = (uint8_t)(x);
				cells9194_pub_->publish(msg);
				break;
			}
			case 808: { /* 0x328: Cells9598 */
				if (dlc < 8) return;
				ex1::msg::Cells9598 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell95: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell95 = (int16_t)(x);
				/* cell95_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell95_bal = (uint8_t)(x);
				/* cell96: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell96 = (int16_t)(x);
				/* cell96_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell96_bal = (uint8_t)(x);
				/* cell97: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell97 = (int16_t)(x);
				/* cell97_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell97_bal = (uint8_t)(x);
				/* cell98: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell98 = (int16_t)(x);
				/* cell98_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell98_bal = (uint8_t)(x);
				cells9598_pub_->publish(msg);
				break;
			}
			case 809: { /* 0x329: Cells99102 */
				if (dlc < 8) return;
				ex1::msg::Cells99102 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell99: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell99 = (int16_t)(x);
				/* cell99_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell99_bal = (uint8_t)(x);
				/* cell100: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell100 = (int16_t)(x);
				/* cell100_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell100_bal = (uint8_t)(x);
				/* cell101: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell101 = (int16_t)(x);
				/* cell101_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell101_bal = (uint8_t)(x);
				/* cell102: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell102 = (int16_t)(x);
				/* cell102_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell102_bal = (uint8_t)(x);
				cells99102_pub_->publish(msg);
				break;
			}
			case 810: { /* 0x32a: Cells103106 */
				if (dlc < 8) return;
				ex1::msg::Cells103106 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell103: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell103 = (int16_t)(x);
				/* cell103_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell103_bal = (uint8_t)(x);
				/* cell104: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell104 = (int16_t)(x);
				/* cell104_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell104_bal = (uint8_t)(x);
				/* cell105: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell105 = (int16_t)(x);
				/* cell105_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell105_bal = (uint8_t)(x);
				/* cell106: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell106 = (int16_t)(x);
				/* cell106_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell106_bal = (uint8_t)(x);
				cells103106_pub_->publish(msg);
				break;
			}
			case 811: { /* 0x32b: Cells107110 */
				if (dlc < 8) return;
				ex1::msg::Cells107110 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cell107: start-bit 0, length 15, endianess intel, scaling 1, offset 0 */
				x = i & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell107 = (int16_t)(x);
				/* cell107_bal: start-bit 15, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 15) & 0x1;
				msg.cell107_bal = (uint8_t)(x);
				/* cell108: start-bit 16, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell108 = (int16_t)(x);
				/* cell108_bal: start-bit 31, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 31) & 0x1;
				msg.cell108_bal = (uint8_t)(x);
				/* cell109: start-bit 32, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell109 = (int16_t)(x);
				/* cell109_bal: start-bit 47, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 47) & 0x1;
				msg.cell109_bal = (uint8_t)(x);
				/* cell110: start-bit 48, length 15, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0x7fff;
				x = (x & 0x4000) ? (x | 0x8000) : x; 
				msg.cell110 = (int16_t)(x);
				/* cell110_bal: start-bit 63, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 63) & 0x1;
				msg.cell110_bal = (uint8_t)(x);
				cells107110_pub_->publish(msg);
				break;
			}
			case 821: { /* 0x335: PackTemperatures1Thru4 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures1Thru4 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp1: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp1 = (int16_t)(x);
				/* temp2: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp2 = (int16_t)(x);
				/* temp3: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp3 = (int16_t)(x);
				/* temp4: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temp4 = (int16_t)(x);
				pack_temperatures1_thru4_pub_->publish(msg);
				break;
			}
			case 822: { /* 0x336: PackTempeartures5Thru8 */
				if (dlc < 8) return;
				ex1::msg::PackTempeartures5Thru8 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp5: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp5 = (int16_t)(x);
				/* temp6: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp6 = (int16_t)(x);
				/* temp7: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp7 = (int16_t)(x);
				/* temp8: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temp8 = (int16_t)(x);
				pack_tempeartures5_thru8_pub_->publish(msg);
				break;
			}
			case 823: { /* 0x337: PackTemperatures9Thru14 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures9Thru14 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp9: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp9 = (int16_t)(x);
				/* temp10: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp10 = (int16_t)(x);
				/* temp11: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp11 = (int16_t)(x);
				/* temp12: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temp12 = (int16_t)(x);
				pack_temperatures9_thru14_pub_->publish(msg);
				break;
			}
			case 824: { /* 0x338: PackTemperatures13Thru14 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures13Thru14 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp13: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp13 = (int16_t)(x);
				/* temp14: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp14 = (int16_t)(x);
				pack_temperatures13_thru14_pub_->publish(msg);
				break;
			}
			case 825: { /* 0x339: PackTemperatures15Thru18 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures15Thru18 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp15: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp15 = (int16_t)(x);
				/* temp16: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp16 = (int16_t)(x);
				/* temp17: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp17 = (int16_t)(x);
				/* temo18: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temo18 = (int16_t)(x);
				pack_temperatures15_thru18_pub_->publish(msg);
				break;
			}
			case 826: { /* 0x33a: PackTemperatures19Thru22 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures19Thru22 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp19: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp19 = (int16_t)(x);
				/* temp20: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp20 = (int16_t)(x);
				/* temp21: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp21 = (int16_t)(x);
				/* temo22: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temo22 = (int16_t)(x);
				pack_temperatures19_thru22_pub_->publish(msg);
				break;
			}
			case 827: { /* 0x33b: PackTemperatures23Thru26 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures23Thru26 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp23: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp23 = (int16_t)(x);
				/* temp24: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp24 = (int16_t)(x);
				/* temp25: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp25 = (int16_t)(x);
				/* temo26: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temo26 = (int16_t)(x);
				pack_temperatures23_thru26_pub_->publish(msg);
				break;
			}
			case 828: { /* 0x33c: PackTemperatures27Thru30 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures27Thru30 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp27: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp27 = (int16_t)(x);
				/* temp28: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp28 = (int16_t)(x);
				/* temp29: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp29 = (int16_t)(x);
				/* temo30: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temo30 = (int16_t)(x);
				pack_temperatures27_thru30_pub_->publish(msg);
				break;
			}
			case 829: { /* 0x33d: PackTemperatures31Thru34 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures31Thru34 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp31: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp31 = (int16_t)(x);
				/* temp32: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp32 = (int16_t)(x);
				/* temp33: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp33 = (int16_t)(x);
				/* temo34: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temo34 = (int16_t)(x);
				pack_temperatures31_thru34_pub_->publish(msg);
				break;
			}
			case 830: { /* 0x33e: PackTemperatures35Thru38 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures35Thru38 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp35: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp35 = (int16_t)(x);
				/* temp36: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp36 = (int16_t)(x);
				/* temp37: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp37 = (int16_t)(x);
				/* temo38: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temo38 = (int16_t)(x);
				pack_temperatures35_thru38_pub_->publish(msg);
				break;
			}
			case 831: { /* 0x33f: PackTemperatures39Thru42 */
				if (dlc < 8) return;
				ex1::msg::PackTemperatures39Thru42 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* temp39: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.temp39 = (int16_t)(x);
				/* temp40: start-bit 16, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xffff;
				msg.temp40 = (int16_t)(x);
				/* temp41: start-bit 32, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffff;
				msg.temp41 = (int16_t)(x);
				/* temo42: start-bit 48, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 48) & 0xffff;
				msg.temo42 = (int16_t)(x);
				pack_temperatures39_thru42_pub_->publish(msg);
				break;
			}
			case 1281: { /* 0x501: MotorDriveCommand */
				if (dlc < 8) return;
				ex1::msg::MotorDriveCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motorvelocitycommand: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motorvelocitycommand = unpack754_32(x);
				/* motorcurrentcommand: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.motorcurrentcommand = unpack754_32(x);
				motor_drive_command_pub_->publish(msg);
				break;
			}
			case 1282: { /* 0x502: MotorPowerCommand */
				if (dlc < 8) return;
				ex1::msg::MotorPowerCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* buscurrentcommand: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.buscurrentcommand = unpack754_32(x);
				motor_power_command_pub_->publish(msg);
				break;
			}
			case 1025: { /* 0x401: StatusInformation */
				if (dlc < 8) return;
				ex1::msg::StatusInformation msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* limit_outputvolt_pwm: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = i & 0x1;
				msg.limit_outputvolt_pwm = (uint8_t)(x);
				/* limit_motor_current: start-bit 1, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 1) & 0x1;
				msg.limit_motor_current = (uint8_t)(x);
				/* limit_velocity: start-bit 2, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 2) & 0x1;
				msg.limit_velocity = (uint8_t)(x);
				/* limit_bus_current: start-bit 3, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 3) & 0x1;
				msg.limit_bus_current = (uint8_t)(x);
				/* limit_bus_volt_upper: start-bit 4, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 4) & 0x1;
				msg.limit_bus_volt_upper = (uint8_t)(x);
				/* limit_bus_volt_lower: start-bit 5, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 5) & 0x1;
				msg.limit_bus_volt_lower = (uint8_t)(x);
				/* limit_temp: start-bit 6, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 6) & 0x1;
				msg.limit_temp = (uint8_t)(x);
				/* reserved_limit: start-bit 7, length 9, endianess intel, scaling 1, offset 0 */
				x = (i >> 7) & 0x1ff;
				msg.reserved_limit = (uint16_t)(x);
				/* error_hardware_over_current: start-bit 16, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0x1;
				msg.error_hardware_over_current = (uint8_t)(x);
				/* error_software_over_current: start-bit 17, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 17) & 0x1;
				msg.error_software_over_current = (uint8_t)(x);
				/* error_dc_over_volt: start-bit 18, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 18) & 0x1;
				msg.error_dc_over_volt = (uint8_t)(x);
				/* error_bad_position: start-bit 19, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 19) & 0x1;
				msg.error_bad_position = (uint8_t)(x);
				/* error_watchdog: start-bit 20, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 20) & 0x1;
				msg.error_watchdog = (uint8_t)(x);
				/* error_configread: start-bit 21, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 21) & 0x1;
				msg.error_configread = (uint8_t)(x);
				/* error_15v_under_volt: start-bit 22, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 22) & 0x1;
				msg.error_15v_under_volt = (uint8_t)(x);
				/* error_desaturation: start-bit 23, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 23) & 0x1;
				msg.error_desaturation = (uint8_t)(x);
				/* reserved_error: start-bit 24, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 24) & 0xff;
				msg.reserved_error = (uint8_t)(x);
				status_information_pub_->publish(msg);
				break;
			}
			case 1026: { /* 0x402: BusMeasurement */
				if (dlc < 8) return;
				ex1::msg::BusMeasurement msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* busvoltage: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.busvoltage = unpack754_32(x);
				/* buscurrent: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.buscurrent = unpack754_32(x);
				bus_measurement_pub_->publish(msg);
				break;
			}
			case 1027: { /* 0x403: VelocityMeasurment */
				if (dlc < 8) return;
				ex1::msg::VelocityMeasurment msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motorvelocity: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motorvelocity = unpack754_32(x);
				/* vehiclevelocity: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.vehiclevelocity = unpack754_32(x);
				velocity_measurment_pub_->publish(msg);
				break;
			}
			case 1028: { /* 0x404: PhaseCurrentMeasurment */
				if (dlc < 8) return;
				ex1::msg::PhaseCurrentMeasurment msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* phasebcurrent: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.phasebcurrent = unpack754_32(x);
				/* phaseccurrent: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.phaseccurrent = unpack754_32(x);
				phase_current_measurment_pub_->publish(msg);
				break;
			}
			case 1029: { /* 0x405: MotorVoltage */
				if (dlc < 8) return;
				ex1::msg::MotorVoltage msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motorvq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motorvq = unpack754_32(x);
				/* motorvd: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.motorvd = unpack754_32(x);
				motor_voltage_pub_->publish(msg);
				break;
			}
			case 1030: { /* 0x406: MotorCurrent */
				if (dlc < 8) return;
				ex1::msg::MotorCurrent msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motoriq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motoriq = unpack754_32(x);
				/* motorid: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.motorid = unpack754_32(x);
				motor_current_pub_->publish(msg);
				break;
			}
			case 1035: { /* 0x40b: MotorPhaseATemperature */
				if (dlc < 8) return;
				ex1::msg::MotorPhaseATemperature msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motortemp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motortemp = unpack754_32(x);
				/* phaseatemp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.phaseatemp = unpack754_32(x);
				motor_phase_a_temperature_pub_->publish(msg);
				break;
			}
			case 1038: { /* 0x40e: Odometeramphours */
				if (dlc < 8) return;
				ex1::msg::Odometeramphours msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* odometer: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.odometer = unpack754_32(x);
				/* busamphours: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.busamphours = unpack754_32(x);
				odometeramphours_pub_->publish(msg);
				break;
			}
			case 1031: { /* 0x407: BackEMF */
				if (dlc < 8) return;
				ex1::msg::BackEMF msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bemfq: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.bemfq = unpack754_32(x);
				/* bemfd: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.bemfd = unpack754_32(x);
				back_emf_pub_->publish(msg);
				break;
			}
			case 1032: { /* 0x408: Rail15v */
				if (dlc < 8) return;
				ex1::msg::Rail15v msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* supply15v: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.supply15v = unpack754_32(x);
				rail15v_pub_->publish(msg);
				break;
			}
			case 1033: { /* 0x409: Rail3v31v9 */
				if (dlc < 8) return;
				ex1::msg::Rail3v31v9 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* supply1v9: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.supply1v9 = unpack754_32(x);
				/* supply3v3: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.supply3v3 = unpack754_32(x);
				rail3v31v9_pub_->publish(msg);
				break;
			}
			case 1036: { /* 0x40c: PhaseBdsptemprature */
				if (dlc < 8) return;
				ex1::msg::PhaseBdsptemprature msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* dsp_temp: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.dsp_temp = unpack754_32(x);
				/* phaseb_temp: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.phaseb_temp = unpack754_32(x);
				phase_bdsptemprature_pub_->publish(msg);
				break;
			}
			case 32: { /* 0x020: MagicCanNode1RBootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::MagicCanNode1RBootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magicnode1r_bladdy: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.magicnode1r_bladdy = (uint16_t)(x);
				magic_can_node1_r_bootloader_address_pub_->publish(msg);
				break;
			}
			case 34: { /* 0x022: MagicCanNode2MBootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::MagicCanNode2MBootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magicnode2m_bladdy: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.magicnode2m_bladdy = (uint16_t)(x);
				magic_can_node2_m_bootloader_address_pub_->publish(msg);
				break;
			}
			case 36: { /* 0x024: MagicCanNode3FBootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::MagicCanNode3FBootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magicnode3f_bladdy: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.magicnode3f_bladdy = (uint16_t)(x);
				magic_can_node3_f_bootloader_address_pub_->publish(msg);
				break;
			}
			case 38: { /* 0x026: FrameFaultBootloaderAddres */
				if (dlc < 2) return;
				ex1::msg::FrameFaultBootloaderAddres msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* framefaultbootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.framefaultbootloaderaddress = (uint16_t)(x);
				frame_fault_bootloader_addres_pub_->publish(msg);
				break;
			}
			case 40: { /* 0x028: FrameFaultCommand */
				if (dlc < 8) return;
				ex1::msg::FrameFaultCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* framefaultcommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.framefaultcommandvalue = (int32_t)(x);
				/* framefaultcommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.framefaultcommandcode = (uint32_t)(x);
				frame_fault_command_pub_->publish(msg);
				break;
			}
			case 44: { /* 0x02c: DriveControlsBootloader */
				if (dlc < 2) return;
				ex1::msg::DriveControlsBootloader msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* drivecontrolsbootloader: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.drivecontrolsbootloader = (uint16_t)(x);
				drive_controls_bootloader_pub_->publish(msg);
				break;
			}
			case 45: { /* 0x02d: DriveControlsCommand */
				if (dlc < 8) return;
				ex1::msg::DriveControlsCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* drivecontrolcommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.drivecontrolcommandvalue = (int32_t)(x);
				/* drivecontrolcommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.drivecontrolcommandcode = (uint32_t)(x);
				drive_controls_command_pub_->publish(msg);
				break;
			}
			case 48: { /* 0x030: CANMirrorBootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::CANMirrorBootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* canmirrorbootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.canmirrorbootloaderaddress = (uint16_t)(x);
				can_mirror_bootloader_address_pub_->publish(msg);
				break;
			}
			case 50: { /* 0x032: CANMirrorCommand */
				if (dlc < 8) return;
				ex1::msg::CANMirrorCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* canmirrorcommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.canmirrorcommandvalue = (int32_t)(x);
				/* canmirrorcommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.canmirrorcommandcode = (uint32_t)(x);
				can_mirror_command_pub_->publish(msg);
				break;
			}
			case 51: { /* 0x033: RiderDisplayBootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::RiderDisplayBootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* riderdisplaybootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.riderdisplaybootloaderaddress = (uint16_t)(x);
				rider_display_bootloader_address_pub_->publish(msg);
				break;
			}
			case 53: { /* 0x035: RiderDisplayCommand */
				if (dlc < 8) return;
				ex1::msg::RiderDisplayCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* riderdisplaycommandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.riderdisplaycommandvalue = (int32_t)(x);
				/* riderdisplaycommandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.riderdisplaycommandcode = (uint32_t)(x);
				rider_display_command_pub_->publish(msg);
				break;
			}
			case 57: { /* 0x039: BIM1BootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::BIM1BootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim1bootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim1bootloaderaddress = (uint16_t)(x);
				bim1_bootloader_address_pub_->publish(msg);
				break;
			}
			case 59: { /* 0x03b: BIM2BootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::BIM2BootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim2bootloaderaddres: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim2bootloaderaddres = (uint16_t)(x);
				bim2_bootloader_address_pub_->publish(msg);
				break;
			}
			case 61: { /* 0x03d: BIM3BootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::BIM3BootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim3bootloaderaddress: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim3bootloaderaddress = (uint16_t)(x);
				bim3_bootloader_address_pub_->publish(msg);
				break;
			}
			case 63: { /* 0x03f: BIM4BootloaderAddress */
				if (dlc < 2) return;
				ex1::msg::BIM4BootloaderAddress msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim4bootloaderaddres: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.bim4bootloaderaddres = (uint16_t)(x);
				bim4_bootloader_address_pub_->publish(msg);
				break;
			}
			case 160: { /* 0x0a0: MagicCanNode1RCommand */
				if (dlc < 8) return;
				ex1::msg::MagicCanNode1RCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magiccannode1commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.magiccannode1commandvalue = (int32_t)(x);
				/* magiccannode1commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.magiccannode1commandcode = (uint32_t)(x);
				magic_can_node1_r_command_pub_->publish(msg);
				break;
			}
			case 161: { /* 0x0a1: MagicCanNode2MCommand */
				if (dlc < 8) return;
				ex1::msg::MagicCanNode2MCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magiccannode2commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.magiccannode2commandvalue = (int32_t)(x);
				/* magiccannode2commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.magiccannode2commandcode = (uint32_t)(x);
				magic_can_node2_m_command_pub_->publish(msg);
				break;
			}
			case 162: { /* 0x0a2: MagicCanNode3FCommand */
				if (dlc < 8) return;
				ex1::msg::MagicCanNode3FCommand msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* magiccannode3commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.magiccannode3commandvalue = (uint32_t)(x);
				/* magiccannode3commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.magiccannode3commandcode = (uint32_t)(x);
				magic_can_node3_f_command_pub_->publish(msg);
				break;
			}
			case 170: { /* 0x0aa: CANcorderHeartbeat */
				if (dlc < 2) return;
				ex1::msg::CANcorderHeartbeat msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* cancorderheartbeat: start-bit 0, length 16, endianess intel, scaling 1, offset 0 */
				x = i & 0xffff;
				msg.cancorderheartbeat = (uint16_t)(x);
				ca_ncorder_heartbeat_pub_->publish(msg);
				break;
			}
			case 176: { /* 0x0b0: BIM1Command */
				if (dlc < 8) return;
				ex1::msg::BIM1Command msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim1commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.bim1commandvalue = (int32_t)(x);
				/* bim1commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.bim1commandcode = (uint32_t)(x);
				bim1_command_pub_->publish(msg);
				break;
			}
			case 177: { /* 0x0b1: BIM2Command */
				if (dlc < 8) return;
				ex1::msg::BIM2Command msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim2commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.bim2commandvalue = (int32_t)(x);
				/* bim2commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.bim2commandcode = (uint32_t)(x);
				bim2_command_pub_->publish(msg);
				break;
			}
			case 178: { /* 0x0b2: BIM3Command */
				if (dlc < 8) return;
				ex1::msg::BIM3Command msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim3commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.bim3commandvalue = (int32_t)(x);
				/* bim3commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.bim3commandcode = (uint32_t)(x);
				bim3_command_pub_->publish(msg);
				break;
			}
			case 179: { /* 0x0b3: BIM4Command */
				if (dlc < 8) return;
				ex1::msg::BIM4Command msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* bim4commandvalue: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.bim4commandvalue = (int32_t)(x);
				/* bim4commandcode: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.bim4commandcode = (uint32_t)(x);
				bim4_command_pub_->publish(msg);
				break;
			}
			case 274: { /* 0x112: MotorScoop */
				if (dlc < 4) return;
				ex1::msg::MotorScoop msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* motorscoop: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.motorscoop = unpack754_32(x);
				motor_scoop_pub_->publish(msg);
				break;
			}
			case 275: { /* 0x113: IMU1 */
				if (dlc < 8) return;
				ex1::msg::IMU1 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* imuaccelx: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.imuaccelx = (int32_t)(x);
				/* imuaceely: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.imuaceely = (int32_t)(x);
				imu1_pub_->publish(msg);
				break;
			}
			case 276: { /* 0x114: IMU2 */
				if (dlc < 8) return;
				ex1::msg::IMU2 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* imuaccelz: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.imuaccelz = (int32_t)(x);
				/* gravityx: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.gravityx = unpack754_32(x);
				imu2_pub_->publish(msg);
				break;
			}
			case 277: { /* 0x115: IMU3 */
				if (dlc < 8) return;
				ex1::msg::IMU3 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* gravityy: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.gravityy = unpack754_32(x);
				/* gravityz: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.gravityz = unpack754_32(x);
				imu3_pub_->publish(msg);
				break;
			}
			case 278: { /* 0x116: IMU4 */
				if (dlc < 8) return;
				ex1::msg::IMU4 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* yaw: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.yaw = unpack754_32(x);
				/* pitch: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.pitch = unpack754_32(x);
				imu4_pub_->publish(msg);
				break;
			}
			case 666: { /* 0x29a: IMU5 */
				if (dlc < 4) return;
				ex1::msg::IMU5 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* multiplexor: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = i & 0xf;
				msg.multiplexor = (uint8_t)(x);
				/* multi2a: start-bit 6, length 2, endianess intel, scaling 1, offset 0 */
				x = (i >> 6) & 0x3;
				msg.multi2a = (uint8_t)(x);
				/* multi1: start-bit 8, length 4, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0xf;
				msg.multi1 = (uint8_t)(x);
				/* multi2b: start-bit 8, length 2, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0x3;
				msg.multi2b = (uint8_t)(x);
				/* multi3: start-bit 8, length 4, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0xf;
				msg.multi3 = (uint8_t)(x);
				/* multi4: start-bit 8, length 4, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0xf;
				msg.multi4 = (uint8_t)(x);
				/* normal: start-bit 16, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 16) & 0xff;
				msg.normal = (int8_t)(x);
				imu5_pub_->publish(msg);
				break;
			}
			case 667: { /* 0x29b: MESSAGENAME */
				if (dlc < 1) return;
				ex1::msg::MESSAGENAME msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t m = reverse_byte_order(data);
				/* nonsensesignal: start-bit 0, length 3, endianess motorola, scaling 1, offset 0 */
				x = (m >> 54) & 0x7;
				msg.nonsensesignal = (uint8_t)(x);
				messagename_pub_->publish(msg);
				break;
			}
			case 668: { /* 0x29c: MESSAGENAME2 */
				if (dlc < 1) return;
				ex1::msg::MESSAGENAME2 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* placeholdersignal: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = i & 0xff;
				msg.placeholdersignal = (uint8_t)(x);
				messagename2_pub_->publish(msg);
				break;
			}
		}
	}

	rclcpp::Subscription<ex1::msg::MagicCanNode1RHeartbeat>::SharedPtr magic_can_node1_r_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode1RHeartbeat>::SharedPtr magic_can_node1_r_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode2Heartbeat>::SharedPtr magic_can_node2_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode2Heartbeat>::SharedPtr magic_can_node2_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode3Heartbeat>::SharedPtr magic_can_node3_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode3Heartbeat>::SharedPtr magic_can_node3_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::FrameFaultHeartbeat>::SharedPtr frame_fault_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::FrameFaultHeartbeat>::SharedPtr frame_fault_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::DriveControlsHeartbeat>::SharedPtr drive_controls_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::DriveControlsHeartbeat>::SharedPtr drive_controls_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::CANMirrorHeatbeart>::SharedPtr can_mirror_heatbeart_sub_;
	rclcpp::Publisher<ex1::msg::CANMirrorHeatbeart>::SharedPtr can_mirror_heatbeart_pub_;
	rclcpp::Subscription<ex1::msg::RiderDisplayHeartbeat>::SharedPtr rider_display_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::RiderDisplayHeartbeat>::SharedPtr rider_display_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::BIM1Heartbeat>::SharedPtr bim1_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::BIM1Heartbeat>::SharedPtr bim1_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::BIM2Heartbeat>::SharedPtr bim2_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::BIM2Heartbeat>::SharedPtr bim2_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::BIM3Heartbeat>::SharedPtr bim3_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::BIM3Heartbeat>::SharedPtr bim3_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::BIM4Heartbeat>::SharedPtr bim4_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::BIM4Heartbeat>::SharedPtr bim4_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::FrameFaultDetectionStatus>::SharedPtr frame_fault_detection_status_sub_;
	rclcpp::Publisher<ex1::msg::FrameFaultDetectionStatus>::SharedPtr frame_fault_detection_status_pub_;
	rclcpp::Subscription<ex1::msg::FrontBrakePressure>::SharedPtr front_brake_pressure_sub_;
	rclcpp::Publisher<ex1::msg::FrontBrakePressure>::SharedPtr front_brake_pressure_pub_;
	rclcpp::Subscription<ex1::msg::RearBrakePressure>::SharedPtr rear_brake_pressure_sub_;
	rclcpp::Publisher<ex1::msg::RearBrakePressure>::SharedPtr rear_brake_pressure_pub_;
	rclcpp::Subscription<ex1::msg::FrontSuspensionTravel>::SharedPtr front_suspension_travel_sub_;
	rclcpp::Publisher<ex1::msg::FrontSuspensionTravel>::SharedPtr front_suspension_travel_pub_;
	rclcpp::Subscription<ex1::msg::RearSuspensionTravel>::SharedPtr rear_suspension_travel_sub_;
	rclcpp::Publisher<ex1::msg::RearSuspensionTravel>::SharedPtr rear_suspension_travel_pub_;
	rclcpp::Subscription<ex1::msg::BusVoltage12V>::SharedPtr bus_voltage12_v_sub_;
	rclcpp::Publisher<ex1::msg::BusVoltage12V>::SharedPtr bus_voltage12_v_pub_;
	rclcpp::Subscription<ex1::msg::PostMotorCoolantTemp>::SharedPtr post_motor_coolant_temp_sub_;
	rclcpp::Publisher<ex1::msg::PostMotorCoolantTemp>::SharedPtr post_motor_coolant_temp_pub_;
	rclcpp::Subscription<ex1::msg::PostControllerCoolantTemp>::SharedPtr post_controller_coolant_temp_sub_;
	rclcpp::Publisher<ex1::msg::PostControllerCoolantTemp>::SharedPtr post_controller_coolant_temp_pub_;
	rclcpp::Subscription<ex1::msg::RadiatorCoolSideCoolantTemp>::SharedPtr radiator_cool_side_coolant_temp_sub_;
	rclcpp::Publisher<ex1::msg::RadiatorCoolSideCoolantTemp>::SharedPtr radiator_cool_side_coolant_temp_pub_;
	rclcpp::Subscription<ex1::msg::AmbientTemp>::SharedPtr ambient_temp_sub_;
	rclcpp::Publisher<ex1::msg::AmbientTemp>::SharedPtr ambient_temp_pub_;
	rclcpp::Subscription<ex1::msg::GPSLatAndValidityStatus>::SharedPtr gps_lat_and_validity_status_sub_;
	rclcpp::Publisher<ex1::msg::GPSLatAndValidityStatus>::SharedPtr gps_lat_and_validity_status_pub_;
	rclcpp::Subscription<ex1::msg::GPSLongitude>::SharedPtr gps_longitude_sub_;
	rclcpp::Publisher<ex1::msg::GPSLongitude>::SharedPtr gps_longitude_pub_;
	rclcpp::Subscription<ex1::msg::GPSAltitudeAndAccuracy>::SharedPtr gps_altitude_and_accuracy_sub_;
	rclcpp::Publisher<ex1::msg::GPSAltitudeAndAccuracy>::SharedPtr gps_altitude_and_accuracy_pub_;
	rclcpp::Subscription<ex1::msg::CurrentTime>::SharedPtr current_time_sub_;
	rclcpp::Publisher<ex1::msg::CurrentTime>::SharedPtr current_time_pub_;
	rclcpp::Subscription<ex1::msg::IMUAccelerationMeasurement>::SharedPtr imu_acceleration_measurement_sub_;
	rclcpp::Publisher<ex1::msg::IMUAccelerationMeasurement>::SharedPtr imu_acceleration_measurement_pub_;
	rclcpp::Subscription<ex1::msg::IMUGyroMeasurement>::SharedPtr imu_gyro_measurement_sub_;
	rclcpp::Publisher<ex1::msg::IMUGyroMeasurement>::SharedPtr imu_gyro_measurement_pub_;
	rclcpp::Subscription<ex1::msg::MotorPlateTemp>::SharedPtr motor_plate_temp_sub_;
	rclcpp::Publisher<ex1::msg::MotorPlateTemp>::SharedPtr motor_plate_temp_pub_;
	rclcpp::Subscription<ex1::msg::BIM1CellStatistics1>::SharedPtr bim1_cell_statistics1_sub_;
	rclcpp::Publisher<ex1::msg::BIM1CellStatistics1>::SharedPtr bim1_cell_statistics1_pub_;
	rclcpp::Subscription<ex1::msg::BIM1CellStatistics2>::SharedPtr bim1_cell_statistics2_sub_;
	rclcpp::Publisher<ex1::msg::BIM1CellStatistics2>::SharedPtr bim1_cell_statistics2_pub_;
	rclcpp::Subscription<ex1::msg::BIM2CellStatisitcs1>::SharedPtr bim2_cell_statisitcs1_sub_;
	rclcpp::Publisher<ex1::msg::BIM2CellStatisitcs1>::SharedPtr bim2_cell_statisitcs1_pub_;
	rclcpp::Subscription<ex1::msg::BIM2CellStatistics2>::SharedPtr bim2_cell_statistics2_sub_;
	rclcpp::Publisher<ex1::msg::BIM2CellStatistics2>::SharedPtr bim2_cell_statistics2_pub_;
	rclcpp::Subscription<ex1::msg::BIM3CellStatisitcs1>::SharedPtr bim3_cell_statisitcs1_sub_;
	rclcpp::Publisher<ex1::msg::BIM3CellStatisitcs1>::SharedPtr bim3_cell_statisitcs1_pub_;
	rclcpp::Subscription<ex1::msg::BIM3CellStatistics2>::SharedPtr bim3_cell_statistics2_sub_;
	rclcpp::Publisher<ex1::msg::BIM3CellStatistics2>::SharedPtr bim3_cell_statistics2_pub_;
	rclcpp::Subscription<ex1::msg::BIM4CellStatistics1>::SharedPtr bim4_cell_statistics1_sub_;
	rclcpp::Publisher<ex1::msg::BIM4CellStatistics1>::SharedPtr bim4_cell_statistics1_pub_;
	rclcpp::Subscription<ex1::msg::BIM4CellStatistics2>::SharedPtr bim4_cell_statistics2_sub_;
	rclcpp::Publisher<ex1::msg::BIM4CellStatistics2>::SharedPtr bim4_cell_statistics2_pub_;
	rclcpp::Subscription<ex1::msg::Cells14>::SharedPtr cells14_sub_;
	rclcpp::Publisher<ex1::msg::Cells14>::SharedPtr cells14_pub_;
	rclcpp::Subscription<ex1::msg::Cells58>::SharedPtr cells58_sub_;
	rclcpp::Publisher<ex1::msg::Cells58>::SharedPtr cells58_pub_;
	rclcpp::Subscription<ex1::msg::Cells912>::SharedPtr cells912_sub_;
	rclcpp::Publisher<ex1::msg::Cells912>::SharedPtr cells912_pub_;
	rclcpp::Subscription<ex1::msg::OdometerVelocity>::SharedPtr odometer_velocity_sub_;
	rclcpp::Publisher<ex1::msg::OdometerVelocity>::SharedPtr odometer_velocity_pub_;
	rclcpp::Subscription<ex1::msg::Cells1316>::SharedPtr cells1316_sub_;
	rclcpp::Publisher<ex1::msg::Cells1316>::SharedPtr cells1316_pub_;
	rclcpp::Subscription<ex1::msg::Cells1720>::SharedPtr cells1720_sub_;
	rclcpp::Publisher<ex1::msg::Cells1720>::SharedPtr cells1720_pub_;
	rclcpp::Subscription<ex1::msg::Cells2124>::SharedPtr cells2124_sub_;
	rclcpp::Publisher<ex1::msg::Cells2124>::SharedPtr cells2124_pub_;
	rclcpp::Subscription<ex1::msg::Cells2528>::SharedPtr cells2528_sub_;
	rclcpp::Publisher<ex1::msg::Cells2528>::SharedPtr cells2528_pub_;
	rclcpp::Subscription<ex1::msg::Cells2932>::SharedPtr cells2932_sub_;
	rclcpp::Publisher<ex1::msg::Cells2932>::SharedPtr cells2932_pub_;
	rclcpp::Subscription<ex1::msg::Cells3336>::SharedPtr cells3336_sub_;
	rclcpp::Publisher<ex1::msg::Cells3336>::SharedPtr cells3336_pub_;
	rclcpp::Subscription<ex1::msg::Cells3740>::SharedPtr cells3740_sub_;
	rclcpp::Publisher<ex1::msg::Cells3740>::SharedPtr cells3740_pub_;
	rclcpp::Subscription<ex1::msg::Cells4144>::SharedPtr cells4144_sub_;
	rclcpp::Publisher<ex1::msg::Cells4144>::SharedPtr cells4144_pub_;
	rclcpp::Subscription<ex1::msg::Cells4548>::SharedPtr cells4548_sub_;
	rclcpp::Publisher<ex1::msg::Cells4548>::SharedPtr cells4548_pub_;
	rclcpp::Subscription<ex1::msg::Cells4952>::SharedPtr cells4952_sub_;
	rclcpp::Publisher<ex1::msg::Cells4952>::SharedPtr cells4952_pub_;
	rclcpp::Subscription<ex1::msg::Cells5354>::SharedPtr cells5354_sub_;
	rclcpp::Publisher<ex1::msg::Cells5354>::SharedPtr cells5354_pub_;
	rclcpp::Subscription<ex1::msg::Cells5558>::SharedPtr cells5558_sub_;
	rclcpp::Publisher<ex1::msg::Cells5558>::SharedPtr cells5558_pub_;
	rclcpp::Subscription<ex1::msg::Cells5962>::SharedPtr cells5962_sub_;
	rclcpp::Publisher<ex1::msg::Cells5962>::SharedPtr cells5962_pub_;
	rclcpp::Subscription<ex1::msg::Cells6366>::SharedPtr cells6366_sub_;
	rclcpp::Publisher<ex1::msg::Cells6366>::SharedPtr cells6366_pub_;
	rclcpp::Subscription<ex1::msg::Cells6770>::SharedPtr cells6770_sub_;
	rclcpp::Publisher<ex1::msg::Cells6770>::SharedPtr cells6770_pub_;
	rclcpp::Subscription<ex1::msg::Cells7174>::SharedPtr cells7174_sub_;
	rclcpp::Publisher<ex1::msg::Cells7174>::SharedPtr cells7174_pub_;
	rclcpp::Subscription<ex1::msg::Cells7578>::SharedPtr cells7578_sub_;
	rclcpp::Publisher<ex1::msg::Cells7578>::SharedPtr cells7578_pub_;
	rclcpp::Subscription<ex1::msg::Cells7982>::SharedPtr cells7982_sub_;
	rclcpp::Publisher<ex1::msg::Cells7982>::SharedPtr cells7982_pub_;
	rclcpp::Subscription<ex1::msg::Cells8386>::SharedPtr cells8386_sub_;
	rclcpp::Publisher<ex1::msg::Cells8386>::SharedPtr cells8386_pub_;
	rclcpp::Subscription<ex1::msg::Cells8790>::SharedPtr cells8790_sub_;
	rclcpp::Publisher<ex1::msg::Cells8790>::SharedPtr cells8790_pub_;
	rclcpp::Subscription<ex1::msg::Cells9194>::SharedPtr cells9194_sub_;
	rclcpp::Publisher<ex1::msg::Cells9194>::SharedPtr cells9194_pub_;
	rclcpp::Subscription<ex1::msg::Cells9598>::SharedPtr cells9598_sub_;
	rclcpp::Publisher<ex1::msg::Cells9598>::SharedPtr cells9598_pub_;
	rclcpp::Subscription<ex1::msg::Cells99102>::SharedPtr cells99102_sub_;
	rclcpp::Publisher<ex1::msg::Cells99102>::SharedPtr cells99102_pub_;
	rclcpp::Subscription<ex1::msg::Cells103106>::SharedPtr cells103106_sub_;
	rclcpp::Publisher<ex1::msg::Cells103106>::SharedPtr cells103106_pub_;
	rclcpp::Subscription<ex1::msg::Cells107110>::SharedPtr cells107110_sub_;
	rclcpp::Publisher<ex1::msg::Cells107110>::SharedPtr cells107110_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures1Thru4>::SharedPtr pack_temperatures1_thru4_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures1Thru4>::SharedPtr pack_temperatures1_thru4_pub_;
	rclcpp::Subscription<ex1::msg::PackTempeartures5Thru8>::SharedPtr pack_tempeartures5_thru8_sub_;
	rclcpp::Publisher<ex1::msg::PackTempeartures5Thru8>::SharedPtr pack_tempeartures5_thru8_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures9Thru14>::SharedPtr pack_temperatures9_thru14_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures9Thru14>::SharedPtr pack_temperatures9_thru14_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures13Thru14>::SharedPtr pack_temperatures13_thru14_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures13Thru14>::SharedPtr pack_temperatures13_thru14_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures15Thru18>::SharedPtr pack_temperatures15_thru18_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures15Thru18>::SharedPtr pack_temperatures15_thru18_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures19Thru22>::SharedPtr pack_temperatures19_thru22_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures19Thru22>::SharedPtr pack_temperatures19_thru22_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures23Thru26>::SharedPtr pack_temperatures23_thru26_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures23Thru26>::SharedPtr pack_temperatures23_thru26_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures27Thru30>::SharedPtr pack_temperatures27_thru30_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures27Thru30>::SharedPtr pack_temperatures27_thru30_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures31Thru34>::SharedPtr pack_temperatures31_thru34_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures31Thru34>::SharedPtr pack_temperatures31_thru34_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures35Thru38>::SharedPtr pack_temperatures35_thru38_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures35Thru38>::SharedPtr pack_temperatures35_thru38_pub_;
	rclcpp::Subscription<ex1::msg::PackTemperatures39Thru42>::SharedPtr pack_temperatures39_thru42_sub_;
	rclcpp::Publisher<ex1::msg::PackTemperatures39Thru42>::SharedPtr pack_temperatures39_thru42_pub_;
	rclcpp::Subscription<ex1::msg::MotorDriveCommand>::SharedPtr motor_drive_command_sub_;
	rclcpp::Publisher<ex1::msg::MotorDriveCommand>::SharedPtr motor_drive_command_pub_;
	rclcpp::Subscription<ex1::msg::MotorPowerCommand>::SharedPtr motor_power_command_sub_;
	rclcpp::Publisher<ex1::msg::MotorPowerCommand>::SharedPtr motor_power_command_pub_;
	rclcpp::Subscription<ex1::msg::StatusInformation>::SharedPtr status_information_sub_;
	rclcpp::Publisher<ex1::msg::StatusInformation>::SharedPtr status_information_pub_;
	rclcpp::Subscription<ex1::msg::BusMeasurement>::SharedPtr bus_measurement_sub_;
	rclcpp::Publisher<ex1::msg::BusMeasurement>::SharedPtr bus_measurement_pub_;
	rclcpp::Subscription<ex1::msg::VelocityMeasurment>::SharedPtr velocity_measurment_sub_;
	rclcpp::Publisher<ex1::msg::VelocityMeasurment>::SharedPtr velocity_measurment_pub_;
	rclcpp::Subscription<ex1::msg::PhaseCurrentMeasurment>::SharedPtr phase_current_measurment_sub_;
	rclcpp::Publisher<ex1::msg::PhaseCurrentMeasurment>::SharedPtr phase_current_measurment_pub_;
	rclcpp::Subscription<ex1::msg::MotorVoltage>::SharedPtr motor_voltage_sub_;
	rclcpp::Publisher<ex1::msg::MotorVoltage>::SharedPtr motor_voltage_pub_;
	rclcpp::Subscription<ex1::msg::MotorCurrent>::SharedPtr motor_current_sub_;
	rclcpp::Publisher<ex1::msg::MotorCurrent>::SharedPtr motor_current_pub_;
	rclcpp::Subscription<ex1::msg::MotorPhaseATemperature>::SharedPtr motor_phase_a_temperature_sub_;
	rclcpp::Publisher<ex1::msg::MotorPhaseATemperature>::SharedPtr motor_phase_a_temperature_pub_;
	rclcpp::Subscription<ex1::msg::Odometeramphours>::SharedPtr odometeramphours_sub_;
	rclcpp::Publisher<ex1::msg::Odometeramphours>::SharedPtr odometeramphours_pub_;
	rclcpp::Subscription<ex1::msg::BackEMF>::SharedPtr back_emf_sub_;
	rclcpp::Publisher<ex1::msg::BackEMF>::SharedPtr back_emf_pub_;
	rclcpp::Subscription<ex1::msg::Rail15v>::SharedPtr rail15v_sub_;
	rclcpp::Publisher<ex1::msg::Rail15v>::SharedPtr rail15v_pub_;
	rclcpp::Subscription<ex1::msg::Rail3v31v9>::SharedPtr rail3v31v9_sub_;
	rclcpp::Publisher<ex1::msg::Rail3v31v9>::SharedPtr rail3v31v9_pub_;
	rclcpp::Subscription<ex1::msg::PhaseBdsptemprature>::SharedPtr phase_bdsptemprature_sub_;
	rclcpp::Publisher<ex1::msg::PhaseBdsptemprature>::SharedPtr phase_bdsptemprature_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode1RBootloaderAddress>::SharedPtr magic_can_node1_r_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode1RBootloaderAddress>::SharedPtr magic_can_node1_r_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode2MBootloaderAddress>::SharedPtr magic_can_node2_m_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode2MBootloaderAddress>::SharedPtr magic_can_node2_m_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode3FBootloaderAddress>::SharedPtr magic_can_node3_f_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode3FBootloaderAddress>::SharedPtr magic_can_node3_f_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::FrameFaultBootloaderAddres>::SharedPtr frame_fault_bootloader_addres_sub_;
	rclcpp::Publisher<ex1::msg::FrameFaultBootloaderAddres>::SharedPtr frame_fault_bootloader_addres_pub_;
	rclcpp::Subscription<ex1::msg::FrameFaultCommand>::SharedPtr frame_fault_command_sub_;
	rclcpp::Publisher<ex1::msg::FrameFaultCommand>::SharedPtr frame_fault_command_pub_;
	rclcpp::Subscription<ex1::msg::DriveControlsBootloader>::SharedPtr drive_controls_bootloader_sub_;
	rclcpp::Publisher<ex1::msg::DriveControlsBootloader>::SharedPtr drive_controls_bootloader_pub_;
	rclcpp::Subscription<ex1::msg::DriveControlsCommand>::SharedPtr drive_controls_command_sub_;
	rclcpp::Publisher<ex1::msg::DriveControlsCommand>::SharedPtr drive_controls_command_pub_;
	rclcpp::Subscription<ex1::msg::CANMirrorBootloaderAddress>::SharedPtr can_mirror_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::CANMirrorBootloaderAddress>::SharedPtr can_mirror_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::CANMirrorCommand>::SharedPtr can_mirror_command_sub_;
	rclcpp::Publisher<ex1::msg::CANMirrorCommand>::SharedPtr can_mirror_command_pub_;
	rclcpp::Subscription<ex1::msg::RiderDisplayBootloaderAddress>::SharedPtr rider_display_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::RiderDisplayBootloaderAddress>::SharedPtr rider_display_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::RiderDisplayCommand>::SharedPtr rider_display_command_sub_;
	rclcpp::Publisher<ex1::msg::RiderDisplayCommand>::SharedPtr rider_display_command_pub_;
	rclcpp::Subscription<ex1::msg::BIM1BootloaderAddress>::SharedPtr bim1_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::BIM1BootloaderAddress>::SharedPtr bim1_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::BIM2BootloaderAddress>::SharedPtr bim2_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::BIM2BootloaderAddress>::SharedPtr bim2_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::BIM3BootloaderAddress>::SharedPtr bim3_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::BIM3BootloaderAddress>::SharedPtr bim3_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::BIM4BootloaderAddress>::SharedPtr bim4_bootloader_address_sub_;
	rclcpp::Publisher<ex1::msg::BIM4BootloaderAddress>::SharedPtr bim4_bootloader_address_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode1RCommand>::SharedPtr magic_can_node1_r_command_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode1RCommand>::SharedPtr magic_can_node1_r_command_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode2MCommand>::SharedPtr magic_can_node2_m_command_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode2MCommand>::SharedPtr magic_can_node2_m_command_pub_;
	rclcpp::Subscription<ex1::msg::MagicCanNode3FCommand>::SharedPtr magic_can_node3_f_command_sub_;
	rclcpp::Publisher<ex1::msg::MagicCanNode3FCommand>::SharedPtr magic_can_node3_f_command_pub_;
	rclcpp::Subscription<ex1::msg::CANcorderHeartbeat>::SharedPtr ca_ncorder_heartbeat_sub_;
	rclcpp::Publisher<ex1::msg::CANcorderHeartbeat>::SharedPtr ca_ncorder_heartbeat_pub_;
	rclcpp::Subscription<ex1::msg::BIM1Command>::SharedPtr bim1_command_sub_;
	rclcpp::Publisher<ex1::msg::BIM1Command>::SharedPtr bim1_command_pub_;
	rclcpp::Subscription<ex1::msg::BIM2Command>::SharedPtr bim2_command_sub_;
	rclcpp::Publisher<ex1::msg::BIM2Command>::SharedPtr bim2_command_pub_;
	rclcpp::Subscription<ex1::msg::BIM3Command>::SharedPtr bim3_command_sub_;
	rclcpp::Publisher<ex1::msg::BIM3Command>::SharedPtr bim3_command_pub_;
	rclcpp::Subscription<ex1::msg::BIM4Command>::SharedPtr bim4_command_sub_;
	rclcpp::Publisher<ex1::msg::BIM4Command>::SharedPtr bim4_command_pub_;
	rclcpp::Subscription<ex1::msg::MotorScoop>::SharedPtr motor_scoop_sub_;
	rclcpp::Publisher<ex1::msg::MotorScoop>::SharedPtr motor_scoop_pub_;
	rclcpp::Subscription<ex1::msg::IMU1>::SharedPtr imu1_sub_;
	rclcpp::Publisher<ex1::msg::IMU1>::SharedPtr imu1_pub_;
	rclcpp::Subscription<ex1::msg::IMU2>::SharedPtr imu2_sub_;
	rclcpp::Publisher<ex1::msg::IMU2>::SharedPtr imu2_pub_;
	rclcpp::Subscription<ex1::msg::IMU3>::SharedPtr imu3_sub_;
	rclcpp::Publisher<ex1::msg::IMU3>::SharedPtr imu3_pub_;
	rclcpp::Subscription<ex1::msg::IMU4>::SharedPtr imu4_sub_;
	rclcpp::Publisher<ex1::msg::IMU4>::SharedPtr imu4_pub_;
	rclcpp::Subscription<ex1::msg::IMU5>::SharedPtr imu5_sub_;
	rclcpp::Publisher<ex1::msg::IMU5>::SharedPtr imu5_pub_;
	rclcpp::Subscription<ex1::msg::MESSAGENAME>::SharedPtr messagename_sub_;
	rclcpp::Publisher<ex1::msg::MESSAGENAME>::SharedPtr messagename_pub_;
	rclcpp::Subscription<ex1::msg::MESSAGENAME2>::SharedPtr messagename2_sub_;
	rclcpp::Publisher<ex1::msg::MESSAGENAME2>::SharedPtr messagename2_pub_;
	rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr frame_subscription_;
	rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr frame_publisher_;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::executors::StaticSingleThreadedExecutor executor;
	auto node = std::make_shared<Ex1Parser>();
	executor.add_node(node);
	executor.spin();
	rclcpp::shutdown();
	return 0;
}
