#ifndef __ST_ALG_MATHFUNCTIONSLIB_1_H__
#define __ST_ALG_MATHFUNCTIONSLIB_1_H__

/* Библиотека функций, которые используются для тестирования методов оптимизации.
 * Основная часть функций взята со страницы: Test functions for optimization = https://en.wikipedia.org/wiki/Test_functions_for_optimization
 * Функций Розенброка: https://en.wikipedia.org/wiki/Rosenbrock_function
 * Список функций: ( 1) Rastrigin function
 *                 ( 2) Ackley's function
 *                 ( 3) Sphere function
 *                 ( 4) Rosenbrock function
 *                 ( 5) Beale's function
 *                 ( 6) Goldstein–Price function
 *                 ( 7) Booth's function
 *                 ( 8) Bukin function N.6
 *                 ( 9) Matyas function
 *                 (10) Lévi function N.13
 *                 (11) Three-hump camel function
 *                 (12) Easom function
 *                 (13) Cross-in-tray function
 *                 (14) Eggholder function
 *                 (15) Hölder table function
 *                 (16) McCormick function
 *                 (17) Schaffer function N. 2
 *                 (18) Schaffer function N. 4
 *                 (19) Styblinski–Tang function
 *                 (20) Simionescu function
 *                 (21) Rosenbrock function (второй вариант, с параметрами)
 *                 (22)
 *                 (23)
 *                 (24)
 *                 (25)
 *                 (26)
 *                 (27)
 *                 (28)
 *                 (29)
 *
 * Надо добавить:  (01) Вероятностная функция Розенброка https://en.wikipedia.org/wiki/Rosenbrock_function
 *                 (02) Shekel function https://en.wikipedia.org/wiki/Shekel_function
 *                 (03) Himmelblau's function https://en.wikipedia.org/wiki/Himmelblau's_function
 */




#include <iomanip>
#include <iostream>
#include <stdexcept>



#include "../stalgconst.h"
#include "../math/stalgmath.h"
#include "../stalgcommon.h"

#include <vector>

#include <math.h>

namespace stalg
{
namespace MathFunctionsLib_1
{
    // Dimension = n
    // Minimum: f(0, 0) = 0
    // Search domain: -5.12 <= x, y <= 5.12
    class Rastrigin
    {
    private:
        const unsigned int dimension_;

    public:
        Rastrigin(const int dimension = 2) : dimension_(dimension) {}
        double operator () (const std::vector<double>& arg) const
        {
            const double A = 10.;
            double value = A * dimension_;
            for (size_t i = 0; i < dimension_; ++i) {
                value += (sqr(arg[i]) - A * cos(2. * pi * arg[i]));
            }
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(0, 0) = 0
    // Search domain: -5. <= x, y <= 5.
    class Ackley
    {
    private:
    private:
        // Ackley(const Ackley&);

    public:
        Ackley() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x_arg = arg[0];
            double y_arg = arg[1];
            double value = -20. * exp(-0.2 * sqrt(0.5 * (sqr(x_arg) + sqr(y_arg)))) - exp(0.5 * (cos(2 * pi * x_arg) + cos(2 * pi * y_arg))) + e_number + 20.;
            return value;
        }
    };
    // Dimension = n
    // Minimum: f(0, ... , 0) = 0
    // Search domain: -infty <= x_1, ... , x_n <= infty
    class SphereFunction
    {
    private:
        const unsigned int dimension_;
    private:
        SphereFunction();
        // SphereFunction(const SphereFunction&);

    public:
        SphereFunction(const int dimension) : dimension_(dimension) {}
        double operator () (const std::vector<double>& arg) const
        {
            double value = 0.;
            for (size_t i = 0; i < dimension_; ++i) {
                value += sqr(arg[i]);
            }
            return value;
        }
    };
    // Dimension = n
    // Minimum: f(1, ... , 1) = 0
    // Search domain: -infty <= x_1, ... , x_n <= infty
    class Rosenbrock
    {
    private:
        const unsigned int dimension_;
    private:
        Rosenbrock();
        // Rosenbrock(const Rosenbrock&);

    public:
        Rosenbrock(const int dimension) : dimension_(dimension) {}
        double operator () (const std::vector<double>& arg) const
        {
            double value = 0.;
            for (size_t i = 0; i + 1 < dimension_; ++i) {
                value += 100. * sqr(arg[i + 1] - sqr(arg[i])) + sqr(arg[i] - 1.);
            }
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(3., 0.5) = 0
    // Search domain: -4.5 <= x, y <= 4.5
    class Beale
    {
    private:
    private:
        // Beale(const Beale&);

    public:
        Beale() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x_arg = arg[0];
            double y_arg = arg[1];
            double value = stalg::sqr(1.5 - x_arg + x_arg * y_arg) + stalg::sqr(2.25 - x_arg + x_arg * sqr(y_arg)) + stalg::sqr(2.625 - x_arg + x_arg * stalg::cube(y_arg));
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(0., -1.) = 3.
    // Search domain: -2. <= x, y <= 2.
    class Goldstein_Price
    {
    private:
    private:
        // Goldstein_Price(const Goldstein_Price&);

    public:
        Goldstein_Price() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value1 = 1. + stalg::sqr(x + y + 1.) * (19. - 14. * x + 3. * stalg::sqr(x) - 14. * y + 6. * x * y + 3. * stalg::sqr(y));
            double value2 = 30. + stalg::sqr(2. * x - 3. * y) * (18. - 32. * x + 12. * stalg::sqr(x) + 48. * y - 36. * x * y + 27. * stalg::sqr(y));
            double value = value1 * value2;
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(1., 3.) = 0.
    // Search domain: -10. <= x, y <= 10.
    class Booth
    {
    private:
    private:
        // Booth(const Booth&);

    public:
        Booth() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = stalg::sqr(x + 2. * y - 7.) + stalg::sqr(2. * x + y - 5.);
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(-10., 1.) = 0.
    // Search domain: -15. <= x <= 5.
    //                 -3. <= y <= 3.
    class BukinFunction_N6
    {
    private:
    private:
        // BukinFunction_N6(const BukinFunction_N6&);

    public:
        BukinFunction_N6() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = 100. * sqrt(stalg::abs(y - 0.01 * stalg::sqr(x))) + 0.01 * stalg::abs(x + 10.);
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(0., 0.) = 0.
    // Search domain: -10. <= x, y <= 10.
    class Matyas
    {
    public:
        Matyas() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = 0.26 * (stalg::sqr(x) + stalg::sqr(y)) - 0.48 * x * y;
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(1., 1.) = 0.
    // Search domain: -10. <= x, y <= 10.
    class LeviFunction_N13
    {
    public:
        LeviFunction_N13() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value =   stalg::sqr(sin(3. * stalg::pi * x))
                           + stalg::sqr(x - 1.) * (1. + stalg::sqr(sin(3. * stalg::pi * y)))
                           + stalg::sqr(y - 1.) * (1. + stalg::sqr(sin(2. * stalg::pi * y)));
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(0., 0.) = 0.
    // Search domain: -5. <= x, y <= 5.
    class ThreeHumpCamelFunction
    {
    public:
        ThreeHumpCamelFunction() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = 2 * stalg::sqr(x) - 1.05 * stalg::bin_power(x, 4) + stalg::bin_power(x, 6) * (1. / 6.) + x * y + stalg::sqr(y);
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(pi, pi) = -1.
    // Search domain: -100. <= x, y <= 100.
    class Easom
    {
    public:
        Easom() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = -cos(x) * cos(y) * exp(-(stalg::sqr(x - stalg::pi) + stalg::sqr(y - stalg::pi)));
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f( 1.34941,  1.34941) = -2.06261
    //          f( 1.34941, -1.34941) = -2.06261
    //          f(-1.34941,  1.34941) = -2.06261
    //          f(-1.34941, -1.34941) = -2.06261
    // Search domain: -100. <= x, y <= 100.
    class CrossInTray
    {
    public:
        CrossInTray() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = -0.0001 * pow(stalg::abs(sin(x) * sin(y) * exp(stalg::abs(100. - sqrt(stalg::sqr(x) + stalg::sqr(y)) / stalg::pi))) + 1., 0.1);
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(512., 404.2319) = -959.6407
    // Search domain: -512. <= x, y <= 512.
    class Eggholder
    {
    public:
        Eggholder() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double y47 = y + 47.;
            double value = -y47 * sin(sqrt(stalg::abs(x / 2. + y47))) - x * sin(sqrt(stalg::abs(x - y47)));
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f( 8.05502,  9.66459) = -19.2085
    //          f( 8.05502, -9.66459) = -19.2085
    //          f(-8.05502,  9.66459) = -19.2085
    //          f(-8.05502, -9.66459) = -19.2085
    // Search domain: -10. <= x, y <= 10.
    class HoelderTable
    {
    public:
        HoelderTable() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = -stalg::abs(sin(x) * cos(y) * exp(stalg::abs(1. - sqrt(stalg::sqr(x) + stalg::sqr(y)) / stalg::pi)));
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(-0.54719, -1.54719) = -1.9133
    // Search domain: -1.5 <= x <= 4.
    //                -3.  <= y <= 4.
    class McCormick
    {
    public:
        McCormick() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = sin(x + y) + stalg::sqr(x - y) - 1.5 * x + 2.5 * y + 1.;
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(0., 0.) = 0.
    // Search domain: -100. <= x, y <= 100.
    class SchafferFunction_N2
    {
    public:
        SchafferFunction_N2() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = 0.5 + (stalg::sqr(sin(stalg::sqr(x) - stalg::sqr(y))) - 0.5) / stalg::sqr(1. + 0.001 * (stalg::sqr(x) + stalg::sqr(y)));
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f(0., 1.25313) = 0.292579
    // Search domain: -100. <= x, y <= 100.
    class SchafferFunction_N4
    {
    public:
        SchafferFunction_N4() {}
        double operator () (const std::vector<double>& arg) const
        {
            double x = arg[0];
            double y = arg[1];
            double value = 0.5 + (stalg::sqr(cos(sin(stalg::abs(stalg::sqr(x) - stalg::sqr(y))))) - 0.5) / stalg::sqr(1. + 0.001 * (stalg::sqr(x) + stalg::sqr(y)));
            return value;
        }
    };
    // Dimension = n
    // Minimum: -39.16617 * n < f(-2.903534, ... , -2.903534) < -39.16616 * n
    // Search domain: -5. <= x_1 , ... , x_n <= 5.
    class Styblinski_Tang
    {
    private:
        const unsigned int dimension_;

    public:
        Styblinski_Tang(const int dimension = 2) : dimension_(dimension) {}
        double operator () (const std::vector<double>& arg) const
        {
            double value = 0.;
            for (size_t i = 0; i < dimension_; ++i) {
                double squared_x = stalg::sqr(arg[i]);
                value += stalg::sqr(squared_x) - 16. * squared_x + 5. * arg[i];
            }
            value /= 2;
            return value;
        }
    };
    // Dimension = 2
    // Minimum: f( 0.85586214, -0.85586214) = -0.072625
    //          f(-0.85586214,  0.85586214) = -0.072625
    // Search domain: -1.25 <= x, y <= 1.25
    //
    // Функция провалила тестирование, из библиотеки пока исключается.
    // Почему-то точка минимума (0.85586214, -0.85586214) не попадает в область определения (летит logic_error).
    /*
    class Simionescu
    {
    public:
        Simionescu() {}
        double operator () (const std::vector<double>& arg, const bool polar = false) const
        {
            double r_T = 1.;
            double r_S = 0.2;
            int n = 8;
            double value = 0.;
            if (polar) {
                // double r2 = stalg::sqr(x) + stalg::sqr(y);
                // double r = sqrt(r2);
                // double phi = atan(x / y);
                double r = arg[0];
                double phi = arg[1];
                double r2 = stalg::sqr(r);
                if (stalg::abs(r2) < stalg::COMPARISON_THRESHOLD) {
                    value = 0.;
                } else if (r2 < stalg::sqr(r_T + r_S * cos(n * phi)) + stalg::COMPARISON_THRESHOLD) {
                    value = 0.05 * r2 * sin(2. * phi);
                } else {
                    throw std::logic_error("Invalid value of arguments - out of definition domain !");
                }
            } else {
                double x = arg[0];
                double y = arg[1];
                if (stalg::abs(x) < stalg::COMPARISON_THRESHOLD && stalg::abs(y) < stalg::COMPARISON_THRESHOLD) {
                    value = 0.;
                } else if (stalg::sqr(x) + stalg::sqr(y) < stalg::sqr(r_T + r_S * cos(n * asin(y / (stalg::sqr(x) + stalg::sqr(y))))) + stalg::COMPARISON_THRESHOLD) {
                    value = 0.1 * x * y;
                } else {
                    throw std::logic_error("Invalid value of arguments - out of definition domain !");
                }
            }
            return value;
        }
    };
    */
    // https://en.wikipedia.org/wiki/Rosenbrock_function
    // Rosenbrock function, Rosenbrock's valley, Rosenbrock's banana function
    // Dimension = n
    // Minimum:
    // Search domain:
    //
    // For n = 2 global minimum is f(a, a^2) = 0
    // For n = 3, a = 1., b = 100. global minimum is (1., 1., 1.)
    //
    // Не сделаны юнит тесты для значений a, b не по умолчанию.
    class Rosenbrock1
    {
    private:
        const unsigned int dimension_;
        const double a_;
        const double b_;

    public:
        Rosenbrock1(const int dimension = 2, const double a = 1., const double b = 100.) : dimension_(dimension), a_(a), b_(b) {}
        double operator () (const std::vector<double>& arg) const
        {
            double value = 0.;
            for (size_t i = 0; i + 1 < dimension_; ++i) {
                value += a_ * stalg::sqr(1 - arg[i]) + b_ * stalg::sqr(arg[i + 1] - stalg::sqr(arg[i]));
            }
            return value;
        }
    };






/*
std::function<double(const std::vector<double>&)> rozenbrok =
        [](const std::vector<double>& arg) {
            double x = arg[0];
            double y = arg[1];
            double value = stalg::sqr(1 - x) + 100. * stalg::sqr(y - x * x);
            return value;
        };
std::function<double(const std::vector<double>&)> himmelblau =
        [](const std::vector<double>& arg) {
            double x = arg[0];
            double y = arg[1];
            double value = stalg::sqr(x * x + y - 11.) + 100 * stalg::sqr(x + y * y - 7);
            return value;
        };
*/
}
}

#endif // __ST_ALG_MATHFUNCTIONSLIB_1_H__
