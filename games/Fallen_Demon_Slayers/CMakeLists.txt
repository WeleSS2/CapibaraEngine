#cmake_minimum_required(VERSION 3.27.2)
#
#project(Fallen_Demon_Slayers VERSION 0.1)
#
#set(CMAKE_CXX_STANDARD 23)
#
#add_subdirectory(src)
#add_subdirectory(gfx)
#
#add_executable(Fallen_Demon_Slayers
#    main.cpp
#    ${SRC_cpp}
#)
#
#target_link_libraries(Fallen_Demon_Slayers PRIVATE 
#    gui
#    flecs
#)
#
#set_target_properties(Fallen_Demon_Slayers PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
#)