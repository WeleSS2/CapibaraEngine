#include "MainMenu.h"


MainMenu::MainMenu(flecs::world *_world, cPositionObject& _data)
    : cRenderObject(_data)
{
    cPositionObject mm = { {"bt", 0}, {800, 0, 100, 50}, {0, 0, 1} };
    auto bt0 = _world->entity().emplace<cButton>(mm);
    bt0.get_mut<cButton>()->applyColor(PINK);
    bt0.get_mut<cButton>()->applyTexture("button");

    mm = { {"bt", 1}, {800, 100, 100, 50}, {0, 0, 1} };
    auto bt1 = _world->entity().emplace<cButton>(mm);
    bt1.get_mut<cButton>()->applyColor(PINK);

    mm = { {"bt", 2}, {800, 200, 100, 50}, {0, 0, 1} };
    auto bt2 = _world->entity().emplace<cButton>(mm);
    bt2.get_mut<cButton>()->applyColor(PINK);

    mm = { {"bt", 3}, {800, 300, 100, 50}, {0, 0, 1} };
    auto bt3 = _world->entity().emplace<cButton>(mm);
    bt3.get_mut<cButton>()->applyColor(PINK);

    mm = { {"bt", 4}, {800, 400, 100, 50}, {0, 0, 1} };
    auto bt4 = _world->entity().emplace<cButton>(mm);
    bt4.get_mut<cButton>()->applyColor(PINK);

    //bt0.get_ref<cButton>()->getClickObject()->addListener(cchangeColor, bt0.get_ref<cButton>(), RED);
    bt0.get_ref<cButton>()->getClickObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki\n"; });
    bt0.get_ref<cButton>()->getClickObject()->addListener({"c", 1}, [](){ std::cout << "Different listener : P\n"; });
    bt1.get_ref<cButton>()->getClickObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 1\n"; });
    bt2.get_ref<cButton>()->getClickObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 2\n"; });
    bt3.get_ref<cButton>()->getClickObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 3\n"; });
    bt4.get_ref<cButton>()->getClickObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 4\n"; });

    this->addModule(bt0.get_mut<cButton>());
    this->addModule(bt1.get_mut<cButton>());
    this->addModule(bt2.get_mut<cButton>());
    this->addModule(bt3.get_mut<cButton>());
    this->addModule(bt4.get_mut<cButton>());
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