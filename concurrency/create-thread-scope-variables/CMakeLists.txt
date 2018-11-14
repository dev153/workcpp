cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
project(create-thread-scope-variables)
add_executable(create_thread_scope_vars MyManagedObject.cpp
                                        CreateThreadScopeVars.cpp)
set_property(TARGET create_thread_scope_vars PROPERTY CXX_STANDARD 17)
target_include_directories(create_thread_scope_vars PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(create_thread_scope_vars pthread)
