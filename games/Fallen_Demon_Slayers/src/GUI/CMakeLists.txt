# Gather all source files in menu directory
file(GLOB_RECURSE MENU_SRC_FILES "*.cpp" "*.hpp")

# Set the source files for the menu library
add_library(gui SHARED ${MENU_SRC_FILES})
add_library(guis STATIC ${MENU_SRC_FILES})

target_link_libraries(gui PUBLIC
    ceRender
    flecs
)

target_link_libraries(guis PUBLIC
    ceRender
    flecs
)

# Include directories
target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(guis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ceRender PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(guis PROPERTIES
    OUTPUT_NAME gui
)