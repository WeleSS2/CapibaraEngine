#include "example.hpp"
#include "logs.hpp"
#include "SDL.h"
#include "spdlog/spdlog.h"

#define INFO

#ifndef INFO
#undef INFOLOG
#define INFOLOG(format, ...) (void())
#endif

#ifndef WARN
#undef WARNLOG
#define WARNLOG(format, ...) (void())
#endif

#ifndef ERROR
#undef ERRORLOG
#define ERRORLOG(format, ...) (void())
#endif


int didEqual(int a, int b)
{
    std::cout << "Huh AAAA\n";

    INFOLOG("Test\n");

    spdlog::info("Hello, {}!","World");

    return 0;
}

std::string working()
{
    return "Assad";
}