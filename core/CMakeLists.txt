add_subdirectory(log)
add_subdirectory(threadpool)
add_subdirectory(example)

set(CAPIENGINE
    engine.cpp
    engine.hpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(capiEngine INTERFACE ${CAPIENGINE})

target_link_libraries(capiEngine INTERFACE 
    SDL2all 
    CE_logslib
    EXAMPLELIB
)

set_target_properties(capiEngine PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

install (TARGETS capiEngine
    DESTINATION ${COMPILED_LIBS}/bin
)