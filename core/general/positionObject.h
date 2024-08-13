#pragma once

#include <iostream>
#include <memory>
#include "structs.h"

/*
 * Base class for all positionable objects:
 *   cPositionObject() {};
 *
 *   cPositionObject(int _id, const cPosSize& _data) 
 *       : id_(_id), posSize_(_data) {};
 *
 *   cPositionObject(const cPositionObject& _data, const IV3& _layer) 
 *       : id_(_data.id_), posSize_(_data.posSize_), layer_(_layer) {};
 */
class cPositionObject
{
public:
    cPositionObject() {};

    cPositionObject(int _id, const cPosSize& _data) 
        : id_(_id), posSize_(_data) {};

    cPositionObject(int _id, const cPosSize& _data, const IV3& _layer) 
        : id_(_id), posSize_(_data), layer_(_layer) {};

    cPositionObject(const cPositionObject& _data)
        : id_(_data.id_), posSize_(_data.posSize_), layer_(_data.layer_) {};

    virtual ~cPositionObject() {};

    const cPosSize& getPosSize() const { return posSize_; }

    void setPosSize(const cPosSize& _data) { posSize_ = _data; }

    const int getId() const { return id_; }

    void setId(const int _data) { id_ = _data; }

    const IV3& getLayer() const { return layer_; }

    void setLayer(const IV3& _data) { layer_ = _data; }

private:
    int id_ = 0;

    cPosSize posSize_;

    IV3 layer_ = { 0, 0, 0 };
};