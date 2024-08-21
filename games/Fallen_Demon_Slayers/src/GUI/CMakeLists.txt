file(GLOB_RECURSE MENU_SRC_FILES "*.cpp" "*.hpp")

add_library(gui SHARED ${MENU_SRC_FILES})
add_library(guis STATIC ${MENU_SRC_FILES})

target_link_libraries(gui PUBLIC
    ceWorld
)

target_link_libraries(guis PUBLIC
    ceWorld
)

target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(guis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(gui PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(guis PROPERTIES
    OUTPUT_NAME gui
)