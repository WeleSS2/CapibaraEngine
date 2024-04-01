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

#define raylib

#include "Singleton.hpp"
#include "logs.hpp"
#include "filler.hpp"
#include "raylib.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RECT_WIDTH = 50;
const int RECT_HEIGHT = 50;
const int MOVE_AMOUNT = 3;

#include <random>
int main(int argc, char *argv[])
{
    test();

    #ifdef raylib
    // Initialize window
    const int screenWidth = 1720;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Move Rectangle with WASD");

    MaximizeWindow();

    // Set up rectangle properties
    Rectangle rec = { screenWidth / 2 - 50, screenHeight / 2 - 50, 100, 100 };

    //SetTargetFPS(120); // Set the desired frame rate

    std::vector<Rectangle*> recs;

    int a = 0, b = 0;

    for (int i = 0; i < 25000; ++i)
    {
        Rectangle* rec = new Rectangle{ screenWidth / 2, screenHeight / 2, 5, 5};

        if (i % 150 == 0)
        {
            a++;
        }

        b++;

        if (i % 150 == 0)
        {
            b = 0;
        }

        recs.emplace_back(rec);
    }

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-5, 5); // define the range
    std::uniform_int_distribution<> color(0, 255);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (IsKeyDown(KEY_W))
            rec.y -= 5;
        if (IsKeyDown(KEY_S))
            rec.y += 5;
        if (IsKeyDown(KEY_A))
            rec.x -= 5;
        if (IsKeyDown(KEY_D))
            rec.x += 5;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < recs.size(); i++)
        {
            if (recs[i]->x > 0 && recs[i]->y > 0 && recs[i]->x < 1700 && recs[i]->y < 900)
            {
                recs[i]->x += distr(gen);
                recs[i]->y += distr(gen);
            }
            else if (recs[i]->x <= 0 && recs[i]->y <= 0)
            {
                recs[i]->x += 5;
                recs[i]->y += 5;
            }
            else
            {
                recs[i]->x -= 5;
                recs[i]->y -= 5;
            }
            
            Color cc = {(unsigned char)color(gen),
                        (unsigned char)color(gen), 
                        (unsigned char)color(gen), 
                        (unsigned char)color(gen)};

            DrawRectangleRec(*recs[i], cc);
        }

        DrawFPS(10, 10); // Display FPS in top-left corner


        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context
    
    #else
    
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
    
    #endif

    return 0;
}