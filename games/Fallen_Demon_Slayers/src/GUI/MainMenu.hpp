#pragma once

#include "TextureManager.hpp"
#include "Button.hpp"
#include "flecs.h"
#include <vector>

class MainMenu : public cRenderObject
{
public:
    MainMenu(flecs::world *_world);

    ~MainMenu();

    const void render() const override;

    void remove(flecs::ref<cButton> bt);

    const void addModule(cButton* _object);

private:
    std::vector<cButton*> toRender;
};