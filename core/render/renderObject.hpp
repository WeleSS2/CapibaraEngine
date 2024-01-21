#pragma once

#include "SDL.h"
#include "multistructs.hpp"

class RenderObject
{
public:
    RenderObject() = delete;
    RenderObject(V3u16 _id) : id_{_id} {};

    virtual const void render() = 0;

    virtual const V3u16 *getID() { return &id_; };
private:
    V3u16 id_{0, 0, 0};
};