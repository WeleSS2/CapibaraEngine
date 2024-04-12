#  
#  Tests for backend code
#  

#enable_testing()
#
#add_executable(TestWindows
#    test_test.cc
#)
#
#target_include_directories(TestWindows PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#
#target_link_libraries(TestWindows PUBLIC
#    ceGeneral
#    ceNetworking
#    GTest::gtest_main
#)
#
#set_target_properties(TestWindows PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIRECTORY}
#)
#
#include(GoogleTest)
#gtest_discover_tests(TestWindows)