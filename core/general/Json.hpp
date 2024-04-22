#include <iostream>
#include <variant>
#include <unordered_map>

typedef std::unordered_map<std::string, std::variant<std::string, double>> VariantUnMap;

std::unique_ptr<VariantUnMap> loadFile(std::string& path);