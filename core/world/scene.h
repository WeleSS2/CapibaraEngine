#pragma once

#include <vector>
#include "flecs.h"
#include "renderObject.h"

/*
 * cScene
 * Default class for inheritance of scenes
 */
class cScene
{
public:
    cScene(flecs::world* _world);

    virtual ~cScene();

    /* Add entity to scene */
    virtual void addEntity(flecs::entity _entity);

    /* Remove entity from scene */
    virtual void removeEntity(flecs::entity _entity);

    /* Render entities in scene */
    virtual void renderScene();

    /* Set position of scene */
    void setPosition(cPosition _data);

    cPosition* getPosition() const;

    /* Set status of scene, status means did it is visible and active or not */
    void setStatus(bool _status, bool _subscenes = false);

    bool getStatus() const;

    /* Set if the scene is active or not */
    void setActive(bool _status, bool _subscenes = false);

    /* Set if the scene is visible or not */
    void setRender(bool _status, bool _subscenes = false);

    void setID(cID _id);

    cID* getID() const;

    /* Get scene flecs entity */
    flecs::entity getScene() const { return scene_; };

    /* Get entity from scene */
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

    /* Get world */
    flecs::world* getWorld() const { return world_; };

    /* Get vector for rendering*/
    const std::vector<flecs::entity>* getRender() { return &toRender_; };

private:
    flecs::world* world_;

    flecs::entity scene_;

    std::vector<flecs::entity> toRender_;
};