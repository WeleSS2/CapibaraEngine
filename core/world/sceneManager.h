#pragma once

#include "scene.h"
#include "flecs.h"

/*
 * cSceneManager
 * Singleton which manage all scenes in application
 * Each scene has its own flecs entity
 */
class cSceneManager
{
public:
    cSceneManager(flecs::world* _world);
    ~cSceneManager();

    cSceneManager(const cSceneManager&) = delete;
    cSceneManager& operator=(const cSceneManager&) = delete;

    static cSceneManager* getInstance();

    /* Add scene to manager */
    void addScene(cScene* _scene);

    /* Get scene by id */
    cScene* getScene(cID _id) const;

    /* Remove scene from manager (Also call destructor) */
    void removeScene(cID _id);

    /* Get scenes*/
    std::vector<cScene*>* getScenes() { return &scenes_; }
private:

    static cSceneManager* instance_;

    static std::once_flag flag_;

    std::vector<cScene*> scenes_;

    static flecs::world* world_;
};