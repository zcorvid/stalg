#ifndef __ST_ALG_VINCENTY_H__
#define __ST_ALG_VINCENTY_H__

/* stalg vincenty's formulae
 * last change: 2019.08.05
 *
 * Компонент модуля геодезии. Реализация формул Винценти для определения
 * координат и расстояний на земном эллипсоиде.
 *
 * Реализация следует статье
 * T. Vincenty, "Direct and inverse solutions of geodesics on the ellipsoid
 *               with application of nested quations"
 *
 * Страница Википедии по теме: https://en.wikipedia.org/wiki/Vincenty's_formulae
 *
 * Не реализовано определение дистанции.
 *
 * geodesy = пущвуын
 *
 */

#include <iostream>

#include <cmath>
#include "../math/stalgmath.h"
#include "../stalgcommon.h"
#include "../stalgconst.h"

namespace stalg
{

class EarthEllipsoid
{
private:
    static constexpr double wgs84_a = 6378137.;
    static constexpr double wgs84_f = 1. / 298.257223563;
    static constexpr double kras_b  = 6356863.019;
    static constexpr double kras_f  = 1 / 298.3;

private:
    const double a_;  // Большая полуось (экваториальный радиус)
    const double b_;  // Малая полуось (полярный радиус)
    const double f_;  // Геометрическое (полярное) сжатие

private:
    static double count_a(const double arg_b, const double arg_f)
    {
        return arg_b / (1 - arg_f);
    }
    static double count_b(const double arg_a, const double arg_f)
    {
        return (1 - arg_f) * arg_a;
    }
    static double count_f(const double arg_a, const double arg_b)
    {
        return (arg_a - arg_b) / arg_a;
    }

private:
    EarthEllipsoid();
    EarthEllipsoid(const double arg_a, const double arg_b, const double arg_f) : a_(arg_a)
                                                                               , b_(arg_b)
                                                                               , f_(arg_f)
    {}

public:
    EarthEllipsoid(const EarthEllipsoid& other) : a_(other.a())
                                                , b_(other.b())
                                                , f_(other.f())
    {}

    static EarthEllipsoid from_ab(const double arg_a, const double arg_b)
    {
        return EarthEllipsoid(arg_a, arg_b, EarthEllipsoid::count_f(arg_a, arg_b));
    }
    static EarthEllipsoid from_af(const double arg_a, const double arg_f)
    {
        return EarthEllipsoid(arg_a, EarthEllipsoid::count_b(arg_a, arg_f), arg_f);
    }
    static EarthEllipsoid from_bf(const double arg_b, const double arg_f)
    {
        return EarthEllipsoid(EarthEllipsoid::count_a(arg_b, arg_f), arg_b, arg_f);
    }

public:
    double a() const
    {
        return a_;
    }
    double b() const
    {
        return b_;
    }
    double f() const
    {
        return f_;
    }

public:
    /* Возвращает земной элиипсоид WGS 84
     */
    static EarthEllipsoid WGS84()
    {
        return EarthEllipsoid::from_af(wgs84_a, wgs84_f);
    }
    /* Возвращает земной элиипсоид Красовского
     */
    static EarthEllipsoid KrasovskyEllipsoid()
    {
        return EarthEllipsoid::from_bf(kras_b, kras_f);
    }
};

class Vincenty
{
private:
    Vincenty();
    Vincenty(const Vincenty&);
public:
    /* Создаёт считалку Винценти по заданной модели Земли
     */
    Vincenty(const EarthEllipsoid& model) : model_(model) {}

private:
    EarthEllipsoid model_;

private:
    // Координаты
    double Fi1;
    double L1;
    double Fi2;
    double L2;
    // Азимуты
    double alpha1;
    double alpha2;
    // Дистанция
    double s;

private:
    // Рабочие переменные
    double L;
    double alpha;
    double cos_alpha;
    double sin_alpha;
    double u2;
    double cos_alpha1;
    double sin_alpha1;
    double U1;
    double tan_U1;
    double cos_U1;
    double sin_U1;
    double U2;
    double tan_U2;
    double sigma1;
    double A;
    double B;
    double dvasm;
    double cos_2sm;
    double cos2_2sm;
    double sin_2sm;
    double sigma;
    double cos_s;
    double sin_s;
    double dsigma;
    double sigma_old;
    double lambda;
    double C;
private:
    // sigma1
    double f1()
    {
        return atan2(tan_U1, cos_alpha1);
    }
    // sin_alpha
    double f2()
    {
        return cos_U1 * sin_alpha1;
    }
    // A
    double f3()
    {
        return 1 + (u2 / 16384) * (4096 + u2 * (-768 + u2 * (320 - 175 * u2)));
    }
    // B
    double f4()
    {
        return (u2 / 1024) * (256 + u2 * (-128 + u2 * (74 - 47 * u2)));
    }
    // 2 * sigma_m
    double f5()
    {
        return 2 * sigma1 + sigma;
    }
    // dsigma
    double f6()
    {
        return B * sin_s * (cos_2sm + 0.25 * B * (cos_s * (-1 + 2 * cos2_2sm) - (1 / 6) * B * cos_2sm * (-3 + 4 * stalg::sqr(sin_s)) * (-3 + 4 * cos2_2sm)));
    }
    // sigma
    double f7()
    {
        return s / (model_.b() * A) + dsigma;
    }
    // sigma first approximation
    double f7_start()
    {
        return s / (model_.b() * A);
    }
    // Fi_2
    double f8()
    {
        return atan2(sin_U1 * cos_s + cos_U1 * sin_s * cos_alpha1, (1 - model_.f()) * sqrt(stalg::sqr(sin_alpha) + stalg::sqr(sin_U1 * sin_s - cos_U1 * cos_s * cos_alpha1)));
    }
    // lambda
    double f9()
    {
        return atan2(sin_s * sin_alpha1, cos_U1 * cos_s - sin_U1 * sin_s * cos_alpha1);
    }
    // C
    double f10()
    {
        return (model_.f() / 16) * stalg::sqr(cos_alpha) * (4 + model_.f() * (4 - 3 * stalg::sqr(cos_alpha)));
    }
    // L
    double f11()
    {
        return lambda - (1 - C) * model_.f() * sin_alpha * (sigma + C * sin_s * (cos_2sm + C * cos_s * (-1 + 2 * cos2_2sm)));
    }
    // alpha_2
    double f12()
    {
        return atan2(sin_alpha, -sin_U1 * sin_s + cos_U1 * cos_s * cos_alpha1);
    }

public:
    // В разработке
    // double calculate_distance(const double Fi1, const double L1, const double Fi2, const double L2) const
    // {
    //     //
    // }
    void calculate_coordinates(const double Fi1_a, const double L1_a, const double s_a, const double alpha1_a)
    {
        // double eps = 1e-20;
        double eps = stalg::COMPARISON_THRESHOLD;

        Fi1    = Fi1_a    * stalg::pi / 180.;
        L1     = L1_a     * stalg::pi / 180.;
        s      = s_a      ;
        alpha1 = alpha1_a * stalg::pi / 180.;

        cos_alpha1 = cos(alpha1);
        sin_alpha1 = sin(alpha1);
        tan_U1 = (1 - model_.f()) * tan(Fi1);
        cos_U1 = sqrt(1 / (1 + stalg::sqr(tan_U1)));
        sin_U1 = sqrt(1 - stalg::sqr(cos_U1));
        sigma1 = f1();
        sin_alpha = f2();
        cos_alpha = sqrt(1 - stalg::sqr(sin_alpha));
        u2 = (1 - stalg::sqr(sin_alpha)) * (model_.a() * model_.a() - model_.b() * model_.b()) / (model_.b() * model_.b());
        A = f3();
        B = f4();
        sigma = f7_start();
        cos_s = cos(sigma);
        sin_s = sin(sigma);

        int counter = 0;

        do
        {
            dvasm = f5();
            cos_2sm = cos(dvasm);
            cos2_2sm = stalg::sqr(cos_2sm);
            sin_2sm = sin(dvasm);
            dsigma = f6();
            sigma_old = sigma;
            sigma = f7();
            cos_s = cos(sigma);
            sin_s = sin(sigma);

            ++counter;
            if (counter > 100)
            {
                qDebug() << "Vincenty::calculate_coordinates : counter = " << counter << fabs(sigma - sigma_old);
            }
            if (counter > 500)
            {
                break;
            }
        } while (fabs(sigma - sigma_old) > eps);
        Fi2 = f8();
        lambda = f9();
        C = f10();
        L = f11();
        alpha2 = f12();
        L2 = L1 + L;
    }

    double latitude2() const
    {
        return Fi2 * 180. / stalg::pi;
    }

    double longitude2() const
    {
        return L2 * 180. / stalg::pi;
    }

    double azimuth2() const
    {
        return alpha2 * 180. / stalg::pi;
    }

    double distance() const
    {
        return s;
    }
};

}

#endif // __ST_ALG_VINCENTY_H__
