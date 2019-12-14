#include <iostream>

#include "cardano.h"

int main(int argc, char* argv[])
{
    stalg::GetRealRoots<float> ( 0, 0, 0);
    stalg::GetRealRoots<float> ( 0, 0,-1);
    stalg::GetRealRoots<float> ( 0,-1, 0);
    stalg::GetRealRoots<float> (-1, 0, 0);
    stalg::GetRealRoots<float> (-6,11,-6);

    std::cout << std::endl;

//    PrintRoots1( 0, 0, 0);
//    PrintRoots1( 0, 0,-1);
//    PrintRoots1( 0,-1, 0);
//    PrintRoots1(-1, 0, 0);
//    PrintRoots1(-6,11,-6);

    std::cout << std::endl;

    return 0;
}
