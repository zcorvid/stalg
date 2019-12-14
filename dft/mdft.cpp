#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

#include "../stalgiostream.h"

#include "dft.h"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::vector<std::complex<double>> mas;
    const int N = 32;
    for (int i = 0; i < N; ++i)
    {
        mas.push_back(  std::polar(1.,   6 * 2 * stalg::pi * i / N)
//                      + std::polar(2., -3 * 2 * stalg::pi * i / N)
//                      + std::polar(3., -5 * 2 * stalg::pi * i / N)
                        );
    }
//    stalg::fft(mas.data(), N);
//    stalg::fft(mas.begin(), mas.end());
//    stalg::fft(mas);
//    std::cout << stalg::abs_mas_normed(mas) << std::endl;
    std::cout << stalg::abs_mas_normed(stalg::get_fft(mas)) << std::endl;
    return 0;
}
