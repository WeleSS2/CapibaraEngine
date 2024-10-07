#pragma once
#include <iostream>
#include <filesystem>
#include <format>
#include <source_location>
#include <print>
#include <string>
#include <fstream>
#include "spdlog/spdlog.h"

#ifdef _WIN32
static const char* OS = "win";
#else
static const char* OS = "unix";
#endif

/*
 * Logs types:
 *   trace = SPDLOG_LEVEL_TRACE,
 *   debug = SPDLOG_LEVEL_DEBUG,
 *   info = SPDLOG_LEVEL_INFO,
 *   warn = SPDLOG_LEVEL_WARN,
 *   err = SPDLOG_LEVEL_ERROR,
 *   critical = SPDLOG_LEVEL_CRITICAL,
 *   off = SPDLOG_LEVEL_OFF,
 */
class Logs{
public:
    static Logs* getInstance();

    template <typename CharT, typename... Args>
    struct basicString : std::basic_format_string<CharT, Args...> {
        template <typename T>
        consteval basicString(const T& fmt, const std::source_location loc = std::source_location::current())
        : std::basic_format_string<CharT, Args...>{fmt}, loc{loc} {};
        
        std::source_location loc;
    };

    template <typename... Args>
    using cString = basicString<char, std::type_identity_t<Args>...>;

    /*
     * Set current path
     * do not paste a path just a name which is in available pathes.
     * default is named as "def"
     */
    void setCurrentPath(std::string name);

    void createDefaultPath(bool setAsCurrent = true);

    void addPath(std::string name, std::string path);

    bool getConsoleLogs()
    {
        return consoleLogs_;
    };

    void setConsoleLogs(bool _consoleLogs)
    {
        consoleLogs_ = _consoleLogs;
    };

    template <typename... Args>
    void saveToFile(int type, const cString<Args...> str, Args&&... args);

    template <typename... Args>
    void printLog(int type, const cString<Args...> str, Args&&... args);

    template <typename... Args>
    static constexpr void Trace(const cString<Args...> str, Args&&... args);

    template <typename... Args>
    static constexpr void Debug(const cString<Args...> str, Args&&... args);

    template <typename... Args>
    static constexpr void Info(const cString<Args...> str, Args&&... args);

    template <typename... Args>
    static constexpr void Warn(const cString<Args...> str, Args&&... args);

    template <typename... Args>
    static constexpr void Error(const cString<Args...> str, Args&&... args);

    template <typename... Args>
    static constexpr void Critical(const cString<Args...> str, Args&&... args);
protected:
    Logs() {};

    Logs(const Logs&) = delete;
    Logs& operator=(const Logs&) = delete;

private:
    bool consoleLogs_;

    std::filesystem::path* currentPath_ = nullptr;

    std::vector<std::pair<std::string, std::filesystem::path*>> paths_;

    static Logs* singleton_;

    static std::once_flag flag_;
};

template <typename... Args>
void Logs::saveToFile(int type, const cString<Args...> str, Args&&... args)
{
    std::string tpStr;

    switch (type)
    {
        case SPDLOG_LEVEL_TRACE:
            tpStr = "LOG_TRACE";
            break;
        case SPDLOG_LEVEL_DEBUG:
            tpStr = "LOG_DEBUG";
            break;
        case SPDLOG_LEVEL_INFO:
            tpStr = "LOG_INFO";
            break;
        case SPDLOG_LEVEL_WARN:
            tpStr = "LOG_WARN";
            break;
        case SPDLOG_LEVEL_ERROR:
            tpStr = "LOG_ERROR";
            break;
        case SPDLOG_LEVEL_CRITICAL:
            tpStr = "LOG_CRITICAL";
            break;
    }

    if (currentPath_ != nullptr)
    {
        std::fstream file(*currentPath_, std::ios_base::out | std::ios_base::app);

        if (file.is_open()) 
        {
            file << tpStr 
                << " | File " << str.loc.file_name() 
                << " | Fn " << str.loc.function_name() 
                << " | Ln " << str.loc.line() 
                << " | Col " << str.loc.column() 
                << " | Log " << std::format(str, std::forward<Args>(args)...)
                << std::endl;
            
            file.close();
        }
    }
}

template <typename... Args>
void Logs::printLog(int type, const cString<Args...> str, Args&&... args)
{
    const char* tpStr;
    switch (type)
    {
        case SPDLOG_LEVEL_TRACE:
            tpStr = "LOG_TRACE";
            break;
        case SPDLOG_LEVEL_DEBUG:
            tpStr = "LOG_DEBUG";
            break;
        case SPDLOG_LEVEL_INFO:
            tpStr = "LOG_INFO";
            break;
        case SPDLOG_LEVEL_WARN:
            tpStr = "LOG_WARN";
            break;
        case SPDLOG_LEVEL_ERROR:
            tpStr = "LOG_ERROR";
            break;
        case SPDLOG_LEVEL_CRITICAL:
            tpStr = "LOG_CRITICAL";
            break;
    }

    println("{} : File - {} : Fn - {} : Ln - {} : Col - {} : Log - {}",
        tpStr, str.loc.file_name(), str.loc.function_name(),
        str.loc.line(), str.loc.column(), std::format(str, std::forward<Args>(args)...)
        );
}

template <typename... Args>
static constexpr void Logs::Trace(const cString<Args...> str, Args&&... args)
{
    Logs::getInstance()->saveToFile(SPDLOG_LEVEL_TRACE, str, std::forward<Args>(args)...);

    if (Logs::getInstance()->getConsoleLogs())
    {
        Logs::getInstance()->printLog(SPDLOG_LEVEL_TRACE, str, std::forward<Args>(args)...);
    }
}

template <typename... Args>
static constexpr void Logs::Debug(const cString<Args...> str, Args&&... args)
{
    Logs::getInstance()->saveToFile(SPDLOG_LEVEL_DEBUG, str, std::forward<Args>(args)...);

    if (Logs::getInstance()->getConsoleLogs())
    {
        Logs::getInstance()->printLog(SPDLOG_LEVEL_DEBUG, str, std::forward<Args>(args)...);
    }
}

template <typename... Args>
static constexpr void Logs::Info(const cString<Args...> str, Args&&... args)
{
    Logs::getInstance()->saveToFile(SPDLOG_LEVEL_INFO, str, std::forward<Args>(args)...);

    if (Logs::getInstance()->getConsoleLogs())
    {
        Logs::getInstance()->printLog(SPDLOG_LEVEL_INFO, str, std::forward<Args>(args)...);
    }
}

template <typename... Args>
static constexpr void Logs::Warn(const cString<Args...> str, Args&&... args)
{
    Logs::getInstance()->saveToFile(SPDLOG_LEVEL_WARN, str, std::forward<Args>(args)...);

    if (Logs::getInstance()->getConsoleLogs())
    {
        Logs::getInstance()->printLog(SPDLOG_LEVEL_WARN, str, std::forward<Args>(args)...);
    }
}

template <typename... Args>
static constexpr void Logs::Error(const cString<Args...> str, Args&&... args)
{
    Logs::getInstance()->saveToFile(SPDLOG_LEVEL_ERROR, str, std::forward<Args>(args)...);

    if (Logs::getInstance()->getConsoleLogs())
    {
        Logs::getInstance()->printLog(SPDLOG_LEVEL_ERROR, str, std::forward<Args>(args)...);
    }
}

template <typename... Args>
static constexpr void Logs::Critical(const cString<Args...> str, Args&&... args)
{
    Logs::getInstance()->saveToFile(SPDLOG_LEVEL_CRITICAL, str, std::forward<Args>(args)...);

    if (Logs::getInstance()->getConsoleLogs())
    {
        Logs::getInstance()->printLog(SPDLOG_LEVEL_CRITICAL, str, std::forward<Args>(args)...);
    }
}