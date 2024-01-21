set(CE_render
    renderObject.cpp
    scene.cpp
)

add_library(CE_renderLIB ${CE_render})

target_link_libraries(CE_renderLIB PUBLIC
    SDLall
    CE_logsLIB
    CE_patternsLIB
)

target_include_directories(CE_renderLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})