#include "Singleton.hpp"

class Engine : CEngine::DPatterns::Singleton<Engine>
{
public:

	Engine();
	~Engine();

	//static Engine* getEngine(){ return getInstance(); };

    const std::string &getTitle();
private:

    std::string title = "";
};