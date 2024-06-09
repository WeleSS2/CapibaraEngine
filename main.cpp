#include <iostream>
#include <stdio.h>
#include <functional>
#include <vector>

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
    const void addListener(Func&& func, Args&&... args){
        listeners.emplace_back([=]() mutable {
	        func(args...);
	    });
    }

    // Method to trigger all listeners
    void click() {
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
void cchangeColor(cButton* button, Color color) {
    std::cout << "CLicked 2 " << button << "    " << button->getId() << "    " << button->getY() << "\n";
    button->applyColor(color);
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
        for (const auto& i : toRender)
        {
            i->render();
        }
    }

    const void addModule(cButton* object)
    {
        std::cout << object->getId() << "    " <<
        object << std::endl;

        toRender.emplace_back(object);
    }

    std::vector<cButton*> toRender;
};

class Panel3 {
public:
    Panel3(std::string id) : _id(id) { std::cout << "Const IS" << std::endl; };

    std::string _id;

    Panel3() {
        auto btt0 = ptr->entity().emplace<cButton>();
        btt0.get_mut<cButton>()->applyColor(PINK);
        btt0.get_mut<cButton>()->create("btt0", {1100, 0, 100, 50});
        
        auto btt1 = ptr->entity().emplace<cButton>();
        btt1.get_mut<cButton>()->applyColor(PINK);
        btt1.get_mut<cButton>()->create("btt1", {1100, 100, 100, 50});
        
        btt0.get_mut<cButton>()->addListener(cchangeColor, btt0.get_mut<cButton>(), BLUE);
        btt1.get_mut<cButton>()->addListener(cchangeColor, btt1.get_mut<cButton>(), BLUE);
        
        this->addModule(btt0.get_mut<cButton>());
        this->addModule(btt1.get_mut<cButton>());
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

#include <random>
int main(int argc, char *argv[])
{   
    // Initialize window
    const int screenWidth = 1600;
    const int screenHeight = 900;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "ECS example with Flecs and Raylib");
    SetTargetFPS(60);
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

    std::cout << "Test   " << TextureManager::getManager()->loadTexture("test.png") << "\n";



















    // Register component
    ecs.component<RectangleComp>();

    // Create a button entity
    ecs.component<Button>();
    ecs.entity()
       .set<Button>({50, 50, 100, 50, BLACK, false});
    ecs.entity()
       .set<Button>({50, 150, 100, 50, BLACK, false});
    ecs.entity()
       .set<Button>({50, 250, 100, 50, BLACK, false});
    ecs.entity()
       .set<Button>({50, 350, 100, 50, BLACK, false});

    auto one = ecs.entity()
       .set<Button>({50, 450, 100, 50, BLACK, false});
    one.get_mut<Button>()->addListener(changeColor, one.get_mut<Button>(), RED);
    
    auto two = ecs.entity()
       .set<Button>({50, 550, 100, 50, BLACK, false});
    two.get_mut<Button>()->addListener(changeColor, two.get_mut<Button>(), BLUE);
    
    auto three = ecs.entity()
       .set<Button>({});
    three.get_mut<Button>()->x = 500;
    three.get_mut<Button>()->y = 300;
    three.get_mut<Button>()->width = 100;
    three.get_mut<Button>()->height = 100;   
    three.get_mut<Button>()->addListener(changeColor, three.get_mut<Button>(), GREEN);

    ecs.component<Panel>();
    auto panel = ecs.entity()
        .set<Panel>({one, two, three});

    // Create an entity with a RectangleComp component

    
    ecs.component<cButton>();
    auto bt0 = ecs.entity().set<cButton>({"bt0", {800, 0, 100, 50}});
    bt0.get_mut<cButton>()->applyColor(PINK);

    auto bt1 = ecs.entity().set<cButton>({"bt1", {800, 100, 100, 50}});
    bt1.get_mut<cButton>()->applyColor(PINK);

    auto bt2 = ecs.entity().set<cButton>({"bt2", {800, 200, 100, 50}});
    bt2.get_mut<cButton>()->applyColor(PINK);

    auto bt3 = ecs.entity().set<cButton>({"bt3", {800, 300, 100, 50}});
    bt3.get_mut<cButton>()->applyColor(PINK);

    auto bt4 = ecs.entity().emplace<cButton>();
    bt4.get_mut<cButton>()->applyColor(PINK);


    bt0.get_mut<cButton>()->addListener(cchangeColor, bt0.get_mut<cButton>(), BLUE);
    bt1.get_mut<cButton>()->addListener(cchangeColor, bt1.get_mut<cButton>(), BLUE);
    bt2.get_mut<cButton>()->addListener(cchangeColor, bt2.get_mut<cButton>(), GREEN);
    bt3.get_mut<cButton>()->addListener(cchangeColor, bt3.get_mut<cButton>(), YELLOW);
    bt4.get_mut<cButton>()->addListener(cchangeColor, bt4.get_mut<cButton>(), BLACK);

    ecs.component<Panel2>();
    auto panel2 = ecs.entity().emplace<Panel2>();
    panel2.get_mut<Panel2>()->addModule(bt0.get_mut<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt1.get_mut<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt2.get_mut<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt3.get_mut<cButton>());
    panel2.get_mut<Panel2>()->addModule(bt4.get_mut<cButton>());
    
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

    std::cout << ecs.query<Panel>().count() << std::endl;


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

            // Query all buttons and check for clicks
            auto buttonQuery = ecs.query<Button>();
            buttonQuery.each([&](flecs::entity e, Button& btn) {
                // Check if the mouse is within the button bounds
                if (mouseX >= btn.x && mouseX <= btn.x + btn.width &&
                    mouseY >= btn.y && mouseY <= btn.y + btn.height) {
            
                    std::cout << btn.y << std::endl;
            
                    btn.click();
                }
            });

            // Query all buttons and check for clicks
            auto buttonQuery2 = ecs.query<cButton>();
            buttonQuery2.each([&](flecs::entity e, cButton& btn) {
                // Check if the mouse is within the button bounds
                if (btn.clickCheck(mouseX, mouseY)) {

                    std::cout << btn.getId() <<"    " << &btn << std::endl;

                    btn.click();
                }
            });
        }

        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (panel.is_alive())
        {
            panel.get<Panel>()->draw();
        }

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