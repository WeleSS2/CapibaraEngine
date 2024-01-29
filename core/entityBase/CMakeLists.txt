set(CE_EN
    object.cpp
)

add_library(CE_entityBLIB SHARED ${CE_EN})
add_library(CE_entityBLIBs STATIC ${CE_EN})

target_link_libraries(CE_entityBLIB PUBLIC
    CE_patternsLIB
)

target_link_libraries(CE_entityBLIBs PUBLIC
    CE_patternsLIB
)

target_include_directories(CE_entityBLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_entityBLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_entityBLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_entityBLIBs PROPERTIES
    OUTPUT_NAME CE_entityBLIB
)