cmake_minimum_required(VERSION 3.27.2)

project(shapes VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

add_executable(shapes
    main.cpp
)

target_link_libraries(shapes PRIVATE 
    ceRender
)

set_target_properties(shapes PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)