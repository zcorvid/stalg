#ifndef __stalg_METRIC_H__
#define __stalg_METRIC_H__

/* stalg metric
 * last change: 16.11.2016
 *
 * Сборник различных функций метрики.
 * Функции сигнатуры double(const T&, const T&).
 */

#include <cmath>

#include "../math/stalgmath.h"

namespace stalg
{
namespace metric
{
    template<class T>
    double standard_distance(const T& first, const T& second)
    {
        return stalg::abs(first - second);
    }
    template<class T>
    double standard_distance_2d_mink2(const T& first, const T& second)
    {
        return sqrt(stalg::sqr(first.x - second.x) + stalg::sqr(first.y - second.y));
    }
}
}

#endif // __stalg_METRIC_H__
