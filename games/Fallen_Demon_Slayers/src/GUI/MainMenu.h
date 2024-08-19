#pragma once

#include "TextureManager.h"
#include "Button.h"
#include "flecs.h"
#include <vector>

class MainMenu : public cRenderObject
{
public:
    MainMenu(MainMenu&&) noexcept = default;

    MainMenu& operator=(MainMenu&&) noexcept = default;

    MainMenu(flecs::world *_world, cPositionObject& _data);

    ~MainMenu() noexcept = default;

    void render() const override;

    void remove(flecs::ref<cButton> bt);

    const void addModule(cButton* _object);

private:
    std::vector<cButton*> toRender;
};