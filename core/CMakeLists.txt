set (MAINENGINE
    logs.cpp
)

set(COMPILED_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../compiled)

include_directories(${CMAKE_SOURCE_DIR})

add_library(capiEngine SHARED ${MAINENGINE} ${EXAMPLESET})

target_link_libraries(capiEngine PRIVATE SDL2)

set_target_properties(capiEngine PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${COMPILED_LIBS}
    RUNTIME_OUTPUT_DIRECTORY ${COMPILED_LIBS}
)

set_target_properties(capiEngine PROPERTIES
    OUTPUT_NAME capiEngine
)

install (TARGETS capiEngine
    DESTINATION ${COMPILED_LIBS}/bin
)

add_subdirectory(example)