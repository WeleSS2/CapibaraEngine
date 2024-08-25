#pragma once

#include <iostream>
#include "structs.h"
#include "scene.h"

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

	void setAppInfo(const cAppInfo& _info) { appInfo_ = _info; };

	const cAppInfo& getAppInfo() const;
	
	void addScene(cScene& _scene)
	{
		scenes_.emplace_back(_scene);
	};

	/*
	int removeScene(cID _id)
	{
		for (auto it = scenes_.begin(); it != scenes_.end(); ++it)
		{
			if (it->getPositionObject()->getId() == _id)
			{
				scenes_.erase(it);
				return 0;
			}
		}

		return -1;
	};

	int enableScene(cID _id)
	{
		for (auto& i : scenes_)
		{
			if (i.getPositionObject()->getId() == _id)
			{
				i.setStatus(true);

				return 0;
			}
		}

		return -1;
	};

	int disableScene(cID _id)
	{
		for (auto& i : scenes_)
		{
			if (i.getPositionObject()->getId() == _id)
			{
				i.setStatus(false);
		
				return 0;
			}
		}

		return -1;
	};*/

protected:
	static Engine* engineInstance_;

	static std::once_flag flag_;

	std::vector<cScene> scenes_;

    cAppInfo appInfo_;
};