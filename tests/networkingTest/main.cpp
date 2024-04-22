#include <iostream>
#include "steam_api.h"
#include "shared.hpp"
#include "Win.hpp"
#include <WS2tcpip.h> // Include the Windows Sockets API header file

#pragma comment(lib, "Ws2_32.lib") // Link with Ws2_32.lib

int test() {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Get the local host name
    char hostname[256];
    result = gethostname(hostname, sizeof(hostname));
    if (result != 0) {
        std::cerr << "gethostname failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Get the IP address corresponding to the local host name
    struct addrinfo* addrResult = nullptr;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo(hostname, nullptr, &hints, &addrResult);
    if (result != 0) {
        std::cerr << "getaddrinfo failed: " << result << std::endl;
        WSACleanup();
        return 1;
    }

    // Extract and print the IP address
    struct sockaddr_in* sockaddr_ipv4 = reinterpret_cast<struct sockaddr_in*>(addrResult->ai_addr);
    char ipAddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ipAddr, INET_ADDRSTRLEN);
    std::cout << "IP Address: " << ipAddr << std::endl;

    // Cleanup
    freeaddrinfo(addrResult);
    WSACleanup();
    return 0;
}

int main()
{
    std::cout << "Compiled 0 \n";
    
    initSteam();

    ServerFunction();

    // Get the Steam user ID
    CSteamID steamUserID = SteamUser()->GetSteamID();
    std::cout << "Steam User ID: " << steamUserID.ConvertToUint64() << std::endl;

    // Shut down Steam API
    SteamAPI_Shutdown();

    std::cout << "Compiled \n";

    test();

    GetIp6();

    while(1);

    return 0;
}