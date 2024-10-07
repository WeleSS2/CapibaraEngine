#pragma once

#include <iostream>
#include <functional>
#include "structs.h"
#include "raylib.h"

struct cID2d
{
    std::string id;
    int x;
    int y;
};

struct cPosition
{
    int posX;
    int posY;
};

struct cRelPosition
{
    int prevX;
    int prevY;
    int posX;
    int posY;
};

struct cSize
{
    int width;
    int height;
};

struct cDepth
{
    int depth;
    
    int maxDepth;
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

/*
 * Define flags for entities
 * None      - 0 - Empty flag, can be used for idk
 * Visible   - 1 - Define did should be rendered or not
 * Modify    - 2 - Define did should be resized automatically to fit declared size
 * UnMovable - 4 - Define did should be movable dynamically
 * Active    - 8 - Define did is currently active or not
 * Node      - 16 - Define did is a node for quad tree (contain another nodes or entites)
 * Iterate   - 32 - Define did node should be iterated (Aka should create nodes below it)
 */
struct cRenderFlags
{
    enum Flags {
        None         = 0,
        Visible      = 1 << 0, // 1 
        Modify       = 1 << 1, // 2 
        UnMovable    = 1 << 2, // 4 
        Active       = 1 << 3, // 8
        Node         = 1 << 4, // 16
        Iterate      = 1 << 5  // 32
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

// Unique tags aka flags not direcly in cRenderFlags
struct cActive {}; // Intercative entity

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