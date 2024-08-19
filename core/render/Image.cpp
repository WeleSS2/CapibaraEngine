#include "image.h"
#include "textureManager.h"

cImage::cImage(cPositionObject& _data)
    : cRenderObject(_data)
{
    //getPositionObject() = std::make_shared<cPositionObject>(std::move(_data));
};

cImage::cImage(std::shared_ptr<cPositionObject> _data)
    : cRenderObject(_data)
{
    //data_ = _data;
};

void cImage::render() const
{
    if (textureApplied_)
    {
        if (!rescale_)
        {
            DrawTexture(*texture_, 
                getPositionObject()->getPosSize().posX, 
                getPositionObject()->getPosSize().posY, WHITE);
        }
        else
        {
            DrawTexturePro(*texture_, *source_, *dest_, { 0.0f, 0.0f }, 0.0f, WHITE);
        }
    }
}

int cImage::applyTexture(std::string& _id, bool _rescale) {
    texture_ = TextureManager::getInstance()->getTextureById(_id);

    if (texture_ == nullptr)
    {
        return -1; 

        std::cout << "Texture not found" << std::endl;
    }

    rescale_ = _rescale;

    if (rescale_)
    {
        drawRescaleTexture();
    }
    
    textureApplied_ = true;

    return 0;
}

void cImage::setFullscreen() {
    getPositionObject()->setPosSize({0, 0, GetScreenWidth(), GetScreenHeight()});

    drawRescaleTexture();

    rescale_ = true;
}


void cImage::drawRescaleTexture() {
    source_ = new Rectangle{ 0.0f, 0.0f, (float)texture_->width, (float)texture_->height };

    dest_ = new Rectangle{ 
        (float) getPositionObject()->getPosSize().posX,
        (float) getPositionObject()->getPosSize().posY,
        (float) getPositionObject()->getPosSize().width,
        (float) getPositionObject()->getPosSize().height 
    };
}