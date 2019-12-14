#include <iostream>
#include <vector>

#include "rungekutta4.h"

double Foo(const double x)
{
    return x*x;
}

int main(int argc, char* argv[])
{
    const int N = 2000000;
    double h = 1. / N;
    std::vector<double> mas;
    double arg = 0.;
    for (int i = 0; i < 2 * N + 1; ++i)
    {
        arg = i * 1. / (2 * N + 1);
        mas.push_back(Foo(arg));
    }

    std::cout << "Integral [0, 1] = " << stalg::rungekutta4(mas.data(), mas.data() + mas.size(), h) << std::endl;

    return 0;
}
