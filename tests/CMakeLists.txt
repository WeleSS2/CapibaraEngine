file(GLOB SUBDIRS "*/CMakeLists.txt")

foreach(subdir IN LISTS SUBDIRS)
    get_filename_component(subdir_name ${subdir} DIRECTORY)
    add_subdirectory(${subdir_name})
endforeach()