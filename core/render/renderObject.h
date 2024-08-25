#pragma once

#include <iostream>
#include <functional>
#include "structs.h"
#include "raylib.h"

struct cPosition
{
    int posX;
    int posY;
};

struct cSize
{
    int width;
    int height;
};

struct cLayer
{
    int layer;
    int layer2;
    int layer3;
};

struct cRotation
{
    float rot = 0.0f;
};

struct cRenderFlags
{
    bool visible = false;
    bool modify = false;
};

//struct cRenderFlags
//{
//    bool visible : 1;
//    bool modify : 1;
//
//    cRenderFlags(uint32_t flags) 
//        : visible(flags & 1),
//        modify(flags & 2)
//        {};
//};

struct cColor
{
    Color color;

    cColor(Color _color) 
    : color(_color) 
    {};
};

struct cText
{
    std::string text;
    int size;
    Color color;
    bool center;

    cText(std::string _text, int _size, Color _color, bool _center = true) 
        : text(_text),
        size(_size),
        color(_color),
        center(_center)
        {};
};

struct cInteraction
{
    cID id;
    std::function<void()> func;

    // Constructor
    template <typename Func, typename... Args>
    cInteraction(cID _id, Func&& _func, Args&&... _args)
        : id(_id),
          func([f = std::forward<Func>(_func), ...args = 
          std::forward<Args>(_args)]() mutable { f(args...); })
    {
    }
};
