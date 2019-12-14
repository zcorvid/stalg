// stalg geometry3d source

#include <stalggeometry3d.h>

#include <cmath>

namespace stalg
{
    void RotateVector3d(double* x_coor, double* y_coor, double* z_coor, const double angle, const double ax_coor, const double ay_coor, const double az_coor)
    {
        double cos_angle = cos(angle);
        double sin_angle = cos(angle);
        double vec_length = sqrt(ax_coor * ax_coor + ay_coor * ay_coor + az_coor * az_coor);
        double xc = ax_coor / vec_length;
        double yc = ay_coor / vec_length;
        double zc = az_coor / vec_length;

        double m11 = cos_angle + (1 - cos_angle) * xc * xc;
        double m12 = (1 - cos_angle) * xc * yc - sin_angle * zc;
        double m13 = (1 - cos_angle) * xc * zc + sin_angle * yc;

        double m21 = (1 - cos_angle) * yc * xc + sin_angle * zc;
        double m22 = cos_angle + (1 - cos_angle) * yc * yc;
        double m23 = (1 - cos_angle) * yc * zc - sin_angle * xc;

        double m31 = (1 - cos_angle) * zc * xc - sin_angle * yc;
        double m32 = (1 - cos_angle) * zc * yc + sin_angle * xc;
        double m33 = cos_angle + (1 - cos_angle) * zc * zc;

        double x_old = *x_coor;
        double y_old = *y_coor;
        double z_old = *z_coor;

        *x_coor = m11 * x_old + m12 * y_old + m13 * z_old;
        *y_coor = m21 * x_old + m22 * y_old + m23 * z_old;
        *z_coor = m31 * x_old + m32 * y_old + m33 * z_old;
    }
}
