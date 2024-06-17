cmake_minimum_required(VERSION 3.27.2)

project(JsonTest VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

add_executable(JsonTest
    main.cpp
)

target_link_libraries(JsonTest PRIVATE 
    ceGeneral
)


set_target_properties(JsonTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)