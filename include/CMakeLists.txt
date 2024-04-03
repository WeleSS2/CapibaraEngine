# SDL2 zlib license

# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.

# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:

# 1. The origin of this software must not be misrepresented; you must not
#   claim that you wrote the original software. If you use this software
#   in a product, an acknowledgment in the product documentation would be
#   appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#   misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

include(FetchContent)

FetchContent_Declare(SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG        release-2.28.5
)

FetchContent_Declare(SDL_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
    GIT_TAG        release-2.22.0
)

FetchContent_Declare(SDL_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG        release-2.8.2
)

FetchContent_Declare(SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
    GIT_TAG        release-2.8.0
)

FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG        v1.13.0
)

FetchContent_Declare(flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs
    GIT_TAG        v3.2.11
)

FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG        5.0
)

#
#FetchContent_Declare(Nova_Physics
#    GIT_REPOSITORY https://github.com/kadir014/nova-physics
#    GIT_TAG        0.7.0
#)

FetchContent_MakeAvailable(SDL SDL_image SDL_mixer SDL_ttf)
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(flecs)
FetchContent_MakeAvailable(raylib)
#FetchContent_MakeAvailable(Nova_Physics)

add_library(SDLall INTERFACE)

add_library(SPDLogs INTERFACE)

add_library(Flecs INTERFACE)

add_library(Raylib INTERFACE)
#
#add_library(NOVAPhys INTERFACE)

target_link_libraries(SDLall INTERFACE
    SDL2
    SDL2main
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)

target_link_libraries(SPDLogs INTERFACE
    spdlog
)

target_link_libraries(Flecs INTERFACE
    flecs::flecs_static
)

target_link_libraries(Raylib INTERFACE
    raylib
)
#
#target_link_libraries(NOVAPhys INTERFACE
#    Nova_Physics
#)
