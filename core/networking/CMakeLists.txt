set(CE_Networking
    Client.cpp
    Server.cpp
    Shared.cpp
)

add_library(ceNetworking SHARED ${CE_Networking})
add_library(ceNetworkings STATIC ${CE_Networking})

target_include_directories(ceNetworking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ceNetworkings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ceNetworking PUBLIC
    SteamSDK
    ceGeneral
    SPDLogs
)

target_link_libraries(ceNetworkings PUBLIC
    SteamSDK
    ceGeneral
    SPDLogs
)

set_target_properties(ceNetworking PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(ceNetworkings PROPERTIES
    OUTPUT_NAME ceNetworking
)