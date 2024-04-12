#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define WIN
#elif __unix__
#define UNIX
#endif