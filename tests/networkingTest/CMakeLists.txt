add_executable(TestSteamSDK
    main.cpp
)

target_include_directories(TestSteamSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestSteamSDK PUBLIC
    CE_main
    CE_NetworkingLIB
)

set_target_properties(TestSteamSDK PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)