#ifndef __ST_ALG_RDP_H__
#define __ST_ALG_RDP_H__

/* stalg rdp
 * last change: 2019.08.05
 *
 * Алгоритм Рамера-Дугласа-Пекера (алгоритм итеративной ближайшей точки, алгоритм разбиения и слияния)
 *
 * Wikipedia : Алгоритм Рамера - Дугласа - Пекера
 *
 */

#include <vector>

#include "../geometry/affine.h"

namespace stalg
{
/* Шаг алгоритма Рамера - Дугласа - Пекера, самостоятельно не используется.
 */
template<class TPoint, class T>
void rdp_step(const std::vector<TPoint> &curve, const T &epsilon, int ifirst, int ilast, std::vector<bool> *flags)
{
    stalg::geometry::line2d<T> lin(curve[ifirst], curve[ilast]);

    // Находим самую удалённую от отрезка точку
    int imax = ifirst + 1;
    T max_dist = lin.distance(curve[imax]);
    for (int i = ifirst + 2; i + 1 < ilast; ++i)
    {
        T curr_dist = lin.distance(curve[i]);
        if (curr_dist > max_dist + 1e-8)     // COMPARISON_THRESHOLD = 1e-8
        {
            imax = i;
            max_dist = curr_dist;
        }
    }

    if (max_dist > epsilon - 1e-8)     // COMPARISON_THRESHOLD = 1e-8
    {
        (*flags)[imax] = true;
        rdp_step(curve, epsilon, ifirst, imax, flags);
        rdp_step(curve, epsilon, imax, ilast, flags);
    }
}

/* Уменьшает число точек кривой, аппроксимированной большей серией точек.
 * На входе - исходный массив точек, возврат - результат обработки (то есть
 * "примерно" та же кривая, но с меньшим количеством точек).
 *
 * Может использоваться для сглаживания дискретно заданной кривой.
 */
template<class TPoint, class T>
std::vector<TPoint> rdp(const std::vector<TPoint> &curve, const T &epsilon)
{
    std::vector<bool> flags(curve.size(), false);
    flags.front() = true;
    flags.back()  = true;
    rdp_step(curve, epsilon, 0, curve.size() - 1, &flags);

    std::vector<TPoint> rv;
    rv.reserve(curve.size());
    for (int i = 0; i < flags.size(); ++i)
    {
        if (flags[i])
        {
            rv.push_back(curve[i]);
        }
    }

    return rv;
}
}

#endif // __ST_ALG_RDP_H__
