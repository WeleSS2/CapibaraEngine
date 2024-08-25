#pragma once

#include <vector>
#include "flecs.h"
#include "renderObject.h"


class cScene
{
public:
    cScene(flecs::world* _world);

    virtual ~cScene();

    virtual void addEntity(flecs::entity _entity);

    virtual void removeEntity(flecs::entity _entity);

    void setPosition(cPosition _data);

    cPosition* getPosition() const;

    void setStatus(bool _status);

    bool getStatus() const;

    void setID(cID _id);

    cID* getID() const;

    flecs::entity getScene() const { return scene_; };

    flecs::entity getEntity(cID _id) const 
    { 
        for (auto i : toRender_) 
        {
            if (*i.get_mut<cID>() == _id)
            {
                return i;
            }; 
        };
    };

    flecs::world* getWorld() const { return world_; };

private:
    flecs::world* world_;

    flecs::entity scene_;

    std::vector<flecs::entity> toRender_;
};