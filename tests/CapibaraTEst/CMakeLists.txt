cmake_minimum_required(VERSION 3.27.2)

project(CapibaraTest VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

add_executable(CapibaraTest
    main.cpp
)

target_link_libraries(CapibaraTest PRIVATE 
    ceRender
    flecs
)

set_target_properties(CapibaraTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)