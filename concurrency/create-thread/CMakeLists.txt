cmake_minimum_required(VERSION 3.0)
project(create-thread)
add_executable(create_thread create_thread.cpp)
set_property(TARGET create_thread PROPERTY CXX_STANDARD 17)
target_link_libraries(create_thread pthread)
