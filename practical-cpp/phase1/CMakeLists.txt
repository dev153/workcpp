cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "phase1")
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} main.cpp
                               Singleton.cpp
                               Stack.cpp
                               TestStack.cpp
                               Publisher.cpp
                               Observer.cpp )
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} pthread)
