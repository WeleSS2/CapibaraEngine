#include "MainMenu.h"


MainMenu::MainMenu(flecs::world *_world, cPositionObject& _data)
    : world_(_world), cRenderObject(_data)
{   
    flecs::entity bt0;
    flecs::entity bt1; 
    flecs::entity bt2;
    flecs::entity bt3;
    flecs::entity bt4;


    createButton(bt0, { {"bt", 0}, {800, 0, 100, 50}, {0, 0, 1} });
    createButton(bt1, { {"bt", 1}, {800, 100, 100, 50}, {0, 0, 1} });
    createButton(bt2, { {"bt", 2}, {800, 200, 100, 50}, {0, 0, 1} });
    createButton(bt3, { {"bt", 3}, {800, 300, 100, 50}, {0, 0, 1} });
    createButton(bt4, { {"bt", 4}, {800, 400, 100, 50}, {0, 0, 1} });

    //bt0.get_ref<cButton>()->getMouseObject()->addListener(cchangeColor, bt0.get_ref<cButton>(), RED);
    bt0.get_mut<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki\n"; });
    bt0.get_mut<cButton>()->getMouseObject()->addListener({"c", 1}, [](){ std::cout << "Different listener : P\n"; });
    bt1.get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 1\n"; });
    bt2.get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 2\n"; });
    bt3.get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 3\n"; });
    bt4.get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ CloseWindow(); std::cout << "Heheszki 4\n"; });

}

void MainMenu::render() const
{
    for (const auto& i : toRender_)
    {
        i.get_mut<cButton>()->render();
    }
}

void MainMenu::createButton(flecs::entity& ent, cPositionObject _data)
{
    ent = world_->entity().emplace<cButton>(_data);

    ent.get_mut<cButton>()->applyColor(PINK);

    toRender_.emplace_back(ent);
}