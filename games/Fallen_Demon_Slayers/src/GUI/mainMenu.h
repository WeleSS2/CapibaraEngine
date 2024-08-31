#pragma once

#include "scene.h"
#include "flecs.h"
#include <vector>

class MainMenu : public cScene
{
public:
    MainMenu(flecs::world *_world);

    virtual ~MainMenu() noexcept = default;

    MainMenu(MainMenu&&) noexcept = default;

    MainMenu& operator=(MainMenu&&) noexcept = default;

    void addButton(flecs::world* _world, int _i, std::string _text);

    void addButton2(flecs::world* _world, int _i, std::string _text);

    void addButton3(flecs::world* _world, int _i, std::string _text);
};
