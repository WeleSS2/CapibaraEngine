#include "sceneManager.h"

cSceneManager* cSceneManager::instance_ = nullptr;
std::once_flag cSceneManager::flag_;
flecs::world* cSceneManager::world_ = nullptr;

cSceneManager::cSceneManager(flecs::world* _world)
{
    world_ = _world;

    if (world_ == nullptr)
    {   // LOG001
        std::cout << "World is null" << std::endl;
    };
};

cSceneManager::~cSceneManager()
{

};

cSceneManager* cSceneManager::getInstance()
{
    if (instance_ == nullptr)
    {
        std::call_once(flag_, []() 
            { 
                instance_ = new cSceneManager(world_);
            }
        );
    }

    return instance_;
};

void cSceneManager::addScene(cScene* _scene)
{
    scenes_.push_back(_scene);
};

cScene* cSceneManager::getScene(cID _id) const
{
    for (auto i : scenes_)
    {
        if (*i->getID() == _id)
        {
            return i;
        }
    }

    return nullptr;
}

void cSceneManager::removeScene(cID _id)
{
    for (auto it = scenes_.begin(); it != scenes_.end(); ++it) 
    {
        if (*(*it)->getID() == _id) 
        {
            scenes_.erase(it);
            
            break;
        }
    }
};

int cSceneManager::setStatus(cID _id, bool _status)
{
    for (auto i : scenes_)
    {
        if (*i->getID() == _id)
        {
            std::cout << "Set Status: " << _status << std::endl;
            
            i->setStatus(_status);

            return 1;
        }
    }

    return -1;
};
