#pragma once

#include <vector>
#include "flecs.h"
#include "renderObject.h"

class cScene : public cRenderObject
{
public:
    cScene(flecs::world* _world, cPositionObject& _data);
    
    virtual ~cScene() noexcept = default;

    /*
     * Set did scene should be rendered or not
     */
    void setStatus(bool _render) { render_ = _render; }

    /*
     * Get did scene is rendered or not
     */
    bool getStatus() const { return render_; }

    flecs::world* getWorld() const { return world_; }

private:
    bool render_ = false;

    flecs::world* world_;
};



// CM001 Old scene
class cOScene : public cRenderObject
{
public:
    cOScene(flecs::world* _world, cPositionObject& _data);
    
    virtual ~cOScene() noexcept = default;

    template <typename T>
    void render() const 
    {
        for (const auto& i : toRender_)
        {
            i.get_mut<T>()->render();
        }    
    }

    template <typename T>
    void addEntity(cPositionObject _data);

    //template <typename T, typename Func, typename... Args>
    //void addEntity(T _type, cPositionObject _data, Func&& _func, Args&&... _args);

    template<typename T>
    T* getEntity(cID _id)
    {
        for (const auto& i : toRender_)
        {
           if (i.get_mut<T>()->getPositionObject()->getId() == _id)
            {
                return i.get_mut<T>();
            }
        }

        return nullptr;
    }

private:
    flecs::world* world_;

    std::vector<flecs::entity> toRender_;
};

template <typename T>
void cOScene::addEntity(cPositionObject _data)
{
    toRender_.emplace_back(world_->entity().emplace<T>(_data));
};//*/