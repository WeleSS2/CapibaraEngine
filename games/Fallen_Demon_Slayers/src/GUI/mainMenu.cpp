#include "mainMenu.h"
#include "raylib.h"
#include "textureManager.h"
#include "sceneManager.h"
#include "../testMap.h"

#include <memory>

MainMenu::MainMenu(flecs::world* _world)
    : cScene(_world)
{
    getScene()
        .set<cID>({"mm", 0})
        .set<cPosition>({0, 0})
        .set<cSize>({GetScreenWidth(), GetScreenHeight()})
        .set<cLayer>({0, 0, 0})
        .set<cRenderFlags>({3})
        .set<cRotation>({0.0f})
        .set<Texture2D>(*(TextureManager::getInstance()->getTextureById("bg2.png")))
        .set<cSceneEntity>({this})
    ;

    
    addButton(_world, 1, "Singleplayer");
    addButton(_world, 2, "Multiplayer");
    addButton(_world, 3, "Options");
    addButton(_world, 4, "Quit");
    
    getEntity({"bt", 1}).emplace<cInteraction>(cInteraction{
        {"c", 0},
        [=]()
        { 
            cSceneManager::getInstance()->setStatus({"mm", 0}, false);

            cSceneManager::getInstance()->setStatus({"map", 0}, true);
        }
    });
    getEntity({"bt", 4}).emplace<cInteraction>(cInteraction{
       {"c", 0},
       [=]()
       {
           CloseWindow();
       } 
    });
}

void MainMenu::addButton(flecs::world* _world, int _i, std::string _text)
{
    addEntity(
    _world->entity().child_of(getScene())
        .set<cID>({"bt", _i})
        .set<cPosition>({cScreenScale::getScaleW() * 40, cScreenScale::getScaleH() * 15 * _i})
        .set<cSize>({cScreenScale::getScaleW() * 20, cScreenScale::getScaleH() * 5})
        .set<cLayer>({0, 0, 0})
        .set<cRenderFlags>({1})
        .set<cRotation>({0.0f})
        .emplace<cColor>(cColor{PINK})
        .emplace<cText>(cText{_text, 18, {0, 0, 0, 255}})
    );
}
