cmake_minimum_required(VERSION 3.27.2)

project(BlaBla VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

add_executable(BlaBla
    main.cpp
)

target_link_libraries(BlaBla PRIVATE 
    ceRender
)

set_target_properties(BlaBla PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)