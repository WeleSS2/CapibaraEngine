set(EXAMPLESET
    example.cpp
)

add_library(EXAMPLELIB SHARED ${EXAMPLESET})
add_library(EXAMPLELIBs STATIC ${EXAMPLESET})

target_link_libraries(EXAMPLELIB PUBLIC
    SDLall
    SPDLogs
    CE_logsLIB
)

target_link_libraries(EXAMPLELIBs PUBLIC
    SDLall
    SPDLogs
    CE_logsLIB
)

target_include_directories(EXAMPLELIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(EXAMPLELIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install (TARGETS EXAMPLELIB
    DESTINATION ${COMPILED_LIBS}/bin
)

set_target_properties(EXAMPLELIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(EXAMPLELIBs PROPERTIES
    OUTPUT_NAME EXAMPLELIB
)