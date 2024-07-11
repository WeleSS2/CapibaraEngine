#include "json.hpp"
#include "logs.hpp"

#include "nlohmann/json.hpp"

#include <fstream>
#include <vector>
#include <filesystem>

using json = nlohmann::json;

std::unique_ptr<VariantUnMap> loadFile(std::string_view path)
{
    if (!std::filesystem::exists(std::filesystem::path(path)))
    {
        std::cout << "Path is: " << path << std::endl;
        ERRORLOG("File do not exist!", path);

        return NULL;
    }

    VariantUnMap map;

    std::unique_ptr<VariantUnMap> ptr;

    std::ifstream file(path.data());

    json data;

    file >> data;

    file.close();
    
    for (auto& [key, value] : data.items())
    {
        if (value.is_string())
        {
            map.insert(std::make_pair(key, value.get<std::string>()));
        }
        else if (value.is_number())
        {
            map.insert(std::make_pair(key, value.get<double>()));
        }
        else
        {
            ERRORLOG("Unknown value type imported from file");
        }
    }

    return std::make_unique<VariantUnMap>(map);

};
