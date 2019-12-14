#ifndef __ST_ALG_CARDANO_H__
#define __ST_ALG_CARDANO_H__

/* stalg cardano
 * last change: 22.06.2018
 *
 * Формула Кардано для решения кубического уравнения.
 *
 * Ссылки:  1. http://tehtab.ru/guide/guidemathematics/equations/cubeequationsuniversalmethods/
 *          2. https://proofwiki.org/wiki/Cardano%27s_Formula
 *          3. http://ru.math.wikia.com/wiki/%D0%A4%D0%BE%D1%80%D0%BC%D1%83%D0%BB%D0%B0_%D0%9A%D0%B0%D1%80%D0%B4%D0%B0%D0%BD%D0%BE
 *          4. Wikipedia : Тригонометрическая формула Виета
 *
 */

#include <iostream>
#include <cmath>
#include <complex>
#include <stdexcept>

#include "../stalgcommon.h"
#include "../math/stalgmath.h"
#include "../stalgconst.h"

namespace stalg
{

template<typename T>
std::vector<T> GetRealRoots(const T &A1, const T &A2, const T &A3)
{
    T B1 = A1;
    T B2 = A2;
    T B3 = A3;
    T p = -(B1 * B1) / 3. + B2;
    T q = 2. * B1 * B1 * B1 / 27. - B1 * B2 / 3. + B3;

    std::complex<T> sq = std::pow(std::complex<T>( q * q / 4. + p * p * p / 27.), std::complex<T>(0.5    ));
    std::complex<T> r1 = std::pow(std::complex<T>(-q / 2. + sq                 ), std::complex<T>(1. / 3.));
    std::complex<T> r2 = std::pow(std::complex<T>(-q / 2. - sq                 ), std::complex<T>(1. / 3.));

    for (int i = 0; std::abs<T>(r1 * r2 + p / 3 ) > stalg::COMPARISON_THRESHOLD && i < 3; ++i)
    {
        r2 *= std::polar<T>(1.0, 2. * stalg::pi / 3.);
    }

    std::complex<T> root1 = r1 + r2 - B1 / 3;
    r1 *= std::polar<T>(T(1), 2. * stalg::pi / 3.);
    r2 *= std::polar<T>(T(1), 2. * 2. * stalg::pi / 3.);
    std::complex<T> root2 = r1 + r2 - B1 / 3;
    r1 *= std::polar<T>(T(1), 2. * stalg::pi / 3.);
    r2 *= std::polar<T>(T(1), 2. * 2. * stalg::pi / 3.);
    std::complex<T> root3 = r1 + r2 - B1 / 3;

    std::cout << root1 << " ";
    std::cout << root2 << " ";
    std::cout << root3 << std::endl;

    // Отбор вещественных корней
    std::vector<T> ans;
    if (fabs(root1.imag()) < stalg::COMPARISON_THRESHOLD)
    {
        ans.push_back(root1.real());
    }
    if (fabs(root2.imag()) < stalg::COMPARISON_THRESHOLD)
    {
        ans.push_back(root2.real());
    }
    if (fabs(root3.imag()) < stalg::COMPARISON_THRESHOLD)
    {
        ans.push_back(root3.real());
    }

    return ans;
}

double PrintRoots1(const long long A1, const long long A2, const long long A3)
{
    long double a = A1;
    long double b = A2;
    long double c = A3;
    long double Q = (a * a - 3. * b) / 9.;
    long double R = (2. * a * a * a - 9. * a * b + 27. * c) / 54.;
    long double S = Q*Q*Q - R*R;
    if (S <= 0)
    {
        throw std::runtime_error("No real solution !");
    }
    long double phi = (1. / 3.) * std::acos(R/std::sqrt(Q*Q*Q));
    std::cout << static_cast<long long>(-2*std::sqrt(Q) * std::cos(phi) - a / 3 + 0.1) << " ";
    std::cout << static_cast<long long>(-2*std::sqrt(Q) * std::cos(phi + 2*stalg::pi/3) - a / 3 + 0.1) << " ";
    std::cout << static_cast<long long>(-2*std::sqrt(Q) * std::cos(phi - 2*stalg::pi/3) - a / 3 + 0.1) << " ";
    return 0;
}

}

#endif // __ST_ALG_CARDANO_H__
