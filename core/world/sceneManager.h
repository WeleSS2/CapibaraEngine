#pragma once

#include "scene.h"
#include "flecs.h"


class cSceneManager
{
public:
    cSceneManager(flecs::world* _world);
    ~cSceneManager();

    cSceneManager(const cSceneManager&) = delete;
    cSceneManager& operator=(const cSceneManager&) = delete;

    static cSceneManager* getInstance();

    void addScene(cScene* _scene);

    cScene* getScene(cID _id) const;

    void removeScene(cID _id);

    int setStatus(cID _id, bool _status);
private:

    static cSceneManager* instance_;

    static std::once_flag flag_;

    std::vector<cScene*> scenes_;

    static flecs::world* world_;
};