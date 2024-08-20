#pragma once

#include "TextureManager.h"
#include "Button.h"
#include "flecs.h"
#include <vector>

class MainMenu : public cRenderObject
{
public:
    MainMenu(flecs::world *_world, cPositionObject& _data);

    ~MainMenu() noexcept = default;

    MainMenu(MainMenu&&) noexcept = default;

    MainMenu& operator=(MainMenu&&) noexcept = default;

    void render() const override;

private:
    void createButton(flecs::entity& ent, cPositionObject _data);

    flecs::world* world_;

    std::vector<flecs::entity> toRender_;
};