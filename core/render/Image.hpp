#pragma once

#include "renderObject.hpp"
#include <vector>
#include <functional>
#include "raylib.h"

class cImage : private cRenderObject {
public:
    cImage() {};

    cImage (const std::string _id, const cPosSize& data_)
        : id_(_id), cRenderObject(data_) { };

    virtual ~cImage() 
    { 
        if (source) delete source;
        if (dest) delete dest;
    }

    // Render color -> texture -> text. It need to looks correctly 
    const void render() const override;

    const std::string& getId() const {return id_; };

    const void applyTexture(const std::string& id, bool rescale_ = false);

    const void drawRescaleTexture();

    const void applyTexture(Texture2D* texture_);

protected:
    std::string id_ = "";

private:
    std::string text_ = "";

    Texture2D* texture_ = nullptr;

    Rectangle* source = nullptr;
    Rectangle* dest = nullptr;

    bool rescale = false;

    bool textureApplied = false;
};