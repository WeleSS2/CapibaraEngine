file(GLOB_RECURSE SUBDIRS "*/CMakeLists.txt")

foreach(subdir IN LISTS SUBDIRS)
    get_filename_component(subdir_name ${subdir} DIRECTORY)
    add_subdirectory(${subdir_name})
endforeach()

set(CAPIENGINE
    engine.cpp
    engine.hpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(CE_main SHARED ${CAPIENGINE})

target_link_libraries(CE_main PUBLIC 
    SDLall 
    CE_logsLIB
    CE_patternsLIB
    CE_renderLIB
    EXAMPLELIB
)

set_target_properties(CE_main PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

install (TARGETS CE_main
    DESTINATION ${COMPILED_LIBS}/bin
)