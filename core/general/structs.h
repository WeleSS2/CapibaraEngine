#pragma once

#include <iostream>

/*
 * Int vector
 * Layers
 * Layers will be renderer from top to bottom (one-two-three)
 * When positions something take it into account
 * It's vecotr of 3 ints to get better logic of them when categorizing
 */
struct IV3
{
    int one;
    int two;
    int three;

    IV3() {};
    IV3(int _one, int _two, int _three)
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
struct appInfo
{
    std::string title = "";
    std::string version = "";
};