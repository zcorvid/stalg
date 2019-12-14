#ifndef __ST_ALG_COLLIS_H__
#define __ST_ALG_COLLIS_H__

#include <cmath>
#include <vector>
#include "math/stalgmath.h"

namespace stalg
{
// Класс препятствия, координаты центра и радиус
template<typename T>
class obstruction
{
public:
    T x;
    T y;
    double R;
};
// Класс движущегося объекта, координаты центра и скорости
template<typename T>
class victim
{
public:
    T x;
    T y;
    T vx;
    T vy;
};
// Возвращает дистанцию до точки столкновения плюс радиус препятствия,
// если столкновения нет - вернёт отрицательное число, если столкновение
// уже произошло - вернёт расстояние до препятствия
template<typename T>
double collide(const stalg::obstruction<T> &ob, const stalg::victim<T> &vic)
{
    double rv = 0;
    double a = -vic.vy;
    double b =  vic.vx;
    double c =  vic.x * vic.vy - vic.y * vic.vx;
    double dist = fabs(a * ob.x + b * ob.y + c) / sqrt(a * a + b * b);
    double D2 = stalg::sqr(ob.x - vic.x) + stalg::sqr(ob.y - vic.y);
    double D  = sqrt(D2);

    std::cout << "D    = " << D    << " ob.R = " << ob.R << std::endl;
    std::cout << "dist = " << dist << " ob.R = " << ob.R << std::endl;

    if (D < ob.R)
    {
        rv = D;
    }
    else if (dist < ob.R)
    {
        double d2 = stalg::sqr(dist);
        rv = sqrt(D2 - d2) - sqrt(stalg::sqr(ob.R) - d2);
        rv += ob.R;
    }
    else
    {
        rv = -1.;
    }
    return rv;
}
// Возвращает индекс движущейся цели, которая столкнётся с препятствием и находится к нему ближе всех
template<typename T>
int GetNearestVictim(const stalg::obstruction<T> &ob, const std::vector<stalg::victim<T>> &vic)
{
    double min_dist = 1000000.;
    int min_ind = -1;
    for (int i = 0; i < vic.size(); ++i)
    {
        double dist = collide(ob, vic[i]);

std::cout << dist << std::endl;

        if (dist > 0)
        {
            if (dist < min_dist)
            {
                min_dist = dist;
                min_ind = i;
            }
        }
    }
    return min_ind;
}
}

#endif // __ST_ALG_COLLIS_H__
