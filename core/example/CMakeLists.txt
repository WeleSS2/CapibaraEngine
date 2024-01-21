set(EXAMPLESET
    example.cpp
)

add_library(EXAMPLELIB ${EXAMPLESET})

target_link_libraries(EXAMPLELIB PUBLIC
    SDLall
    CE_logslib
)

target_include_directories(EXAMPLELIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})