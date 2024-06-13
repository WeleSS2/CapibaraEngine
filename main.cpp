#include <iostream>
#include <stdio.h>
#include <functional>
#include <vector>
#include <string>
#include <sstream>

#define raylib

#include "logs.hpp"
#include "Button.hpp"
#include "TextureManager.hpp"
#include "raylib.h"
#include <flecs.h>

using namespace std;

// Component to hold rectangle properties
struct RectangleComp {
    float x, y;      // Position
    float width, height; // Size
    Color color;     // Color
};

flecs::world *ptr = NULL;

struct Velocity {
    float vx, vy;
};

struct Button {
    int x, y;        // Position
    int width, height; // Size
    Color color;     // Color
    bool isClicked;

    Button(){};
    
    Button(int _x, int _y, int _width, int _height, Color _color, bool _isClicked)
           : x(_x), y(_y), width(_width), height(_height), color(_color), isClicked(_isClicked) {}

        // A vector to hold any callable that matches the signature
    std::vector<std::function<void()>> listeners;

    // Method to add a listener with any number of arguments
    template<typename Func, typename... Args>
    const void addListener(Func&& func, Args&&... args)
    {
        listeners.emplace_back([=]() mutable {
	        func(args...);
	    });
    }

    // Method to trigger all listeners
    void click() 
    {
        for (auto& listener : listeners) {
            listener(); 
        }
    }
};

// Example function to be called
void changeColor(Button* button, Color color) {
    std::cout << "CLicked " << button->y<< "\n";
    button->color = color;
};

// Example function to be called
void cchangeColor(flecs::ref<cButton> button, Color color) {
    button.get()->applyColor(color);
};

void test()
{
    std::cout << "Simple test \n";
}

class Panel {
public:
    Panel(){};
    Panel(flecs::entity _one, flecs::entity _two, flecs::entity _three)
    {
        everythingFine = true;
        one = _one;
        two = _two; 
        three = _three;
    
        // Check did they are exist and are correct, if not whole module will be set to failed
        auto btnOne = this->one.get<Button>();
        if (!btnOne) {
            everythingFine = false;
        }

        auto btnTwo = this->two.get<Button>();
        if (!btnTwo) {
            everythingFine = false;
        }

        auto btnThree = this->three.get<Button>();
        if (!btnThree) {
            everythingFine = false;
        }
    };

    const void draw() const
    {
        // Draw each button in the panel
        auto btnOne = this->one.get<Button>();
        DrawRectangle(one.get<Button>()->x, btnOne->y, btnOne->width, btnOne->height, btnOne->color);
        
        auto btnTwo = this->two.get<Button>();
        DrawRectangle(btnTwo->x, btnTwo->y, btnTwo->width, btnTwo->height, btnTwo->color);
        
        auto btnThree = this->three.get<Button>();
        DrawRectangle(btnThree->x, btnThree->y, btnThree->width, btnThree->height, btnThree->color);
    }

private:

    bool everythingFine;
    flecs::entity one;
    flecs::entity two;
    flecs::entity three;
};

class Panel2 {
public:
    Panel2(){};

    const void render() const
    {
        for (auto& i : toRender)
        {
            //if (i.entity().is_alive()) 
            {
                i.entity().get_mut<cButton>()->render();
            }
        }
    }

    void remove(flecs::ref<cButton> bt)
    {
        for (int i = 0; i < toRender.size(); i++) //auto i : toRender)
        {
            if (toRender[i].get()->getId() == bt.get()->getId())
            {
                toRender.erase(toRender.begin() + i);
            }
        }
    }

    const void addModule(flecs::ref<cButton> object)
    {
        toRender.emplace_back(object);
    }

    std::vector<flecs::ref<cButton>> toRender;
};

class Panel3 {
public:
    Panel3(std::string _id) : id(_id) { std::cout << "Const IS" << std::endl; };

    std::string id;

    Panel3() 
    {
        //*
        
        //ecs_bulk_init(*ptr, );

        for (int i = 0; i < 1; i++)
        {            
            
            std::string name = "btt" + std::to_string(i);

            auto bt0 = ptr->entity().set<cButton>({name, {(uint16_t)(1 + (i)), (uint16_t)(1 + (i)), 100, 50}});
            bt0.get_ref<cButton>()->applyColor(PINK);
            bt0.get_ref<cButton>()->applyTexture("test.png");
        
            bt0.get_ref<cButton>()->addListener(cchangeColor, bt0.get_ref<cButton>(), BLUE);
        
            this->addModule(bt0.get_mut<cButton>());
        }
        //*/
        /*
        int i = 0;
        auto btt0 = ptr->entity().emplace<cButton>();

            std::string name = "btt" + std::to_string(i);

            btt0.get_mut<cButton>()->create(name, {(uint16_t)(1 + i), (uint16_t)(1 + i), 200, 200});
            btt0.get_mut<cButton>()->applyColor(PINK);
            btt0.get_mut<cButton>()->applyTexture("test.png");

            btt0.get_mut<cButton>()->addListener(cchangeColor, btt0.get_mut<cButton>(), BLUE);
        
            this->addModule(btt0.get_mut<cButton>());
        
        i = 100;
        btt0 = ptr->entity().emplace<cButton>();

            name = "btt" + std::to_string(i);

            btt0.get_mut<cButton>()->create(name, {(uint16_t)(1 + i), (uint16_t)(1 + i), 200, 200});
            btt0.get_mut<cButton>()->applyColor(PINK);
            btt0.get_mut<cButton>()->applyTexture("test.png");

            btt0.get_mut<cButton>()->addListener(cchangeColor, btt0.get_mut<cButton>(), BLUE);
        
            this->addModule(btt0.get_mut<cButton>());
        //
        //*
        i = 200;
        btt0 = ptr->entity().emplace<cButton>();

            name = "btt" + std::to_string(i);

            btt0.get_mut<cButton>()->create(name, {(uint16_t)(1 + i), (uint16_t)(1 + i), 200, 200});
            btt0.get_mut<cButton>()->applyColor(PINK);
            btt0.get_mut<cButton>()->applyTexture("test.png");

            btt0.get_mut<cButton>()->addListener(cchangeColor, btt0.get_mut<cButton>(), BLUE);
        
            this->addModule(btt0.get_mut<cButton>());
        
        i = 300;
        btt0 = ptr->entity().emplace<cButton>();

            name = "btt" + std::to_string(i);

            btt0.get_mut<cButton>()->create(name, {(uint16_t)(1 + i), (uint16_t)(1 + i), 200, 200});
            btt0.get_mut<cButton>()->applyColor(PINK);
            btt0.get_mut<cButton>()->applyTexture("test.png");

            btt0.get_mut<cButton>()->addListener(cchangeColor, btt0.get_mut<cButton>(), BLUE);
        
            this->addModule(btt0.get_mut<cButton>());
        */
        std::cout << toRender.size() << std::endl;
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

void deleteButton(flecs::ref<cButton> button, flecs::ref<Panel2> parent) {
    //button.get()->~cButton();
    button.entity().destruct();
    std::cout << "Killed \n";

    parent.get()->remove(button);
};

#include <random>
int main(int argc, char *argv[])
{   
    // Initialize window
    const int screenWidth = 1600;
    const int screenHeight = 900;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "ECS example with Flecs and Raylib");
    //SetTargetFPS(60);
    MaximizeWindow();

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-5, 5); // define the range
    std::uniform_int_distribution<> color(0, 255);
    std::uniform_int_distribution<> distrXY(-5.0f, 5.0f); // Define the range for velocity

    // Initialize Flecs
    // In every class which use world make dependency injection for 
    // testing purposes BUT in constructor add taking an instance from 
    // singleton. Also make singleton for world instance, this way easy to 
    // use singleton is connected to easy tests with dependency injection.
    // Testing can be minimal harder but i dont need to think about passing 
    // instance of world everywhere in runtime or general debug environemnt.
    flecs::world ecs;

    ptr = &ecs;

    // TEST AREA

    TextureManager::getManager()->loadTexture("test.png");

















    // Register component
    ecs.component<RectangleComp>();

    // Create an entity with a RectangleComp component

    
    ecs.component<cButton>();
    auto bt0 = ecs.entity().set<cButton>({"bta0", {800, 0, 100, 50}});
    bt0.get_mut<cButton>()->applyColor(PINK);

    auto bt1 = ecs.entity().set<cButton>({"bta1", {800, 100, 100, 50}});
    bt1.get_mut<cButton>()->applyColor(PINK);

    auto bt2 = ecs.entity().set<cButton>({"bta2", {800, 200, 100, 50}});
    bt2.get_mut<cButton>()->applyColor(PINK);

    auto bt3 = ecs.entity().set<cButton>({"bta3", {800, 300, 100, 50}});
    bt3.get_mut<cButton>()->applyColor(PINK);

    auto bt4 = ecs.entity().set<cButton>({"bta4", {800, 400, 100, 50}});
    bt4.get_mut<cButton>()->applyColor(PINK);

    ecs.component<Panel2>();
    auto panel2 = ecs.entity().emplace<Panel2>();

    bt0.get_ref<cButton>()->addListener(cchangeColor, bt0.get_ref<cButton>(), RED);
    bt1.get_ref<cButton>()->addListener(cchangeColor, bt1.get_ref<cButton>(), BLUE);
    bt2.get_ref<cButton>()->addListener(cchangeColor, bt2.get_ref<cButton>(), GREEN);
    bt3.get_ref<cButton>()->addListener(cchangeColor, bt3.get_ref<cButton>(), YELLOW);
    bt4.get_ref<cButton>()->addListener(deleteButton, bt4.get_ref<cButton>(), panel2.get_ref<Panel2>());
    bt4.get_ref<cButton>()->addListener([](){ std::cout << "Heheszki\n"; });

    panel2.get_mut<Panel2>()->addModule(bt0.get_ref<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt1.get_ref<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt2.get_ref<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt3.get_ref<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt4.get_ref<cButton>());
    
    ecs.component<Panel3>();
    auto panel3 = ecs.entity().emplace<Panel3>();
    
    ecs.system<RectangleComp, Velocity>().each([](RectangleComp &rc, Velocity &vel) {
        rc.x += vel.vx;
        rc.y += vel.vy;

        // Keep entities within screen bounds
        if (rc.x < 0 || rc.x > screenWidth - rc.width) vel.vx *= -1;
        if (rc.y < 0 || rc.y > screenHeight - rc.height) vel.vy *= -1;
    });

    for (int i = 0; i < 100; i++) {
        float x = std::rand() % GetScreenWidth();  // Random x coordinate within screen bounds
        float y = std::rand() % GetScreenHeight(); // Random y coordinate within screen bounds

        float vx = distrXY(gen); // Random velocity x
        float vy = distrXY(gen); // Random velocity`

        ecs.entity()
           .set<RectangleComp>({x, y, 5, 5, RED}).set<Velocity>({vx, vy});
    }

    auto a = ecs.query<Panel>().count();



    for (int i = 0; i < 50; i++) {
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
        
        // Check for button click
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