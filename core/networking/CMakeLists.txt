set(CE_Networking
    client.cpp
    server.cpp
    shared.cpp
)

add_library(CE_NetworkingLIB SHARED ${CE_Networking})
add_library(CE_NetworkingLIBs STATIC ${CE_Networking})

target_include_directories(CE_NetworkingLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CE_NetworkingLIBs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CE_NetworkingLIB PUBLIC
    SteamSDK
    SPDLogs
)

target_link_libraries(CE_NetworkingLIBs PUBLIC
    SteamSDK
    SPDLogs
)

set_target_properties(CE_NetworkingLIB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_NetworkingLIBs PROPERTIES
    OUTPUT_NAME CE_NetworkingLIB
)