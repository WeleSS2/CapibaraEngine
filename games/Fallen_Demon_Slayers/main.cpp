#include <iostream>
#include <chrono>
#include <functional>

#include "TextureManager.h"
#include "MainMenu.h"
#include "testMap.h"
#include "renderManager.h"
#include "sceneManager.h"
#include "playerManager.h"
#include "spdlog/spdlog.h"
#include "quadTree.h"
#include "logs.h"

#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING

flecs::world *ptr = NULL;

int main() 
{
    //TraceLog("Just a simple log", 1231231);
    flecs::world ecs;
    ptr = &ecs;

    cQuadTree tree(ptr, 1000, 1000, 5);

    if (!tree.generateDefault(0))
    {
        //std::cout << "Failed to generate default tree" << std::endl;
    }

    if (!tree.getOrigin().has<cNode>())
    {
        //std::cout << "Failed to get default tree" << std::endl;
    }

    tree.getOrigin().get<cNode>()->printNodes();

    Logs::getInstance()->createDefaultPath();

    Logs::setLevel(SPDLOG_LEVEL_DEBUG);

    int value = 22;

    Logs::Debug("Starting Engine... {} {}", value, " Does it work??!");
    
    
    SetConfigFlags( FLAG_FULLSCREEN_MODE |
       FLAG_WINDOW_RESIZABLE);

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Test");
    cScreenScale::setScale(GetScreenWidth() / 100, GetScreenHeight() / 100);

    SetTargetFPS(1200);

    spdlog::debug("Loading Textures...", value);

    TextureManager::getInstance()->loadTexture("bg2.png");
    //TextureManager::getInstance()->loadTexture("test.png");
    //TextureManager::getInstance()->loadTexture("grass.png");
    //TextureManager::getInstance()->loadTexture("water.png");
    //TextureManager::getInstance()->loadTexture("road.png");
    //TextureManager::getInstance()->loadTexture("building.png");

    auto query = ecs.query<cRenderFlags>();

    int speed = 2;

    bool loaded = false;

    MainMenu* scene = new MainMenu(ptr);

    TestMap* map = new TestMap(ptr);

    spdlog::debug("Creating scenes...");

    cSceneManager::getInstance()->addScene(static_cast<TestMap*>(map));

    cSceneManager::getInstance()->addScene(static_cast<cScene*>(scene));

    cPlayerManager::create(ptr);

    flecs::entity et = cSceneManager::getInstance()->getScene(cID{"map", 0})->
            getEntity(cID{"player", 0});

    cPlayerManager::getInstance()->setLocalPlayer(et);

    cPlayerManager::getInstance()->updateCamera();

    spdlog::debug("Starting game loop...");

    while (!WindowShouldClose()) 
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        ecs.defer_begin();

        query.each([&](flecs::entity e, cRenderFlags& s) 
        {
            if (e.get<cRenderFlags>()->value & cRenderFlags::Visible)
            {
                //spdlog::debug("{}", e.get<cID>()->idStr);
                if (e.has<cActive>())
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
                                e.get<cInteraction>()->func();
                            }
                        }
                    }

                    if (e.get<cID>()->idStr == "player")
                    {
                        //if (!loaded)
                        //{
                        //    loaded = true;
                        //    e.get_mut<cRelPosition>()->prevX = e.get<cRelPosition>()->posX;
                        //    e.get_mut<cRelPosition>()->prevY = e.get<cRelPosition>()->posY;
                        //}
                        
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
/*
                        if (e.get<cRelPosition>()->posX >= e.get<cRelPosition>()->prevX + 64)
                        {
                            // Update map
                            e.get_mut<cRelPosition>()->prevX = e.get<cRelPosition>()->posX;
                        }

                        if (e.get<cRelPosition>()->posY >= e.get<cRelPosition>()->prevY + 64)
                        {
                            // Update map
                            e.get_mut<cRelPosition>()->prevY = e.get<cRelPosition>()->posY;
                        }
                        
                        if (e.get<cRelPosition>()->posX <= e.get<cRelPosition>()->prevX - 64)
                        {
                            // Update map
                            e.get_mut<cRelPosition>()->prevX = e.get<cRelPosition>()->posX;
                        }

                        if (e.get<cRelPosition>()->posY <= e.get<cRelPosition>()->prevY - 64)
                        {
                            // Update map
                            e.get_mut<cRelPosition>()->prevY = e.get<cRelPosition>()->posY;
                        }*/
                    }
                }
            }
        });

        ecs.defer_end();

        BeginDrawing();
        
        if (et.get<cRenderFlags>()->value & cRenderFlags::Visible)
        {
            cPlayerManager::getInstance()->moveCamera();

            BeginMode3D(cPlayerManager::getInstance()->getCamera());
        }

        // Start drawing
        ecs.system<cSceneEntity>("Render").each
        (
            [&](flecs::entity e, cSceneEntity s)
            {
                e.get_mut<cSceneEntity>()->scene->renderScene();
            }
        );

        ecs.progress();

        if (et.get<cRenderFlags>()->value & cRenderFlags::Visible)
        {
            EndMode3D();
        }

        DrawFPS(10, 10);
        EndDrawing();
        ClearBackground(RAYWHITE);
    }

    CloseWindow();

    return 0;
}