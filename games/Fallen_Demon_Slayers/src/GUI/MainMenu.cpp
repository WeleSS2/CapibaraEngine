#include "MainMenu.h"


MainMenu::MainMenu(flecs::world *_world, cPositionObject& _data)
    : cRenderObject(_data)
{
    std::cout << "MainMenu" << std::endl;
    cPositionObject mm = { {"bt", 0}, {800, 0, 100, 50}, {0, 0, 1} };
    //auto bt0 = _world->entity().set<cButton>(mm);
    auto bt0 = _world->entity().emplace<cButton>(mm);
    std::cout << "bt0" << std::endl;
    
    bt0.get_mut<cButton>()->applyColor(PINK);

    //auto bt1 = _world->entity().set<cButton>({{ {"bt", 1}, {800, 100, 100, 50}, {0, 0, 1} }});
    //bt1.get_mut<cButton>()->applyColor(PINK);

    //auto bt2 = _world->entity().set<cButton>({{ {"bt", 2}, {800, 200, 100, 50}, {0, 0, 1} }});
    //bt2.get_mut<cButton>()->applyColor(PINK);

    //auto bt3 = _world->entity().set<cButton>({{ {"bt", 3}, {800, 300, 100, 50}, {0, 0, 1} }});
    //bt3.get_mut<cButton>()->applyColor(PINK);

    //auto bt4 = _world->entity().set<cButton>({{ {"bt", 4}, {800, 400, 100, 50}, {0, 0, 1} }});
    //bt4.get_mut<cButton>()->applyColor(PINK);

    //bt0.get_ref<cButton>()->getClickObject()->addListener(cchangeColor, bt0.get_ref<cButton>(), RED);
    // bt1.get_ref<cButton>()->addListener(cchangeColor, bt1.get_ref<cButton>(), BLUE);
    // bt2.get_ref<cButton>()->addListener(cchangeColor, bt2.get_ref<cButton>(), GREEN);
    // bt3.get_ref<cButton>()->addListener(cchangeColor, bt3.get_ref<cButton>(), YELLOW);
    // bt4.get_ref<cButton>()->addListener(deleteButton, bt4.get_ref<cButton>(), this);
     bt0.get_ref<cButton>()->getClickObject()->addListener([](){ std::cout << "Heheszki\n"; });

    this->addModule(bt0.get_mut<cButton>());
    //this->addModule(bt1.get_mut<cButton>());
    //this->addModule(bt2.get_mut<cButton>());
    //this->addModule(bt3.get_mut<cButton>());
    //this->addModule(bt4.get_mut<cButton>());
}

void MainMenu::render() const
{
    for (const auto& i : toRender)
    {
        i->render();
    }
}

const void MainMenu::addModule(cButton* object)
{
    toRender.emplace_back(object);
}