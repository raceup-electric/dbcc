cmake_minimum_required(VERSION 3.5)
project(ex2)

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
find_package(can_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)

set(msg_files
  "msg/WS200IDInfo.msg"
  "msg/WS200Status.msg"
  "msg/WS200BusMeasurement.msg"
  "msg/VelocityMeasurement.msg"
  "msg/PhaseCurrent.msg"
  "msg/MotorVoltage.msg"
  "msg/MotorCurrent.msg"
  "msg/MotorBackEMF.msg"
  "msg/WS200Rail15V.msg"
  "msg/WS200LowRail.msg"
  "msg/WS200MotorTemp.msg"
  "msg/WS200DSPBoardTemp.msg"
  "msg/WS200PhaseCTemp.msg"
  "msg/WS200BusAmpHours.msg"
  "msg/WS200SlipSpeed.msg"
  "msg/Header.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES builtin_interfaces
)

# Ensure that C++ nodes can use the generated message headers
ament_export_dependencies(rosidl_default_runtime)


add_executable(${PROJECT_NAME}_parser src/${PROJECT_NAME}_parser.cpp)
ament_target_dependencies(${PROJECT_NAME}_parser rclcpp builtin_interfaces can_msgs)
rosidl_target_interfaces(${PROJECT_NAME}_parser
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

install(TARGETS
  ${PROJECT_NAME}_parser
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
