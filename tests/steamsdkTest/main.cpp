#include <iostream>
#include "steam_api.h"

int main()
{
        std::cout << "Compiled 0 \n";
    // Initialize Steam API
    if (!SteamAPI_Init()) {
        std::cerr << "Failed to initialize Steam API!" << std::endl;
        return 1;
    }

    // Check if Steam is running
    if (!SteamAPI_IsSteamRunning()) {
        std::cerr << "Steam is not running!" << std::endl;
        return 1;
    }

    // Get the Steam user ID
    CSteamID steamUserID = SteamUser()->GetSteamID();
    std::cout << "Steam User ID: " << steamUserID.ConvertToUint64() << std::endl;

    // Shut down Steam API
    SteamAPI_Shutdown();

    std::cout << "Compiled \n";
}