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
    enum Flags {
        None         = 0,
        Visible      = 1 << 0, // 1
        Modify       = 1 << 1, // 2
        UnMovable    = 1 << 2, // 4
        RenderedArea = 1 << 3  // 8
    };

    int value;

    cRenderFlags(int v = None) : value(v) {}

    cRenderFlags operator|(Flags flag) const 
    {
        return cRenderFlags(value | flag);
    }

    cRenderFlags& operator|(cRenderFlags flag)
    {
        value |= flag.value;
        return *this;
    }

    bool operator&(Flags flag) const
    {
        return (value & flag) == flag;
    }

    bool operator==(int v) const 
    {
        return value == v;
    }

    bool operator!=(int v) const
    {
        return value != v;
    }
};

class cScene;

struct cSceneEntity
{
    cScene* scene = nullptr;
};

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
