  
#  Tests for backend code
add_executable(example_gTest
    test_test.cpp
)

target_link_libraries(example_gTest PRIVATE
    ceMain
    gtest_main
)

include(GoogleTest)

gtest_discover_tests(example_gTest
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )