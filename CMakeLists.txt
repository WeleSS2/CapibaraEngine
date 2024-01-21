cmake_minimum_required (VERSION 3.27.2)

project (CapibaraEngine VERSION 0.1)

set (CMAKE_CXX_STANDARD 23)
set (MAIN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(include)
add_subdirectory(core)
add_subdirectory(tests)

add_executable(Testing 
    main.cpp
)

target_link_libraries(Testing PRIVATE 
    CE_main
)

set(OUTPUT
    Testing
    CE_main
)

set_target_properties(${OUTPUT} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)