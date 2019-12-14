#ifndef __ST_ALG_AFFINE_H__
#define __ST_ALG_AFFINE_H__

/* stalg affine geometry
 * last change: 2019.08.05
 *
 * Реализация аффинной геометрии
 *
 */

#include <cmath>

namespace stalg
{
namespace geometry
{
/* Классы двумерного вектора и двумерной точки.
 *
 * Операции: (1) Сложение векторов
 *           (2) Вычитание векторов
 *           (3) Минус вектор
 *           (4) Умножение вектора на константу
 *           (5) Разность точек (результат - вектор)
 *           (6) Прибавление вектора к точке (результат - точка)
 *
 */
template<class T>
class vector2d
{
public:
    T x;
    T y;
public:
    vector2d() : x(), y()
    {
        //
    }
    vector2d(const T &x_, const T &y_) : x(x_), y(y_)
    {
        //
    }
    vector2d<T> operator - () const
    {
        return vector2d<T>(-x, -y);
    }
    vector2d<T> operator + (const vector2d<T> &oth) const
    {
        return vector2d<T>(x + oth.x, y + oth.y);
    }
    vector2d<T> operator - (const vector2d<T> &oth) const
    {
        return (*this) + (-oth);
    }
    vector2d<T> operator * (const T &k) const
    {
        return vector2d<T>(k * x, k * y);
    }
    friend
    vector2d<T> operator * (const T &k, const vector2d<T> &vec)
    {
        return vec * k;
    }

    friend class point2d<T>;
};

template<class T>
class point2d
{
public:
    T x;
    T y;
public:
    point2d() : x(), y()
    {
        //
    }
    point2d(const T &x_, const T &y_) : x(x_), y(y_)
    {
        //
    }
    friend
    vector2d<T> operator - (const point2d<T> &lhs, const vector2d<T> &rhs)
    {
        return vector2d<T>(lhs.x - rhs.x, lhs.y - rhs.y);
    }
    point2d<T> operator + (const vector2d<T> &vec) const
    {
        return vector2d<T>(x + vec.x, y + vec.y);
    }

    friend class vector2d<T>;
};

/* Прямая на плоскости
 *                     аффинно   : A0      + A1 * x  + A2 *  y = 0
 *                     проективно: A0 * L0 + A1 * L1 + A2 * L2 = 0
 */
template<class T>
class line2d
{
private:
    line2d() = delete;
private:
    T A0;
    T A1;
    T A2;

    T norm0()
    {
        return std::sqrt(A1 * A1 + A2 * A2);
    }

public:
    line2d(const T &a, const T &b, const T &c) : A0(a), A1(b), A2(c)
    {
        if (A0 == 0 && A1 == 0 && A2 == 0)
        {
//            throw std::string("Full zero line");
            std::cerr << "Full zero line" << std::endl;
        }
    }
    line2d(const line2d<T> &oth) : A0(oth.A0), A1(oth.A1), A2(oth.A2)
    {
        //
    }
    line2d(const point2d<T> &p1, const point2d<T> &p2) : A0(p1.x * p2.y - p2.x * p1.y)
                                                       , A1( - (p2.y - p1.y) )
                                                       , A2(   (p2.x - p1.x) )
    {
        //
    }
    /* Значение уравнения прямой (несущего функционала) в заданной точке
     */
    T operator () (const point2d<T> &p)
    {
        return A0 + A1 * p.x + A2 * p.y;
    }
    /* Расстояние от прямой до точки
     */
    T distance(const point2d<T> &p)
    {
        return (*this)(p) / norm0();
    }
};

/* Класс линейного отображения.
 */
template<class T>
class LinearMap2d
{
private:
    // Matrix, by columns
    //    || a c ||
    //    || b d ||
    T a_, b_, c_, d_;
public:
    // By default this is Identity map.
    explicit LinearMap2d(const T &k = T(1)) : a_(k), b_(0), c_(0), d_(k)
    {
        //
    }
    LinearMap2d(const T &a, const T &b, const T &c, const T &d) : a_(a), b_(b), c_(c), d_(d)
    {
        //
    }
    /* Детерминант отображения.
     */
    T det() const
    {
        return a * d - b * c;
    }
    LinearMap2d<T> operator - () const
    {
        return LinearMap2d<T>(-a_, -b_, -c_, -d_);
    }
    friend
    LinearMap2d<T> operator + (const LinearMap2d<T> &lhs, const LinearMap2d<T> &rhs)
    {
        return LinearMap2d<T>(lhs.a_ + rhs.a_, lhs.b_ + rhs.b_, lhs.c_ + rhs.c_, lhs.d_ + rhs.d_);
    }
    friend
    LinearMap2d<T> operator - (const LinearMap2d<T> &lhs, const LinearMap2d<T> &rhs)
    {
        return lhs + (-rhs);
    }
    /* Композиция отображений.
     */
    friend
    LinearMap2d<T> operator * (const LinearMap2d<T> &lhs, const LinearMap2d<T> &rhs)
    {
        T a = lhs.a_ * rhs.a_ + lhs.c_ * rhs.b_;
        T b = lhs.b_ * rhs.a_ + lhs.d_ * rhs.b_;
        T c = lhs.a_ * rhs.c_ + lhs.c_ * rhs.d_;
        T d = lhs.b_ * rhs.c_ + lhs.d_ * rhs.d_;
        return LinearMap2d<T>(a, b, c, d);
    }
    /* Результат применения отображения к вектору.
     */
    vector2d<T> operator * (const vector2d<T> &arg)
    {
        return vector2d<T>(a_ * arg.x + c_ * arg.y, b_ * arg.x + d_ * arg.y);
    }
};
} // namespace geometry
} // namespace stalg

#endif // __ST_ALG_AFFINE_H__
