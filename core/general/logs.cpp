#include "logs.h"

#include <fstream>
#include <cstdarg>
#include <stdio.h>
#include <cstdlib>

#define DEBUGLOG

Logs* Logs::singleton_ = nullptr;
std::once_flag Logs::flag_;
std::string Logs::currentPath_;

Logs* Logs::getInstance()
{
    if (singleton_ == nullptr)
    {
        std::call_once(flag_, []() 
        { 
            #ifdef _WIN32
            
                #ifdef DEBUGLOG
                std::cout << "Appdata error \n";
                #endif
            
                if(APPDATA_DIR() == "")
                {
                    return -1;
                }
            
                currentPath_ = std::string(APPDATA_DIR()) + "/CapibaraEngine/Logs";// + Engine::getEngine()->getTitle() + "/Logs";
            
            #else
                currentPath_ = "/var/log/CapibaraEngine/Logs";// + Engine::getEngine()->getTitle() + "/Logs";
            #endif
            
            #ifdef DEBUGLOG
            std::cout << "Test path: " << currentPath_ << "\n";
            #endif
            
            singleton_ = new Logs(); 

            return 0;
        }
        );
    }

    return singleton_;
}

const int Logs::SaveLog(type _logType, 
                  const std::filesystem::path& _file,
                  const char* _function,
                  int _line,
                  std::string _log...)
{
    if (singleton_ == nullptr)
    {
        Logs::getInstance();
    }

    if (singleton_ == nullptr)
    {
        return -1; 
    }

    #ifdef DEBUGLOG
    std::cout << "Input \n" << currentPath_ << "\n";
    #endif

    std::string logInfo;

    switch (_logType)
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
    va_start(args, _log);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), _log.c_str(), args);

    va_end(args);

    #ifdef DEBUGLOG
    std::cout << buffer << "\n";
    #endif

    if(!sf::exists(sf::path(currentPath_)))
    {
        sf::create_directories(currentPath_);
    }

    currentPath_ += "/" + _file.filename().generic_string();

    if(_file.filename().extension() == ".h")
    {
        currentPath_.erase(currentPath_.length() - 1, 1);
        currentPath_.append("log");
    }
    else if (_file.filename().extension() == ".cpp" || _file.filename().extension() == ".hpp")
    {
        currentPath_.replace(currentPath_.length() - 3, 3, "log");
    }
    
    std::fstream out(currentPath_, std::ios_base::out | std::ios_base::app);

    if(out.is_open())
    {
        #ifdef DEBUGLOG
        std::cout << logInfo
            << " | "
            << "File: "
            << _file
            << " | "
            << "Function: "
            << _function
            << " | "
            << "Line: "
            << _line
            << " | "
            << buffer
            << std::endl;
        #endif
        out << logInfo
            << " | "
            << "File: "
            << _file
            << " | "
            << "Function: "
            << _function
            << " | "
            << "Line: "
            << _line
            << " | "
            << buffer
            << std::endl;
    }

    out.close();

    return 0;
}
