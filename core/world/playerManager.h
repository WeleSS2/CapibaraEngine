#pragma once

#include <iostream>
#include "flecs.h"
#include "renderObject.h"

/*
 * cPlayerManager
 * Singleton which manage all players in application
 * Each player has its own flecs entity
 */
class cPlayerManager
{
public:
    cPlayerManager(flecs::world* _world) {};
    ~cPlayerManager() {};
    cPlayerManager(const cPlayerManager&) = delete;
    cPlayerManager& operator=(const cPlayerManager&) = delete;
    
    static cPlayerManager* getInstance();
    
    static cPlayerManager* create(flecs::world* _world);

    /* Add player to manager */
    void addPlayer(flecs::entity* _player);
    
    /* Get player by id */
    flecs::entity* getPlayer(cID _id) const;
    
    /* Remove player from manager (Also call destructor) */
    void removePlayer(cID _id);
    
    /* Get players*/
    std::vector<flecs::entity>* getPlayers() { return &players_; }

    /* Get local player */
    flecs::entity getLocalPlayer() const { return localPlayer_; }

    /* Set local player */
    void setLocalPlayer(flecs::entity _player) { localPlayer_ = _player; }

    /* Update local player camera */
    void updateCamera();

    /* Move local player camera */
    void moveCamera();

    /* Get local player camera */
    Camera getCamera() const { return camera; }
private:
    static cPlayerManager* instance_;
    static std::once_flag flag_;
    
    std::vector<flecs::entity> players_;
    
    flecs::entity localPlayer_;

    Camera camera = { 0 };

    flecs::world* world_;
};