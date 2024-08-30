#include "settings.h"
#include "logs.h"
#include "json.h"
#include "../engine.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define ERROR
#define WARN
#define INFO



#ifdef ERROR
#define LogError(format, ...) Logs::SaveLog(eERROR, std::filesystem::path(__FILE__), __func__, __LINE__, format, ##__VA_ARGS__)
#else
#define LogError(format, ...)
#endif

#ifdef WARN
#define LogWarn(format, ...) Logs::SaveLog(eWARNING, std::filesystem::path(__FILE__), __func__, __LINE__, format, ##__VA_ARGS__)
#else
#define LogWarn(format, ...)
#endif

#ifdef INFO
#define LogInfo(format, ...) Logs::SaveLog(eINFO, std::filesystem::path(__FILE__), __func__, __LINE__, format, ##__VA_ARGS__)
#else
#define LogInfo(format, ...)
#endif

namespace fs = std::filesystem;

Settings::Settings()
{
    mainPath = "";
};

Settings::~Settings()
{

}

std::string Settings::getPath()
{
    if (mainPath != "")
    {
        return mainPath;
    }
};

void Settings::setPath(std::string& path)
{
    mainPath = path;
}

int Settings::findSettings()
{
    std::string defPath = "";
    
    if (mainPath != "")
    {
        defPath = mainPath;
    }
    else
    {
    
    #ifdef _WIN32
        if(APPDATA_DIR() == "")
        {
            LogWarn("Appdata do not exist?!");

            return -1;
        }

        //defPath = std::string(APPDATA_DIR()) + "/CapibaraEngine/" + Engine::getEngine()->getTitle() + "/Settings";
    #elif __unix__
        //defPath = "~/.config/CapibaraEngine/" + Engine::getEngine()->getTitle() + "/Settings";
    #endif
    
    }

    if(!fs::exists(fs::path(defPath)))
    {
        if(fs::create_directories(defPath))
        {
            mainPath = defPath;

            return openSettingsFile(defPath + "/Settings.json");
        }
        else
        {
            LogError("Failed to create settings directory");
            
            return -1;
        }
    }
    else
    {
        if (fs::exists(fs::path(defPath + "/settings.json")))
        {
            mainPath = defPath;

            return 0;
        }
        else
        {
            return openSettingsFile(defPath + "/Settings.json");
        }
    }

    LogError("Total error at checking path for settings");

    return -1;
}

int Settings::openSettingsFile(std::string& path)
{
    std::ofstream file(path);
            
    if (file.is_open())
    {
        file.close();
    
        return 0;
    }

    LogError("Failed to create settings file");

    return -1;
}

void Settings::loadSettings()
{

}
