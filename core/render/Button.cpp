#include "Button.hpp"

const void cButton::create(std::string _id, cPosSize data_)
{
    id_ = _id;
    posSize_ = data_;
}

const void cButton::render() const
{
    if (colorApplied)
    {
        DrawRectangle(this->posSize_.posX, this->posSize_.posY, this->posSize_.width, this->posSize_.height, color_);
    }

    if (textureApplied)
    {
        // TODO
    }

    if (textApplied)
    {
        // TODO
    }
}

void cButton::click()
{
    this->applyColor(RED);
    
    for (auto& listener : listeners) {
        listener();
    }
}

bool cButton::clickCheck(int x, int y) const
{
    if (x >= this->posSize_.posX 
        && x <= this->posSize_.posX + this->posSize_.width 
        && y >= this->posSize_.posY 
        && y <= this->posSize_.posY + this->posSize_.height)
    {
        return true;
    }

    return false;
}

void cButton::applyColor(Color _color) {
    color_ = _color;
    colorApplied = true;
}

void cButton::applyText(const std::string& _text) {
    text_ = _text;
    textApplied = true;
}

void cButton::applyTexture(const std::string& id) {
    // TODO
    textureApplied = true;
}

void cButton::applyTexture(Texture2D* _texture) {
    texture_ = _texture;
    textureApplied = true;
}
