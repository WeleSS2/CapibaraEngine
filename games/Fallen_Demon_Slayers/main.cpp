#include <iostream>
#include <chrono>
#include <functional>

#include "TextureManager.h"
#include "MainMenu.h"
#include "src/testMap.h"
#include "renderManager.h"
#include "sceneManager.h"

flecs::world *ptr = NULL;

int main() 
{
    SetConfigFlags( FLAG_FULLSCREEN_MODE |
       FLAG_WINDOW_RESIZABLE);

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Test");
    cScreenScale::setScale(GetScreenWidth() / 100, GetScreenHeight() / 100);

    SetTargetFPS(120);
    
    flecs::world ecs;
    ptr = &ecs;

    TextureManager::getInstance()->loadTexture("bg2.png");
    //TextureManager::getInstance()->loadTexture("test.png");
    //TextureManager::getInstance()->loadTexture("grass.png");
    //TextureManager::getInstance()->loadTexture("water.png");
    //TextureManager::getInstance()->loadTexture("road.png");
    //TextureManager::getInstance()->loadTexture("building.png");

    auto query = ecs.query<cRenderFlags>();

    int speed = 10;

    MainMenu* scene = new MainMenu(ptr);

    TestMap* map = new TestMap(ptr);

    cSceneManager::getInstance()->addScene(static_cast<TestMap*>(map));

    cSceneManager::getInstance()->addScene(static_cast<cScene*>(scene));

    flecs::entity et = cSceneManager::getInstance()->getScene(cID{"map", 0})->
            getEntity(cID{"player", 0});

    Camera2D camera = { 0 };
    camera.target = {
            (float)et.get<cPosition>()->posX,
            (float)et.get<cPosition>()->posY
        };
    camera.offset = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) 
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        ecs.defer_begin();
            query.each([&](flecs::entity e, cRenderFlags& s) 
            {
                if (e.get<cRenderFlags>()->value & cRenderFlags::Visible)
                {
                    if ( mouseX >= e.get<cPosition>()->posX 
                        && mouseY >= e.get<cPosition>()->posY
                        && mouseX <= e.get<cPosition>()->posX + e.get<cSize>()->width 
                        && mouseY <= e.get<cPosition>()->posY + e.get<cSize>()->height )
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
                    }

                    if (e.get<cID>()->idStr == "player")
                    {
                        if (IsKeyDown(KEY_A))
                        {
                            e.get_mut<cPosition>()->posX -= speed;
                        }

                        if (IsKeyDown(KEY_D))
                        {
                            e.get_mut<cPosition>()->posX += speed;
                        }

                        if (IsKeyDown(KEY_W))
                        {   
                            e.get_mut<cPosition>()->posY -= speed;
                        }

                        if (IsKeyDown(KEY_S))
                        {
                            e.get_mut<cPosition>()->posY += speed;
                        }

                        if (IsKeyDown(KEY_SPACE))
                        {
                            std::cout << (float)cSceneManager::getInstance()->getScene(cID{"map", 0})->
                            getEntity(cID{"player", 0}).get<cPosition>()->posX << std::endl;

                            std::cout << (float)cSceneManager::getInstance()->getScene(cID{"map", 0})->
                            getEntity(cID{"player", 0}).get<cPosition>()->posY << std::endl;
                        
                            std::cout << camera.target.x << std::endl;

                            std::cout << camera.target.y << std::endl;

                            std::cout << "--------------------------" << std::endl;
                        }
                    }
                }
            });
        ecs.defer_end();

        BeginDrawing();
        
        if (et.get<cRenderFlags>()->value & cRenderFlags::Visible)
        {
            camera.target = {
                (float)et.get<cPosition>()->posX,
                (float)et.get<cPosition>()->posY
            };
        
            BeginMode2D(camera);
        }

        // Start drawing
        ecs.system<cRenderFlags>("Render").each
        (
            [&](flecs::entity e, cRenderFlags s) 
            {
                //cRenderManager::getInstance()->cameraMove(e, &cam);

                cRenderManager::getInstance()->render(e);
            }
        );

        ecs.progress();

        if (et.get<cRenderFlags>()->value & cRenderFlags::Visible)
        {
            EndMode2D();
        }

        DrawFPS(10, 10);
        EndDrawing();
        ClearBackground(RAYWHITE);
    }

    CloseWindow();

    return 0;
}