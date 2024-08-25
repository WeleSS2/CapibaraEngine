#include "renderManager.h"
#include "renderObject.h"
#include "raylib.h"

cRenderManager* cRenderManager::instance_ = nullptr;
std::once_flag cRenderManager::flag_;
flecs::world* cRenderManager::world_ = nullptr;

cRenderManager::cRenderManager(flecs::world* _world)
{
    world_ = _world;

    if (world_ == nullptr) // LOG001  
    {   
        std::cout << "World is null" << std::endl;
    };
};

cRenderManager::~cRenderManager()
{

};

cRenderManager* cRenderManager::getInstance()
{
    if (instance_ == nullptr)
    {
        std::call_once(flag_, []() 
            { 
                instance_ = new cRenderManager(world_);
            }
        );
    }

    return instance_;
}

void cRenderManager::render(flecs::entity_view _entity) const
{
    if (_entity.has<cRenderFlags>())
    {
        if (_entity.get<cRenderFlags>()->visible)
        {
            // Check if colored
            renderColorRectangle(_entity);

            // Check if texture applied
            renderTexture(_entity);

            // Render text
            renderText(_entity);
        }
    }
}


void cRenderManager::renderColorRectangle(flecs::entity_view _entity) const
{
    if (_entity.has<cColor>())
    {
        DrawRectangle(_entity.get<cPosition>()->posX,
            _entity.get<cPosition>()->posY,
            _entity.get<cSize>()->width,
            _entity.get<cSize>()->height,
            _entity.get<cColor>()->color);
    }
}


void cRenderManager::renderTexture(flecs::entity_view _entity) const
{
    if (_entity.has<Texture2D>())
    {
        if (_entity.get<cRenderFlags>()->modify)
        {
            DrawTexturePro(*_entity.get<Texture2D>(),
                { 0.0f, 0.0f, (float)_entity.get<Texture2D>()->width,
                    (float)_entity.get<Texture2D>()->height},
                { (float)_entity.get<cPosition>()->posX,
                    (float)_entity.get<cPosition>()->posY,
                  (float)_entity.get<cSize>()->width,
                    (float)_entity.get<cSize>()->height},
                { 0.0f, 0.0f }, _entity.get<cRotation>()->rot, WHITE);
        }
        else 
        {
            DrawTexture(*_entity.get<Texture2D>(),
                         _entity.get<cPosition>()->posX,
                        _entity.get<cPosition>()->posY, WHITE);
        }
    }
}

void cRenderManager::renderText(flecs::entity_view _entity) const
{
    if (_entity.has<cText>())
    {
        if (_entity.get<cText>()->center)
        {
            int textLength = MeasureText(_entity.get<cText>()->text.c_str(),
                                         _entity.get<cText>()->size);

            DrawTextEx(GetFontDefault(), _entity.get<cText>()->text.c_str(),
                {(float)_entity.get<cPosition>()->posX + 
                ((_entity.get<cSize>()->width - textLength) / 2),
                (float)_entity.get<cPosition>()->posY + 
                ((_entity.get<cSize>()->height - _entity.get<cText>()->size) / 2)},
                _entity.get<cText>()->size, 0.0f,
                _entity.get<cText>()->color);
        }
        else
        {
            DrawText(_entity.get<cText>()->text.c_str(),
                _entity.get<cPosition>()->posX,
                _entity.get<cPosition>()->posY,
                _entity.get<cText>()->size,
                _entity.get<cText>()->color);
        }
    }
}