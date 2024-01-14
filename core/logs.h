#include <iostream>
#include <filesystem>

#ifdef _WIN32
#define APPDATA_DIR() (std::getenv("APPDATA") ? std::getenv("APPDATA") : "")
#else
#define APPDATA_DIR() ""
#endif

#define Log(inType, format, ...) Logs::SaveLog(inType, std::filesystem::path(__FILE__), __func__, __LINE__, format, ##__VA_ARGS__)

enum type{
    INFO,
    WARNING,
    ERROR
};

class Logs{
public:

    // Save log to a file in default path location
    const int SaveLog(type logType, 
                       const std::filesystem::path& file,
                       const char* function,
                       int line,
                       std::string log...);
    Logs();
    Logs(std::string subPath);

    // Set subfolder for logs
    const void SetPath(std::string path);

private:
    std::string currentPath;
};