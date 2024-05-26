#include "Json.hpp"
#include "Logs.hpp"

#include "nlohmann/json.hpp"

#include <fstream>
#include <vector>
#include <filesystem>

using json = nlohmann::json;

std::unique_ptr<VariantUnMap> loadFile(std::string& path)
{
    if (!std::filesystem::exists(std::filesystem::path(path)))
    {
        ERRORLOG("File do not exist!");

        return NULL;
    }

    VariantUnMap map;

    std::unique_ptr<VariantUnMap> ptr;

    std::ifstream file(path);

    json data;

    file >> data;

    file.close();
    /*
    for (auto& [key, value] : data.items())
    {
        if (value.is_string())
        {
            map.insert(key, value.get<std::string>());
        }
        else if (value.is_number())
        {
            double val = value.get<double>();
            //map.insert(key, val);
        }
        else
        {
            ERRORLOG("Unknown value type imported from file");
        }
    }

*/
    return std::make_unique<VariantUnMap>(map);

};
