#include <iostream>
#include <vector>

#include "stalgstatistics.h"

int main()
{
    std::vector<double> mas1 = {1, 2, 3, 4, 5, 6.1, 7, 8, 9, 10};
    std::vector<double> mas2(10, 9.1);
    std::vector<double> mas3 = {8.32, 8.45, 8.41, 8.44, 8.45, 8.19, 8.34, 8.35, 8.39, 8.33};
    std::vector<double> mas4 = {8.32, 8.45, 8.41, 240.8, 8.45, 8.19, 8.34, 8.35, 8.39, 8.33};
    std::vector<double> mas5 = {1., 1., 1., 5., 5., 5., 10., 10., 10.};
    std::vector<double> mas6 = {1., 5., 10.};
    std::vector<double> mas = mas6;
    // std::cout << "#stalg::Sum                  = " << stalg::Sum(mas1.begin(), mas1.end(), 0.) << std::endl;
    // std::cout << "#stalg::SumOfPowers1         = " << stalg::SumOfPowers(mas1.begin(), mas1.end(), 1, 0.) << std::endl;
    // std::cout << "#stalg::SumOfPowers2         = " << stalg::SumOfPowers(mas1.begin(), mas1.end(), 2, 0.) << std::endl;
    // std::cout << "#stalg::SumOfPowers3         = " << stalg::SumOfPowers(mas1.begin(), mas1.end(), 3, 0.) << std::endl;
    // std::cout << "#stalg::AverageValue         = " << stalg::AverageValue(mas1.begin(), mas1.end(), 0.) << std::endl;
    // std::cout << "#stalg::statistics::Moment1  = " << stalg::statistics::Moment(mas1.begin(), mas1.end(), 1, 0.) << std::endl;
    // std::cout << "#stalg::statistics::Moment2  = " << stalg::statistics::Moment(mas1.begin(), mas1.end(), 2, 0.) << std::endl;
    // std::cout << "#stalg::statistics::Moment3  = " << stalg::statistics::Moment(mas1.begin(), mas1.end(), 3, 0.) << std::endl;
    std::cout << "#stalg::statistics::Mean     = " << stalg::statistics::Mean(mas.begin(), mas.end(), 0.) << std::endl;
    // std::cout << "#stalg::statistics::Variance = " << stalg::statistics::Variance(mas1.begin(), mas1.end(), 0.) << std::endl;
    std::cout << stalg::statistics::tukey_mean(mas.begin(), mas.end(), 0.) << std::endl;
    return 0;
}

