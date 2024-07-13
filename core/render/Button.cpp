#include "button.h"
#include "textureManager.h"

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
        if (!rescale)
        {
            DrawTexture(*texture_, this->posSize_.posX, this->posSize_.posY, WHITE);
        }
        else
        {
            DrawTexturePro(*texture_, *source, *dest, { 0.0f, 0.0f }, 0.0f, WHITE);
        }
    }

    if (textApplied)
    {
        // TODO
    }
}

void cButton::click()
{
    for (auto& listener : listeners) {
        listener();
    }
}

bool cButton::clickCheck(int x, int y) const
{
    if (x <= this->posSize_.posX 
        || x >= this->posSize_.posX + this->posSize_.width 
        || y <= this->posSize_.posY 
        || y >= this->posSize_.posY + this->posSize_.height)
    {
        return false;
    }

    return true;
}

const void cButton::applyColor(Color _color) {
    color_ = _color;
    colorApplied = true;
}

const void cButton::applyText(const std::string& _text) {
    text_ = _text;
    textApplied = true;
}

const void cButton::applyTexture(const std::string& id, bool rescale_) {
    texture_ = TextureManager::getManager()->getTextureById(id);

    rescale = rescale_;

    if (rescale)
    {
        drawRescaleTexture();
    }
    
    textureApplied = true;
}

const void cButton::drawRescaleTexture() {
    source = new Rectangle{ 0.0f, 0.0f, (float)texture_->width, (float)texture_->height };
    dest = new Rectangle{ 
        (float)this->posSize_.posX,
        (float)this->posSize_.posY,
        (float)( this->posSize_.width),
        (float)( this->posSize_.height) 
    };
}

const void cButton::applyTexture(Texture2D* _texture) {
    texture_ = _texture;
    textureApplied = true;
}
