#include <iostream>
#include <stdio.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include "SDL.h"
#include "SDL_main.h"
#elif __APPLE__
#include <SDL2/SDL.h>
#elif __unix__
#include "SDL.h" // Not sure about that
#endif

#include "Singleton.hpp"
#include "logs.hpp"
#include "filler.hpp"
#include "raylib.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RECT_WIDTH = 50;
const int RECT_HEIGHT = 50;
const int MOVE_AMOUNT = 10;

int main(int argc, char *argv[])
{
    test();

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("SDL Rectangle Move", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Rect rect = {SCREEN_WIDTH / 2 - RECT_WIDTH / 2, SCREEN_HEIGHT / 2 - RECT_HEIGHT / 2, RECT_WIDTH, RECT_HEIGHT};

    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

            if( currentKeyStates[ SDL_SCANCODE_W ] )
            {
                rect.y -= MOVE_AMOUNT;
            }
            
            if( currentKeyStates[ SDL_SCANCODE_S ] )
            {
                rect.y += MOVE_AMOUNT;
            }

            if( currentKeyStates[ SDL_SCANCODE_A ] )
            {
                rect.x -= MOVE_AMOUNT;
            }

            if( currentKeyStates[ SDL_SCANCODE_D ] )
            {
                rect.x += MOVE_AMOUNT;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}