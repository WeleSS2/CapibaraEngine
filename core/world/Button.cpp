#include "button.h"
#include "textureManager.h"

cButton::cButton(cPositionObject& _data)
    : cRenderObject(_data)
{

};

cButton::cButton(std::shared_ptr<cPositionObject> _data)
    : cRenderObject(_data)
{
   
};

void cButton::render() const
{
    if (colorApplied_)
    {
        DrawRectangle(
            getPositionObject()->getPosSize().posX, 
            getPositionObject()->getPosSize().posY,
            getPositionObject()->getPosSize().width, 
            getPositionObject()->getPosSize().height, 
            color_);
    }

    if (textureApplied_)
    {
        image_->updateTexture();

        image_->render();
    }

    if (textApplied_)
    {
        DrawText(text_.c_str(), textPosX_, textPosY_, 20, WHITE);
    }
};

void cButton::applyColor(Color _color) 
{
    color_ = _color;
    colorApplied_ = true;
};

void cButton::applyText(const std::string& _text) 
{
    int textWidth = MeasureText(_text.c_str(), 20);
    int textHeight = 20;

    textPosX_ = getPositionObject()->getPosSize().posX + (getPositionObject()->getPosSize().width - textWidth) / 2;
    textPosY_ = getPositionObject()->getPosSize().posY + (getPositionObject()->getPosSize().height - textHeight) / 2;

    text_ = _text;
    textApplied_ = true;
};

int cButton::applyTexture(std::string _id, bool _rescale) 
{
    image_ = std::make_shared<cImage>(getPositionObject());

    if(image_->applyTexture(_id, _rescale) != 0)
    {
        return -1;
    }

    textureApplied_ = true;

    return 0;
};

int cButton::applyTexture(std::shared_ptr<cImage> _image) 
{
    if (_image == nullptr)
    {
        return -1;
    }

    image_ = _image;

    textureApplied_ = true;

    return 0;
};

std::unique_ptr<cMouseObject>& cButton::getMouseObject()
{
    if (!click_)
    {
        click_ = std::make_unique<cMouseObject>(getPositionObject());
    }

    return click_;
};