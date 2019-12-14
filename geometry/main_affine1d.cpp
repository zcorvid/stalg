#include <iostream>

#include "affine1d.h"

int main(int argc, char* argv[])
{
    std::cout << stalg::convert_range_nochecks<double>(2  , 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range_nochecks<double>(4  , 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range_nochecks<double>(2.5, 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range_nochecks<double>(4.5, 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range_nochecks<double>(2.5, 1, 3, -1, 1)<< std::endl;
    std::cout << stalg::convert_range_nochecks<double>(8.5, 1, 3, -1, 1)<< std::endl;

    std::cout << std::endl;

    std::cout << stalg::convert_range<double>( 2  , 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>( 4  , 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>( 2.5, 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>( 4.5, 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>( 2.5, 1, 3, -1, 1)<< std::endl;
    std::cout << stalg::convert_range<double>( 8.5, 1, 3, -1, 1)<< std::endl;

    std::cout << std::endl;
//    std::cout << stalg::convert_range<double>(-0.5   , 1, 2,  0, 1)<< std::endl;

    std::cout << stalg::convert_range<double>(-2  , 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>(-4  , 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>(-2.5, 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>(-4.5, 1, 3,  0, 1)<< std::endl;
    std::cout << stalg::convert_range<double>(-2.5, 1, 3, -1, 1)<< std::endl;
    std::cout << stalg::convert_range<double>(-8.5, 1, 3, -1, 1)<< std::endl;
    return 0;
}
