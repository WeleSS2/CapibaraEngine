#include <iostream>

class Engine 
{
public:

	Engine();
	~Engine();

	//static Engine* getEngine(){ return getInstance(); };

    const std::string &getTitle();
private:

    std::string title = "";
};