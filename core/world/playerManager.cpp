#include "playerManager.h"

cPlayerManager* cPlayerManager::instance_ = nullptr;
std::once_flag cPlayerManager::flag_;

cPlayerManager* cPlayerManager::getInstance() {
    if (instance_ == nullptr) {
        // log error
        return nullptr;
    }

    return instance_;
}

cPlayerManager* cPlayerManager::create(flecs::world* _world) {
    std::call_once(flag_, [&] {
        instance_ = new cPlayerManager(_world);
    });
    return instance_;
}

void cPlayerManager::addPlayer(flecs::entity* _player) {
    players_.push_back(*_player);
}

flecs::entity* cPlayerManager::getPlayer(cID _id) const {
    for (auto i : players_) {
        if (*i.get_mut<cID>() == _id) {
            return &i;
        }
    }

    flecs::entity a;
    
    // print error
    return nullptr;
}

void cPlayerManager::removePlayer(cID _id) {
    int a = 0;
    for (auto i : players_) {
        if (*i.get_mut<cID>() == _id) {
            players_.erase(players_.begin() + a);
            break;
        }
        a++;
    }
}

void cPlayerManager::updateCamera() {
    // Define the camera to look into our 3D world
    // +32f to keep it in center, - bsc only it work. Idk why
    camera.position = { (float)localPlayer_.get<cPosition>()->posX + 32.0f,
                        (float)localPlayer_.get<cPosition>()->posY + 32.0f, -500.0f };
    camera.target = { (float)localPlayer_.get<cPosition>()->posX + 32.0f,
                        (float)localPlayer_.get<cPosition>()->posY + 32.0f, 0.0f };
    camera.up = { 0.0f, -1.0f, 0.0f };
    camera.fovy = (float)GetScreenHeight();
    camera.projection = CAMERA_ORTHOGRAPHIC;

}

void cPlayerManager::moveCamera() {
    camera.target = {
        (float)localPlayer_.get<cPosition>()->posX + 32.0f,
        (float)localPlayer_.get<cPosition>()->posY + 32.0f,
        0.0f
    };
    camera.position = {
        (float)localPlayer_.get<cPosition>()->posX + 32.0f,
        (float)localPlayer_.get<cPosition>()->posY + 32.0f,
        -500.0f
    };
}