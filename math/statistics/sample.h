#ifndef __ST_ALG_SAMPLE_H__
#define __ST_ALG_SAMPLE_H__

/* stalg sample
 * last change: 2019.08.05
 *
 * Сборник операций над выборками
 *
 */

#include "../stalgmath.h"

namespace stalg
{
/* Взятие производной.
 */
template<class T>
T derivative(const T &mas)
{
    T ret_mas;
    for (int i = 1; i < mas.size(); ++i)
    {
        ret_mas.push_back(mas[i] - mas[i - 1]);
    }
    return ret_mas;
}
/* Взятие интеграла.
 */
template<class T>
T integral(const T &mas)
{
    T ret_mas;
    if (!mas.empty())
    {
        ret_mas.push_back(mas.front());
        for (int i = 1; i < mas.size(); ++i)
        {
            ret_mas.push_back(mas[i] + ret_mas[i - 1]);
        }
    }
    return ret_mas;
}
namespace filter
{
template<class T>
T outliers(const T &mas, int w = 1)
{
    T rv;
    if (w == 0)
    {
        rv = mas;
    }
    else
    {
        for (int i = 0; i < w; ++i)
        {
            rv.push_back(mas[i]);
        }
        for (int i = w; i + w < mas.size(); ++i)
        {
            double S1 = 0;
            double S2 = 0;
            for (int h = -w; h <= w; ++h)
            {
                S1 += mas[i + h];
                S2 += stalg::sqr(mas[i + h]);
            }
            double mOld = S1 * 1.0 / (2 * w + 1);
            double mNew = (S1 - mas[i]) * 1.0 / (2 * w);
            double sOld = S2 * 1.0 / (2 * w + 1) - mOld * mOld;
            double sNew = (S2 - stalg::sqr(mas[i])) * 1.0 / (2 * w) - mNew * mNew;
            if (sNew <= sOld)
            {
                rv.push_back(mas[i]);
            }
            else
            {
                rv.push_back(0.0);
            }
        }
        for (int i = mas.size() - w; i < mas.size(); ++i)
        {
            rv.push_back(mas[i]);
        }
    }
    return rv;
}
template<class T>
T truncate(const T &mas, double minValue = 1e2, double maxValue = 1e9)
{
    T rv;
    for (int i = 0; i < mas.size(); ++i)
    {
        if (stalg::abs(mas[i]) >= minValue && stalg::abs(mas[i]) <= maxValue)
        {
            rv.push_back(mas[i]);
        }
        else
        {
            rv.push_back(0.0);
        }
    }
    return rv;
}
template<class T>
T saw(const T &mas)
{
    T rv;
    rv.push_back(0.0);
    for (int i = 1; i + 1 < mas.size(); ++i)
    {
        if (mas[i - 1] < mas[i] && mas[i] > mas[i + 1])
        {
            rv.push_back(mas[i]);
        }
        else
        {
            rv.push_back(0.0);
        }
    }
    rv.push_back(0.0);
    return rv;
}
template<class T>
T correct_zero(const T &mas, double border = 0.1)
{
    T rv;
    for (int i = 0; i < mas.size(); ++i)
    {
        if (stalg::abs(mas[i]) > border)
        {
            rv.push_back(mas[i]);
        }
        else
        {
            rv.push_back(0.0);
        }
    }
    return rv;
}
}
}

#endif // __ST_ALG_SAMPLE_H__
