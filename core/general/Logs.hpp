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
    static Logs* getInstance();

    // Save log to a file in default path location
    static const int SaveLog(type _logType, 
                       const std::filesystem::path& _file,
                       const char* _function,
                       int _line,
                       std::string _log...);
protected:
    Logs() {};

    Logs(const Logs&) = delete;
    Logs& operator=(const Logs&) = delete;

private:
    static Logs* singleton_;

    static std::once_flag flag_;

    static std::string currentPath_;
};