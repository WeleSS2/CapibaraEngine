set(CE_render
    renderObject.cpp
    scene.cpp
    renderManager.cpp
)

add_library(CE_renderLIB SHARED ${CE_render})
add_library(CE_renderLIBs STATIC ${CE_render})

target_link_libraries(CE_renderLIB PUBLIC
    SDLall
    CE_logsLIB
    CE_entityBLIB
    CE_patternsLIB
)

target_link_libraries(CE_renderLIBs PUBLIC
    SDLall
    CE_logsLIB
    CE_entityBLIB
    CE_patternsLIB
)

target_include_directories(CE_renderLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_renderLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_renderLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_renderLIBs PROPERTIES
    OUTPUT_NAME CE_renderLIB
)