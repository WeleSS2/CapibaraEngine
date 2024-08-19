#include "button.h"
#include "textureManager.h"

cButton::cButton(cPositionObject& _data)
    : cRenderObject(_data)
{
    std::cout << "Button" << std::endl;
    //data_ = std::make_shared<cPositionObject>(std::move(_data));
    //std::cout << "data" << std::endl;

};

cButton::cButton(std::shared_ptr<cPositionObject> _data)
    : cRenderObject(_data)
{
    //std::cout << "PTR" << std::endl;
};

//void cButton::create(std::string _id, cPosSize data_)
//{
//    id_ = _id;
//    posSize_ = data_;
//}

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
        image_->render();
    }

    if (textApplied_)
    {
        // TODO
    }
};

void cButton::applyColor(Color _color) {
    color_ = _color;
    colorApplied_ = true;
};

void cButton::applyText(const std::string& _text) {
    text_ = _text;
    textApplied_ = true;
};

void cButton::applyTexture(std::string& _id, bool _rescale) 
{
    image_ = std::make_shared<cImage>(getPositionObject());

    image_->applyTexture(_id, _rescale);

    textureApplied_ = true;
};

void cButton::applyTexture(std::shared_ptr<cImage> _image) 
{
    image_ = _image;

    textureApplied_ = true;
};

std::unique_ptr<cClickObject>& cButton::getClickObject()
{
    std::cout << "getClickObject" << std::endl;
    if (!click_)
    {
        std::cout << "make_unique" << std::endl;
        click_ = std::make_unique<cClickObject>(getPositionObject());
    }

    return click_;
};