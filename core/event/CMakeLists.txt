set(CE_Event
    event.cpp)

add_library(ceEvent SHARED ${CE_Event})
add_library(ceEvents STATIC ${CE_Event})

target_link_libraries(ceEvent PUBLIC
    ceGeneral
)

target_link_libraries(ceEvents PUBLIC
    ceGeneral
)

target_include_directories(ceEvent PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ceEvents PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ceEvent PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(ceEvents PROPERTIES
    OUTPUT_NAME ceEvent
)