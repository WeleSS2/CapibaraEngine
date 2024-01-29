#pragma once

#include <iostream>
#include "multistructs.hpp"

namespace CEngine {
    class Object {
    public:
        Object(V3u16 _id) : id_{_id} {};
        
        Object(const Object &other) : id_(other.getId()) {};
        
        Object() = delete;

        const V3u16& getId() const noexcept { return id_; }
    private:
        V3u16 id_;
    };
};