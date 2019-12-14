#ifndef __ST_ALG_GEOM_H__
#define __ST_ALG_GEOM_H__

#include <cmath>

namespace stalg
{
template<typename T>
class point2d
{
public:
    T x, y;

    point2d() : x(), y()
    {
        //
    }

    point2d(const point2d& other) : x(other.x), y(other.y)
    {
        //
    }

    point2d(const T& xC, const T& yC) : x(xC), y(yC)
    {
        //
    }

    point2d<T> operator+ (const point2d<T> &other)
    {
        return point2d<T>(x + other.x, y + other.y);
    }

    point2d<T> operator* (const T &lambda)
    {
        return point2d<T>(x * lambda, y * lambda);
    }

    point2d<T> operator/ (const T &lambda)
    {
        return point2d<T>(x / lambda, y / lambda);
    }

private:

};

point2d<double> getCamPoint(const double x, const double y, const double m, const double H, const double beta)
{
    double cb = cos(beta);
    double sb = sin(beta);
    double denom = y * sb + H * cb;
    double xCoor = -m * x / denom;
    double yCoor = m * (-y * cb + H * sb) / denom;
    return point2d<double>(xCoor, yCoor);
}

point2d<double> getXydPoint(const double xp, const double yp, const double m, const double H, const double beta)
{
    double cb = cos(beta);
    double sb = sin(beta);
    double denom = yp * sb + m * cb;
    double xCoor = -H * xp / denom;
    double yCoor = H * (-yp * cb + m * sb) / denom;
    return point2d<double>(xCoor, yCoor);
}

template<typename T>
stalg::point2d<T> combine_points(const T &alpha, const stalg::point2d<T> &p1, const stalg::point2d<T> &p2)
{
//    stalg::point2d<T> center = (1 - alpha) * center_ + alpha * other.center_;
    return stalg::point2d<T>((1 - alpha) * p1.x + alpha * p2.x, (1 - alpha) * p1.y + alpha * p2.y);
}

template<typename T>
class homothety2d
{
private:
    homothety2d<T>();
private:
    T k_;
    stalg::point2d<T> center_;
public:
    homothety2d<T>(const homothety2d<T> &other) : k_(other.k_), center_(other.center_)
    {
        //
    }

    homothety2d<T>(const T &k, const stalg::point2d<T> &center) : k_(k), center_(center)
    {
        //
    }

    homothety2d<T> operator * (const homothety2d<T> &other)
    {
        T k1 = k_;
        T k2 = other.k_;
        T k = k1 * k2;
        T alpha = (1 - k2) / (1 - k1 * k2);
        stalg::point2d<T> center = stalg::combine_points(alpha, center_, other.center_);
        return stalg::homothety2d<T>(k, center);
    }
};

}

#endif // __ST_ALG_GEOM_H__
