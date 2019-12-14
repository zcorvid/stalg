#include <iostream>
#include <vector>

#include <cmath>

// #include "rungekutta4.h"
#include "integral.h"
#include "../../stalgconst.h"

double Foo(const double x)
{
    return sin(x);
}

int main(int argc, char* argv[])
{
    const int N = 2000000;
    double h = 0.5 * stalg::pi * 1. / N;
    std::vector<double> mas;
    double arg = 0.;
    for (int i = 0; i < N + 1; ++i)
    {
        arg = i * h;
        mas.push_back(Foo(arg));
    }

    std::cout << "Integral [0, 1] = " << stalg::integral_trapezoidal(mas.data(), mas.data() + mas.size(), h) << std::endl;

    return 0;
}
