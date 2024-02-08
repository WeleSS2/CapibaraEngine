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

int main(int argc, char *argv[])
{
    ERRORLOG("ERRORLOG!!!");
    
    SDL_Rect aaa;
    
    //Pozdrawiam Jacoba :*
    std::cout << "Hello team!" << std::endl;
    printf("Do not limit youself, seek for all possible solutions! \n");
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Set the draw color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Clear the screen
    SDL_RenderClear(renderer);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Wait for a few seconds
    SDL_Delay(20000);

    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}