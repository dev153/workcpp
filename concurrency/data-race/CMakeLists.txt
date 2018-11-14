cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
add_executable(data_race MyManagedObject.cpp
                         DataRace.cpp)
set_property(TARGET data_race PROPERTY CXX_STANDARD 17)
target_include_directories(data_race PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(data_race pthread)

