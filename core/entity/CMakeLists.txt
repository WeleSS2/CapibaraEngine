set(CE_Entity
    hitboxedObject.cpp
)

add_library(CE_entityLIB SHARED ${CE_Entity})
add_library(CE_entityLIBs STATIC ${CE_Entity})

target_link_libraries(CE_entityLIB PUBLIC
    CE_entityBLIB
)

target_link_libraries(CE_entityLIBs PUBLIC
    CE_entityBLIB
)

target_include_directories(CE_entityLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_entityLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_entityLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_entityLIBs PROPERTIES
    OUTPUT_NAME CE_entityLIB
)