/* CAN message encoder/decoder: automatically generated - do not edit. */

#include <rclcpp/rclcpp.hpp>
#include <cstring>
#include <cstdint>
#include <can_msgs/msg/frame.hpp>

#include <bitfield_edge/msg/edge_packed.hpp>
#include <bitfield_edge/msg/edge_float.hpp>
#include <bitfield_edge/msg/edge_double.hpp>
#include <bitfield_edge/msg/edge_enums.hpp>
#include <bitfield_edge/msg/edge_mux.hpp>


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

class BitfieldEdgeParser : public rclcpp::Node {
public:
	BitfieldEdgeParser() : Node("bitfield_edge_parser", "/bitfield_edge") {
		createPublishers();
		createSubscriptions();
	}

private:
	void createSubscriptions() {
		auto qos = rclcpp::SensorDataQoS();

		/* 0x064: EdgePacked */
		edge_packed_sub_ = this->create_subscription<bitfield_edge::msg::EdgePacked>(
			"edge_packed", qos, [this](const bitfield_edge::msg::EdgePacked::SharedPtr msg) {
				if (msg->header.frame_id == "r") return;
				uint64_t x;
				uint64_t i = 0;
				/* flag0: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->flag0))) & 0x1;
				i |= x;
				/* byte_a: start-bit 1, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->byte_a))) & 0xff;
				x <<= 1; 
				i |= x;
				/* flag1: start-bit 9, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->flag1))) & 0x1;
				x <<= 9; 
				i |= x;
				/* byte_b: start-bit 10, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->byte_b))) & 0xff;
				x <<= 10; 
				i |= x;
				/* flag2: start-bit 18, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->flag2))) & 0x1;
				x <<= 18; 
				i |= x;
				/* byte_c: start-bit 19, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->byte_c))) & 0xff;
				x <<= 19; 
				i |= x;
				/* flag3: start-bit 27, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->flag3))) & 0x1;
				x <<= 27; 
				i |= x;
				/* byte_d: start-bit 28, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->byte_d))) & 0xff;
				x <<= 28; 
				i |= x;
				/* signed3: start-bit 36, length 3, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->signed3))) & 0x7;
				x <<= 36; 
				i |= x;
				/* unsigned5: start-bit 39, length 5, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->unsigned5))) & 0x1f;
				x <<= 39; 
				i |= x;
				/* signed8: start-bit 44, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->signed8))) & 0xff;
				x <<= 44; 
				i |= x;
				/* unsigned12: start-bit 52, length 12, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->unsigned12))) & 0xfff;
				x <<= 52; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 100);
			}
		);

		/* 0x065: EdgeFloat */
		edge_float_sub_ = this->create_subscription<bitfield_edge::msg::EdgeFloat>(
			"edge_float", qos, [this](const bitfield_edge::msg::EdgeFloat::SharedPtr msg) {
				if (msg->header.frame_id == "r") return;
				uint64_t x;
				uint64_t i = 0;
				/* f32: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->f32))) & 0xffffffff;
				i |= x;
				/* raw32: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->raw32))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 101);
			}
		);

		/* 0x066: EdgeDouble */
		edge_double_sub_ = this->create_subscription<bitfield_edge::msg::EdgeDouble>(
			"edge_double", qos, [this](const bitfield_edge::msg::EdgeDouble::SharedPtr msg) {
				if (msg->header.frame_id == "r") return;
				uint64_t x;
				uint64_t i = 0;
				/* d64: start-bit 0, length 64, endianess intel, scaling 1, offset 0 */
				x = (pack754_64((msg->d64))) & 0xffffffffffffffff;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 102);
			}
		);

		/* 0x067: EdgeEnums */
		edge_enums_sub_ = this->create_subscription<bitfield_edge::msg::EdgeEnums>(
			"edge_enums", qos, [this](const bitfield_edge::msg::EdgeEnums::SharedPtr msg) {
				if (msg->header.frame_id == "r") return;
				uint64_t x;
				uint64_t i = 0;
				/* mode: start-bit 0, length 2, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->mode))) & 0x3;
				i |= x;
				/* state: start-bit 2, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->state))) & 0x1;
				x <<= 2; 
				i |= x;
				/* inline_enum: start-bit 3, length 3, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->inline_enum))) & 0x7;
				x <<= 3; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 103);
			}
		);

		/* 0x068: EdgeMux */
		edge_mux_sub_ = this->create_subscription<bitfield_edge::msg::EdgeMux>(
			"edge_mux", qos, [this](const bitfield_edge::msg::EdgeMux::SharedPtr msg) {
				if (msg->header.frame_id == "r") return;
				uint64_t x;
				uint64_t i = 0;
				/* mux: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->mux))) & 0xff;
				i |= x;
				/* muxed_a: start-bit 8, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->muxed_a))) & 0xff;
				x <<= 8; 
				i |= x;
				/* muxed_b: start-bit 8, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->muxed_b))) & 0xff;
				x <<= 8; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 104);
			}
		);

		frame_subscription_ = this->create_subscription<can_msgs::msg::Frame>(
			"/can/bitfield_edge/read", qos, [this](const can_msgs::msg::Frame::SharedPtr msg) {
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
		auto qos = rclcpp::SensorDataQoS();

		edge_packed_pub_ = this->create_publisher<bitfield_edge::msg::EdgePacked>("edge_packed", qos);
		edge_float_pub_ = this->create_publisher<bitfield_edge::msg::EdgeFloat>("edge_float", qos);
		edge_double_pub_ = this->create_publisher<bitfield_edge::msg::EdgeDouble>("edge_double", qos);
		edge_enums_pub_ = this->create_publisher<bitfield_edge::msg::EdgeEnums>("edge_enums", qos);
		edge_mux_pub_ = this->create_publisher<bitfield_edge::msg::EdgeMux>("edge_mux", qos);
		frame_publisher_ = this->create_publisher<can_msgs::msg::Frame>("/can/bitfield_edge/write", qos);
	}

	void decodeMessage(uint64_t data, uint8_t dlc, uint32_t id, const rclcpp::Time& timestamp) {
		switch(id) {
			case 100: { /* 0x064: EdgePacked */
				if (dlc < 8) return;
				bitfield_edge::msg::EdgePacked msg;
				msg.header.stamp = timestamp;
				msg.header.frame_id = "r";
				uint64_t x;
				uint64_t i = (data);
				/* flag0: start-bit 0, length 1, endianess intel, scaling 1, offset 0 */
				x = i & 0x1;
				msg.flag0 = (uint8_t)(x);
				/* byte_a: start-bit 1, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 1) & 0xff;
				msg.byte_a = (uint8_t)(x);
				/* flag1: start-bit 9, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 9) & 0x1;
				msg.flag1 = (uint8_t)(x);
				/* byte_b: start-bit 10, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 10) & 0xff;
				msg.byte_b = (uint8_t)(x);
				/* flag2: start-bit 18, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 18) & 0x1;
				msg.flag2 = (uint8_t)(x);
				/* byte_c: start-bit 19, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 19) & 0xff;
				msg.byte_c = (uint8_t)(x);
				/* flag3: start-bit 27, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 27) & 0x1;
				msg.flag3 = (uint8_t)(x);
				/* byte_d: start-bit 28, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 28) & 0xff;
				msg.byte_d = (uint8_t)(x);
				/* signed3: start-bit 36, length 3, endianess intel, scaling 1, offset 0 */
				x = (i >> 36) & 0x7;
				x = (x & 0x4) ? (x | 0xf8) : x; 
				msg.signed3 = (int8_t)(x);
				/* unsigned5: start-bit 39, length 5, endianess intel, scaling 1, offset 0 */
				x = (i >> 39) & 0x1f;
				msg.unsigned5 = (uint8_t)(x);
				/* signed8: start-bit 44, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 44) & 0xff;
				msg.signed8 = (int8_t)(x);
				/* unsigned12: start-bit 52, length 12, endianess intel, scaling 1, offset 0 */
				x = (i >> 52) & 0xfff;
				msg.unsigned12 = (uint16_t)(x);
				edge_packed_pub_->publish(msg);
				break;
			}
			case 101: { /* 0x065: EdgeFloat */
				if (dlc < 8) return;
				bitfield_edge::msg::EdgeFloat msg;
				msg.header.stamp = timestamp;
				msg.header.frame_id = "r";
				uint64_t x;
				uint64_t i = (data);
				/* f32: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.f32 = unpack754_32(x);
				/* raw32: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.raw32 = (uint32_t)(x);
				edge_float_pub_->publish(msg);
				break;
			}
			case 102: { /* 0x066: EdgeDouble */
				if (dlc < 8) return;
				bitfield_edge::msg::EdgeDouble msg;
				msg.header.stamp = timestamp;
				msg.header.frame_id = "r";
				uint64_t x;
				uint64_t i = (data);
				/* d64: start-bit 0, length 64, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffffffffffff;
				msg.d64 = unpack754_64(x);
				edge_double_pub_->publish(msg);
				break;
			}
			case 103: { /* 0x067: EdgeEnums */
				if (dlc < 2) return;
				bitfield_edge::msg::EdgeEnums msg;
				msg.header.stamp = timestamp;
				msg.header.frame_id = "r";
				uint64_t x;
				uint64_t i = (data);
				/* mode: start-bit 0, length 2, endianess intel, scaling 1, offset 0 */
				x = i & 0x3;
				msg.mode = (uint8_t)(x);
				/* state: start-bit 2, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 2) & 0x1;
				msg.state = (uint8_t)(x);
				/* inline_enum: start-bit 3, length 3, endianess intel, scaling 1, offset 0 */
				x = (i >> 3) & 0x7;
				msg.inline_enum = (uint8_t)(x);
				edge_enums_pub_->publish(msg);
				break;
			}
			case 104: { /* 0x068: EdgeMux */
				if (dlc < 8) return;
				bitfield_edge::msg::EdgeMux msg;
				msg.header.stamp = timestamp;
				msg.header.frame_id = "r";
				uint64_t x;
				uint64_t i = (data);
				/* mux: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = i & 0xff;
				msg.mux = (uint8_t)(x);
				/* muxed_a: start-bit 8, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0xff;
				msg.muxed_a = (uint8_t)(x);
				/* muxed_b: start-bit 8, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0xff;
				msg.muxed_b = (uint8_t)(x);
				edge_mux_pub_->publish(msg);
				break;
			}
		}
	}

	rclcpp::Subscription<bitfield_edge::msg::EdgePacked>::SharedPtr edge_packed_sub_;
	rclcpp::Publisher<bitfield_edge::msg::EdgePacked>::SharedPtr edge_packed_pub_;
	rclcpp::Subscription<bitfield_edge::msg::EdgeFloat>::SharedPtr edge_float_sub_;
	rclcpp::Publisher<bitfield_edge::msg::EdgeFloat>::SharedPtr edge_float_pub_;
	rclcpp::Subscription<bitfield_edge::msg::EdgeDouble>::SharedPtr edge_double_sub_;
	rclcpp::Publisher<bitfield_edge::msg::EdgeDouble>::SharedPtr edge_double_pub_;
	rclcpp::Subscription<bitfield_edge::msg::EdgeEnums>::SharedPtr edge_enums_sub_;
	rclcpp::Publisher<bitfield_edge::msg::EdgeEnums>::SharedPtr edge_enums_pub_;
	rclcpp::Subscription<bitfield_edge::msg::EdgeMux>::SharedPtr edge_mux_sub_;
	rclcpp::Publisher<bitfield_edge::msg::EdgeMux>::SharedPtr edge_mux_pub_;
	rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr frame_subscription_;
	rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr frame_publisher_;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::executors::StaticSingleThreadedExecutor executor;
	auto node = std::make_shared<BitfieldEdgeParser>();
	executor.add_node(node);
	executor.spin();
	rclcpp::shutdown();
	return 0;
}
