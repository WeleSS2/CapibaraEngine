#include "logs.h"

#include <fstream>
#include <cstdarg>
#include <stdio.h>
#include <cstdlib>

Logs::Logs()
{

}

const int Logs::SaveLog(type logType, 
                  const std::filesystem::path& file,
                  const char* function,
                  int line,
                  std::string log...)
{
    std::string logInfo;

    switch (logType)
    {
        case INFO:
            logInfo = "INFO";
            break;
        case WARNING:
            logInfo = "WARNING";
            break;
        case ERROR:
            logInfo = "ERROR";
            break;
    };

    namespace sf = std::filesystem;

    va_list args;
    va_start(args, log);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), log.c_str(), args);

    va_end(args);

#ifdef _WIN32
    if(APPDATA_DIR() == "")
    {
        return 0;
    }

    std::string defPath = std::string(APPDATA_DIR()) + "/CapibaraStudio/Logs" + currentPath;
#else
    std::string defPath = "/var/log/CapibaraStudio/Logs" + currentPath;
#endif

    if(!sf::exists(sf::path(defPath)))
    {
        sf::create_directories(defPath);
    }

    defPath += "/" + file.filename().generic_string();

    if(file.filename().extension() == ".h")
    {
        defPath.erase(defPath.length() - 1, 1);
        defPath.append("log");
    }
    else if (file.filename().extension() == ".cpp")
    {
        defPath.replace(defPath.length() - 3, 3, "log");
    }
    
    std::fstream out(defPath, std::ios_base::out | std::ios_base::app);

    if(out.is_open())
    {
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

const int Logs::SetPath(std::string path)
{
    currentPath = path;
}