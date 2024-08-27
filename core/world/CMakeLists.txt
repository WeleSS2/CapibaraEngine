set(CE_world
    scene.cpp
    sceneManager.cpp
    renderManager.cpp
)

add_library(ceWorld SHARED ${CE_world})
add_library(ceWorlds STATIC ${CE_world})

target_link_libraries(ceWorld PUBLIC
    ceRender
    ceEvent
    RaylibStatic
    flecs
)

target_link_libraries(ceWorlds PUBLIC
    ceRender
    ceEvent
    RaylibStatic
    flecs
)

target_include_directories(ceWorld PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ceWorlds PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


set_target_properties(ceWorld PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(ceWorlds PROPERTIES
    OUTPUT_NAME ceWorld
)