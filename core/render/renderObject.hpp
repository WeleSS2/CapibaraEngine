#pragma once

#include "object.hpp"

namespace CEngine {
    class RenderObject : public Object
    {
    public:
        RenderObject(V3u16 _id) : Object{_id} { };
        
        RenderObject() = delete;
        
    protected:
        virtual const void render() = 0;

    };
}