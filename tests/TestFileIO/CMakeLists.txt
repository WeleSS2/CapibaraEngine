add_executable(TestFileIO
    main.cpp
)

target_include_directories(TestFileIO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestFileIO PUBLIC
    ceGeneral
)

set_target_properties(TestFileIO PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)