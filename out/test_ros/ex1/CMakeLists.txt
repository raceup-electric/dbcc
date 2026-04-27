cmake_minimum_required(VERSION 3.5)
project(ex1)

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
  "msg/MagicCanNode1RHeartbeat.msg"
  "msg/MagicCanNode2Heartbeat.msg"
  "msg/MagicCanNode3Heartbeat.msg"
  "msg/FrameFaultHeartbeat.msg"
  "msg/DriveControlsHeartbeat.msg"
  "msg/CANMirrorHeatbeart.msg"
  "msg/RiderDisplayHeartbeat.msg"
  "msg/BIM1Heartbeat.msg"
  "msg/BIM2Heartbeat.msg"
  "msg/BIM3Heartbeat.msg"
  "msg/BIM4Heartbeat.msg"
  "msg/FrameFaultDetectionStatus.msg"
  "msg/FrontBrakePressure.msg"
  "msg/RearBrakePressure.msg"
  "msg/FrontSuspensionTravel.msg"
  "msg/RearSuspensionTravel.msg"
  "msg/BusVoltage12V.msg"
  "msg/PostMotorCoolantTemp.msg"
  "msg/PostControllerCoolantTemp.msg"
  "msg/RadiatorCoolSideCoolantTemp.msg"
  "msg/AmbientTemp.msg"
  "msg/GPSLatAndValidityStatus.msg"
  "msg/GPSLongitude.msg"
  "msg/GPSAltitudeAndAccuracy.msg"
  "msg/CurrentTime.msg"
  "msg/IMUAccelerationMeasurement.msg"
  "msg/IMUGyroMeasurement.msg"
  "msg/MotorPlateTemp.msg"
  "msg/BIM1CellStatistics1.msg"
  "msg/BIM1CellStatistics2.msg"
  "msg/BIM2CellStatisitcs1.msg"
  "msg/BIM2CellStatistics2.msg"
  "msg/BIM3CellStatisitcs1.msg"
  "msg/BIM3CellStatistics2.msg"
  "msg/BIM4CellStatistics1.msg"
  "msg/BIM4CellStatistics2.msg"
  "msg/Cells14.msg"
  "msg/Cells58.msg"
  "msg/Cells912.msg"
  "msg/OdometerVelocity.msg"
  "msg/Cells1316.msg"
  "msg/Cells1720.msg"
  "msg/Cells2124.msg"
  "msg/Cells2528.msg"
  "msg/Cells2932.msg"
  "msg/Cells3336.msg"
  "msg/Cells3740.msg"
  "msg/Cells4144.msg"
  "msg/Cells4548.msg"
  "msg/Cells4952.msg"
  "msg/Cells5354.msg"
  "msg/Cells5558.msg"
  "msg/Cells5962.msg"
  "msg/Cells6366.msg"
  "msg/Cells6770.msg"
  "msg/Cells7174.msg"
  "msg/Cells7578.msg"
  "msg/Cells7982.msg"
  "msg/Cells8386.msg"
  "msg/Cells8790.msg"
  "msg/Cells9194.msg"
  "msg/Cells9598.msg"
  "msg/Cells99102.msg"
  "msg/Cells103106.msg"
  "msg/Cells107110.msg"
  "msg/PackTemperatures1Thru4.msg"
  "msg/PackTempeartures5Thru8.msg"
  "msg/PackTemperatures9Thru14.msg"
  "msg/PackTemperatures13Thru14.msg"
  "msg/PackTemperatures15Thru18.msg"
  "msg/PackTemperatures19Thru22.msg"
  "msg/PackTemperatures23Thru26.msg"
  "msg/PackTemperatures27Thru30.msg"
  "msg/PackTemperatures31Thru34.msg"
  "msg/PackTemperatures35Thru38.msg"
  "msg/PackTemperatures39Thru42.msg"
  "msg/MotorDriveCommand.msg"
  "msg/MotorPowerCommand.msg"
  "msg/StatusInformation.msg"
  "msg/BusMeasurement.msg"
  "msg/VelocityMeasurment.msg"
  "msg/PhaseCurrentMeasurment.msg"
  "msg/MotorVoltage.msg"
  "msg/MotorCurrent.msg"
  "msg/MotorPhaseATemperature.msg"
  "msg/Odometeramphours.msg"
  "msg/BackEMF.msg"
  "msg/Rail15v.msg"
  "msg/Rail3v31v9.msg"
  "msg/PhaseBdsptemprature.msg"
  "msg/MagicCanNode1RBootloaderAddress.msg"
  "msg/MagicCanNode2MBootloaderAddress.msg"
  "msg/MagicCanNode3FBootloaderAddress.msg"
  "msg/FrameFaultBootloaderAddres.msg"
  "msg/FrameFaultCommand.msg"
  "msg/DriveControlsBootloader.msg"
  "msg/DriveControlsCommand.msg"
  "msg/CANMirrorBootloaderAddress.msg"
  "msg/CANMirrorCommand.msg"
  "msg/RiderDisplayBootloaderAddress.msg"
  "msg/RiderDisplayCommand.msg"
  "msg/BIM1BootloaderAddress.msg"
  "msg/BIM2BootloaderAddress.msg"
  "msg/BIM3BootloaderAddress.msg"
  "msg/BIM4BootloaderAddress.msg"
  "msg/MagicCanNode1RCommand.msg"
  "msg/MagicCanNode2MCommand.msg"
  "msg/MagicCanNode3FCommand.msg"
  "msg/CANcorderHeartbeat.msg"
  "msg/BIM1Command.msg"
  "msg/BIM2Command.msg"
  "msg/BIM3Command.msg"
  "msg/BIM4Command.msg"
  "msg/MotorScoop.msg"
  "msg/IMU1.msg"
  "msg/IMU2.msg"
  "msg/IMU3.msg"
  "msg/IMU4.msg"
  "msg/IMU5.msg"
  "msg/MESSAGENAME.msg"
  "msg/MESSAGENAME2.msg"
  "msg/Header.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES builtin_interfaces
)

# Ensure that C++ nodes can use the generated message headers
ament_export_dependencies(rosidl_default_runtime)


add_executable(${PROJECT_NAME}_parser src/${PROJECT_NAME}_parser.cpp)
target_include_directories(${PROJECT_NAME}_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
ament_target_dependencies(${PROJECT_NAME}_parser rclcpp builtin_interfaces can_msgs)
rosidl_target_interfaces(${PROJECT_NAME}_parser
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

install(DIRECTORY include/
  DESTINATION include
)

install(TARGETS
  ${PROJECT_NAME}_parser
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
