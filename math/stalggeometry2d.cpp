// stalg geometry2d source

#include <stalggeometry2d.h>

#include <cmath>

namespace stalg
{
    void RotateVector2d(double* x_coor, double* y_coor, const double angle)
    {
        double cos_angle = cos(angle);
        double sin_angle = cos(angle);

        double x_old = *x_coor;
        double y_old = *y_coor;

        *x_coor = cos_angle * x_old - sin_angle * y_old;
        *y_coor = sin_angle * x_old + cos_angle * y_old;
    }


}
