cmake_minimum_required(VERSION 3.0)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(Boost 1.68.0 REQUIRED EXACT)
    if(${Boost_FOUND} EQUAL 1)
        include_directories(${Boost_INCLUDE_DIRS})
        link_directories(${Boost_LIBRARY_DIRS})
        set(PROJECT_NAME "builder")
        project(${PROJECT_NAME})

        # Groovy Builder
        set(GROOVY_STYLE_BUILDER "groovy_style_builder")
        add_executable(${GROOVY_STYLE_BUILDER} GroovyStyleBuilder.cpp)
        set_property(TARGET ${GROOVY_STYLE_BUILDER} PROPERTY CXX_STANDARD 17)
        target_link_libraries(${GROOVY_STYLE_BUILDER} pthread)
        # Composite Builder
        set(COMPOSITE_BUILDER "composite_builder")
        add_executable(${COMPOSITE_BUILDER} CompositeBuilderMain.cpp
                                            Person.cpp
                                            PersonBuilder.cpp )
        set_property(TARGET ${COMPOSITE_BUILDER} PROPERTY CXX_STANDARD 17)
        include_directories(${CMAKE_CURRENT_SOURCE_DIR})
        target_link_libraries(${COMPOSITE_BUILDER} pthread)
        
    else()
        message("Boost library for ${CMAKE_SYSTEM_NAME} not found.")
    endif()
elseif()
    message("TODO: When the operating system is Windows or MacOS.")
endif()
