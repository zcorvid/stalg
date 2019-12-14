#ifndef __ST_ALG_AFFINE_1D_H__
#define __ST_ALG_AFFINE_1D_H__

/* stalg affine geometry 1 dimensional
 * last change: 2019.08.05
 *
 * Реализация аффинной геометрии, одномерная специфика
 *
 */

namespace stalg
{
/* Возвращает канонического представителя фактора R/[0,1].
 */
template<typename T>
T sphere_canonical01(const T &x)
{
    if (x >= 0)
    {
        return x - (int)x;
    }
    else
    {
        return (x) + int(-x) + 1;
    }
}

/* Возвращает канонического представителя фактора R/[0,1] (работает только для положительных аргументов).
 */
template<typename T>
T sphere_canonical01_positive(const T &x)
{
    return x - (int)x;
}

/* Линейное отображение прямых, такое, что f(a1) = a2, f(b1) = b2
 */
template<typename T>
T linearMap1d_segment(const T &x, const T &a1, const T &b1, const T &a2, const T &b2)
{
    return a2 + ((x - a1) /(b1 - a1)) * (b2 - a2);
}

/* Линейное отображение сегментов (отрезков).
 */
// int сюда передавать запрещено (float или double).
template<typename T>
class linearMapSeg final
{
private:
    linearMapSeg() = delete;
private:
    T k_;
    T b_;
public:
    linearMapSeg(const linearMapSeg &oth) : k_(oth.k_), b_(oth.b_)
    {
        //
    }
    linearMapSeg(T a, T b, T c, T d)  // [a, b] |----> [c, d]
    {
        k_ = (d - c) / (b - a);
        b_ = c - a * (d - c) / (b - a);
    }
    T operator () (const T &x)
    {
        return k_ * x + b_;
    }
};

/* Линейное отображение окружностей C(a1, a2) |-----> C(a2, b2), такое, что f(a1) = a2, f(b1) = b2
 * <Примечание> C(a, b) := R / [a, b] - групповой фактор
 */
template<typename T>
T linearMap1d_sphere(const T &x, const T &a1, const T &b1, const T &a2, const T &b2)
{
    return a2 + sphere_canonical01((x - a1) /(b1 - a1)) * (b2 - a2);
}

/* Линейное отображение окружностей C(a1, a2) |-----> C(a2, b2), такое, что f(a1) = a2, f(b1) = b2 (только для положительных x)
 * <Примечание> C(a, b) := R / [a, b] - групповой фактор
 */
template<typename T>
T linearMap1d_sphere_nochecks(const T &x, const T &a1, const T &b1, const T &a2, const T &b2)
{
    return a2 + sphere_canonical01_positive((x - a1) /(b1 - a1)) * (b2 - a2);
}

/* Преобразует диапазоны
 */
template<typename T>
T convert_range(const T &x, const T &a1, const T &b1, const T &a2, const T &b2)
{
    return linearMap1d_sphere(x, a1, b1, a2, b2);
}

/* Преобразует диапазоны, только для чисел, не меньше левой границы
 */
template<typename T>
T convert_range_nochecks(const T &x, const T &a1, const T &b1, const T &a2, const T &b2)
{
    return linearMap1d_sphere_nochecks(x, a1, b1, a2, b2);
}

/* Поворачивает вектор (x, y) на угол angle (угол в радианах)
 */
template<typename T>
void rotateVector2d(T &x, T &y, const T angle)
{
    T ca = cos(angle);
    T sa = sin(angle);
    T rx = x * ca - y * sa;
    T ry = x * sa + y * ca;
    x = rx;
    y = ry;
}

/* Сдвигает вектор (x, y) на вектор (rx, ry)
 */
template<typename T>
void translateVector2d(T &x, T &y, const T &rx, const T &ry)
{
    x += rx;
    y += ry;
}
}

#endif // __ST_ALG_AFFINE_1D_H__
