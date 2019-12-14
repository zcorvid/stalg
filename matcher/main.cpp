#include "nnmatcher_external.h"

#include <math.h>
#include <iostream>
#include <functional>
#include <vector>

#include "../stalgiostream.h"

double dist(double a, double b)
{
    // a = b;
    return fabs(a - b);
}

class custom_distance
{
public:
    custom_distance() {}
    double operator () (const int& x, const int& y) {
        return dist(x, y);
    }
};

int main()
{
    // stalg::NNMatcherExternal<int> matcher([](const int& x, const int& y){ return abs((x - y)*(x - y));});
    stalg::NNMatcherExternal<int> matcher;
    matcher.Classify({2, 45, 55, 99}, {0, 50, 100}, 6.1, 1);
    matcher.Report();
    matcher.Classify({1, 45, 55, 99, 2}, {0, 50, 100}, 6.1, false);
    matcher.Report();

	return 0;
}

