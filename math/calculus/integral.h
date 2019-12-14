#ifndef __ST_ALG_INTEGRAL__H__
#define __ST_ALG_INTEGRAL__H__

/* stalg integral
 * last change: 04.05.2018
 *
 * Численное интегрирование таблично заданной функции.
 * Реализован только метод трапеций (на отрезках разбиения функция приближена линейной).
 *
 * Входные параметры: диапазон массива значений функции, h - шаг (равномерной) сетки.
 * Возвращаемое значение: значение интеграла.
 */

namespace stalg
{
template<typename T>
T integral_trapezoidal(T* first_pos, T* last_pos, T h)
{
    double S = (h / 2.) * ( (*first_pos) + (*(last_pos - 1)) );
    for (T* it = first_pos + 1; it != last_pos - 1; ++it)
    {
        S += h * (*it);
    }
    return S;
}
}

#endif // __ST_ALG_INTEGRAL__H__
