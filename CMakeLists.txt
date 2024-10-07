cmake_minimum_required (VERSION 3.27.2)

project(CapibaraEngine VERSION 0.1)

set (CMAKE_CXX_STANDARD 26)
set (MAIN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)
#set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(include)
add_subdirectory(core)
add_subdirectory(games)
add_subdirectory(tests)

set(OUTPUT
    ceMain
)

set_target_properties(${OUTPUT} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)