#include <iostream>
#include <chrono>
#include <functional>

#include "TextureManager.h"
#include "MainMenu.h"
#include "renderManager.h"
#include "sceneManager.h"

flecs::world *ptr = NULL;

int main() 
{
    SetConfigFlags( FLAG_FULLSCREEN_MODE |
       FLAG_WINDOW_RESIZABLE);

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Test");
    cScreenScale::setScale(GetScreenWidth() / 100, GetScreenHeight() / 100);

    SetTargetFPS(10000);
    
    flecs::world ecs;
    ptr = &ecs;

    TextureManager::getInstance()->loadTexture("bg2.png");
    TextureManager::getInstance()->loadTexture("test.png");
    TextureManager::getInstance()->loadTexture("grass.png");
    TextureManager::getInstance()->loadTexture("water.png");
    TextureManager::getInstance()->loadTexture("road.png");
    TextureManager::getInstance()->loadTexture("building.png");

    auto query = ecs.query<cRenderFlags>();

    MainMenu* scene = new MainMenu(ptr);

    scene->setID({"mm", 0});

    cSceneManager::getInstance()->addScene(static_cast<cScene*>(scene));

    //auto buttonQuery2 = ecs.query<cButton>();

    std::vector <int> xx;
    std::vector <int> yy;
    int counter = 250168;

    //for ( int i = 0 ; i < counter ;i++)
    //{
    //    xx.emplace_back(GetRandomValue(0, 1920));
    //    yy.emplace_back(GetRandomValue(0, 1080));
    //}

    Texture2D text = LoadTexture("texture.png");

    while (!WindowShouldClose()) {

        ecs.progress();
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        
        ecs.defer_begin();
            //buttonQuery2.each([&](flecs::entity e, cButton& btn) {
            //    if (btn.getMouseObject()->mouseCheck(mouseX, mouseY)) 
            //    {
            //        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            //        {
            //            btn.getMouseObject()->executeListeners({"c", 0});
            //        }
            //        else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            //        {
            //            btn.getMouseObject()->executeListeners({"c", 1});
            //        }
            //    }
            //
            //    if (btn.getPositionObject()->getId().idStr == "btm")
            //    {
            //        btn.move();
            //    }
            //});
            cID tmp = {"mm", 0};
            query.each([&](flecs::entity e, cRenderFlags& s) {
                if ( mouseX >= e.get<cPosition>()->posX 
                    && mouseY >= e.get<cPosition>()->posY
                    && mouseX <= e.get<cPosition>()->posX + e.get<cSize>()->width 
                    && mouseY <= e.get<cPosition>()->posY + e.get<cSize>()->height)
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (e.has<cInteraction>())
                        {
                            if (e.get<cInteraction>()->id == cID{"c", 0})
                            {
                                e.get<cInteraction>()->func();
                            }
                        }
                    }
                    //else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                    //{
                    //    if (e.has<cRenderFlags>())
                    //    {
                    //        if (*e.get<cID>() == tmp)
                    //        {
                    //            cSceneManager::getInstance()->setStatus({"mm", 0}, false);
                    //        }
                    //    } 
                    //}
                }
            });
        ecs.defer_end();

        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //for ( int i = 0 ; i < counter ;i++)
        //{
        //    DrawRectangle(xx[i], yy[i], 200, 50, PINK);
        //    DrawTexture(*TextureManager::getInstance()->getTextureById("test.png"),
        //         xx[i], yy[i], WHITE);
        //}

        ecs.system<cRenderFlags>("Render").each
        (
            [&](flecs::entity_view e, cRenderFlags s) 
            {
                cRenderManager::getInstance()->render(e);
            }
        );

        DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }

    return 0;
}