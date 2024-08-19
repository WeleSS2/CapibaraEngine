#include "clickObject.h"

cClickObject::cClickObject(cPositionObject _data) 
{
    data_ = std::make_shared<cPositionObject>(std::move(_data));
};

cClickObject::cClickObject(std::shared_ptr<cPositionObject> _data) 
    : data_(_data) 
{
    
};

void cClickObject::setPositionObject(std::shared_ptr<cPositionObject> _data) 
{ 
    data_ = _data; 
};

std::shared_ptr<cPositionObject> cClickObject::getPositionObject() const 
{ 
    return data_; 
};

void cClickObject::click() {
    for (auto& i : listeners_) {
        i.second();
    }
};

void cClickObject::executeListeners(const cID& id) {
    for (auto& i : listeners_) {
        if (i.first == id) {
            i.second();
        }
    }
};

bool cClickObject::mouseCheck(int x, int y) const {
    if (x <= data_->getPosSize().posX
        || x >= data_->getPosSize().posX + data_->getPosSize().width
        || y <= data_->getPosSize().posY
        || y >= data_->getPosSize().posY + data_->getPosSize().height)
    {
        return false;
    }

    return true;
};

