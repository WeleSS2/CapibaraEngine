add_subdirectory(log)
add_subdirectory(designpatt)
add_subdirectory(threadpool)
add_subdirectory(example)

set(CAPIENGINE
    engine.cpp
    engine.hpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(CE_main INTERFACE ${CAPIENGINE})

target_link_libraries(CE_main INTERFACE 
    SDL2all 
    CE_logslib
    CE_patterns
    EXAMPLELIB
)

set_target_properties(CE_main PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

install (TARGETS CE_main
    DESTINATION ${COMPILED_LIBS}/bin
)