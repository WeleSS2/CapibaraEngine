#include "json.h"
#include "logs.h"

#include "nlohmann/json.hpp"

#include <fstream>
#include <vector>
#include <filesystem>

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


using json = nlohmann::json;

std::unique_ptr<VariantUnMap> loadFile(std::string_view _path)
{
    if (!std::filesystem::exists(std::filesystem::path(_path)))
    {
        LogError("File do not exist!", _path);

        return NULL;
    }

    VariantUnMap map;

    std::unique_ptr<VariantUnMap> ptr;

    std::ifstream file(_path.data());

    json data;

    file >> data;

    file.close();
    
    for (auto& [key, value] : data.items())
    {
        if (value.is_string())
        {
            map.insert(std::make_pair( key, value.get<std::string>()));
        }
        else if (value.is_number())
        {
            map.insert(std::make_pair(key, value.get<double>()));
        }
        else
        {
            LogError("Unknown value type imported from file");
        }
    }

    return std::make_unique<VariantUnMap>(map);

};
