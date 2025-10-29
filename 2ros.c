
#include "2ros.h"
#include "util.h"
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <regex.h>

static const bool swap_motorola = true; // WHAT ????


// TODO check, copiato da socketcan_writer
static char *setup_real_time = "\
    void setupRealTime(int32_t priority) {\n\
        if (priority > 99) priority = 99;\n\
\n\
        struct sched_param schp = {};\n\
        schp.sched_priority = priority;\n\
        struct rlimit rt_limit = {priority, priority};\n\
\n\
        if (setrlimit(RLIMIT_RTPRIO, &rt_limit) || sched_setscheduler(0, SCHED_FIFO, &schp)) {\n\
            RCLCPP_WARN(this->get_logger(), \"Realtime priority could not be set.\");\n\
        } else {\n\
            RCLCPP_INFO(this->get_logger(), \"Realtime priority set to %d\", priority);\n\
        }\n\
    }\n\
\n";

// TODO check, adattato da socketcan_writer
static char *create_and_write_socket = "\
    void setupSocket(const std::string &ifname) {\n\
        socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);\n\
        if (socket_ < 0) {\n\
            RCLCPP_FATAL(this->get_logger(), \"Failed to create CAN socket for %s: %s\", ifname.c_str(), strerror(errno));\n\
            rclcpp::shutdown();\n\
            return;\n\
        }\n\
\n\
        struct ifreq ifr;\n\
        std::strncpy(ifr.ifr_name, ifname.c_str(), IFNAMSIZ);\n\
        if (ioctl(socket_, SIOCGIFINDEX, &ifr) < 0) {\n\
            RCLCPP_FATAL(this->get_logger(), \"CAN interface %s not found: %s\", ifname.c_str(), strerror(errno));\n\
            close(socket_);\n\
            // rclcpp::shutdown();\n\
            return;\n\
        }\n\
\n\
        struct sockaddr_can addr = {};\n\
        addr.can_family = AF_CAN;\n\
        addr.can_ifindex = ifr.ifr_ifindex;\n\
\n\
        if (bind(socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0) {\n\
            RCLCPP_FATAL(this->get_logger(), \"Failed to bind socket to %s: %s\", ifname.c_str(), strerror(errno));\n\
            close(socket_);\n\
            rclcpp::shutdown();\n\
            return;\n\
        }\n\
\n\
        RCLCPP_INFO(this->get_logger(), \"Connected to CAN interface: %s\", ifname.c_str());\n\
    }\n\
\n\
    void writeToSocket(uint32_t can_id, const uint8_t* data, size_t size) {\n\
        struct can_frame frame = {};\n\
        frame.can_id = can_id;\n\
        frame.can_dlc = std::min<size_t>(size, 8);\n\
        std::memcpy(frame.data, data, frame.can_dlc);\n\
\n\
        int nbytes = write(socket_, &frame, sizeof(struct can_frame));\n\
\n\
        if (nbytes != sizeof(struct can_frame)) {\n\
            RCLCPP_ERROR(this->get_logger(), \"Write error on CAN socket: \045s\", strerror(errno));\n\
        } else {\n\
            RCLCPP_DEBUG(this->get_logger(), \"Message sent on CAN to CAN ID 0x\045X\", can_id);\n\
        }\n\
    }\n\
\n";

static char *float_pack = "\
/* pack754() -- pack a floating point number into IEEE-754 format */ \n\
static uint64_t pack754(const double f, const unsigned bits, const unsigned expbits) {\n\
	if (f == 0.0) /* get this special case out of the way */\n\
		return signbit(f) ? (1uLL << (bits - 1)) :  0;\n\
	if (f != f) /* NaN, encoded as Exponent == all-bits-set, Mantissa != 0, Signbit == Do not care */\n\
		return (1uLL << (bits - 1)) - 1uLL;\n\
	if (f == INFINITY) /* +INFINITY encoded as Mantissa == 0, Exponent == all-bits-set */\n\
		return ((1uLL << expbits) - 1uLL) << (bits - expbits - 1);\n\
	if (f == -INFINITY) /* -INFINITY encoded as Mantissa == 0, Exponent == all-bits-set, Signbit == 1 */\n\
		return (1uLL << (bits - 1)) | ((1uLL << expbits) - 1uLL) << (bits - expbits - 1);\n\
\n\
	long long sign = 0;\n\
	double fnorm = f;\n\
	/* check sign and begin normalization */\n\
	if (f < 0) { sign = 1; fnorm = -f; }\n\
\n\
	/* get the normalized form of f and track the exponent */\n\
	int shift = 0;\n\
	while (fnorm >= 2.0) { fnorm /= 2.0; shift++; }\n\
	while (fnorm < 1.0)  { fnorm *= 2.0; shift--; }\n\
	fnorm = fnorm - 1.0;\n\
\n\
	const unsigned significandbits = bits - expbits - 1; // -1 for sign bit\n\
\n\
	/* calculate the binary form (non-float) of the significand data */\n\
	const long long significand = fnorm * (( 1LL << significandbits) + 0.5f);\n\
\n\
	/* get the biased exponent */\n\
	const long long exp = shift + ((1LL << (expbits - 1)) - 1); // shift + bias\n\
\n\
	/* return the final answer */\n\
	return (sign << (bits - 1)) | (exp << (bits - expbits - 1)) | significand;\n\
}\n\
\n\
static inline uint32_t   pack754_32(const float  f)   { return   pack754(f, 32, 8); }\n\
static inline uint64_t   pack754_64(const double f)   { return   pack754(f, 64, 11); }\n\
\n\n";

static char *float_unpack = "\
/* unpack754() -- unpack a floating point number from IEEE-754 format */ \n\
static double unpack754(const uint64_t i, const unsigned bits, const unsigned expbits) {\n\
	if (i == 0) return 0.0;\n\
\n\
	const uint64_t expset = ((1uLL << expbits) - 1uLL) << (bits - expbits - 1);\n\
	if ((i & expset) == expset) { /* NaN or +/-Infinity */\n\
		if (i & ((1uLL << (bits - expbits - 1)) - 1uLL)) /* Non zero Mantissa means NaN */\n\
			return NAN;\n\
		return (i & (1uLL << (bits - 1))) ? -INFINITY : INFINITY;\n\
	}\n\
\n\
	/* pull the significand */\n\
	const unsigned significandbits = bits - expbits - 1; /* - 1 for sign bit */\n\
	double result = (i & ((1LL << significandbits) - 1)); /* mask */\n\
	result /= (1LL << significandbits);  /* convert back to float */\n\
	result += 1.0f;                        /* add the one back on */\n\
\n\
	/* deal with the exponent */\n\
	const unsigned bias = (1 << (expbits - 1)) - 1;\n\
	long long shift = ((i >> significandbits) & ((1LL << expbits) - 1)) - bias;\n\
	while (shift > 0) { result *= 2.0; shift--; }\n\
	while (shift < 0) { result /= 2.0; shift++; }\n\
	\n\
	return ((i >> (bits - 1)) & 1) ? -result : result; /* sign it, and return */\n\
}\n\
\n\
static inline float    unpack754_32(uint32_t i) { return unpack754(i, 32, 8); }\n\
static inline double   unpack754_64(uint64_t i) { return unpack754(i, 64, 11); }\n\
\n\n";

static unsigned fix_start_bit(bool motorola, unsigned start, unsigned siglen)
{
	if (motorola)
		start = (8 * (7 - (start / 8))) + (start % 8) - (siglen - 1);
	return start;
}

static const char *determine_unsigned_type_c(unsigned length)
{
	const char *type = "uint64_t";
	if (length <= 32)
		type = "uint32_t";
	if (length <= 16)
		type = "uint16_t";
	if (length <= 8)
		type = "uint8_t";
	return type;
}

static const char *determine_signed_type_c(unsigned length)
{
	const char *type = "int64_t";
	if (length <= 32)
		type = "int32_t";
	if (length <= 16)
		type = "int16_t";
	if (length <= 8)
		type = "int8_t";
	return type;
}

static const char *determine_type_c(unsigned length, bool is_signed, bool is_floating)
{
	if (is_floating)
		return length == 64 ? "dbcc_double_t" : "dbcc_float_t";
	return is_signed ?
		determine_signed_type_c(length) :
		determine_unsigned_type_c(length);
}

static const char *determine_unsigned_type_rosmsg(unsigned length)
{
	const char *type = "uint64";
	if (length <= 32)
		type = "uint32";
	if (length <= 16)
		type = "uint16";
	if (length <= 8)
		type = "uint8";
	return type;
}

static const char *determine_signed_type_rosmsg(unsigned length)
{
	const char *type = "int64";
	if (length <= 32)
		type = "int32";
	if (length <= 16)
		type = "int16";
	if (length <= 8)
		type = "int8";
	return type;
}

static const char *determine_type_rosmsg(unsigned length, bool is_signed, bool is_floating)
{
	if (is_floating)
		return length == 64 ? "float64" : "float32";
	return is_signed ?
		determine_signed_type_rosmsg(length) :
		determine_unsigned_type_rosmsg(length);
}

static int comment(signal_t *sig, FILE *o, const char *indent)
{
	assert(sig);
	assert(o);
	return fprintf(o, "%s/* %s: start-bit %u, length %u, endianess %s, scaling %g, offset %g */\n",
			indent,
			sig->name,
			sig->start_bit,
			sig->bit_length,
			sig->endianess == endianess_motorola_e ? "motorola" : "intel",
			sig->scaling,
			sig->offset) < 0 ? - 1 : 0;
}


static void create_folders(const char *path) {
	if (mkdir(path, 0777) == -1) {
		if (errno != EEXIST) {
			error("error creating folder");
		}
	}

	char *fullpath = duplicate(path);
	size_t name_size = strlen(path) + strlen("/msg") + 1; /* + 1 for '\0' */
	fullpath = reallocator(fullpath, name_size);
	strcat(fullpath, "/msg");
	if (mkdir(fullpath, 0777) == -1) {
		if (errno != EEXIST) {
			free(fullpath);
			error("error creating folder");
		}
	}
	free(fullpath);

	fullpath = duplicate(path);
	name_size = strlen(path) + strlen("/src") + 1; /* + 1 for '\0' */
	fullpath = reallocator(fullpath, name_size);
	strcat(fullpath, "/src");
	if (mkdir(fullpath, 0777) == -1) {
		if (errno != EEXIST) {
			free(fullpath);
			error("error creating folder");
		}
	}
	free(fullpath);
}

void str_to_upper(char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		str[i] = toupper((unsigned char)str[i]);
	}
}

static int check_regex_syntax(const char *pattern, const char *text) {
	regex_t regex;
	int ret;

	// Compile the regex
	ret = regcomp(&regex, pattern, REG_EXTENDED);
	if (ret) {
		error("Could not compile regex\n");
	}

	// Execute regex
	ret = regexec(&regex, text, 0, NULL, 0);

	// Free memory
	regfree(&regex);

	return ret == 0;
}

static void check_message_namimg(const char* message) {
	int ok = check_regex_syntax("^[A-Z][A-Za-z0-9]*$", message);
	if (!ok) {
		fprintf(stderr, "WARNING: '%s' is not a valid %s. It should have the pattern %s. ROS2 will not compile.\n", message, "message", "^[A-Z][A-Za-z0-9]*$");
	}
}

static void check_signal_namimg(const char* signal) {
	int ok = check_regex_syntax("^[a-z][a-z0-9_]*$", signal);
	if (strstr(signal, "__")) ok = 0; // (?!.*__)
	if (strlen(signal) > 0 && signal[strlen(signal)-1] == '_') ok = 0; // (?!.*_$)
	if (!ok) {
		fprintf(stderr, "WARNING: '%s' is not a valid %s. It should have the pattern %s. ROS2 will not compile.\n", signal, "signal", "^(?!.*__)(?!.*_$)[a-z][a-z0-9_]*$");
	}
}

static void check_value_namimg(const char* value) {
	int ok = check_regex_syntax("^[A-Z]([A-Z0-9_]?[A-Z0-9]+)*$", value);
	if (!ok) {
		fprintf(stderr, "WARNING: '%s' is not a valid %s. It should have the pattern %s. ROS2 will not compile.\n", value, "value", "^[A-Z]([A-Z0-9_]?[A-Z0-9]+)*$");
	}
}

static void check_package_namimg(const char* package) {
	int ok = check_regex_syntax("^[a-z][a-z0-9_]*[a-z0-9]$", package);
	if (!ok) {
		fprintf(stderr, "WARNING: '%s' is not a valid name. It should have the pattern %s. Please specify a valid name.\n", package, "^[a-z][a-z0-9_]*[a-z0-9]$");
	}
}

static void check_input_naming(const dbc_t *dbc, const char *package_name) {
	for (size_t i = 0; i < dbc->message_count; i++) {
		const can_msg_t *msg = dbc->messages[i];
		check_message_namimg(msg->name);
		
		for (size_t j = 0; j < msg->signal_count; j++) {
			const signal_t *sig = msg->sigs[j];
			check_signal_namimg(sig->name);
			
			if (!sig->val_list) continue;
			for (size_t k = 0; k < sig->val_list->val_list_item_count; k++) {
				const val_list_item_t *val = sig->val_list->val_list_items[k];
				check_value_namimg(val->name);
			}
		}
	}
	check_package_namimg(package_name);
}

static void generate_ros_msgs(const dbc_t *dbc, const char *outdir) {
	for (size_t i = 0; i < dbc->message_count; i++) {
		const can_msg_t *msg = dbc->messages[i];
		size_t name_size = strlen(outdir) + strlen("/msg/") + strlen(msg->name) + strlen(".msg") + 1; /* + 1 for '\0' */
		char *file_name = allocate(name_size);
		snprintf(file_name, name_size, "%s%s%s%s", outdir, "/msg/", msg->name, ".msg");
		FILE *file = fopen_or_die(file_name, "wb");

		if (msg->comment) 
			fprintf(file, "# %s\n\n", msg->comment);

		for (size_t j = 0; j < msg->signal_count; j++) {
			const signal_t *sig = msg->sigs[j];
			const char *type = determine_type_rosmsg(sig->bit_length, sig->is_signed, sig->is_floating);
			const char *name = sig->name;
			fprintf(file, "%s %s\n", type, name);
		}

		fprintf(file, "\n");

		for (size_t j = 0; j < msg->signal_count; j++) {
			const signal_t *sig = msg->sigs[j];
			if (!sig->val_list) {
				continue;
			}

			val_list_item_t **val = sig->val_list->val_list_items;

			fprintf(file, "\n# %s constants\n", sig->name);
			
			for (size_t k = 0; k < sig->val_list->val_list_item_count; k++) {
				char *name = val[k]->name;
				const unsigned value = val[k]->value;
				const char *type = determine_type_rosmsg(sig->bit_length, sig->is_signed, sig->is_floating);
				
				fprintf(file, "%s %s=%d\n", type, name, value);
			}
		}

		fclose(file);
		free(file_name);
	}
}


static void pascal2snake(char *out, const size_t out_size, const char *pascal) {
	size_t j = 0;
	for (size_t i = 0; pascal[i] && j + 1 < out_size; i++) {
		// handles upper/lower case letter and numbers like ros compiler (in theory)
		if (i > 0 && isupper((unsigned char)pascal[i]) &&
			(pascal[i+1] ? 
				!isupper((unsigned char)pascal[i-1]) || islower((unsigned char)pascal[i+1])
				: !isupper((unsigned char)pascal[i-1]))) {
			if (j + 1 < out_size) out[j++] = '_';
		}
		if (j + 1 < out_size)
			out[j++] = (char)tolower((unsigned char)pascal[i]);
	}
	out[j] = '\0';
}

static void snake2pascal(char *out, const size_t out_size, const char *snake) {
	size_t j = 0;
	int upper = 1;
	for (size_t i = 0; snake[i] && j + 1 < out_size; i++) {
		while (snake[i] == '_') {
			i++;
			upper = 1;
		}
		if (upper) {
			out[j++] = (char)toupper((unsigned char)snake[i]);
			upper = 0;
		} else {
			out[j++] = (char)tolower((unsigned char)snake[i]);
		}
	}
	out[j] = '\0';
}

static void create_headers(const dbc_t *dbc, FILE *file, const char *package_name) {
	fprintf(file, "\
#include <rclcpp/rclcpp.hpp>\n\
//...TODO ADD ALL INCLUDES\n\
\n");
	for (size_t i = 0; i < dbc->message_count; i++) {
		const can_msg_t *msg = dbc->messages[i];
		char snake_msg_name[strlen(msg->name) * 2]; // snake_case message name
		pascal2snake(snake_msg_name, strlen(msg->name) * 2, msg->name);

		fprintf(file, "#include <%s/msg/%s.hpp>\n", package_name, snake_msg_name);
	}
	fprintf(file, "\n\n");
}

static void create_constructor_destructor(FILE *file, const char *class_name, const char *node_name) {
	fprintf(file, "\
    %s() : Node(\"%s\") {\n\
        int priority = this->declare_parameter<int>(\"sched_priority\", 99);\n\
		std::string interface_name = this->declare_parameter<std::string>(\"interface_name\", \"can0\");\n\n\
        setupRealTime(priority);\n\
        setupSocket(interface_name);\n\
        createSubscriptions();\n\
    }\n\n\
    virtual ~%s() {\n\
        if (socket_ >= 0) close(socket_);\n\
    }\n\n",
	class_name, node_name, class_name);
}

static int signal2serializer(signal_t *sig, FILE *o, const char *indent)
{
	assert(sig);
	assert(o);
	bool motorola = (sig->endianess == endianess_motorola_e);
	int start = fix_start_bit(motorola, sig->start_bit, sig->bit_length);

	uint64_t mask = sig->bit_length == 64 ?
		0xFFFFFFFFFFFFFFFFuLL :
		(1uLL << sig->bit_length) - 1uLL;

	if (comment(sig, o, indent) < 0)
		return -1;

	if (sig->is_floating) {
		assert(sig->bit_length == 32 || sig->bit_length == 64);
		if (fprintf(o, "%sx = pack754_%u(msg.%s) & 0x%"PRIx64";\n", indent, sig->bit_length, sig->name, mask) < 0)
			return -1;
	} else {
		if (fprintf(o, "%sx = ((%s)(msg.%s)) & 0x%"PRIx64";\n", indent, determine_unsigned_type_c(sig->bit_length), sig->name, mask) < 0)
			return -1;
	}
	if (start)
		if (fprintf(o, "%sx <<= %u; \n", indent, start) < 0)
			return -1;
	if (fprintf(o, "%s%c |= x;\n", indent, motorola ? 'm' : 'i') < 0)
		return -1;
	return 0;
}

static int msg_pack(FILE *c, can_msg_t *msg, const char *package_name)
{
	assert(msg);
	assert(c);

	bool motorola_used = false;
	bool intel_used = false;

	for (size_t i = 0; i < msg->signal_count; i++)
		if (msg->sigs[i]->endianess == endianess_motorola_e)
			motorola_used = true;
		else
			intel_used = true;

	const bool message_has_signals = motorola_used || intel_used;

	char snake_msg_name[strlen(msg->name) * 2]; // snake_case message name
	pascal2snake(snake_msg_name, strlen(msg->name) * 2, msg->name);

	fprintf(c, "\t\t%s_sub_ = this->create_subscription<%s::msg::%s>(\n", snake_msg_name, package_name, msg->name);
	fprintf(c, "\t\t\t\"/%s/%s\", 10, [this](const %s::msg::%s::SharedPtr msg) {\n", package_name, snake_msg_name, package_name, msg->name);

	if (message_has_signals)
		fprintf(c, "\t\t\t\tuint64_t x;\n");
	if (motorola_used)
		fprintf(c, "\t\t\t\tuint64_t m = 0;\n");
	if (intel_used)
		fprintf(c, "\t\t\t\tuint64_t i = 0;\n");
	if (!message_has_signals)
		fprintf(c, "\t\t\t\tUNUSED(o);\n\t\tUNUSED(data);\n");
	
	for (size_t i = 0; i < msg->signal_count; i++) {
		// TODO add multiplexed signal logic
		if (msg->sigs[i]->is_multiplexed)
			fprintf(stderr, "WARNING: multiplexed signal are not yet supported! (%ld - %s: %s)\n",
				msg->id, msg->name, msg->sigs[i]->name);

		signal2serializer(msg->sigs[i], c, "\t\t\t\t");
	}

	if (message_has_signals) {
		fprintf(c, "\t\t\t\tuint64_t data = %s%s%s%s%s;\n",
			swap_motorola && motorola_used ? "reverse_byte_order" : "",
			motorola_used ? "(m)" : "",
			motorola_used && intel_used ? "|" : "",
			(!swap_motorola && intel_used) ? "reverse_byte_order" : "",
			intel_used ? "(i)" : "");
	}
	fprintf(c, "\t\t\t\twriteToSocket(%ld, reinterpret_cast<uint8_t*>(&data), sizeof(data))\n", msg->id);
	fprintf(c, "\t\t\t}\n\t\t);\n\n");
	return 0;
}

static void create_subscribers(const dbc_t *dbc, FILE *file, const char *package_name) {
	fprintf(file, "\tvoid createSubscriptions() {\n");
	for (size_t i = 0; i < dbc->message_count; i++) {
		msg_pack(file, dbc->messages[i], package_name);
	}
	fprintf(file, "\t}\n\n");
}

static void create_variables(const dbc_t *dbc, FILE *file, const char *package_name) {
	fprintf(file, "\tint socket_{-1};\n\n");
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		char snake_msg_name[strlen(msg->name) * 2]; // snake_case message name
		pascal2snake(snake_msg_name, strlen(msg->name) * 2, msg->name);

		fprintf(file, "\trclcpp::Subscription<%s::msg::%s>::SharedPtr %s_sub_;\n", package_name, msg->name, snake_msg_name);
	}
}

static void create_main(FILE *file, const char *class_name) {
	fprintf(file, "\
int main(int argc, char **argv) {\n\
    rclcpp::init(argc, argv);\n\
    rclcpp::spin(std::make_shared<%s>());\n\
    rclcpp::shutdown();\n\
    return 0;\n\
}\n", class_name);
}

static void generate_ros_node(const dbc_t *dbc, const char *outdir, const char *package_name) {
	size_t node_name_size = strlen(package_name) + strlen("_parser") + 1; /* + 1 for '\0' */
	char *node_name = allocate(node_name_size);
	snprintf(node_name, node_name_size, "%s%s", package_name, "_parser");

	size_t file_name_size = strlen(outdir) + strlen("/src/") + strlen(node_name) + strlen(".cpp") + 1;
	char *file_name = allocate(file_name_size);
	snprintf(file_name, file_name_size, "%s%s%s%s", outdir, "/src/", node_name, ".cpp");
	
	size_t class_name_size = strlen(node_name);
	char *class_name = allocate(class_name_size);
	snake2pascal(class_name, class_name_size, node_name);

	FILE *file = fopen_or_die(file_name, "wb");

	create_headers(dbc, file, package_name);
	fprintf(file, "class %s : public rclcpp::Node {\n", class_name);
	fprintf(file, "public:\n");
	create_constructor_destructor(file, class_name, node_name);
	fprintf(file, "private:\n");
	fprintf(file, "%s", setup_real_time);
	fprintf(file, "%s", create_and_write_socket);
	create_subscribers(dbc, file, package_name);
	create_variables(dbc, file, package_name);
	fprintf(file, "}\n\n");
	create_main(file, class_name);

	fclose(file);
	free(class_name);
	free(file_name);
	free(node_name);
}

int dbc2ros(const dbc_t *dbc, const char *outdir, const char *package_name) {
	assert(dbc);
	assert(outdir);
	assert(package_name);

	check_input_naming(dbc, package_name);

	create_folders(outdir);

	generate_ros_msgs(dbc, outdir);

	generate_ros_node(dbc, outdir, package_name);

	return 0;
}