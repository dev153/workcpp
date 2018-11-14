cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
project(thread-local-example)
add_executable(thread_local_example MyManagedObject.cpp
                                    ThreadLocalExample.cpp)
set_property(TARGET thread_local_example PROPERTY CXX_STANDARD 17)
target_include_directories(thread_local_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(thread_local_example pthread)
