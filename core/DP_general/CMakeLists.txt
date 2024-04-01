set(CE_DP
    Singleton.cpp
    multistructs.cpp
    logs.cpp
)

add_library(CE_DPgeneralLIB SHARED ${CE_DP})
add_library(CE_DPgeneralLIBs STATIC ${CE_DP})

target_include_directories(CE_DPgeneralLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_DPgeneralLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_DPgeneralLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_DPgeneralLIBs PROPERTIES
    OUTPUT_NAME CE_DPgeneralLIB
)