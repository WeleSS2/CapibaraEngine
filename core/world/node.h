#pragma once

#include "flecs.h"
#include "renderObject.h"
#include <vector>
#include <iostream>

/*
 * cNode
 * 0 - NW
 * 1 - NE
 * 2 - SW
 * 3 - SE
 */
class cNode
{
public:
    cNode(flecs::world* _world, flecs::entity* _parent);
    ~cNode() noexcept = default; // ADD CLEARING FOR NODES IMPORTANT!!!

    cNode(cNode&&) noexcept = default;
    cNode& operator=(cNode&&) noexcept = default;

    bool pushNode(flecs::entity* _node);

    bool updateNode();

    const bool printNodes() const
    {
        //std::cout << nodes_.size() << std::endl;

        for (int i = 0; i < nodes_.size(); i++)
        {
            //std::cout << "Node id is  " << i << std::endl;

            if (parent_->has<cDepth>())
            {
                //std::cout << "Current depth is" << parent_->get<cDepth>()->depth 
                //          << "And node id is" << i << std::endl;
            }

            if (parent_->has<cSize>())
            {
                //std::cout << "Current size is" << parent_->get<cSize>()->width
                //          << "And node id is" << i << std::endl;
            }

            //std::cout << "END " << i << std::endl;
        }

        return true;
    }

private:
    flecs::world* world_;

    flecs::entity* parent_;

    std::vector<flecs::entity*> nodes_;
};