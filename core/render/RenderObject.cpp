#include "renderObject.h"

cRenderObject::cRenderObject(cPositionObject _data) 
{ 
    data_ = std::make_shared<cPositionObject>(std::move(_data));
};

cRenderObject::cRenderObject(std::shared_ptr<cPositionObject> _data) 
    : data_(_data) 
{

};

void cRenderObject::setPositionObject(std::shared_ptr<cPositionObject> _data) 
{ 
    data_ = _data; 
};

std::shared_ptr<cPositionObject> cRenderObject::getPositionObject() const 
{ 
    return data_; 
};