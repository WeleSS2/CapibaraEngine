#include "renderObject.h"

cRenderObject::cRenderObject(cPositionObject& _data) 
{ 
    std::cout << "Constructor   " << _data.getId().idStr << std::endl;
    data_ = std::make_shared<cPositionObject>(std::move(_data));
    std::cout << "data" << std::endl;
};

cRenderObject::cRenderObject(std::shared_ptr<cPositionObject> _data) 
    : data_(_data) 
{
    std::cout << "PTR RO" << std::endl;
};

void cRenderObject::setPositionObject(std::shared_ptr<cPositionObject> _data) 
{ 
    data_ = _data; 
};

std::shared_ptr<cPositionObject> cRenderObject::getPositionObject() const 
{ 
    return data_; 
};