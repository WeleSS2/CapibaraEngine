#include "image.hpp"
#include "textureManager.hpp"

const void cImage::render() const
{
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
}

const void cImage::applyTexture(const std::string& id, bool rescale_) {
    texture_ = TextureManager::getManager()->getTextureById(id);

    rescale = rescale_;

    if (rescale)
    {
        drawRescaleTexture();
    }
    
    textureApplied = true;
}

const void cImage::drawRescaleTexture() {
    source = new Rectangle{ 0.0f, 0.0f, (float)texture_->width, (float)texture_->height };
    dest = new Rectangle{ 
        (float)this->posSize_.posX,
        (float)this->posSize_.posY,
        (float)( this->posSize_.width),
        (float)( this->posSize_.height) 
    };
}

const void cImage::applyTexture(Texture2D* _texture) {
    texture_ = _texture;
    textureApplied = true;
}
