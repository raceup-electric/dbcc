/* CAN message encoder/decoder: automatically generated - do not edit. */

#include <rclcpp/rclcpp.hpp>
#include <cstring>
#include <cstdint>
#include <can_msgs/msg/frame.hpp>

#include <enum/msg/ivt_sleep_ack.hpp>
#include <enum/msg/ivt_ctrl.hpp>
#include <enum/msg/enum1.hpp>
#include <enum/msg/enum2.hpp>


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

class EnumParser : public rclcpp::Node {
public:
	EnumParser() : Node("enum_parser", "/enum") {
		createPublishers();
		createSubscriptions();
	}

private:
	void createSubscriptions() {
		auto qos = rclcpp::SensorDataQoS();

		/* 0x122: IVTSleepAck */
		ivt_sleep_ack_sub_ = this->create_subscription<enum::msg::IVTSleepAck>(
			"ivt_sleep_ack", qos, [this](const enum::msg::IVTSleepAck::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* ivt_sleep_ack: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->ivt_sleep_ack))) & 0xf;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 1, 290);
			}
		);

		/* 0x003: IVTCtrl */
		ivt_ctrl_sub_ = this->create_subscription<enum::msg::IVTCtrl>(
			"ivt_ctrl", qos, [this](const enum::msg::IVTCtrl::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* ivt_ctrl_fuse_state: start-bit 13, length 1, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->ivt_ctrl_fuse_state))) & 0x1;
				x <<= 13; 
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 3);
			}
		);

		/* 0x001: Enum1 */
		enum1_sub_ = this->create_subscription<enum::msg::Enum1>(
			"enum1", qos, [this](const enum::msg::Enum1::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* state: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->state))) & 0xf;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 1);
			}
		);

		/* 0x004: Enum2 */
		enum2_sub_ = this->create_subscription<enum::msg::Enum2>(
			"enum2", qos, [this](const enum::msg::Enum2::SharedPtr msg) {
				if (msg->header.received) return;
				uint64_t x;
				uint64_t i = 0;
				/* state: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = ((uint8_t)((msg->state))) & 0xf;
				i |= x;
				uint64_t data = (i);
				publishFrame(data, 8, 4);
			}
		);

		frame_subscription_ = this->create_subscription<can_msgs::msg::Frame>(
			"/can/enum/read", qos, [this](const can_msgs::msg::Frame::SharedPtr msg) {
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

		ivt_sleep_ack_pub_ = this->create_publisher<enum::msg::IVTSleepAck>("ivt_sleep_ack", qos);
		ivt_ctrl_pub_ = this->create_publisher<enum::msg::IVTCtrl>("ivt_ctrl", qos);
		enum1_pub_ = this->create_publisher<enum::msg::Enum1>("enum1", qos);
		enum2_pub_ = this->create_publisher<enum::msg::Enum2>("enum2", qos);
		frame_publisher_ = this->create_publisher<can_msgs::msg::Frame>("/can/enum/write", qos);
	}

	void decodeMessage(uint64_t data, uint8_t dlc, uint32_t id, const rclcpp::Time& timestamp) {
		switch(id) {
			case 290: { /* 0x122: IVTSleepAck */
				if (dlc < 1) return;
				enum::msg::IVTSleepAck msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* ivt_sleep_ack: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = i & 0xf;
				x = (x & 0x8) ? (x | 0xf0) : x; 
				msg.ivt_sleep_ack = (int8_t)(x);
				ivt_sleep_ack_pub_->publish(msg);
				break;
			}
			case 3: { /* 0x003: IVTCtrl */
				if (dlc < 8) return;
				enum::msg::IVTCtrl msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* ivt_ctrl_fuse_state: start-bit 13, length 1, endianess intel, scaling 1, offset 0 */
				x = (i >> 13) & 0x1;
				msg.ivt_ctrl_fuse_state = (uint8_t)(x);
				ivt_ctrl_pub_->publish(msg);
				break;
			}
			case 1: { /* 0x001: Enum1 */
				if (dlc < 8) return;
				enum::msg::Enum1 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* state: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = i & 0xf;
				msg.state = (uint8_t)(x);
				enum1_pub_->publish(msg);
				break;
			}
			case 4: { /* 0x004: Enum2 */
				if (dlc < 8) return;
				enum::msg::Enum2 msg;
				msg.header.stamp = timestamp;
				msg.header.received = true;
				uint64_t x;
				uint64_t i = (data);
				/* state: start-bit 0, length 4, endianess intel, scaling 1, offset 0 */
				x = i & 0xf;
				msg.state = (uint8_t)(x);
				enum2_pub_->publish(msg);
				break;
			}
		}
	}

	rclcpp::Subscription<enum::msg::IVTSleepAck>::SharedPtr ivt_sleep_ack_sub_;
	rclcpp::Publisher<enum::msg::IVTSleepAck>::SharedPtr ivt_sleep_ack_pub_;
	rclcpp::Subscription<enum::msg::IVTCtrl>::SharedPtr ivt_ctrl_sub_;
	rclcpp::Publisher<enum::msg::IVTCtrl>::SharedPtr ivt_ctrl_pub_;
	rclcpp::Subscription<enum::msg::Enum1>::SharedPtr enum1_sub_;
	rclcpp::Publisher<enum::msg::Enum1>::SharedPtr enum1_pub_;
	rclcpp::Subscription<enum::msg::Enum2>::SharedPtr enum2_sub_;
	rclcpp::Publisher<enum::msg::Enum2>::SharedPtr enum2_pub_;
	rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr frame_subscription_;
	rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr frame_publisher_;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::executors::StaticSingleThreadedExecutor executor;
	auto node = std::make_shared<EnumParser>();
	executor.add_node(node);
	executor.spin();
	rclcpp::shutdown();
	return 0;
}
