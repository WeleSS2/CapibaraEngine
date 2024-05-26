#include <iostream>
#include "Json.hpp"
#include "Logs.hpp"

int main()
{
    std::string path = "file.json";

    std::unique_ptr<VariantUnMap> map = loadFile(path);

    return 0;
}