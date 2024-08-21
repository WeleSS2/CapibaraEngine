#pragma once
#include <vector>
#include <functional>

#include "raylib.h"

#include "image.h"
#include "mouseObject.h"
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
    void move()
    {
            // Get the screen width and height
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Generate a random direction (up, down, left, right)
    int directionX = (rand() % 2 == 0) ? -1 : 1;
    int directionY = (rand() % 2 == 0) ? -1 : 1;

    // Generate a random movement amount
    int randomX = rand() % 5 + 1; // Random movement between 1 and 5
    int randomY = rand() % 5 + 1; // Random movement between 1 and 5

    // Update position
    int _x = getPositionObject()->getPosSize().posX + directionX * randomX;
    int _y = getPositionObject()->getPosSize().posY + directionY * randomY;

    // Ensure the button doesn't move outside the screen
    _x = std::max(0, std::min(_x, screenWidth - getPositionObject()->getPosSize().width));
    _y = std::max(0, std::min(_y, screenHeight - getPositionObject()->getPosSize().height));

    getPositionObject()->setPosSize({_x, _y, getPositionObject()->getPosSize().width, getPositionObject()->getPosSize().height});
    }

    void applyColor(Color _color);

    void applyText(const std::string& text);

    int applyTexture(std::string id, bool rescale_ = false);

    int applyTexture(std::shared_ptr<cImage> _image);

    std::unique_ptr<cMouseObject>& getMouseObject();

private:
    void drawRescaleTexture();

    //std::shared_ptr<cPositionObject> data_ = nullptr;

    std::shared_ptr<cImage> image_ = nullptr;

    std::unique_ptr<cMouseObject> click_ = nullptr;

    std::string text_ = "";

    int textPosX_ = 0;

    int textPosY_ = 0;

    Color color_ = {};

    bool colorApplied_ = false;

    bool textureApplied_ = false;

    bool textApplied_ = false;
};