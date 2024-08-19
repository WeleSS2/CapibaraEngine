#pragma once

#include <iostream>

/*
 * Int vector
 * Layers
 * Layers will be renderer from top to bottom (one-two-three)
 * When positions something take it into account
 * It's vecotr of 3 ints to get better logic of them when categorizing
 */
struct cIV3
{
    int one;
    int two;
    int three;

    cIV3() {};
    cIV3(int _one, int _two, int _three)
    : one(_one), two(_two), three(_three) {};
};

/* 
 * 4x16bit vector
 * Position and Size
 * Used for rendering only, for others create a new struct with different name
 * x, y, width, height
 */
struct cPosSize 
{
    int posX;
    int posY;
    int width;
    int height;

    cPosSize() {};
    cPosSize(int _posX, int _posY, int _width, int _height)
        : posX(_posX), posY(_posY), width(_width), height(_height) {};
};
/*
 * App info
 * Title and version
 */
struct cAppInfo
{
    std::string title = "";
    std::string version = "";
};

/*
 * ID for entities
 * WE use combination of string and int 
 * total of N bits but try to keep string part as small
 * as possible, this way we have huge amount of potential IDs
 * for copies of one entity type and flexible approach for different 
 * entities
 * 
 *     cID(const std::string& _idStr, int _idNum)
 *       : idStr(_idStr), idNum(_idNum) {};
 */
struct cID
{
    std::string idStr = "";
    int idNum = 0;

    cID() {};

    cID(const std::string& _idStr, int _idNum)
        : idStr(_idStr), idNum(_idNum) {};

    cID operator++() { idNum++; };
    cID operator++(int) { idNum++; return *this; };
    
    cID operator--() { idNum--; };
    cID operator--(int) { idNum--; return *this; };

    bool operator==(const cID& _id) const { return ((idStr == _id.idStr) && (idNum == _id.idNum)); };
};