set(CE_DP
    Singleton.hpp
    Singleton.cpp
)

add_library(CE_patterns ${CE_DP})

target_include_directories(CE_patterns PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
