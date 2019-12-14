// stalg random source

#include <cstdlib>
#include <time.h>

#include <stalgrandom.h>

namespace stalg
{
    void InitCRandomizer(const unsigned int seed)
    {
        srand(seed);
    }

    int CRandomNumber(const int min_val, const int max_val)
    {
        return min_val + (max_val - min_val) * (rand() * 1. / RAND_MAX);
    }

    double CRandomDouble(const double min_val, const double max_val)
    {
        return min_val + (max_val - min_val) * (rand() * 1. / RAND_MAX);
    }
}
