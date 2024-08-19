#pragma once

#include <iostream>
#include <memory>
#include "structs.h"

/*
 * Base class for all positionable objects:
 *   cPositionObject() {};
 *
 *   cPositionObject(cID _id, const cPosSize& _data) 
 *       : id_(_id), posSize_(_data) {};
 *
 *   cPositionObject(const cPositionObject& _data, const cIV3& _layer) 
 *       : id_(_data.id_), posSize_(_data.posSize_), layer_(_layer) {};
 */
class cPositionObject
{
public:
    cPositionObject() {};

    cPositionObject(cID _id, const cPosSize& _data) 
        : id_(_id), posSize_(_data) {};

    cPositionObject(cID _id, const cPosSize& _data, const cIV3& _layer) 
        : id_(_id), posSize_(_data), layer_(_layer) {};

    cPositionObject(const cPositionObject& _data)
        : id_(_data.id_), posSize_(_data.posSize_), layer_(_data.layer_) {};

    virtual ~cPositionObject() {};

    const cPosSize& getPosSize() const { return posSize_; }

    void setPosSize(const cPosSize& _data) { posSize_ = _data; }

    const cID getId() const { return id_; }

    void setId(const cID _data) { id_ = _data; }

    const cIV3& getLayer() const { return layer_; }

    void setLayer(const cIV3& _data) { layer_ = _data; }

private:
    cID id_;

    cPosSize posSize_;

    cIV3 layer_ = { 0, 0, 0 };
};