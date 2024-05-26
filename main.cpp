#include <iostream>
#include <stdio.h>

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
    return 0;
}