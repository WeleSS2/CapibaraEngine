add_library(EXAMPLELIB
    example.cpp
)

target_link_libraries(EXAMPLELIB PRIVATE SDL2)

target_include_directories(EXAMPLELIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})