set(CE_DP
    singleton.cpp
    multistructs.cpp
)

add_library(CE_patternsLIB ${CE_DP})

target_include_directories(CE_patternsLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
