#pragma once
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#define APPDATA_DIR() (std::getenv("APPDATA") ? std::getenv("APPDATA") : "")
#else
#define APPDATA_DIR() ""
#endif

#define INFOLOG(format, ...) Logs::SaveLog(eINFO, std::filesystem::path(__FILE__), __func__, __LINE__, format, ##__VA_ARGS__)

#define WARNLOG(format, ...) Logs::SaveLog(eWARNING, std::filesystem::path(__FILE__), __func__, __LINE__, format, ##__VA_ARGS__)

#define ERRORLOG(format, ...) Logs::SaveLog(eERROR, std::filesystem::path(__FILE__), __func__, __LINE__, format, ##__VA_ARGS__)

enum type{
    eINFO,
    eWARNING,
    eERROR
};

class Logs{
public:

    // Save log to a file in default path location
    static const int SaveLog(type logType, 
                       const std::filesystem::path& file,
                       const char* function,
                       int line,
                       std::string log...);
    Logs();
private:
    std::string currentPath;
};