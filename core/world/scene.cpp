#include "scene.h"


cScene::cScene(flecs::world* _world, cPositionObject& _data)
    : world_(_world), cRenderObject(_data)
{
    
};

cOScene::cOScene(flecs::world* _world, cPositionObject& _data)
    : world_(_world), cRenderObject(_data)
{
    
};