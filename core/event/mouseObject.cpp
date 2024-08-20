#include "mouseObject.h"

cMouseObject::cMouseObject(cPositionObject _data) 
{
    data_ = std::make_shared<cPositionObject>(std::move(_data));
};

cMouseObject::cMouseObject(std::shared_ptr<cPositionObject> _data) 
    : data_(_data) 
{
    
};

void cMouseObject::setPositionObject(std::shared_ptr<cPositionObject> _data) 
{ 
    data_ = _data; 
};

std::shared_ptr<cPositionObject> cMouseObject::getPositionObject() const 
{ 
    return data_; 
};

void cMouseObject::executeListeners(const cID& id) {
    for (auto& i : listeners_) {
        if (i.first == id) {
            i.second();
        }
    }
};

bool cMouseObject::mouseCheck(int x, int y) const {
    if (x <= data_->getPosSize().posX
        || x >= data_->getPosSize().posX + data_->getPosSize().width
        || y <= data_->getPosSize().posY
        || y >= data_->getPosSize().posY + data_->getPosSize().height)
    {
        return false;
    }

    return true;
};

