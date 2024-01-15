set(CE_LOGS
    logs.cpp
)

add_library(CE_LOGSLIB ${CE_LOGS})

target_include_directories(CE_LOGSLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})