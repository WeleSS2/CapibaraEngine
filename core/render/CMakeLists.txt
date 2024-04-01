set(CE_render
    render.cpp
)

add_library(CE_renderLIB SHARED ${CE_render})
add_library(CE_renderLIBs STATIC ${CE_render})

target_link_libraries(CE_renderLIB PUBLIC
    SDLall
    CE_DPgeneralLIB
)

target_link_libraries(CE_renderLIBs PUBLIC
    SDLall
    CE_DPgeneralLIB
)

target_include_directories(CE_renderLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_renderLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_renderLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_renderLIBs PROPERTIES
    OUTPUT_NAME CE_renderLIB
)