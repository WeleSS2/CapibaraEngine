#include <iostream>
#include <chrono>

#include "MainMenu.h"

flecs::world *ptr = NULL;

int main() 
{
    SetConfigFlags( FLAG_FULLSCREEN_MODE
        | FLAG_WINDOW_RESIZABLE);

    InitWindow(1920, 1080, "Test");

    flecs::world ecs;
    cPositionObject po = {{"gmm", 0}, {0, 0, 1920, 1080}, {0, 0, 0}};

    ptr = &ecs;

    ecs.component<cButton>();

    ecs.component<MainMenu>();
    auto mm = ecs.entity().emplace<MainMenu>(ptr, po);

    double sum = 0;
    double iter = 0;

    auto buttonQuery2 = ecs.query<cButton>();

    while (!WindowShouldClose()) {
        //iter++;

        //if (sum >= 1000000) {
        //    std::cout << "Iter sum was" << iter << std::endl;
        //    break;
        //}
        ecs.progress();
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        //
        //

        ecs.defer_begin();
            buttonQuery2.each([&](flecs::entity e, cButton& btn) {
                //auto start = std::chrono::high_resolution_clock::now();
                if (btn.getMouseObject()->mouseCheck(mouseX, mouseY)) 
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        btn.getMouseObject()->executeListeners({"c", 0});
                    }
                    else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                    {
                        btn.getMouseObject()->executeListeners({"c", 1});
                    }
                }
                //auto finish = std::chrono::high_resolution_clock::now();
                //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
            
                //sum += std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
            });
        ecs.defer_end();

        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(mm.is_alive())
        {
            mm.get_mut<MainMenu>()->render();
        }

        DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }

    return 0;
}