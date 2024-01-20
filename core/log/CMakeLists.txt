set(CE_LOGS
    logs.cpp
)

add_library(CE_logslib ${CE_LOGS})

target_include_directories(CE_logslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})