#include "image.h"
#include "textureManager.h"

cImage::cImage(cPositionObject _data)
    : cRenderObject(_data)
{
    data_ = std::make_shared<cPositionObject>(std::move(_data));
};

cImage::cImage(std::shared_ptr<cPositionObject> _data)
    : cRenderObject(_data)
{
    data_ = _data;
};

void cImage::render() const
{
    if (textureApplied_)
    {
        if (!rescale_)
        {
            DrawTexture(*texture_, 
                data_->getPosSize().posX, 
                data_->getPosSize().posY, WHITE);
        }
        else
        {
            DrawTexturePro(*texture_, *source_, *dest_, { 0.0f, 0.0f }, 0.0f, WHITE);
        }
    }
}

void cImage::applyTexture(std::string& _id, bool _rescale) {
    texture_ = TextureManager::getInstance()->getTextureById(_id);

    rescale_ = _rescale;

    if (rescale_)
    {
        drawRescaleTexture();
    }
    
    textureApplied_ = true;
}

void cImage::setFullscreen() {
    data_->setPosSize({0, 0, GetScreenWidth(), GetScreenHeight()});

    drawRescaleTexture();

    rescale_ = true;
}


void cImage::drawRescaleTexture() {
    source_ = new Rectangle{ 0.0f, 0.0f, (float)texture_->width, (float)texture_->height };

    dest_ = new Rectangle{ 
        (float) data_->getPosSize().posX,
        (float) data_->getPosSize().posY,
        (float) data_->getPosSize().width,
        (float) data_->getPosSize().height 
    };
}