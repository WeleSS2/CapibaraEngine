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
    //bool operator==(const cID _id) const { return ((idStr == _id.idStr) && (idNum == _id.idNum)); };

};

/*
 * Screen scale
 * Fill on start of the program
 */
struct cScreenScale
{
    static int scaleW;
    static int scaleH;

    static int getScaleW() { if (scaleW == 0) return -1; return scaleW; };
    static int getScaleH() { if (scaleH == 0) return -1; return scaleH; };

    static void setScale(int _w, int _h) { scaleW = _w; scaleH = _h; };
};