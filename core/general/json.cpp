#include "json.h"
#include "logs.h"

#include "nlohmann/json.hpp"

#include <fstream>
#include <vector>
#include <filesystem>

using json = nlohmann::json;

std::unique_ptr<VariantUnMap> loadFile(std::string_view _path)
{
    if (!std::filesystem::exists(std::filesystem::path(_path)))
    {
        //LogError("File do not exist!", _path);

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
            //LogError("Unknown value type imported from file");
        }
    }

    return std::make_unique<VariantUnMap>(map);

};
