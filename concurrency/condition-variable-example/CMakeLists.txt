cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
add_executable(condition_variable_example MyManagedObject.cpp
                                          ConditionVariableExample.cpp)
set_property(TARGET condition_variable_example PROPERTY CXX_STANDARD 17)
target_include_directories(condition_variable_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(condition_variable_example pthread)

