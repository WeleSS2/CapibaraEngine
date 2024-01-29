#pragma once

#include "object.hpp"

namespace CEngine {
    class HitboxedObject : public Object{
    public:
        HitboxedObject(V3u16 _id) : Object{_id} { };
        HitboxedObject() = delete;
        
        virtual ~HitboxedObject() = default;
    private:

    };
}