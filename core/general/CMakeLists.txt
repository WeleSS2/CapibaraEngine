file(GLOB_RECURSE FILES "*.cpp")

set(CE_DP
    logs.cpp
    json.cpp
    structs.cpp
    
)

add_library(ceGeneral SHARED ${CE_DP})
add_library(ceGenerals STATIC ${CE_DP})

target_include_directories(ceGeneral PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ceGenerals PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ceGeneral PUBLIC
    Json
)

target_link_libraries(ceGenerals PUBLIC
    Json
)

set_target_properties(ceGeneral PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(ceGenerals PROPERTIES
    OUTPUT_NAME ceGeneral
)