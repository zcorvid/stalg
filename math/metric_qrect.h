#ifndef __ST_ALG_METRIC_QRECT_H__
#define __ST_ALG_METRIC_QRECT_H__

/* Библиотека расстояний для объектов QRect. Представленные расстояния
 * являются эвристиками и не являются метриками в математическом смысле.
 *
 */

#include <cmath>

#include <QRect>

namespace stalg
{
// Расстояние по ближайшей точке (для пересекающихся прямоугольников равно нулю)
double qrd_min_d(const QRect &lqr, const QRect &rqr)
{
    double d1 = 0.;
    double d2 = 0.;
    if (lqr.right() < rqr.left())
    {
        d1 = rqr.left() - lqr.right();
    }
    else if(rqr.right() < lqr.left())
    {
        d1 = lqr.left() - rqr.right();
    }
    if (lqr.bottom() < rqr.top())
    {
        d2 = rqr.top() - lqr.bottom();
    }
    else if(rqr.bottom() < lqr.top())
    {
        d2 = lqr.top() - rqr.bottom();
    }
    return sqrt(d1 * d1 + d2 * d2);
}
// Расстояние по минимуму площади разности множеств (для вложенных прямоугольников равно нулю)
double qrd_s(const QRect &lqr, const QRect &rqr)
{
    QRect inters = lqr & rqr;
    return std::min(lqr.width() * lqr.height(), rqr.width() * rqr.height()) - inters.width() * inters.height();
}
// Смешанное расстояние, для StP, некоторая эвристика для оценки шанса, что прямоугольники - части одной цели
double qrd_stp(const QRect &lqr, const QRect &rqr, double alpha = 1., double beta = 1.)
{
    return alpha * qrd_min_d(lqr, rqr) + beta * qrd_s(lqr, rqr);
}
}

#endif // __ST_ALG_METRIC_QRECT_H__
