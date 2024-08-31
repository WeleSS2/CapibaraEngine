#include "testMap.h"
#include <random>

TestMap::TestMap(flecs::world* _world) : cScene(_world)
{
    getScene()
        .set<cID>({"map", 0})
        .set<cPosition>({-100, -100})
        .set<cSize>({GetScreenWidth() + 200, GetScreenHeight() + 200})
        .set<cLayer>({0, 0, 0})
        .set<cRenderFlags>({0})
        .set<cRotation>({0.0f})
    ;

    spawnDefault(_world);

    addEntity(
        _world->entity().child_of(getScene())
            .set<cID>({"player", 0})
            .set<cPosition>({cScreenScale::getScaleW() * 50, cScreenScale::getScaleH() * 50})
            .set<cAbsPosition>({
                (float)cScreenScale::getScaleW() * 50,
                (float)cScreenScale::getScaleH() * 50,
                (float)cScreenScale::getScaleW() * 50,
                (float)cScreenScale::getScaleH() * 50
            })
            .set<cSize>({50, 50})
            .set<cLayer>({0, 0, 1})
            .set<cRenderFlags>({4})
            .set<cRotation>({0.0f})
            .emplace<cColor>(cColor{BLUE})
    );
}

void TestMap::spawnTile(flecs::world* _world,
    int _id, 
    std::pair<int, int> _pos,
    cColor* _color)
{
    addEntity(
        _world->entity().child_of(getScene())
            .set<cID>({"tile", _id})
            .set<cPosition>({_pos.first, _pos.second})
            .set<cSize>({val, val})
            .set<cLayer>({0, 0, 0})
            .set<cRenderFlags>({0})
            .set<cRotation>({0.0f})
            .emplace<cColor>(*_color)
    );
}

void TestMap::spawnDefault(flecs::world* _world)
{
    int mult = 1000;

    std::pair<int, int> pos(-mult, -mult);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    
    while (1)
    {
        Color color;
        color.r = dis(gen);
        color.g = dis(gen);
        color.b = dis(gen);
    
        cColor c(color);

        spawnTile(_world, 0, pos, &c);
    
        pos.first += val;

        if (pos.first > GetScreenWidth() + mult)
        {
            borderLR.second = pos.first;
            pos.first = -mult;
            pos.second += val;
        }

        if (pos.second > GetScreenHeight() + mult)
        {
            borderTB.second = pos.second;
            break;
        }
    }
}

void TestMap::spawnOnX(flecs::world* _world)
{
    //std::cout << "Enter X\n";
    
    if (neg)
    {
        borderLR.first += val;
        borderLR.second += val;
    }
    else
    {
        borderLR.first -= val;
        borderLR.second -= val;
    }

    int i = borderTB.first;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    
    while (1)
    {
        Color color;
        color.r = dis(gen);
        color.g = dis(gen);
        color.b = dis(gen);
    
        cColor c(color);        

        std::cout << "Spawning on " << borderLR.first << " - " << i << "\n";

        if (neg)
        {
            spawnTile(_world, 0, std::make_pair(borderLR.second - val, i), &c);
        }
        else
        {
            spawnTile(_world, 0, std::make_pair(borderLR.first + val, i), &c);
        }

        this->setStatus(true);

        i += val;

        if (i > borderTB.second - borderTB.first)
            break;
    }
}

void TestMap::spawnOnY(flecs::world* _world)
{

    if (neg)
    {
        borderTB.first += val;
        borderTB.second += val;
    }
    else
    {
        borderTB.first -= val;
        borderTB.second -= val;
    }

    std::cout << "Enter Y\n";

    int i = borderLR.first;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    
    while (1)
    {
        Color color;
        color.r = dis(gen);
        color.g = dis(gen);
        color.b = dis(gen);
    
        cColor c(color);

        std::cout << "Spawning on " << i << " - " << borderTB.first << "\n";

        if (neg)
        {
            spawnTile(_world, 0, std::make_pair(i, borderTB.second), &c);
        }
        else
        {
            spawnTile(_world, 0, std::make_pair(i, borderTB.first), &c);
        }
        

        this->setStatus(true);

        i += val;

        if (i > borderLR.second - borderLR.first)
            break;
    }
}

void TestMap::setNeg(bool _status)
{
    neg = _status;
}