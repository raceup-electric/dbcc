/* CAN message encoder/decoder: automatically generated - do not edit. */

#include <rclcpp/rclcpp.hpp>
#include <cstring>
#include <can_msgs/msg/frame.hpp>

#include <mul_val/msg/extendedmultiplexwranges.hpp>
#include <mul_val/msg/extendedmultiplex.hpp>


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

class MulValParser : public rclcpp::Node {
public:
	MulValParser() : Node("mul_val_parser", "/mul_val") {
		createPublishers();
		createSubscriptions();
	}

private:
	void createSubscriptions() {
		auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort().durability_volatile();

		/* 0x000: Extendedmultiplexwranges */
		extendedmultiplexwranges_sub_ = this->create_subscription<mul_val::msg::Extendedmultiplexwranges>(
			"extendedmultiplexwranges", qos, [this](const mul_val::msg::Extendedmultiplexwranges::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* muxer_w_multiple_ranges: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->muxer_w_multiple_ranges))) & 0xff;
				i |= x;
				/* muxed_w_ranges: start-bit 8, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->muxed_w_ranges))) & 0xff;
				x <<= 8; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 2, 0);
			}
		);

		/* 0x692: Extendedmultiplex */
		extendedmultiplex_sub_ = this->create_subscription<mul_val::msg::Extendedmultiplex>(
			"extendedmultiplex", qos, [this](const mul_val::msg::Extendedmultiplex::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* sig1: start-bit 0, length 2, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->sig1))) & 0x3;
				i |= x;
				/* sig2: start-bit 2, length 2, endianess intel, scaling -1, offset 4 */
				x = ((uint8_t)((msg->sig2 + -4) * -1)) & 0x3;
				x <<= 2; 
				i |= x;
				/* sig3: start-bit 4, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->sig3))) & 0xf;
				x <<= 4; 
				i |= x;
				/* simple_muxer: start-bit 8, length 16, endianess intel, scaling 1, offset 0 */
				x = ((uint16_t)((msg->simple_muxer))) & 0xffff;
				x <<= 8; 
				i |= x;
				/* muxed_muxer: start-bit 24, length 8, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->muxed_muxer))) & 0xff;
				x <<= 24; 
				i |= x;
				/* muxed1: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->muxed1))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				/* muxed2: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = ((uint32_t)((msg->muxed2))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1682);
			}
		);

		frame_subscription_ = this->create_subscription<can_msgs::msg::Frame>(
			"/can/mul_val/read", qos, [this](const can_msgs::msg::Frame::SharedPtr msg) {
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

		extendedmultiplexwranges_pub_ = this->create_publisher<mul_val::msg::Extendedmultiplexwranges>("extendedmultiplexwranges", qos);
		extendedmultiplex_pub_ = this->create_publisher<mul_val::msg::Extendedmultiplex>("extendedmultiplex", qos);
		frame_publisher_ = this->create_publisher<can_msgs::msg::Frame>("/can/mul_val/write", qos);
	}

	void decodeMessage(uint64_t data, uint8_t dlc, uint32_t id, const rclcpp::Time& timestamp) {
		switch(id) {
			case 0: { /* 0x000: Extendedmultiplexwranges */
				if (dlc < 2) return;
				mul_val::msg::Extendedmultiplexwranges msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* muxer_w_multiple_ranges: start-bit 0, length 8, endianess intel, scaling 1, offset 0 */
				x = i & 0xff;
				msg.muxer_w_multiple_ranges = (uint8_t)(x);
				/* muxed_w_ranges: start-bit 8, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0xff;
				msg.muxed_w_ranges = (int8_t)(x);
				extendedmultiplexwranges_pub_->publish(msg);
				break;
			}
			case 1682: { /* 0x692: Extendedmultiplex */
				if (dlc < 8) return;
				mul_val::msg::Extendedmultiplex msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* sig1: start-bit 0, length 2, endianess intel, scaling 1, offset 0 */
				x = i & 0x3;
				msg.sig1 = (uint8_t)(x);
				/* sig2: start-bit 2, length 2, endianess intel, scaling -1, offset 4 */
				x = (i >> 2) & 0x3;
				msg.sig2 = (uint8_t)(x) * -1 + 4;
				/* sig3: start-bit 4, length 4, endianess intel, scaling 1, offset 0 */
				x = (i >> 4) & 0xf;
				msg.sig3 = (uint8_t)(x);
				/* simple_muxer: start-bit 8, length 16, endianess intel, scaling 1, offset 0 */
				x = (i >> 8) & 0xffff;
				msg.simple_muxer = (uint16_t)(x);
				/* muxed_muxer: start-bit 24, length 8, endianess intel, scaling 1, offset 0 */
				x = (i >> 24) & 0xff;
				msg.muxed_muxer = (uint8_t)(x);
				/* muxed1: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.muxed1 = (uint32_t)(x);
				/* muxed2: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.muxed2 = (uint32_t)(x);
				extendedmultiplex_pub_->publish(msg);
				break;
			}
		}
	}

	rclcpp::Subscription<mul_val::msg::Extendedmultiplexwranges>::SharedPtr extendedmultiplexwranges_sub_;
	rclcpp::Publisher<mul_val::msg::Extendedmultiplexwranges>::SharedPtr extendedmultiplexwranges_pub_;
	rclcpp::Subscription<mul_val::msg::Extendedmultiplex>::SharedPtr extendedmultiplex_sub_;
	rclcpp::Publisher<mul_val::msg::Extendedmultiplex>::SharedPtr extendedmultiplex_pub_;
	rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr frame_subscription_;
	rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr frame_publisher_;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::executors::StaticSingleThreadedExecutor executor;
	auto node = std::make_shared<MulValParser>();
	executor.add_node(node);
	executor.spin();
	rclcpp::shutdown();
	return 0;
}
