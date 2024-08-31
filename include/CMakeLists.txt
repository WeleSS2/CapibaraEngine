# TODO ADD ALL LICENSES!!!

# Fetching 

include(FetchContent)

FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG        v1.13.0
)

FetchContent_Declare(flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs
    GIT_TAG        v4.0.1
)

FetchContent_Declare(gtests
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG        v1.14.0
)

FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG        v1.91.0
)

FetchContent_Declare(box2D
    GIT_REPOSITORY https://github.com/erincatto/box2d
    GIT_TAG        v3.0.0
)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG        v3.11.3
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

# Fetch Declare 

FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(flecs)
FetchContent_MakeAvailable(gtests)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(box2D)

# Add libraries

add_library(SPDLogs INTERFACE)

add_library(Flecs INTERFACE)

add_library(Json INTERFACE)

add_library(Imgui INTERFACE)

add_library(Box2D INTERFACE)

# Link libraries

target_link_libraries(SPDLogs INTERFACE
    spdlog
)

target_link_libraries(Flecs INTERFACE
    flecs::flecs_static
)

target_link_libraries(Json INTERFACE
    nlohmann_json::nlohmann_json
)

target_link_libraries(Imgui INTERFACE
    imgui
)

target_link_libraries(Box2D INTERFACE
    box2d
)

# Static linking

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdk")

if(WIN32)
    set(LIB_PATH "${LIB_DIR}/redistributable_bin/steam_api.lib")
elseif(UNIX OR ANDROID)
    set(LIB_PATH "${LIB_DIR}/redistributable_bin/linux64/libsteam_api.so")
elseif(APPLE)
    set(LIB_PATH "${LIB_DIR}/redistributable_bin/osx/libsteam_api.dylib")
endif()

add_library(SteamSDK INTERFACE)

target_include_directories(SteamSDK INTERFACE
    "${LIB_DIR}/public/steam"
)

target_link_libraries(SteamSDK INTERFACE ${LIB_PATH})

# Static for raylib

set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Raylib")

set(RAYLIB_LIBS "${RAYLIB_DIR}/build/raylib/Debug/raylib.lib")

add_library(RaylibStatic INTERFACE)

target_include_directories(RaylibStatic INTERFACE
    "${RAYLIB_DIR}/build/raylib/include"
)

if(WIN32)
    target_link_libraries(RaylibStatic INTERFACE ${RAYLIB_LIBS} winmm.lib)
    file(COPY ${CMAKE_SOURCE_DIR}/build/_deps/flecs-build/Debug/flecs.dll DESTINATION ${MAIN_OUTPUT_DIRECTORY}/Debug)
elseif(UNIX OR ANDROID)
    target_link_libraries(RaylibStatic INTERFACE ${RAYLIB_LIBS})
    file(COPY ${CMAKE_SOURCE_DIR}/build/_deps/flecs-build/Debug/flecs.so DESTINATION ${MAIN_OUTPUT_DIRECTORY})
elseif(APPLE)
    target_link_libraries(RaylibStatic INTERFACE ${RAYLIB_LIBS})
    file(COPY ${CMAKE_SOURCE_DIR}/build/_deps/flecs-build/Debug/flecs.dylib DESTINATION ${MAIN_OUTPUT_DIRECTORY})
endif()
