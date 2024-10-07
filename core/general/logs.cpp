#include "logs.h"

#include <fstream>
#include <cstdarg>
#include <stdio.h>
#include <cstdlib>

#undef DEBUGLOG

Logs* Logs::singleton_ = nullptr;
std::once_flag Logs::flag_;

Logs* Logs::getInstance()
{
    
    if (singleton_ == nullptr)
    {
        std::call_once(flag_, []() 
        { 
            singleton_ = new Logs(); 
        }
        );
    }

    return singleton_;
}
/*
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
}*/

void Logs::setCurrentPath(std::string _path)
{
    if (currentPath_ != nullptr)
    {
        delete currentPath_;
    }

    currentPath_ = new std::filesystem::path(_path);
}

void Logs::createDefaultPath(bool setAsCurrent)
{
    if (currentPath_ != nullptr)
    {
        delete currentPath_;
    }

    if (std::string(OS) == "win")
    {
        if (setAsCurrent)
        {
            std::string appData = std::getenv("APPDATA");

            currentPath_ = new std::filesystem::path(appData + "/CapibaraEngine/Logs");
        }
        else
        {
            std::string appData = std::getenv("APPDATA");

            std::filesystem::path* path = new std::filesystem::path(appData + "/CapibaraEngine/Logs");
        
            paths_.push_back(std::make_pair("def", path));
        }
    }
    else
    {
        if (setAsCurrent)
        {
            currentPath_ = new std::filesystem::path("/var/log/CapibaraEngine/Logs");
        }
        else
        {
            std::filesystem::path* path = new std::filesystem::path("/var/log/CapibaraEngine/Logs");
        
            paths_.push_back(std::make_pair("def", path));
        }
    }
}

void Logs::addPath(std::string _name, std::string _path)
{
    for (auto& path : paths_)
    {
        if (path.first == _name)
        {
            delete path.second;
            
            path.second = new std::filesystem::path(_path);

            return;
        }
    }

    paths_.push_back(std::make_pair(_name, new std::filesystem::path(_path)));
}