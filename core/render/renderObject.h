#pragma once

#include "structs.h"
#include "positionObject.h"

/*
 * Base class for all renderable objects
 * Have virtual method render which must be implemented
 */
class cRenderObject
{
public:
    cRenderObject(cPositionObject _data);
    
    cRenderObject(std::shared_ptr<cPositionObject> _data);

    virtual ~cRenderObject() {};

    /*
     * Render object to screen
     */
    virtual void render() const = 0;

    void setPositionObject(std::shared_ptr<cPositionObject> _data);

    std::shared_ptr<cPositionObject> getPositionObject() const;

private:
    std::shared_ptr<cPositionObject> data_ = nullptr;
};