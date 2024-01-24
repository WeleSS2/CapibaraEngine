#pragma once

#include <memory.h>
#include <vector>

#include "SDL.h"
#include "scene.hpp"

namespace CEngine {
    class RenderManager {
    public:
        RenderManager(SDL_Renderer* _renderer, SDL_Window* _window)
        : renderer_{_renderer}, window_{_window} {};

        SDL_Renderer* getRenderer()
        {
            return renderer_;
        };

        SDL_Window* getWindow()
        {
            return window_;
        };
    private:
        SDL_Renderer* renderer_ = NULL;

        SDL_Window* window_ = NULL;

        std::vector<std::unique_ptr<RenderObject>> freeObjects_;

        std::vector<std::unique_ptr<Scene>> scenes_;
    };
}
