#pragma once

#include "renderObject.hpp"
#include <vector>
#include <memory>

class Scene : public RenderObject 
{
public:
    Scene(V3u16 _id) : RenderObject{_id} {};

    const void render() override {}; 
private:
    std::vector<std::unique_ptr<RenderObject>> objects_;
};