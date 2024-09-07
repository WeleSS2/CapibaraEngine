#include "scene.h"
#include "textureManager.h"
#include "raylib.h"

cScene::cScene(flecs::world* _world)
    : world_(_world)
{
    scene_ = world_->entity();
};

cScene::~cScene()
{
    // Check did ecs need something to avoid leaks
}

void cScene::addEntity(flecs::entity _entity)
{

    toRender_.emplace_back(_entity);

}

void cScene::removeEntity(flecs::entity _entity)
{
    toRender_.erase(std::remove(toRender_.begin(), toRender_.end(), _entity), toRender_.end());
}

void cScene::setPosition(cPosition _data)
{
    if (scene_.has<cPosition>())
    {
        scene_.get_mut<cPosition>()->posX = _data.posX;
        scene_.get_mut<cPosition>()->posY = _data.posY;
    }
}

cPosition* cScene::getPosition() const
{
    if (scene_.has<cPosition>())
    {
        return const_cast<cPosition*>(scene_.get<cPosition>());
    }
    else
    {
        return nullptr;
    }
}

void cScene::setStatus(bool _status)
{
    for (const auto& i : toRender_)
    {
        if (i.has<cRenderFlags>())
        {
            if (i.has<cSceneEntity>())
            {
                i.get_mut<cSceneEntity>()->scene->setStatus(_status);
            }

            if (_status)
            {
                i.get_mut<cRenderFlags>()->value |= _status;
            }
            else
            {
                i.get_mut<cRenderFlags>()->value &= _status;
            }
        }
    }

    if (scene_.has<cRenderFlags>())
    {
        if (_status)
        {
            scene_.get_mut<cRenderFlags>()->value |= _status;
        }
        else
        {
            scene_.get_mut<cRenderFlags>()->value &= _status;
        }
    }
}

bool cScene::getStatus() const
{
    if (scene_.has<cRenderFlags>())
    {
        return scene_.get<cRenderFlags>()->Visible;
    }

    // TODO throw error false is also correct on return so we can use 
    // int sand convert or just throw error and terminate program or restart
    // scene
    // What i think should be better as if return isn't true or false
    // A whole scene is corrupted. 
}

void cScene::setID(cID _id)
{
    if (scene_.has<cID>())
    {
        scene_.get_mut<cID>()->idNum = _id.idNum;
        scene_.get_mut<cID>()->idStr = _id.idStr;
    }
}

cID* cScene::getID() const
{
    if (scene_.has<cID>())
    {
        return const_cast<cID*>(scene_.get<cID>());
    }
    else
    {
        return nullptr;
    }
}
