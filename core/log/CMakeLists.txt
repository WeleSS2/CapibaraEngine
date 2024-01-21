set(CE_LOGS
    logs.cpp
)

add_library(CE_logsLIB ${CE_LOGS})

target_include_directories(CE_logsLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})