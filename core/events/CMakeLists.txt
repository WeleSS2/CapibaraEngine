set(CE_events
    eventManager.cpp
)

add_library(CE_eventsLIB SHARED ${CE_events})
add_library(CE_eventsLIBs STATIC ${CE_events})

target_link_libraries(CE_eventsLIB PUBLIC
    SDLall
    CE_entityBLIB
    CE_logsLIB
    CE_patternsLIB
)

target_link_libraries(CE_eventsLIBs PUBLIC
    SDLall
    CE_entityBLIB
    CE_logsLIB
    CE_patternsLIB
)

target_include_directories(CE_eventsLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_eventsLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_eventsLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_eventsLIBs PROPERTIES
    OUTPUT_NAME CE_eventsLIB
)