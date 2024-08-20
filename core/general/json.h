#pragma once

#include <iostream>
#include <variant>
#include <unordered_map>

//        TODO!!! Broken currently

/*
 * Load json file and return VariantUnMap
 * VariantUnMap is a map of keys and values to evade using json everywhere
 * Basically json values are moved here
 */
typedef std::unordered_map<std::string, std::variant<std::string, double>> VariantUnMap;

/*
 * Load json file from path and return VariantUnMap
 * Path can be relative or absolute
 * Relative is %appdata%/CapibaraStudio/$title$
 * TO user relative use $ character on the start of the path
 */
std::unique_ptr<VariantUnMap> loadFile(std::string_view _path);