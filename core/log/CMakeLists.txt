set(CE_LOGS
    logs.cpp
)

add_library(CE_logsLIB SHARED ${CE_LOGS})
add_library(CE_logsLIBs STATIC ${CE_LOGS})

target_include_directories(CE_logsLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_logsLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_logsLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_logsLIBs PROPERTIES
    OUTPUT_NAME CE_logsLIB
)