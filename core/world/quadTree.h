#pragma once

#include "node.h"

/*
 * cQuadTree
 * 0 - NW
 * 1 - NE
 * 2 - SW
 * 3 - SE
 */
class cQuadTree
{
public:
    cQuadTree(flecs::world* _world, int _width, int _height, int _depth);
    ~cQuadTree() noexcept = default;

    cQuadTree(cQuadTree&&) noexcept = default;
    cQuadTree& operator=(cQuadTree&&) noexcept = default;

    bool generateDefault(int currentDepth);

    //void addEntity(flecs::entity _entity);

    std::vector<flecs::entity> getEntities() const;

    flecs::entity getOrigin() const { return origin_; };

private:
    flecs::world* world_;

    flecs::entity origin_;

    cPosition targetPosition_;
};