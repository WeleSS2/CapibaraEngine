set(CE_render
    renderObject.cpp
    textureManager.cpp
)

add_library(ceRender SHARED ${CE_render})
add_library(ceRenders STATIC ${CE_render})

target_link_libraries(ceRender PUBLIC
    ceGeneral
    RaylibStatic
)

target_link_libraries(ceRenders PUBLIC
    ceGeneral
    ceEvent
    RaylibStatic
)

target_include_directories(ceRender PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ceRenders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ceRender PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(ceRenders PROPERTIES
    OUTPUT_NAME ceRender
)