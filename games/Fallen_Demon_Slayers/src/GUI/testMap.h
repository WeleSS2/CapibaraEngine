#pragma once

#include <iostream>
#include "map.h"


class TestMap : public cMap
{
public:
    TestMap(flecs::world* _world);
    virtual ~TestMap() noexcept = default;

    TestMap(TestMap&&) noexcept = default;

    TestMap& operator=(TestMap&&) noexcept = default;

    void spawnTile(flecs::world* _world,
        int _id,
        std::pair<int, int> _pos,
        cColor* _color);

    void spawnDefault(flecs::world* _world);

    void spawnOnX(flecs::world* _world);

    void spawnOnY(flecs::world* _world);

    void setNeg(bool _status);
private:
    int val = 64;

    bool neg = false ;

    std::pair<int, int> borderLR{0, 0};

    std::pair<int, int> borderTB{0, 0};
};