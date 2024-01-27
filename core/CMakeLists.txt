file(GLOB_RECURSE SUBDIRS "*/CMakeLists.txt")

foreach(subdir IN LISTS SUBDIRS)
    get_filename_component(subdir_name ${subdir} DIRECTORY)
    add_subdirectory(${subdir_name})
endforeach()

set(CAPIENGINE
    engine.cpp
    engine.hpp
)

add_library(CE_main SHARED ${CAPIENGINE})
add_library(CE_mains STATIC ${CAPIENGINE})

target_include_directories(CE_main PUBLIC ${CMAKE_SOURCE_DIR})

target_include_directories(CE_mains PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(CE_main PUBLIC 
    CE_renderLIB
    EXAMPLELIB
)

target_link_libraries(CE_mains PUBLIC 
    CE_renderLIB
    EXAMPLELIB
)

set_target_properties(CE_main PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(CE_mains PROPERTIES
    OUTPUT_NAME CE_main
)

install (TARGETS CE_main
    DESTINATION ${COMPILED_LIBS}/bin
)