#include <iostream>

#include "vincenty.h"

#include "../stalgconst.h"

int main(int argc, char* argv[])
{
    double F1, L1, F2, L2;
    double s, alpha1;
    // std::cout << "Test Inverse problem Vincenty." << std::endl;
    // std::cout << "Input : " << std::endl;
    // std::cin >> F1 >> L1 >> F2 >> L2;
    // std::cout << stalg::VincentyDistance(radian(F1), radian(L1), radian(F2), radian(L2)) << std::endl;



    stalg::Vincenty vin(stalg::EarthEllipsoid::KrasovskyEllipsoid());


    std::cout << "Test Direct problem Vincenty." << std::endl;
    std::cout << "Input : " << std::endl;
    std::cin >> F1 >> L1 >> s >> alpha1;
    // stalg::VincentyCoordinates(radian(F1), radian(L1), s, radian(alpha1), &F2, &L2);
    vin.calculate_coordinates(F1, L1, s, alpha1);
    std::cout << "Fi2, L2 = " << vin.latitude2() << ", " << vin.longitude2() << std::endl;
    return 0;
}
