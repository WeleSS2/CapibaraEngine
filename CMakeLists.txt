cmake_minimum_required (VERSION 3.23)

project (CapibaraEngine VERSION 0.1)

set (CMAKE_CXX_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(include)
add_subdirectory(compiled)
add_subdirectory(core)
add_subdirectory(tests)


add_executable(Testing 
    main.cpp
)

target_link_libraries(Testing PRIVATE SDL2)