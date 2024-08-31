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

    cCamera cam = {0 ,0};

    int speed = 10;

    MainMenu* scene = new MainMenu(ptr);

    TestMap* map = new TestMap(ptr);

    cSceneManager::getInstance()->addScene(static_cast<TestMap*>(map));

    cSceneManager::getInstance()->addScene(static_cast<cScene*>(scene));

    while (!WindowShouldClose()) {
        // This is a breakpoint it will wait for asynchronous ecs and rendering
        ecs.progress();
        ClearBackground(RAYWHITE);

        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        
        cam.offsetY = 0;
        cam.offsetX = 0;

        ecs.defer_begin();
            query.each([&](flecs::entity e, cRenderFlags& s) {
                if (e.get<cRenderFlags>()->value & cRenderFlags::Visible)
                {
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
                    }

                    if (e.get<cID>()->idStr == "player")
                    {
                        if (IsKeyDown(KEY_A))
                        {
                            e.get_mut<cAbsPosition>()->posX -= speed;

                            cam.offsetX += speed;
                        }

                        if (IsKeyDown(KEY_D))
                        {
                            e.get_mut<cAbsPosition>()->posX += speed;

                            cam.offsetX -= speed;
                        }

                        if (IsKeyDown(KEY_W))
                        {   
                            e.get_mut<cAbsPosition>()->posY -= speed;

                            cam.offsetY += speed; 
                        }

                        if (IsKeyDown(KEY_S))
                        {
                            e.get_mut<cAbsPosition>()->posY += speed;

                            cam.offsetY -= speed;
                        }
                    }
                }
            });
        ecs.defer_end();

        ecs.system<cAbsPosition>("PlayerSpawn").each
        (
            [&](flecs::entity e, cAbsPosition s) 
            {
                if (e.get<cRenderFlags>()->value & cRenderFlags::Visible)
                {
                    if (e.get<cAbsPosition>()->posX > e.get<cAbsPosition>()->basePosX + 32)
                    {
                        map->setNeg(true);

                        //map->spawnOnX(ptr);

                        e.get_mut<cAbsPosition>()->basePosX += 32;
                    }

                    if (e.get<cAbsPosition>()->posY > e.get<cAbsPosition>()->basePosY + 32)
                    {
                        map->setNeg(true);

                        //map->spawnOnY(ptr);

                        e.get_mut<cAbsPosition>()->basePosY += 32;
                    }

                    if (e.get<cAbsPosition>()->posX < e.get<cAbsPosition>()->basePosX - 32)
                    {
                        map->setNeg(false);

                        //map->spawnOnX(ptr);

                        e.get_mut<cAbsPosition>()->basePosX -= 32;
                    }

                    if (e.get<cAbsPosition>()->posY < e.get<cAbsPosition>()->basePosY - 32)
                    {
                        map->setNeg(false);

                        //map->spawnOnY(ptr);

                        e.get_mut<cAbsPosition>()->basePosY -= 32;
                    }
                }
            }
        );

        // Start drawing
        BeginDrawing();

        ecs.system<cRenderFlags>("Render").each
        (
            [&](flecs::entity e, cRenderFlags s) 
            {
                cRenderManager::getInstance()->cameraMove(e, &cam);

                cRenderManager::getInstance()->render(e);
            }
        );

        DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }

    return 0;
}