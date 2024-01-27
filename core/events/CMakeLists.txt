set(CE_events
    eventManager.cpp
)

add_library(CE_eventsLIB ${CE_events})

target_link_libraries(CE_eventsLIB PUBLIC
    SDLall
    CE_logsLIB
    CE_patternsLIB
)

target_include_directories(CE_eventsLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})