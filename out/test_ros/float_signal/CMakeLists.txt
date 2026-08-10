cmake_minimum_required(VERSION 3.5)
project(float_signal)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(can_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/NewMessage0.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs
)

# Ensure that C++ nodes can use the generated message headers
ament_export_dependencies(rosidl_default_runtime)


add_executable(${PROJECT_NAME}_parser src/${PROJECT_NAME}_parser.cpp)
target_include_directories(${PROJECT_NAME}_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
ament_target_dependencies(${PROJECT_NAME}_parser rclcpp std_msgs can_msgs)
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)
target_link_libraries(${PROJECT_NAME}_parser ${cpp_typesupport_target})

install(DIRECTORY include/
  DESTINATION include
)

install(TARGETS
  ${PROJECT_NAME}_parser
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
