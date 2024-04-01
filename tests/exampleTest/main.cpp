#include <iostream>

int main()
{
    char asd;
    std::cout << "Working here ASD \n";
    std::cin >> asd;

    int v = 20;
    int *vp = &v;
    void *vv = vp;
    int  *vpp = (int *)vv;

    std::cout << *vpp << std::endl;
}