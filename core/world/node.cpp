#include "node.h"

cNode::cNode(flecs::world* _world, flecs::entity* _parent)
    : world_(_world), parent_(_parent)
{
    //if(_parent.has<cDepth>())
    //{
    //    std::cout << "Parent has depth " << _parent.get<cDepth>()->depth  << std::endl;
    //}
}

bool cNode::pushNode(flecs::entity* _node)
{
    if (nodes_.size() < 4) 
    {
        if (_node->has<cDepth>())
        {
            //std::cout << "Node has depth " << _node->get<cDepth>()->depth << std::endl;
        }

        nodes_.emplace_back(_node);

        return true;
    }
    
    return false;
}

bool cNode::updateNode()
{
    int posA = 0, posB = 0;
    
    for (auto i : nodes_)
    {
        if (i->get<cRenderFlags>()->value & cRenderFlags::Iterate)
        {
            if (posA > 2)
            {
                // DOLOG
                return false;
            }


            int width = i->get<cSize>()->width / 2;
            int height = i->get<cSize>()->height / 2;

            flecs::entity* node = new flecs::entity(world_->entity()
                .set<cNode>({world_, i})
                .emplace<cRenderFlags>(16)
                .set<cSize>({width, height})
                .set<cPosition>({posA * width, posB * height})
                .set<cDepth>({i->get<cDepth>()->depth + 1, i->get<cDepth>()->maxDepth})
            );
            // Push entity to node
            i->get_mut<cNode>()->pushNode(node);

            posA++;
            if (posA == 2)
            {
                posB++;
                
                posA = 0;
            }

            if (posB == 2)
            {
                // DOLOG
                return true;
            }
        }    
    }
}