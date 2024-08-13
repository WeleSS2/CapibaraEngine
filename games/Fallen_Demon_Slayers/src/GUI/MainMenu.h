#pragma once

#include "TextureManager.h"
#include "Button.h"
#include "flecs.h"
#include <vector>

class MainMenu : public cRenderObject
{
public:
    MainMenu(flecs::world *_world);

    ~MainMenu();

    void render() const override;

    void remove(flecs::ref<cButton> bt);

    const void addModule(cButton* _object);

private:
    std::vector<cButton*> toRender;
};