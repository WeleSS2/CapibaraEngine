#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#ifdef UNICODE
#define TPSTR WPSTR
#define tchar wchar_t
#else
#define TPSTR PSTR
#define tchar char
#endif

void GetIp6();