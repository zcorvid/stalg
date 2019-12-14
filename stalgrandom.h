#ifndef __ST_ALG_RANDOM_H__
#define __ST_ALG_RANDOM_H__

// stalg random
// 2.08.2016

// Генераторы случайных чисел.

namespace stalg
{
    void InitCRandomizer(const unsigned int seed);

    int CRandomNumber(const int min_val, const int max_val);
    double CRandomDouble(const double min_val, const double max_val);
}

#endif // __ST_ALG_RANDOM_H__
