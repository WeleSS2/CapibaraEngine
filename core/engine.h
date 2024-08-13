#pragma once

#include <iostream>
#include "structs.h"

/*
 * Engine
 * Main class and access point for other classes if 
 * they do not have Managers
 * Thread safe singleton
 * TODO: THread save methods
 */
class Engine 
{
public:

	Engine() {};
	~Engine() {};

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	Engine(Engine&&) = delete;
	Engine& operator=(Engine&&) = delete;

	static Engine* getInstance();

	const appInfo& getAppInfo() const;
protected:
	static Engine* engineInstance_;

	static std::once_flag flag_;

    appInfo appInfo_;
};