add_executable(TestExample
    main.cpp
)

target_include_directories(TestExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestExample PRIVATE EXAMPLELIB)