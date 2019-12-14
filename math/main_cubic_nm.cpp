#include <iostream>

#include "cubic_nm.h"

int main(int argc, char* argv[])
{
    std::cout << stalg::CubicGetRoot<double>(0,  0,  0, -1., 1  ) << std::endl;
    std::cout << stalg::CubicGetRoot<double>(0,  0, -1, -1., 100) << std::endl;
    std::cout << stalg::CubicGetRoot<double>(0, -1,  0, -1., 1  ) << std::endl;
    std::cout << stalg::CubicGetRoot<double>(0, -1,  0, 0.5, 100) << std::endl;

    std::cout << stalg::CubicGetRoot<double>(-6, 11, -6, 0.5, 1.5) << std::endl;
    std::cout << stalg::CubicGetRoot<double>(-6, 11, -6, 1.5, 2.5) << std::endl;
    std::cout << stalg::CubicGetRoot<double>(-6, 11, -6, 2.5, 3.5) << std::endl;
//    std::cout << root = stalg::CubicGetRoot(0,  0, 0, -1, 1) << std::endl;
//    std::cout << root = stalg::CubicGetRoot(0,  0, 0, -1, 1) << std::endl;
//    std::cout << root = stalg::CubicGetRoot(0,  0, 0, -1, 1) << std::endl;
//    std::cout << root = stalg::CubicGetRoot(0,  0, 0, -1, 1) << std::endl;
//    std::cout << root = stalg::CubicGetRoot(0,  0, 0, -1, 1) << std::endl;
//    std::cout << root = stalg::CubicGetRoot(0,  0, 0, -1, 1) << std::endl;
//    std::cout << root = stalg::CubicGetRoot(0,  0, 0, -1, 1) << std::endl;

    std::cout << std::endl;

//    PrintRoots1( 0, 0, 0);
//    PrintRoots1( 0, 0,-1);
//    PrintRoots1( 0,-1, 0);
//    PrintRoots1(-1, 0, 0);
//    PrintRoots1(-6,11,-6);

    std::cout << std::endl;

    return 0;
}
