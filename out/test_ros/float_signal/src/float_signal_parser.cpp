/* CAN message encoder/decoder: automatically generated - do not edit. */

#include <rclcpp/rclcpp.hpp>
#include <cstring>
#include <can_msgs/msg/frame.hpp>

#include <float_signal/msg/new_message0.hpp>


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

class FloatSignalParser : public rclcpp::Node {
public:
	FloatSignalParser() : Node("float_signal_parser", "/float_signal") {
		createPublishers();
		createSubscriptions();
	}

private:
	void createSubscriptions() {
		auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort().durability_volatile();

		/* 0x400: NewMessage0 */
		new_message0_sub_ = this->create_subscription<float_signal::msg::NewMessage0>(
			"new_message0", qos, [this](const float_signal::msg::NewMessage0::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* float_signal_0: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->float_signal_0))) & 0xffffffff;
				i |= x;
				/* float_signal_1: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (pack754_32((msg->float_signal_1))) & 0xffffffff;
				x <<= 32; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1024);
			}
		);

		frame_subscription_ = this->create_subscription<can_msgs::msg::Frame>(
			"/can/float_signal/read", qos, [this](const can_msgs::msg::Frame::SharedPtr msg) {
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

		new_message0_pub_ = this->create_publisher<float_signal::msg::NewMessage0>("new_message0", qos);
		frame_publisher_ = this->create_publisher<can_msgs::msg::Frame>("/can/float_signal/write", qos);
	}

	void decodeMessage(uint64_t data, uint8_t dlc, uint32_t id, const rclcpp::Time& timestamp) {
		switch(id) {
			case 1024: { /* 0x400: NewMessage0 */
				if (dlc < 8) return;
				float_signal::msg::NewMessage0 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* float_signal_0: start-bit 0, length 32, endianess intel, scaling 1, offset 0 */
				x = i & 0xffffffff;
				msg.float_signal_0 = unpack754_32(x);
				/* float_signal_1: start-bit 32, length 32, endianess intel, scaling 1, offset 0 */
				x = (i >> 32) & 0xffffffff;
				msg.float_signal_1 = unpack754_32(x);
				new_message0_pub_->publish(msg);
				break;
			}
		}
	}

	rclcpp::Subscription<float_signal::msg::NewMessage0>::SharedPtr new_message0_sub_;
	rclcpp::Publisher<float_signal::msg::NewMessage0>::SharedPtr new_message0_pub_;
	rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr frame_subscription_;
	rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr frame_publisher_;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::executors::StaticSingleThreadedExecutor executor;
	auto node = std::make_shared<FloatSignalParser>();
	executor.add_node(node);
	executor.spin();
	rclcpp::shutdown();
	return 0;
}
