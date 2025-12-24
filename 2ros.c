
#include "2ros.h"
#include "util.h"
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <regex.h>

static const bool swap_motorola = true;


// TODO check, copiato da socketcan_writer
static const char *setup_real_time = "\
	void setupRealTime(uint32_t priority) {\n\
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
static const char *create_and_write_socket = "\
	void setupSocket(const std::string &ifname) {\n\
		socket_ = socket(AF_CAN, SOCK_RAW, CAN_RAW);\n\
		if (socket_ < 0) {\n\
			throw std::runtime_error(\"Failed to create CAN socket\");\n\
		}\n\
\n\
		struct ifreq ifr {};\n\
		std::strncpy(ifr.ifr_name, ifname.c_str(), IFNAMSIZ - 1);\n\
\n\
		if (ioctl(socket_, SIOCGIFINDEX, &ifr) < 0) {\n\
			close(socket_);\n\
			socket_ = -1;\n\
			throw std::runtime_error(\"CAN interface not found: \" + ifname);\n\
		}\n\
\n\
		struct sockaddr_can addr {};\n\
		addr.can_family = AF_CAN;\n\
		addr.can_ifindex = ifr.ifr_ifindex;\n\
\n\
		if (bind(socket_, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {\n\
			close(socket_);\n\
			socket_ = -1;\n\
			throw std::runtime_error(\"Failed to bind CAN socket\");\n\
		}\n\
\n\
		RCLCPP_INFO(this->get_logger(), \"Connected to CAN interface: %s\", ifname.c_str());\n\
	}\n\
\n\
	void writeToSocket(uint32_t can_id, const void* data, uint8_t dlc) {\n\
		struct can_frame frame = {};\n\
		frame.can_id = can_id;\n\
		frame.can_dlc = std::min<uint8_t>(dlc, 8);\n\
		std::memcpy(frame.data, data, frame.can_dlc);\n\
\n\
		ssize_t nbytes = write(socket_, &frame, sizeof(struct can_frame));\n\
\n\
		if (nbytes != sizeof(struct can_frame)) {\n\
			RCLCPP_ERROR(this->get_logger(), \"Write error on CAN socket: \045s\", strerror(errno));\n\
		}\n\
	}\n\
\n";

static const char *read_socket = "\
			struct can_frame frame;\n\
			ssize_t nbytes = read(socket_, &frame, sizeof(struct can_frame));\n\n\
			if (nbytes < 0) {\n\
				RCLCPP_ERROR(this->get_logger(), \"Read error on CAN socket \045s\", strerror(errno));\n\
				continue;\n\
			} else if ((size_t)nbytes < sizeof(struct can_frame)) {\n\
				RCLCPP_ERROR(this->get_logger(), \"Read incomplete CAN frame\");\n\
				continue;\n\
			}\n\
\n";

static const char *float_pack = "\
static inline uint32_t pack754_32(const float f) {\n\
\tuint32_t i;\n\
\tstd::memcpy(&i, &f, sizeof(i));\n\
\treturn i;\n\
}\n\n\
static inline uint64_t pack754_64(const double d) {\n\
\tuint64_t i;\n\
\tstd::memcpy(&i, &d, sizeof(i));\n\
\treturn i;\n\
}\n\n";

static const char *float_unpack = "\
static inline float unpack754_32(const uint32_t i) {\n\
\tfloat f;\n\
\tstd::memcpy(&f, &i, sizeof(f));\n\
\treturn f;\n\
}\n\n\
static inline double unpack754_64(const uint64_t i) {\n\
\tdouble d;\n\
\tstd::memcpy(&d, &i, sizeof(d));\n\
\treturn d;\n\
}\n\n";

static const char *reverse_byte_order =
"static inline uint64_t reverse_byte_order(uint64_t x) {\n"
"\tx = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;\n"
"\tx = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;\n"
"\tx = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;\n"
"\treturn x;\n"
"}\n\n";

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
		return length == 64 ? "double" : "float";
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


static void generate_folders(const char *path) {
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

static void generate_package_xml(const char *outdir, const char *package_name) {
	size_t file_name_size = strlen(outdir) + strlen("/package.xml") + 1;
	char *file_name = allocate(file_name_size);
	snprintf(file_name, file_name_size, "%s%s", outdir, "/package.xml");

	FILE *file = fopen_or_die(file_name, "wb");

	fprintf(file, "\
<?xml version=\"1.0\"?>\n\
<?xml-model href=\"http://download.ros.org/schema/package_format3.xsd\" schematypens=\"http://www.w3.org/2001/XMLSchema\"?>\n\
<package format=\"3\">\n\
  <name>%s</name>\n\
  <version>0.0.0</version>\n\
  <description>TODO: Package description</description>\n\
  <maintainer email=\"todo@raceup.it\">driverless</maintainer>\n\
  <license>TODO: License declaration</license>\n\n\
  <buildtool_depend>ament_cmake</buildtool_depend>\n\
  <build_depend>rosidl_default_generators</build_depend>\n\n\
  <depend>rclcpp</depend>\n\
  <exec_depend>rosidl_default_runtime</exec_depend>\n\n\
  <member_of_group>rosidl_interface_packages</member_of_group>\n\n\
  <export>\n\
    <build_type>ament_cmake</build_type>\n\
  </export>\n\
</package>\n", package_name);

	fclose(file);
	free(file_name);
}

static void generate_cmakelists_txt(const dbc_t *dbc, const char *outdir, const char *package_name) {
	size_t file_name_size = strlen(outdir) + strlen("/CMakeLists.txt") + 1;
	char *file_name = allocate(file_name_size);
	snprintf(file_name, file_name_size, "%s%s", outdir, "/CMakeLists.txt");

	FILE *file = fopen_or_die(file_name, "wb");

	fprintf(file, "\
cmake_minimum_required(VERSION 3.5)\n\
project(%s)\n\n\
# Default to C99\n\
if(NOT CMAKE_C_STANDARD)\n\
  set(CMAKE_C_STANDARD 99)\n\
endif()\n\n\
# Default to C++14\n\
if(NOT CMAKE_CXX_STANDARD)\n\
  set(CMAKE_CXX_STANDARD 14)\n\
endif()\n\n\
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES \"Clang\")\n\
  add_compile_options(-Wall -Wextra -Wpedantic)\n\
endif()\n\n\
# find dependencies\n\
find_package(ament_cmake REQUIRED)\n\
find_package(rclcpp REQUIRED)\n\
find_package(rosidl_default_generators REQUIRED)\n\
#find_package(std_msgs REQUIRED)\n\n\
set(msg_files\n", package_name);

	for (size_t i = 0; i < dbc->message_count; i++) {
		const can_msg_t *msg = dbc->messages[i];
		fprintf(file, "  \"msg/%s.msg\"\n", msg->name);
	}
	fprintf(file, "\
)\n\n\
rosidl_generate_interfaces(${PROJECT_NAME}\n\
  ${msg_files}\n\
  #DEPENDENCIES std_msgs\n\
)\n\n\
# Ensure that C++ nodes can use the generated message headers\n\
ament_export_dependencies(rosidl_default_runtime)\n\n\n\
add_executable(${PROJECT_NAME}_writer src/${PROJECT_NAME}_writer.cpp)\n\
ament_target_dependencies(${PROJECT_NAME}_writer rclcpp)\n\
target_link_libraries(${PROJECT_NAME}_writer\n\
  ${PROJECT_NAME}__rosidl_typesupport_cpp\n\
)\n\n\
install(TARGETS\n\
  ${PROJECT_NAME}_writer\n\
  DESTINATION lib/${PROJECT_NAME}\n\
)\n\n\
ament_package()\n");

	fclose(file);
	free(file_name);
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

static void fix_message_naming(char** message) {
	assert(message);
	assert(*message);

	char* src = *message;
	size_t len = strlen(src);

	// Worst case: all chars kept + possible prepended 'A' + '\0'
	char* dst = allocate(len + 2);
	size_t j = 0;

	for (size_t i = 0; i < len; ++i) {
		if (isalnum((unsigned char)src[i])) {
			dst[j++] = src[i];
		}
	}

	if (j == 0 || isdigit((unsigned char)dst[0])) {
		memmove(dst + 1, dst, j);
		dst[0] = 'A';
		j++;
	}

	dst[0] = (char)toupper((unsigned char)dst[0]);

	dst[j] = '\0';

	if (strcmp(src, dst)) {
		fprintf(stderr, "'%s' changed to '%s'. Messages should have the pattern %s.\n", src, dst, "^[A-Z][A-Za-z0-9]*$");
	}

	free(*message);
	*message = dst;
}

static void fix_signal_naming(char** signal) {
	assert(signal);
	assert(*signal);

	char* src = *signal;
	size_t len = strlen(src);

	// Worst case: all chars kept + possible prepended 'a' + '\0'
	char* dst = allocate(len + 2);
	size_t j = 0;

	for (size_t i = 0; i < len; ++i) {
		unsigned char c = (unsigned char)src[i];

		if (isupper(c)) {
			c = (unsigned char)tolower(c);
		}

		if (islower(c) || isdigit(c)) {
			dst[j++] = (char)c;
		} else if (c == '_') {
			if (j > 0 && dst[j-1] != '_') {
				dst[j++] = '_';
			}
		}
	}

	if (j == 0 || !islower((unsigned char)dst[0])) {
		memmove(dst + 1, dst, j);
		dst[0] = 'a';
		j++;
	}

	if (dst[j - 1] == '_') {
		j--;
	}

	dst[j] = '\0';

	if (strcmp(src, dst)) {
		fprintf(stderr, "'%s' changed to '%s'. Signals should have the pattern %s.\n", src, dst, "^(?!.*__)(?!.*_$)[a-z][a-z0-9_]*$");
	}

	if (strcmp(dst, "timestamp") == 0) {
		fprintf(stderr, "WARNING: illegal signal named '%s'. The generated code will not compile!\n", dst);
	}

	free(*signal);
	*signal = dst;
}

static void fix_value_naming(char** value) {
	assert(value);
	assert(*value);

	char* src = *value;
	size_t len = strlen(src);

	// Worst case: all chars kept + possible prepended 'A' + '\0'
	char* dst = allocate(len + 2);
	size_t j = 0;

	for (size_t i = 0; i < len; ++i) {
		unsigned char c = (unsigned char)src[i];

		if (islower(c)) {
			c = (unsigned char)toupper(c);
		}

		if (isupper(c) || isdigit(c)) {
			dst[j++] = (char)c;
		} else if (c == '_') {
			if (j > 0 && dst[j-1] != '_') {
				dst[j++] = '_';
			}
		}
	}

	if (j == 0 || !isupper((unsigned char)dst[0])) {
		memmove(dst + 1, dst, j);
		dst[0] = 'A';
		j++;
	}

	if (dst[j - 1] == '_') {
		j--;
	}

	dst[j] = '\0';

	if (strcmp(src, dst)) {
		fprintf(stderr, "'%s' changed to '%s'. Values should have the pattern %s.\n", src, dst, "^[A-Z]([A-Z0-9_]?[A-Z0-9]+)*$");
	}

	free(*value);
	*value = dst;
}

static void check_package_naming(const char* package) {
	int ok = check_regex_syntax("^[a-z][a-z0-9_]*[a-z0-9]$", package);
	if (!ok) {
		fprintf(stderr, "WARNING: '%s' is not a valid name. It should have the pattern %s. Please specify a valid name.\n", package, "^[a-z][a-z0-9_]*[a-z0-9]$");
	}
}

static void check_naming_duplicates(const dbc_t *dbc) {
	// check for duplicate message names
	for (size_t i = 0; i < dbc->message_count; i++) {
		for (size_t j = i+1; j < dbc->message_count; j++) {
			if (strcmp(dbc->messages[i]->name, dbc->messages[j]->name) == 0) {
				fprintf(stderr, "WARNING: duplicate message name '%s'. The generated code will not compile!\n",
					dbc->messages[i]->name);
			}
		}
		
		// check for duplicate signal names
		can_msg_t *msg = dbc->messages[i];
		for (size_t j = 0; j < msg->signal_count; j++) {
			for (size_t k = j+1; k < msg->signal_count; k++) {
				if (strcmp(msg->sigs[j]->name, msg->sigs[k]->name) == 0) {
					fprintf(stderr, "WARNING: duplicate signal name '%s' in message '%s'. The generated code will not compile!\n",
						msg->sigs[j]->name, msg->name);
				}
			}

			// check for duplicate value names
			signal_t *sig = msg->sigs[j];
			if (!sig->val_list) continue;
			for (size_t k = 0; k < sig->val_list->val_list_item_count; k++) {
				for (size_t l = k+1; l < sig->val_list->val_list_item_count; l++) {
					if (strcmp(sig->val_list->val_list_items[k]->name, sig->val_list->val_list_items[l]->name) == 0) {
						fprintf(stderr, "WARNING: duplicate value name '%s' in signal '%s', message '%s'. The generated code will not compile!\n",
							sig->val_list->val_list_items[k]->name, sig->name, msg->name);
					}
				}
			}
		}
	}
}

static char *duplicate_upper(const char *s)
{
	size_t len = strlen(s);
	char *out = allocate(len + 1);
	for (size_t i = 0; i < len; i++) {
		out[i] = (char)toupper((unsigned char)s[i]);
	}
	out[len] = '\0';
	return out;
}

static void fix_duplicate_value_naming(const dbc_t *dbc) {
	// check for duplicate value names across different signals in the same message
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		uint8_t *needs_prefix = allocate(msg->signal_count);

		for (size_t j = 0; j < msg->signal_count; j++) {
			signal_t *sig_a = msg->sigs[j];
			if (!sig_a->val_list) continue;

			for (size_t k = j + 1; k < msg->signal_count; k++) {
				signal_t *sig_b = msg->sigs[k];
				if (!sig_b->val_list) continue;

				for (size_t va = 0; va < sig_a->val_list->val_list_item_count; va++) {
					const char *name_a = sig_a->val_list->val_list_items[va]->name;

					for (size_t vb = 0; vb < sig_b->val_list->val_list_item_count; vb++) {
						const char *name_b = sig_b->val_list->val_list_items[vb]->name;

						if (strcmp(name_a, name_b) == 0) {
							needs_prefix[j] = 1;
							needs_prefix[k] = 1;
						}
					}
				}
			}
		}

		for (size_t j = 0; j < msg->signal_count; j++) {
			if (!needs_prefix[j]) continue;

			signal_t *sig = msg->sigs[j];
			char *sig_upper = duplicate_upper(sig->name);

			for (size_t v = 0; v < sig->val_list->val_list_item_count; v++) {
				val_list_item_t *item = sig->val_list->val_list_items[v];

				char *old_name = item->name;
				size_t new_len = strlen(sig_upper) + strlen(old_name) + 2;
				char *new_name = allocate(new_len);

				snprintf(new_name, new_len, "%s_%s", sig_upper, old_name);

				//fprintf(stdout, "'%s' changed to '%s'.\n", old_name, new_name);
				item->name = new_name;
				free(old_name);
			}
			free(sig_upper);
		}
		free(needs_prefix);
	}
}

static void check_input_naming(const dbc_t *dbc, const char *package_name) {
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		fix_message_naming(&msg->name);
		
		for (size_t j = 0; j < msg->signal_count; j++) {
			signal_t *sig = msg->sigs[j];
			fix_signal_naming(&sig->name);
			
			if (!sig->val_list) continue;
			for (size_t k = 0; k < sig->val_list->val_list_item_count; k++) {
				val_list_item_t *val = sig->val_list->val_list_items[k];
				fix_value_naming(&val->name);
			}
		}
	}
	check_package_naming(package_name);
	check_naming_duplicates(dbc);
	fix_duplicate_value_naming(dbc);
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

		fprintf(file, "builtin_interfaces/Time timestamp\n");

		for (size_t j = 0; j < msg->signal_count; j++) {
			const signal_t *sig = msg->sigs[j];
			const char *type = "float64";
			if (sig->offset == 0.0 && sig->scaling == 1.0)
				type = determine_type_rosmsg(sig->bit_length, sig->is_signed, sig->is_floating);
			const char *name = sig->name;
			const char *comment = sig->comment;

			fprintf(file, "%s %s", type, name);
			if (comment) fprintf(file, " # %s", comment);
			fprintf(file, "\n");
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


static char *pascal2snake(const char *pascal) {
	size_t len = strlen(pascal) * 2 + 1; // TODO basta meno
	char *out = allocate(len);
	size_t j = 0;
	for (size_t i = 0; pascal[i]; i++) {
		// handles upper/lower case letter and numbers like ros compiler (in theory)
		if (i > 0 && isupper((unsigned char)pascal[i]) &&
			(pascal[i+1] ? 
				!isupper((unsigned char)pascal[i-1]) || islower((unsigned char)pascal[i+1])
				: !isupper((unsigned char)pascal[i-1]))) {
			out[j++] = '_';
		}
		out[j++] = (char)tolower((unsigned char)pascal[i]);
	}
	out[j] = '\0';
	return out;
}

static char *snake2pascal(const char *snake) {
	size_t len = strlen(snake) + 1;
	char *out = allocate(len);
	size_t j = 0;
	int upper = 1;
	for (size_t i = 0; snake[i]; i++) {
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
	return out;
}

static void create_headers(const dbc_t *dbc, FILE *file, const char *package_name) {
	fprintf(file, "\
#include <rclcpp/rclcpp.hpp>\n\
#include <cstring>\n\
#include <string>\n\
#include <unistd.h>\n\
#include <net/if.h>\n\
#include <sys/ioctl.h>\n\
#include <sys/socket.h>\n\
#include <sys/resource.h>\n\
#include <linux/can.h>\n\
#include <linux/can/raw.h>\n\
#include <sched.h>\n\
#include <cerrno>\n\
#include <algorithm>\n\
#include <thread>\n\
#include <atomic>\n\
\n");
	for (size_t i = 0; i < dbc->message_count; i++) {
		const can_msg_t *msg = dbc->messages[i];
		char *snake_msg_name = pascal2snake(msg->name); // snake_case message name

		fprintf(file, "#include <%s/msg/%s.hpp>\n", package_name, snake_msg_name);
		free(snake_msg_name);
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
		createPublishers();\n\
		read_thread_ = std::thread(&%s::readLoop, this);\n\
	}\n\n\
	virtual ~%s() {\n\
		running_ = false;\n\
		if (socket_ >= 0) shutdown(socket_, SHUT_RDWR); // Unblock blocking read()\n\
		if (read_thread_.joinable()) read_thread_.join();\n\
		if (socket_ >= 0) close(socket_);\n\
	}\n\n",
	class_name, node_name, class_name, class_name);
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

	if (sig->is_floating)
		assert(sig->bit_length == 32 || sig->bit_length == 64);

	fprintf(o, "%sx = (", indent);
	if (sig->is_floating)
		fprintf(o, "pack754_%u", sig->bit_length);
	else
		fprintf(o, "(%s)", determine_unsigned_type_c(sig->bit_length));
	fprintf(o, "((msg->%s", sig->name);
	if (sig->offset != 0.0)
		fprintf(o, " + %g", -1.0 * sig->offset);
	fprintf(o, ")");
	if (sig->scaling != 1.0)
		fprintf(o, " * %g", 1.0 / sig->scaling);
	fprintf(o, ")) & 0x%"PRIx64";\n", mask);


	if (start)
		if (fprintf(o, "%sx <<= %u; \n", indent, start) < 0)
			return -1;
	if (fprintf(o, "%s%c |= x;\n", indent, motorola ? 'm' : 'i') < 0)
		return -1;
	return 0;
}

static int signal2deserializer(signal_t *sig, FILE *o, const char *indent)
{
	assert(sig);
	assert(o);
	const bool motorola   = (sig->endianess == endianess_motorola_e);
	const unsigned start  = fix_start_bit(motorola, sig->start_bit, sig->bit_length);
	const unsigned length = sig->bit_length;
	const uint64_t mask = length == 64 ?
		0xFFFFFFFFFFFFFFFFuLL :
		(1uLL << length) - 1uLL;

	if (comment(sig, o, indent) < 0)
		return -1;

	if (start) {
		if (fprintf(o, "%sx = (%c >> %d) & 0x%"PRIx64";\n", indent, motorola ? 'm' : 'i', start, mask) < 0)
			return -1;
	} else {
		if (fprintf(o, "%sx = %c & 0x%"PRIx64";\n", indent, motorola ? 'm' : 'i',  mask) < 0)
			return -1;
	}

	if (sig->is_floating) {
		assert(length == 32 || length == 64);
	} else if (sig->is_signed) {
		const uint64_t top = (1uL << (length - 1));
		uint64_t negative = ~mask;
		if (length <= 32)
			negative &= 0xFFFFFFFF;
		if (length <= 16)
			negative &= 0xFFFF;
		if (length <= 8)
			negative &= 0xFF;
		if (negative)
			if (fprintf(o, "%sx = (x & 0x%"PRIx64") ? (x | 0x%"PRIx64") : x; \n", indent, top, negative) < 0)
				return -1;
	}

	const char *type = determine_type_c(sig->bit_length, sig->is_signed, sig->is_floating);
	if (sig->scaling != 1.0 || sig->offset != 0.0)
		type = "double";

	fprintf(o, "%smsg.%s = ", indent, sig->name);
	if (sig->is_floating)
		fprintf(o, "unpack754_%d", length);
	else
		fprintf(o, "(%s)", type);
	fprintf(o, "(x)");
	if (sig->scaling != 1.0)
		fprintf(o, " * %g", sig->scaling);
	if (sig->offset != 0.0)
		fprintf(o, " + %g", sig->offset);
	fprintf(o, ";\n");
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

	char *snake_msg_name = pascal2snake(msg->name); // snake_case message name

	fprintf(c, "\t\t%s_sub_ = this->create_subscription<%s::msg::%s>(\n", snake_msg_name, package_name, msg->name);
	fprintf(c, "\t\t\t\"/%s/%s\", 10, [this](const %s::msg::%s::SharedPtr%s) {\n",
		package_name, snake_msg_name, package_name, msg->name, message_has_signals ? " msg" : "");

	free(snake_msg_name);

	if (message_has_signals)
		fprintf(c, "\t\t\t\tuint64_t x;\n");
	if (motorola_used)
		fprintf(c, "\t\t\t\tuint64_t m = 0;\n");
	if (intel_used)
		fprintf(c, "\t\t\t\tuint64_t i = 0;\n");
	
	for (size_t i = 0; i < msg->signal_count; i++) {
		// TODO add multiplexed signal logic
		if (msg->sigs[i]->is_multiplexed)
			fprintf(stderr, "WARNING: multiplexed signal are not yet supported! (%ld - %s: %s)\n",
				msg->id, msg->name, msg->sigs[i]->name);

		signal2serializer(msg->sigs[i], c, "\t\t\t\t");
	}

	fprintf(c, "\t\t\t\tuint64_t data = %s%s%s%s%s%s;\n",
		swap_motorola && motorola_used ? "reverse_byte_order" : "",
		motorola_used ? "(m)" : "",
		motorola_used && intel_used ? "|" : "",
		(!swap_motorola && intel_used) ? "reverse_byte_order" : "",
		intel_used ? "(i)" : "",
		message_has_signals ? "" : "0");

	fprintf(c, "\t\t\t\twriteToSocket(%ld, &data, %d);\n", msg->id, msg->dlc);
	fprintf(c, "\t\t\t}\n\t\t);\n\n");
	return 0;
}

static int msg_unpack(FILE *c, can_msg_t *msg, const char *package_name)
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

	fprintf(c, "\t\t\t\tcase %ld: {\n", msg->id);

	if (msg->dlc)
		fprintf(c, "\t\t\t\t\tif (frame.can_dlc < %u) continue;\n", msg->dlc);

	fprintf(c, "\t\t\t\t\t%s::msg::%s msg;\n", package_name, msg->name);
	fprintf(c, "\t\t\t\t\tmsg.timestamp = this->get_clock()->now();\n");

	if (message_has_signals)
		fprintf(c, "\t\t\t\t\tuint64_t x;\n");
	if (motorola_used)
		fprintf(c, "\t\t\t\t\tuint64_t m = %s(data);\n", swap_motorola ? "reverse_byte_order" : "");
	if (intel_used)
		fprintf(c, "\t\t\t\t\tuint64_t i = %s(data);\n", swap_motorola ? "" : "reverse_byte_order");
	
	
	for (size_t i = 0; i < msg->signal_count; i++) {
		// TODO add multiplexed signal logic
		if (msg->sigs[i]->is_multiplexed)
			fprintf(stderr, "WARNING: multiplexed signal are not yet supported! (%ld - %s: %s)\n",
				msg->id, msg->name, msg->sigs[i]->name);

		signal2deserializer(msg->sigs[i], c, "\t\t\t\t\t");
	}

	char *snake_msg_name = pascal2snake(msg->name);
	fprintf(c, "\t\t\t\t\t%s_pub_->publish(msg);\n", snake_msg_name);
	free(snake_msg_name);

	fprintf(c, "\t\t\t\t\tbreak;\n\t\t\t\t}\n");
	return 0;
}

static void create_subscribers(const dbc_t *dbc, FILE *file, const char *package_name) {
	fprintf(file, "\tvoid createSubscriptions() {\n");
	for (size_t i = 0; i < dbc->message_count; i++) {
		msg_pack(file, dbc->messages[i], package_name);
	}
	fprintf(file, "\t}\n\n");
}

static void create_publishers(const dbc_t *dbc, FILE *file, const char *package_name) {
	fprintf(file, "\tvoid createPublishers() {\n");
	
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		
		char *snake_msg_name = pascal2snake(msg->name); // snake_case message name

		fprintf(file, "\t\t%s_pub_ = this->create_publisher<%s::msg::%s>", snake_msg_name, package_name, msg->name);
		fprintf(file, "(\"/%s/%s\", 10);\n", package_name, snake_msg_name);
		free(snake_msg_name);
	}
	fprintf(file, "\t}\n\n");

	fprintf(file, "\tvoid readLoop() {\n\t\twhile (running_ && rclcpp::ok()) {\n");
	fprintf(file, "%s", read_socket);
	fprintf(file, "\t\t\tuint64_t data;\n\t\t\tstd::memcpy(&data, frame.data, frame.can_dlc);\n\n");
	fprintf(file, "\t\t\tswitch(frame.can_id) {\n");
	for (size_t i = 0; i < dbc->message_count; i++) {
		msg_unpack(file, dbc->messages[i], package_name);
	}
	fprintf(file, "\t\t\t}\n");
	fprintf(file, "\t\t}\n\t}\n\n");
}

static void create_variables(const dbc_t *dbc, FILE *file, const char *package_name) {
	fprintf(file, "\tint socket_{-1};\n\tstd::atomic<bool> running_{true};\n\tstd::thread read_thread_;\n\n");
	for (size_t i = 0; i < dbc->message_count; i++) {
		can_msg_t *msg = dbc->messages[i];
		char *snake_msg_name = pascal2snake(msg->name); // snake_case message name

		fprintf(file, "\trclcpp::Subscription<%s::msg::%s>::SharedPtr %s_sub_;\n", package_name, msg->name, snake_msg_name);
		fprintf(file, "\trclcpp::Publisher<%s::msg::%s>::SharedPtr %s_pub_;\n", package_name, msg->name, snake_msg_name);
		free(snake_msg_name);
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
	size_t node_name_size = strlen(package_name) + strlen("_writer") + 1; /* + 1 for '\0' */
	char *node_name = allocate(node_name_size);
	snprintf(node_name, node_name_size, "%s%s", package_name, "_writer");

	size_t file_name_size = strlen(outdir) + strlen("/src/") + strlen(node_name) + strlen(".cpp") + 1;
	char *file_name = allocate(file_name_size);
	snprintf(file_name, file_name_size, "%s%s%s%s", outdir, "/src/", node_name, ".cpp");
	
	char *class_name = snake2pascal(node_name);

	FILE *file = fopen_or_die(file_name, "wb");

	create_headers(dbc, file, package_name);
	fprintf(file, "%s", float_pack);
	fprintf(file, "%s", float_unpack);
	fprintf(file, "%s", reverse_byte_order);
	fprintf(file, "class %s : public rclcpp::Node {\n", class_name);
	fprintf(file, "public:\n");
	create_constructor_destructor(file, class_name, node_name);
	fprintf(file, "private:\n");
	fprintf(file, "%s", setup_real_time);
	fprintf(file, "%s", create_and_write_socket);
	create_subscribers(dbc, file, package_name);
	create_publishers(dbc, file, package_name);
	create_variables(dbc, file, package_name);
	fprintf(file, "};\n\n");
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
	generate_folders(outdir);
	generate_package_xml(outdir, package_name);
	generate_cmakelists_txt(dbc, outdir, package_name);
	generate_ros_msgs(dbc, outdir);
	generate_ros_node(dbc, outdir, package_name);

	return 0;
}