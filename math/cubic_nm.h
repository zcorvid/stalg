#ifndef __ST_ALG_CUBIC_NM_H__
#define __ST_ALG_CUBIC_NM_H__

/* stalg cubic_nm
 * last change: 22.06.2018
 *
 * Метод Ньютона для решения кубического уравнения.
 *
 * Ссылки:  1.
 *          2.
 *          3.
 *
 */

#include <iostream>
#include <cmath>

#include "../stalgcommon.h"
#include "../math/stalgmath.h"
#include "../stalgconst.h"

namespace stalg
{

template<typename T>
T CubicGetRoot(const T &A1, const T &A2, const T &A3, const T &left,const T &right, int iterations = 1000)
{
    T a = left ;
    T b = right;

    T x_prev = (a + b) / 2.;
    T x_next = (a + b) / 2.;
    int counter = 0;
    do
    {
        ++counter;
        x_prev  = x_next;
        T f_val =          x_prev * x_prev * x_prev +     A1 * x_prev * x_prev + A2 * x_prev + A3;
        T f_der = 3      * x_prev * x_prev          + 2 * A1 * x_prev          + A2              ;

        if (fabs(f_der) > stalg::COMPARISON_THRESHOLD)
        {
            x_next = x_prev - f_val / f_der;
        }
        else if (counter > iterations)
        {
            break;
        }
        else
        {
            x_next = (a + x_next) / 2;
            x_prev = a - 10000;
        }
    } while (fabs(x_next - x_prev) > stalg::COMPARISON_THRESHOLD);

    return x_next;
}

}

#endif // __ST_ALG_CUBIC_NM_H__
