cmake_minimum_required(VERSION 3.27.2)

project(CapibaraTEst VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

add_executable(CapibaraTEst
    main.cpp
)

target_link_libraries(CapibaraTEst PRIVATE 
    ceRender
    flecs
)

set_target_properties(CapibaraTEst PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)