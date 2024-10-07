#include "quadTree.h"

cQuadTree::cQuadTree(flecs::world* _world, int _width, int _height, int _depth)
    : world_(_world)
{
    //std::cout << "Generating quad tree" << std::endl;
    origin_ = _world->entity()
        .emplace<cNode>(world_, &origin_)
        .set<cRenderFlags>({16})
        .set<cSize>({_width, _height})
        .set<cPosition>({0, 0})
        .set<cDepth>({0, _depth})
        ;

    //std::cout << "Quad tree generatedAA" << std::endl; 
}

bool cQuadTree::generateDefault(int currentDepth)
{
    //std::cout << "Generating default quad tree" << std::endl;

    int posA = 0, posB = 0;
    
    while (true)
    {

        if (posA > 2)
        {
            // DOLOG Skipped while generating
            return false;
        }

        // Generate node
        int width = origin_.get<cSize>()->width / 2;
        int height = origin_.get<cSize>()->height / 2;

        flecs::entity* node = new flecs::entity(world_->entity()
            .emplace<cNode>(world_, &origin_)
            .emplace<cRenderFlags>(16)
            .set<cSize>({width, height})
            .set<cPosition>({posA * width, posB * height})
            .set<cDepth>({currentDepth, origin_.get<cDepth>()->maxDepth}));

        if (node->has<cNode>())
        {
            //std::cout << "Node created" << std::endl;
        }

        // Push entity to node
        origin_.get_mut<cNode>()->pushNode(node);
        
        // Call subnodes recursively if node have player to build origin last leaf
        //if (node.get<cPosition>()->posX >= targetPosition_.posX 
        //    && node.get<cPosition>()->posX + width < targetPosition_.posX
        //    && node.get<cPosition>()->posY >= targetPosition_.posY
        //    && node.get<cPosition>()->posY + height < targetPosition_.posY)
        //{
        //    node.get_mut<cRenderFlags>()->value |= cRenderFlags::Iterate;
        //
        //    node.get_mut<cNode>()->createNode();
        //}

        // Calculate another node
        posA++;
        
        if (posA == 2)
        {
            posA = 0;

            posB++;
        }

        if (posB == 2)
        {
            posB = 0;

            //std::cout << "Quad tree generated" << std::endl;

            return true;
        }
    }
};

