#include "example.h"
#include "logs.h"
#include "sdl.h"

#ifdef INFO
#define INFOLOG(format, ...) Log(INFO, format, ...)
#else
#define INFOLOG(format, ...) (void())
#endif

#ifdef WARN
#define WARNLOG(format, ...) Log(WARNING, format, ...)
#else
#define WARNLOG(format, ...) (void())
#endif

#ifdef ERROR
#define ERRORLOG(format, ...) Log(ERROR, format, ...)
#else
#define ERRORLOG(format, ...) (void())
#endif


int didEqual(int a, int b)
{
    INFOLOG("->");
    if (a == b)
    {
        return 1;
    }
    else
        return 0;
}