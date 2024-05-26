set(CE_render
    render.cpp
)

add_library(ceRender SHARED ${CE_render})
add_library(ceRenders STATIC ${CE_render})

target_link_libraries(CE_renderLIB PUBLIC
    CE_DPgeneralLIB
)

target_link_libraries(CE_renderLIBs PUBLIC
    CE_DPgeneralLIB
)

target_include_directories(ceRender PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ceRenders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ceRender PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(ceRenders PROPERTIES
    OUTPUT_NAME ceRender
)