#include "MainMenu.h"


#include <memory>


MainMenu::MainMenu(flecs::world* _world, cPositionObject& _data)
    : cScene(_world, _data)
{   
    createButton({ {"bt", 0}, {800, 0, 100, 50}, {0, 0, 1} });
    createButton({ {"bt", 1}, {800, 100, 100, 50}, {0, 0, 1} });
    createButton({ {"bt", 2}, {800, 200, 100, 50}, {0, 0, 1} });
    createButton({ {"bt", 3}, {800, 300, 100, 50}, {0, 0, 1} });
    createButton({ {"bt", 4}, {800, 400, 100, 50}, {0, 0, 1} });

    //toRender_[0].get_ref<cButton>()->getMouseObject()->addListener(cchangeColor, bt0.get_ref<cButton>(), RED);
    toRender_[0].get_mut<cButton>()->getMouseObject()->addListener({"c", 0}, 
    [](){ 
        std::cout << "Heheszki\n"; 
    
        //Engine::getInstance()->enableScene({"map", 0});
    });

    toRender_[0].get_mut<cButton>()->getMouseObject()->addListener({"c", 1}, [](){ std::cout << "Different listener : P\n"; });
    toRender_[0].get_mut<cButton>()->applyText("Play");
    toRender_[1].get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 1\n"; });
    toRender_[2].get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 2\n"; });
    toRender_[3].get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ std::cout << "Heheszki 3\n"; });
    toRender_[4].get_mut<cButton>()->applyText("Quit");
    toRender_[4].get_ref<cButton>()->getMouseObject()->addListener({"c", 0}, [](){ CloseWindow(); std::cout << "Heheszki 4\n"; });

    cPositionObject po = {{"bg", 0}, {0, 0, 1920, 1080}, {0, 0, 0}};

    bg_ = getWorld()->entity().emplace<cImage>(po);
    bg_.get_mut<cImage>()->applyTexture("bg2.png", true);
}

void MainMenu::render() const
{
    bg_.get_mut<cImage>()->render();

    for (const auto& i : toRender_)
    {
        i.get_mut<cButton>()->render();
    }
}

void MainMenu::createButton(cPositionObject _data)
{
    toRender_.emplace_back(getWorld()->entity().emplace<cButton>(_data));

    toRender_.back().get_mut<cButton>()->applyColor(PINK);
}