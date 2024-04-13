#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#ifdef UNICODE
#define PTSTR PWSTR
#define tchar wchar_t
#else
#define PTSTR PSTR
#define tchar char
#endif

void GetIp6();