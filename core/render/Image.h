#pragma once
#include <vector>
#include <functional>

#include "raylib.h"

#include "renderObject.h"

class cImage : public cRenderObject {
public:
    cImage(cPositionObject& _data);

    cImage (std::shared_ptr<cPositionObject> _data);

    virtual ~cImage() {};

    cImage(cImage&&) noexcept = default;
    
    cImage& operator=(cImage&&) noexcept = default;

    cImage& operator=(const cImage& other) {
        return *this;
    }

    //void setPositionObject(std::shared_ptr<cPositionObject> _data);

    //std::shared_ptr<cPositionObject> getPositionObject() const;

    /*
     * Render image
     */
    void render() const override;

    void updateTexture()
    {
        drawRescaleTexture();
    }

    /*
     * Apply texture
     * Rescale texture means that texture will be scaled to fit size declared
     * and will break their ratio if needed
     */
    int applyTexture(std::string id, bool rescale_ = false);

    /* 
     * Rescale texture to fit fullscreen
     */
    void setFullscreen();

private:
    void drawRescaleTexture();

    //std::shared_ptr<cPositionObject> data_ = nullptr;

    Texture2D* texture_ = nullptr;

    Rectangle* source_ = nullptr;
    Rectangle* dest_ = nullptr;

    bool rescale_ = false;

    bool textureApplied_ = false;
};