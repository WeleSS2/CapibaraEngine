  
#  Tests for backend code
add_executable(gTestsExample
    test_test.cpp
)

target_link_libraries(gTestsExample PRIVATE
    ceMain
    gtest_main
)

include(GoogleTest)

gtest_discover_tests(gTestsExample
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )