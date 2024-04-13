#include <iostream>
#include "steam_api.h"
#include "shared.hpp"
#include "Win.hpp"

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

    GetIp6();

    while(1);

    return 0;
}