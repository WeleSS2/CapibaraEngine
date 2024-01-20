set(CE_DP
    Singleton.cpp
)

add_library(CE_patterns ${CE_DP})

target_include_directories(CE_patterns PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CE_patterns PROPERTIES
    LINKER_LANGUAGE CXX
)