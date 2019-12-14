#include <iostream>
#include <vector>
#include <cmath>

#include "aver.h"

int main(int argc, char* argv[])
{
    std::vector<double> t;
    std::vector<double> x;

    srand(191217);

    for (int i = 0; i < 100; ++i)
    {
        t.push_back(i);
        x.push_back(i + 0.4 * ( (rand() * 1. / RAND_MAX) - 0.5 ) );
    }

    double d;
    int num;
    std::cout << "Enter, please, d and num: ";
    std::cin >> d >> num;

    std::vector<double> ans = plls::averager_mean(t, x, d, num);

    for (int i = 0; i < ans.size(); ++i)
    {
        std::cout << "x[" << i << "] = " << x[i] << std::endl;
    }
    std::cout << "" << std::endl;

    for (int i = 0; i < ans.size(); ++i)
    {
        std::cout << "ans[" << i << "] = " << ans[i] << std::endl;
    }
    std::cout << "" << std::endl;

    for (int i = 0; i < ans.size(); ++i)
    {
        std::cout << "s[" << i << "] = " << fabs(i - ans[i]) << std::endl;
    }

    return 0;
}
