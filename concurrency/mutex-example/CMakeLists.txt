cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
add_executable(mutex_example MyManagedObject.cpp
                             MutexExample.cpp)
set_property(TARGET mutex_example PROPERTY CXX_STANDARD 17)
target_include_directories(mutex_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mutex_example pthread)

