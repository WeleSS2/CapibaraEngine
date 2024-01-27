set(CE_DP
    singleton.cpp
    multistructs.cpp
)

add_library(CE_patternsLIB SHARED ${CE_DP})
add_library(CE_patternsLIBs STATIC ${CE_DP})

target_include_directories(CE_patternsLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_patternsLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_patternsLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_patternsLIBs PROPERTIES
    OUTPUT_NAME CE_patternsLIB
)