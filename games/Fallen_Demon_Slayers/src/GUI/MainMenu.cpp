#include "MainMenu.h"


MainMenu::MainMenu(flecs::world *_world)
{
    auto bt0 = _world->entity().set<cButton>({"bta0", {800, 0, 100, 50}});
    bt0.get_mut<cButton>()->applyColor(PINK);

    auto bt1 = _world->entity().set<cButton>({"bta1", {800, 100, 100, 50}});
    bt1.get_mut<cButton>()->applyColor(PINK);

    auto bt2 = _world->entity().set<cButton>({"bta2", {800, 200, 100, 50}});
    bt2.get_mut<cButton>()->applyColor(PINK);

    auto bt3 = _world->entity().set<cButton>({"bta3", {800, 300, 100, 50}});
    bt3.get_mut<cButton>()->applyColor(PINK);

    auto bt4 = _world->entity().set<cButton>({"bta4", {800, 400, 100, 50}});
    bt4.get_mut<cButton>()->applyColor(PINK);

    // bt0.get_ref<cButton>()->addListener(cchangeColor, bt0.get_ref<cButton>(), RED);
    // bt1.get_ref<cButton>()->addListener(cchangeColor, bt1.get_ref<cButton>(), BLUE);
    // bt2.get_ref<cButton>()->addListener(cchangeColor, bt2.get_ref<cButton>(), GREEN);
    // bt3.get_ref<cButton>()->addListener(cchangeColor, bt3.get_ref<cButton>(), YELLOW);
    // bt4.get_ref<cButton>()->addListener(deleteButton, bt4.get_ref<cButton>(), this);
    // bt4.get_ref<cButton>()->addListener([](){ std::cout << "Heheszki\n"; });

    this->addModule(bt0.get_mut<cButton>());
    this->addModule(bt1.get_mut<cButton>());
    this->addModule(bt2.get_mut<cButton>());
    this->addModule(bt3.get_mut<cButton>());
    this->addModule(bt4.get_mut<cButton>());
}

MainMenu::~MainMenu()
{

}

const void MainMenu::render() const
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