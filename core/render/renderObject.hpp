#pragma once

#include "multistructs.hpp"

namespace CEngine {
    class RenderObject
    {
    protected:
        RenderObject(V3u16 _id) : id_{_id} {};
        RenderObject() = delete;

        virtual const void render() = 0;

        virtual const V3u16 *getID() { return &id_; };
    private:
        V3u16 id_{0, 0, 0};
    };
}