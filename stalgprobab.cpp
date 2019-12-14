// stalg probability source

#include <cstdlib>

#include <stalgrandom.h>

#include <stalgprobab.h>

namespace stalg
{
    bool TryBernoulli(const double p_parameter)
    {
        int rand_number = rand();
        if (rand_number <= RAND_MAX * p_parameter)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool TryBernoulli(const int p_numerator, const int p_denominator)
    {
        int rand_number = CRandomNumber(0, p_denominator);
        if (rand_number <= p_numerator)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
