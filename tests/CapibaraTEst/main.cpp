#include <iostream>
#include <stdio.h>
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <random>

#define raylib

#include "logs.h"
#include "Button.h"
#include "TextureManager.h"
#include "raylib.h"
#include <flecs.h>

using namespace std;

flecs::world *ptr = NULL;

void cchangeColor(flecs::ref<cButton> button, Color color) 
{
    button.get()->applyColor(color);
};

class Panel2 
{
public:

    Panel2();
    
    const void render() const
    {
        for (const auto& i : toRender)
        {
            i->render();
        }
    }

    void remove(flecs::ref<cButton> bt)
    {
        for (int i = 0; i < toRender.size(); i++) //auto i : toRender)
        {
            if (toRender[i]->getId() == bt.get()->getId())
            {
                toRender.erase(toRender.begin() + i);
            }
        }
    }

    const void addModule(cButton* object)
    {
        toRender.emplace_back(object);
    }

    std::vector<cButton*> toRender;
};

void deleteButton(flecs::ref<cButton> button, Panel2* panel) 
{
    button.entity().destruct();

    panel->remove(button);
};

Panel2::Panel2 () 
{
    auto bt0 = ptr->entity().set<cButton>({"bta0", {800, 0, 100, 50}});
    bt0.get_mut<cButton>()->applyColor(PINK);

    auto bt1 = ptr->entity().set<cButton>({"bta1", {800, 100, 100, 50}});
    bt1.get_mut<cButton>()->applyColor(PINK);

    auto bt2 = ptr->entity().set<cButton>({"bta2", {800, 200, 100, 50}});
    bt2.get_mut<cButton>()->applyColor(PINK);

    auto bt3 = ptr->entity().set<cButton>({"bta3", {800, 300, 100, 50}});
    bt3.get_mut<cButton>()->applyColor(PINK);

    auto bt4 = ptr->entity().set<cButton>({"bta4", {800, 400, 100, 50}});
    bt4.get_mut<cButton>()->applyColor(PINK);

    bt0.get_ref<cButton>()->addListener(cchangeColor, bt0.get_ref<cButton>(), RED);
    bt1.get_ref<cButton>()->addListener(cchangeColor, bt1.get_ref<cButton>(), BLUE);
    bt2.get_ref<cButton>()->addListener(cchangeColor, bt2.get_ref<cButton>(), GREEN);
    bt3.get_ref<cButton>()->addListener(cchangeColor, bt3.get_ref<cButton>(), YELLOW);
    bt4.get_ref<cButton>()->addListener(deleteButton, bt4.get_ref<cButton>(), this);
    bt4.get_ref<cButton>()->addListener([](){ std::cout << "Heheszki\n"; });

    this->addModule(bt0.get_mut<cButton>());
    this->addModule(bt1.get_mut<cButton>());
    this->addModule(bt2.get_mut<cButton>());
    this->addModule(bt3.get_mut<cButton>());
    this->addModule(bt4.get_mut<cButton>());
};

class Panel3 
{
public:
    Panel3(std::string _id) : id(_id) {  };

    std::string id;

    Panel3() 
    {
        for (int i = 0; i < 1; i++)
        {            
            
            std::string name = "btt" + std::to_string(i);

            auto bt0 = ptr->entity().set<cButton>({name, {(uint16_t)(1 + (i)), (uint16_t)(1 + (i)), 100, 50}});
            bt0.get_ref<cButton>()->applyColor(PINK);
            bt0.get_ref<cButton>()->applyTexture("test.png");
        
            bt0.get_ref<cButton>()->addListener(cchangeColor, bt0.get_ref<cButton>(), BLUE);
        
            this->addModule(bt0.get_mut<cButton>());
        }
    };
    

    const void render() const
    {
        for (const auto& i : toRender)
        {
            i->render();
        }
    }

    const void addModule(cButton* object)
    {
        toRender.emplace_back(object);
    }

    std::vector<cButton*> toRender;
};

int main(int argc, char *argv[])
{
    // Initialize window
    const int screenWidth = 1600;
    const int screenHeight = 900;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Test");
    //SetTargetFPS(60);

    flecs::world ecs;

    ptr = &ecs;

    // TEST AREA
    TextureManager::getManager()->loadTexture("test.png");


    ecs.component<cButton>();

    ecs.component<Panel2>();
    auto panel2 = ecs.entity().emplace<Panel2>();
    
    ecs.component<Panel3>();
    auto panel3 = ecs.entity().emplace<Panel3>();
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Update ECS
        ecs.progress();
        
        // Check for button click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            ecs.defer_begin();
            auto buttonQuery2 = ecs.query<cButton>();
            buttonQuery2.each([&](flecs::entity e, cButton& btn) {
                if (btn.mouseCheck(mouseX, mouseY)) {
                    btn.click();
                }
            });
            ecs.defer_end();
        }

        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (panel2.is_alive())
        {
            panel2.get<Panel2>()->render(); 
        }

        if (panel3.is_alive())
        {
            panel3.get<Panel3>()->render();
        }

        DrawFPS(10, 10); // Display FPS in top-left corner
        EndDrawing();
    }

    return 0;
}