#include <iostream>

#include "geom.h"

int main(int argc, char* argv[])
{
    stalg::homothety2d<double> homo1(2, stalg::point2d<double>(0, 0));
    stalg::homothety2d<double> homo2(2, stalg::point2d<double>(3, 3));
    stalg::homothety2d<double> homo3 = homo1 * homo2;
    std::cout << homo3.k_ << " " << homo3.center_.x << " " << homo3.center_.y << std::endl;
    return 0;
}
