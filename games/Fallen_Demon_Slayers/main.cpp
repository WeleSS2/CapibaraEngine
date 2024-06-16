#include <iostream>

#include <flecs.h>

#include "MainMenu.hpp"

flecs::world *ptr = NULL;

int main() 
{
    SetConfigFlags( FLAG_FULLSCREEN_MODE
        | FLAG_WINDOW_RESIZABLE);

    InitWindow(1920, 1080, "Test");

    flecs::world ecs;

    ptr = &ecs;

    //MainMenu mm(&ecs);

    while (!WindowShouldClose()) {
        ecs.progress();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            ecs.defer_begin();
            auto buttonQuery2 = ecs.query<cButton>();
            buttonQuery2.each([&](flecs::entity e, cButton& btn) {
                if (btn.clickCheck(mouseX, mouseY)) {
                    btn.click();
                }
            });
            ecs.defer_end();
        }

        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);


        DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }
    return 0;
}