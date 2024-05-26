add_executable(TestNetworking
    main.cpp
)

target_include_directories(TestNetworking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestNetworking PUBLIC
    CE_main
    CE_NetworkingLIB
)

set_target_properties(TestNetworking PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)