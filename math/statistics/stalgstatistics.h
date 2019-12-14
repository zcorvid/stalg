#ifndef __ST_ALG_STATISTICS_H__
#define __ST_ALG_STATISTICS_H__

/* stalg statistics
 * last change: 04.05.2018
 *
 * Сборник статистических алгоритмов.
 *
 */

#include <cmath>

#include <vector>
#include <stdexcept>

#include "../stalgmath.h"
#include "../weight.h"

namespace stalg
{
    template<class InputIterator, typename T>
    T Sum(InputIterator begin, InputIterator end, T init_value)
    {
        for (InputIterator it = begin; it != end; ++it)
        {
            // sum += *it;
            init_value += *it;
        }
        return init_value;
    }

    template<class InputIterator, typename T>
    T SumOfPowers(InputIterator begin, InputIterator end, unsigned int exponent, T init_value)
    {
        for (InputIterator it = begin; it != end; ++it)
        {
            init_value += stalg::bin_power(*it, exponent);
        }
        return init_value;
    }

    template<class InputIterator, typename T>
    T Product(InputIterator begin, InputIterator end, T init_value)
    {
        for (InputIterator it = begin; it != end; ++it)
        {
            init_value *= *it;
        }
        return init_value;
    }

    // Функция помечена для удаления из библиотеки
    template<class InputIterator, typename T>
    T AverageValue(InputIterator begin, InputIterator end, T init_value)
    {
        return Sum(begin, end, init_value) / (1. * (end - begin));
    }

namespace statistics
{
    template<class InputIterator, typename T>
    T Moment(InputIterator begin, InputIterator end, unsigned int moment_number, T init_value)
    {
        return SumOfPowers(begin, end, moment_number, init_value) * 1. / (end - begin);
    }

    /* Среднее (математическое ожидание).
     */
    template<class InputIterator, typename T>
    T Mean(InputIterator begin, InputIterator end, T init_value)
    {
        return Sum(begin, end, init_value) * 1. / (end - begin);
    }

    /* Дисперсия.
     */
    template<class InputIterator, typename T>
    T Variance(InputIterator begin, InputIterator end, T init_value)
    {
        return Moment(begin, end, 2, init_value) - stalg::sqr(Mean(begin, end, init_value));
    }

    // Вычисление медианы. Не оптимизирована, использует сортировку скопированного диапазона.
    template<class InputIterator, typename T>
    T Median(InputIterator begin, InputIterator end, T init_value)
    {
        std::vector<T> sample(begin, end);
        std::sort(sample.begin(), sample.end());
        return init_value + sample[sample.size() / 2];
    }

    // Средневзвешенное среднее по методу Тьюки
    template<class InputIterator, typename T>
    T tukey_mean(InputIterator begin, InputIterator end, T init_value, const double c_par, const double epsila)
    {
        std::vector<T> sample(begin, end);
        std::sort(sample.begin(), sample.end());
        T median = sample[sample.size() / 2];

        std::vector<T> deviations(sample.size(), 0);
        for (int i = 0; i < sample.size(); ++i)
        {
            deviations[i] = stalg::abs(sample[i] - median);
        }
        std::sort(deviations.begin(), deviations.end());
        T sedian = deviations[deviations.size() / 2];

        std::vector<T> ushki(sample.size(), 0);
        for (int i = 0; i < ushki.size(); ++i)
        {
            ushki[i] = (sample[i] - median) / (c_par * sedian + epsila);
        }

        double num = 0.;
        double den = 0.;
        for (int i = 0; i < sample.size(); ++i)
        {
            T uw = stalg::ml_weight::biquadratic_weight(ushki[i]);
            num += uw * sample[i];
            den += uw;
        }
        return init_value + num / den;
    }
    /* Среднее без учёта par максимумов и par минимумов.
     */
    template<class InputIterator, typename T>
    T ExcludedMinMax_Mean(InputIterator begin, InputIterator end, T init_value, const int par)
    {
        T rv;
        if (end - begin > 2 * par)
        {
            std::vector<T> sample(begin, end);
            std::sort(sample.begin(), sample.end());
            rv = Mean(sample.begin() + par, sample.end() - par, init_value);
        }
        else
        {
            rv = Mean(begin, end, init_value);
        }
        return rv;
    }

    template<class InputIterator, typename T>
    T FixedBorderTruncated_Mean(InputIterator begin, InputIterator end, T init_value, const unsigned int border_percent)
    {
        std::vector<T> sample(begin, end);
        std::sort(sample.begin(), sample.end());
        unsigned int len = sample.size();
        unsigned int first = len * border_percent / 100u;
        unsigned int last = len - 1u - first;
        return Mean(sample.begin() + first, sample.begin() + last + 1, init_value);
    }

    template<class InputIterator, typename T>
    T SKOBorderTruncated_Mean(InputIterator begin, InputIterator end, T init_value, const double multiplier)
    {
        std::vector<T> sample(begin, end);
        std::sort(sample.begin(), sample.end());
        T mean = Mean(sample.begin(), sample.end(), T(0));
        T sko = sqrt(Variance(sample.begin(), sample.end(), T(0)));
        T left = mean - multiplier * sko;
        T right = mean + multiplier * sko;
        unsigned int len = sample.size();
        unsigned int first = 0u;
        unsigned int last = len - 1u;
        while (sample[first] < left && first < len)
        {
            ++first;
        }
        while (sample[last] > right && last > -1)
        {
            --last;
        }
        if (first > last)
        {
            throw std::runtime_error("first > last !");
        }
        return Mean(sample.begin() + first, sample.begin() + last + 1, init_value);
    }
}
}

#endif // __ST_ALG_STATISTICS_H__
