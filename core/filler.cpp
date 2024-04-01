#include "filler.hpp"
#include "flecs.h"

void test()
{
    flecs::world testWorld;

    testWorld.entity("Parent").set<int>(40);
    
    std::cout << "Assad \n";
}