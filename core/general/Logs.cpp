#include "logs.hpp"
#include "../Engine.hpp"

#include <fstream>
#include <cstdarg>
#include <stdio.h>
#include <cstdlib>

#define DEBUGLOG

Logs* Logs::singleton = nullptr;
std::once_flag Logs::flag;
std::string Logs::currentPath;

Logs* Logs::getInstance()
{
    if (singleton == nullptr)
    {
        std::call_once(flag, []() 
        { 
            #ifdef _WIN32
            
                #ifdef DEBUGLOG
                std::cout << "Appdata error \n";
                #endif
            
                if(APPDATA_DIR() == "")
                {
                    return -1;
                }
            
                currentPath = std::string(APPDATA_DIR()) + "/CapibaraEngine/Logs";// + Engine::getEngine()->getTitle() + "/Logs";
            
            #else
                currentPath = "/var/log/CapibaraEngine/Logs";// + Engine::getEngine()->getTitle() + "/Logs";
            #endif
            
            #ifdef DEBUGLOG
            std::cout << "Test path: " << currentPath << "\n";
            #endif
            
            singleton = new Logs(); 
        }
        );
    }

    return singleton;
}

const int Logs::SaveLog(type logType, 
                  const std::filesystem::path& file,
                  const char* function,
                  int line,
                  std::string log...)
{
    if (singleton == nullptr)
    {
        Logs::getInstance();
    }

    if (singleton == nullptr)
    {
        return -1; 
    }

    #ifdef DEBUGLOG
    std::cout << "Input \n" << currentPath << "\n";
    #endif

    std::string logInfo;

    switch (logType)
    {
        case eINFO:
            logInfo = "INFO";
            break;
        case eWARNING:
            logInfo = "WARNING";
            break;
        case eERROR:
            logInfo = "ERROR";
            break;
    };

    namespace sf = std::filesystem;

    va_list args;
    va_start(args, log);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), log.c_str(), args);

    va_end(args);

    if(!sf::exists(sf::path(currentPath)))
    {
        sf::create_directories(currentPath);
    }

    currentPath += "/" + file.filename().generic_string();

    if(file.filename().extension() == ".h")
    {
        currentPath.erase(currentPath.length() - 1, 1);
        currentPath.append("log");
    }
    else if (file.filename().extension() == ".cpp" || file.filename().extension() == ".hpp")
    {
        currentPath.replace(currentPath.length() - 3, 3, "log");
    }
    
    std::fstream out(currentPath, std::ios_base::out | std::ios_base::app);

    if(out.is_open())
    {
        #ifdef DEBUGLOG
        std::cout << logInfo
            << " | "
            << "File: "
            << file
            << " | "
            << "Function: "
            << function
            << " | "
            << "Line: "
            << line
            << " | "
            << buffer
            << std::endl;
        #endif
        out << logInfo
            << " | "
            << "File: "
            << file
            << " | "
            << "Function: "
            << function
            << " | "
            << "Line: "
            << line
            << " | "
            << buffer
            << std::endl;
    }

    out.close();

    return 0;
}