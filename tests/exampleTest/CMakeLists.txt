add_executable(TestExample
    main.cpp
)

target_include_directories(TestExample PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestExample PUBLIC 
    EXAMPLELIB
)

set_target_properties(TestExample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)