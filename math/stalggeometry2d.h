#ifndef __ST_ALG_GEOMETRY2D_H__
#define __ST_ALG_GEOMETRY2D_H__

// stalg 2-dimensional geometry
// 04.05.2018

namespace stalg
{
    void RotateVector2d(double* x_coor, double* y_coor, const double angle);

    class Polygon
    {
    private:
    public:
    };

    template<typename T>
    T SignedArea(const T &x1, const T &y1, const T &x2, const T &y2)
    {
        return x1 * y2 - x2 * y1;
    }

    template<typename T>
    double SignedArea(const T &v1, const T &v2)
    {
        return v1.x() * v2.y() - v2.x() * v1.y();
    }

    // Нужен класс аффинной геометрии
}

#endif // __ST_ALG_GEOMETRY2D_H__
