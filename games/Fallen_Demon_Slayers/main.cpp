#include <iostream>
#include <chrono>

#include "MainMenu.h"
#include "scene.h"

flecs::world *ptr = NULL;

struct test
{
    Rectangle* dest_ = nullptr;
};

int main() 
{
    SetConfigFlags( //FLAG_FULLSCREEN_MODE
       FLAG_WINDOW_RESIZABLE);

    InitWindow(1920, 1000, "Test");

    SetTargetFPS(1000);

    std::vector<test> v;

    Texture text = LoadTexture("gfx/test.png");

    Rectangle* source_ = nullptr;

    source_ = new Rectangle{0.0f, 0.0f, (float)text.width, (float)text.height};

    for (int i = 0; i < 5000; i++)
    {
        test t;
                
        t.dest_ = new Rectangle{(float)GetRandomValue(0, 1920), (float)GetRandomValue(0, 1920), 100.0f, 124.0f};

        v.push_back(t);
    }

    while(WindowShouldClose() == false)
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto& i : v)
        {
            //DrawTexture(text, i.x, i.y, WHITE);

            DrawTexturePro(text, *source_, *i.dest_, { 0.0f, 0.0f }, 0.0f, WHITE);
        }


        DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }
    /*
    flecs::world ecs;
    cPositionObject po = {{"gmm", 0}, {0, 0, 1920, 1080}, {0, 0, 1}};

    ptr = &ecs;

    TextureManager::getInstance()->loadTexture("bg2.png");
    TextureManager::getInstance()->loadTexture("test.png");
    TextureManager::getInstance()->loadTexture("grass.png");
    TextureManager::getInstance()->loadTexture("water.png");
    TextureManager::getInstance()->loadTexture("road.png");
    TextureManager::getInstance()->loadTexture("building.png");

    ecs.component<cButton>();
    ecs.component<MainMenu>();
    ecs.component<cImage>();

    auto mm = ecs.entity().emplace<MainMenu>(ptr, po);

    //for (int i = 0; i < 5000; i++)
    //{
    //    flecs::entity ent = ecs.entity();
    //    ent.set<pos>({300, 300});
    //    ent.set<sprite>({TextureManager::getInstance()->getTextureById("test.png")});
    //}

    // CM001 Old scene
    ecs.component<cOScene>();
    auto scene = ecs.entity().emplace<cOScene>(ptr, po);
    for (int i = 0; i < 5000; i++)
    {
        po = {{"btm", i}, {800, 100, 50, 62}, {0, 0, 1}};
        scene.get_mut<cOScene>()->addEntity<cButton>(po);

        cButton* bt = scene.get_mut<cOScene>()->getEntity<cButton>({"btm", i});

        //std::cout << i << std::endl;

        bt->applyColor(RED);

        bt->applyTexture("test.png", true);
    }//

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

                if (btn.getPositionObject()->getId().idStr == "btm")
                {
                    btn.move();
                }
            });
        ecs.defer_end();

        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (mm.is_alive())
        {
            mm.get_mut<MainMenu>()->render();
        }

        //ecs.system<pos, sprite>("Render").each([&](flecs::entity e, pos& p, sprite& s) {
        //    DrawTexture(*s.text, p.x, p.y, WHITE);
        //});

        // CM001 Old scene
        if (scene.is_alive())
        {
            scene.get_mut<cOScene>()->render<cButton>();
        }

        DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }*/

    return 0;
}