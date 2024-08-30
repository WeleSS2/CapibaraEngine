#include "engine.h"

Engine* Engine::engineInstance_ = nullptr;
std::once_flag Engine::flag_;

Engine* Engine::getInstance() { 
	if (engineInstance_ == nullptr)
	{
		std::call_once(flag_, []() { 
			engineInstance_ = new Engine(); 
		
			return 0;
		}
		);
	}
	
	return engineInstance_; 	
};

const cAppInfo& Engine::getAppInfo() const
{
    return appInfo_;
};
