#pragma once

#include <variant>
#include "json.h"

using json = nlohmann::json;
/*
 * Settings class
 * Using json files to load and save values in folder 
 * %appdata%/CapibaraStudio/$title$/settings/$custom$.json
 * $custom$ can be anything also a additional path
 * mac / unix eq: 
 */
class Settings {
public:

    Settings();
    ~Settings();

    // Getters
    static Settings* getSettings() {return getInstance(); };

    std::string getPath();

    // Setters
    void setPath(std::string& path);

    // Methods

    /* Check did settings file exist. If not create them
     * -1 Fail
     *  0 Success
     */
    int findSettings();

    /* Load all settings
     * 
     * 
     */
    void loadSettings();

    // Save all current settings to file
    void saveSettings();

    // Iterate through directory to get all files
    void checkDirectory();

    // Open file to load all settings
    void openFile();

    // Save value into memory
    template <typename T>
    static int SaveValue(const std::string& key, T value);

    // Get settings pair from map
    template <typename T>
    static const T* LoadValue(const std::string& key);
    
private:

    int openSettingsFile(std::string& path);

    std::string mainPath = "";

    // Settings are kept here in union, always use string as name and value later
    std::unordered_map<std::string, std::variant<
                        std::string, 
                        double>> settings;


};

template <typename T>
static int Settings::SaveValue(const std::string& key, T value) {

    keyMap[key] = value;
    return 1;
}

template <typename T>
static const T* Settings::LoadValue(const std::string& name) {
    if (keyMap.count(name) > 0) {
        return reinterpret_cast<const T*>(&keyMap[name]);
    }
    else
    {
        LOG("Warn: Key '"
            + name.toStdString()
            + "' does not exist."
            );
    }

    return nullptr;
}
