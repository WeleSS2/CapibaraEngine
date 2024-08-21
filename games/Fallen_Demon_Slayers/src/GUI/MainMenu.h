#pragma once

#include "TextureManager.h"
#include "Button.h"
#include "scene.h"
#include "flecs.h"
#include <vector>

class MainMenu : public cScene
{
public:
    MainMenu(flecs::world *_world, cPositionObject& _data);

    virtual ~MainMenu() noexcept = default;

    MainMenu(MainMenu&&) noexcept = default;

    MainMenu& operator=(MainMenu&&) noexcept = default;

    void render() const override;

private:
    void createButton(cPositionObject _data);

    std::vector<flecs::entity> toRender_;

    flecs::entity bg_;
};