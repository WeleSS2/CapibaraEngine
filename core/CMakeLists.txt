file(GLOB_RECURSE SUBDIRS "*/CMakeLists.txt")

foreach(subdir IN LISTS SUBDIRS)
    get_filename_component(subdir_name ${subdir} DIRECTORY)
    add_subdirectory(${subdir_name})
endforeach()

set(CAPIENGINE
    engine.cpp
)

add_library(ceMain SHARED ${CAPIENGINE})
add_library(ceMains STATIC ${CAPIENGINE})

target_link_libraries(ceMain PUBLIC 
    ceWorld
)

target_link_libraries(ceMains PUBLIC
    ceWorld
)

target_include_directories(ceMain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ceMains PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ceMain PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
)

set_target_properties(ceMains PROPERTIES
    OUTPUT_NAME ceMain
)