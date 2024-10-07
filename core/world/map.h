#pragma once

#include "scene.h"

class cMap : public cScene
{
public:
    cMap(flecs::world* _world);
    virtual ~cMap() noexcept = default;

    cMap(cMap&&) noexcept = default;

    cMap& operator=(cMap&&) noexcept = default;

    std::vector<std::vector<flecs::entity>> getMap() const
    {
        return vMap_;
    };

    

private:
    std::vector<std::vector<bool>> vScreen_;

    std::vector<std::vector<flecs::entity>> vMap_;
};