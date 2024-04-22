#include <iostream>
#include <random>
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
#include <flecs.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RECT_WIDTH = 50;
const int RECT_HEIGHT = 50;
const int MOVE_AMOUNT = 3;





using namespace std;

// Component to hold rectangle properties
struct RectangleComp {
    float x, y;      // Position
    float width, height; // Size
    Color color;     // Color
};


struct Velocity {
    float vx, vy;
};



int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "ECS example with Flecs and Raylib");
    //SetTargetFPS(60);


    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-5, 5); // define the range
    std::uniform_int_distribution<> color(0, 255);
    std::uniform_int_distribution<> distrXY(-5.0f, 5.0f); // Define the range for velocity

    // Initialize Flecs
    flecs::world ecs;

    // Register component
    ecs.component<RectangleComp>();

    // Create an entity with a RectangleComp component


    ecs.system<RectangleComp, Velocity>().each([](RectangleComp &rc, Velocity &vel) {
        rc.x += vel.vx;
        rc.y += vel.vy;

        // Keep entities within screen bounds
        if (rc.x < 0 || rc.x > screenWidth - rc.width) vel.vx *= -1;
        if (rc.y < 0 || rc.y > screenHeight - rc.height) vel.vy *= -1;
    });




    for (int i = 0; i < 10000; i++) {
        float x = std::rand() % GetScreenWidth();  // Random x coordinate within screen bounds
        float y = std::rand() % GetScreenHeight(); // Random y coordinate within screen bounds

        float vx = distrXY(gen); // Random velocity x
        float vy = distrXY(gen); // Random velocity`

        ecs.entity()
           .set<RectangleComp>({x, y, 5, 5, RED}).set<Velocity>({vx, vy});
        
}



    for (int i = 0; i < 50000; i++) {
        float x = std::rand() % GetScreenWidth();  // Random x coordinate within screen bounds
        float y = std::rand() % GetScreenHeight(); // Random y coordinate within screen bounds

        float vx = distrXY(gen); // Random velocity x
        float vy = distrXY(gen); // Random velocity`

        ecs.entity()
           .set<RectangleComp>({x, y, 5, 5, RED}).set<Velocity>({vx, vy});
        
}



    for (int i = 0; i < 50000; i++) {
        float x = std::rand() % GetScreenWidth();  // Random x coordinate within screen bounds
        float y = std::rand() % GetScreenHeight(); // Random y coordinate within screen bounds

        float vx = distrXY(gen); // Random velocity x
        float vy = distrXY(gen); // Random velocity`

        ecs.entity()
           .set<RectangleComp>({x, y, 5, 5, GREEN}).set<Velocity>({vx, vy});
        
}



    for (int i = 0; i < 50000; i++) {
        float x = std::rand() % GetScreenWidth();  // Random x coordinate within screen bounds
        float y = std::rand() % GetScreenHeight(); // Random y coordinate within screen bounds

        float vx = distrXY(gen); // Random velocity x
        float vy = distrXY(gen); // Random velocity`

        ecs.entity()
           .set<RectangleComp>({x, y, 5, 5, YELLOW}).set<Velocity>({vx, vy});
        
}


    for (int i = 0; i < 10000; i++) {
        float x = std::rand() % GetScreenWidth();  // Random x coordinate within screen bounds
        float y = std::rand() % GetScreenHeight(); // Random y coordinate within screen bounds

        float vx = distrXY(gen); // Random velocity x
        float vy = distrXY(gen); // Random velocity`

        ecs.entity()
           .set<RectangleComp>({x, y, 5, 5, RED}).set<Velocity>({vx, vy});
        
}

    // Main game loop
    while (!WindowShouldClose()) {
        // Update ECS
        ecs.progress();

        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        auto query = ecs.query<RectangleComp>(); // Create a query for entities with RectangleComp
        query.each([](flecs::entity e, RectangleComp& rc) {
            DrawRectangle(rc.x, rc.y, rc.width, rc.height, rc.color); // Use Raylib to draw the rectangle
        });

 DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }

    #ifdef raylib

    
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