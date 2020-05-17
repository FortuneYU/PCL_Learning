cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(pcd_read_visualize)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcd_read_visualize pcd_read_visualize.cpp)
target_link_libraries (pcd_read_visualize ${PCL_LIBRARIES})