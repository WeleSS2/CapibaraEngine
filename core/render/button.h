#pragma once
#include <vector>
#include <functional>

#include "raylib.h"

#include "image.h"
#include "clickObject.h"
class cButton : public cRenderObject {
public:
    cButton(cButton&&) noexcept = default;
    
    cButton& operator=(cButton&&) noexcept = default;

    cButton& operator=(const cButton& other) {
        return *this;
    }

    cButton(cPositionObject& _data);

    cButton(std::shared_ptr<cPositionObject> _data);

    virtual ~cButton() noexcept = default;

    //void setPositionObject(std::shared_ptr<cPositionObject> _data);

    //std::shared_ptr<cPositionObject> getPositionObject() const;

    // Render color -> texture -> text. It need to looks correctly 
    void render() const override;

    // DO not use constructor with .set as it's cause double fire of constructor
    //void create(std::string _id, cPosSize data_);

    void applyColor(Color _color);

    void applyText(const std::string& text);

    int applyTexture(std::string id, bool rescale_ = false);

    int applyTexture(std::shared_ptr<cImage> _image);

    std::unique_ptr<cClickObject>& getClickObject();

private:
    void drawRescaleTexture();

    //std::shared_ptr<cPositionObject> data_ = nullptr;

    std::shared_ptr<cImage> image_ = nullptr;

    std::unique_ptr<cClickObject> click_ = nullptr;

    std::string text_ = "";

    Color color_ = {};

    bool colorApplied_ = false;

    bool textureApplied_ = false;

    bool textApplied_ = false;
};