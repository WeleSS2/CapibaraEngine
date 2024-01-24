#pragma once

#include "Singleton.hpp"
#include "renderManager.hpp"

namespace CEngine {
    class Engine : public DPatterns::Singleton<Engine> {
    public:
        Engine(SDL_Renderer* _renderer, SDL_Window* _window)
        : renderManager_(_renderer, _window) {};

        static Engine* getInstance()
        {
            return Singleton<Engine>::getInstance();
        };
    private:

        void startMainLoop();

        void rerender();

        std::make_unique<RenderManager> renderManager_;
    };
}
