#include <memory.h>
#include <vector>

#include "SDL.h"

#include "Singleton.hpp"
#include "Multistructs.hpp"
#include "renderObject.hpp"

namespace CEngine {
    class Engine : public CEngine::DPatterns::Singleton<Engine> {
    public:
        Engine(SDL_Renderer* _renderer, SDL_Window* _window)
        : renderer_{_renderer}, window_{_window} {};

        static Engine* getInstance()
        {
            return Singleton<Engine>::getInstance();
        };

        SDL_Renderer* getRenderer()
        {
            return renderer_;
        };

        SDL_Window* getWindow()
        {
            return window_;
        };

    private:

        void startMainLoop();

        void rerender();

        SDL_Renderer* renderer_ = NULL;

        SDL_Window* window_ = NULL;

        std::vector<std::unique_ptr<RenderObject>> freeObjects_;


    };
}
