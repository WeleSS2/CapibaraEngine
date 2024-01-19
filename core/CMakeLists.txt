add_subdirectory(log)
add_subdirectory(threadpool)
add_subdirectory(example)

set(CAPIENGINE
    engine.h
    engine.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(capiEngine SHARED ${CAPIENGINE})

target_link_libraries(capiEngine PRIVATE 
    SDL2 
    CE_LOGSLIB
    BSTP_LIB 
)

set_target_properties(capiEngine PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${COMPILED_LIBS}
    RUNTIME_OUTPUT_DIRECTORY ${COMPILED_LIBS}
    OUTPUT_NAME capiEngine
)

install (TARGETS capiEngine
    DESTINATION ${COMPILED_LIBS}/bin
)