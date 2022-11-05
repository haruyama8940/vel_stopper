cmake_minimum_required(VERSION 3.0.2)
project(vel_stopper)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  std_srvs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES vel_stopper
#  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs std_srvs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
  src/vel_stopper.cpp
)

add_executable(${PROJECT_NAME}_node src/vel_stopper.cpp)


target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

