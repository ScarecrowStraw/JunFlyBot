cmake_minimum_required(VERSION 3.0.2)
project(data_collection)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

# find_package(Boost REQUIRED COMPONENTS system)

add_message_files(
  FILES
  rtk.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

catkin_install_python(PROGRAMS 
  scripts/alvinxy/alvinxy.py
  scripts/alvinxy/alvinxy_example.py
  scripts/geonav_transform/geonav_conversions.py
  scripts/geonav_transform/utmtest.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_executable(${PROJECT_NAME}_node src/data-collection_node.cpp
                                   src/Print.cpp
                                   src/SparkFun_u-blox_GNSS_Arduino_Library.cpp
                                   src/Utils.cpp)

target_link_libraries(${PROJECT_NAME}_node
 ${catkin_LIBRARIES}
)




