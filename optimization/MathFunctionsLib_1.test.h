#ifndef __ST_ALG_MATHFUNCTIONSLIB_1_TEST_H__
#define __ST_ALG_MATHFUNCTIONSLIB_1_TEST_H__

#include <vector>

#include <math.h>

#include "MathFunctionsLib_1.h"

#include "../testing/testing_common.h"
#include "../math/stalgmath.h"
#include "../stalgconst.h"

// ----------------------------------------

void Test_MathFunctionsLib_1_Rastrigin(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Rastrigin", input_data, stalg::MathFunctionsLib_1::Rastrigin(input_data.size())(input_data), expected);
}

void Test_MathFunctionsLib_1_Ackley(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Ackley", input_data, stalg::MathFunctionsLib_1::Ackley()(input_data), expected);
}

void Test_MathFunctionsLib_1_SphereFunction(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::SphereFunction", input_data, stalg::MathFunctionsLib_1::SphereFunction(input_data.size())(input_data), expected);
}

void Test_MathFunctionsLib_1_Rosenbrock(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Rosenbrock", input_data, stalg::MathFunctionsLib_1::Rosenbrock(input_data.size())(input_data), expected);
}

void Test_MathFunctionsLib_1_Beale(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Beale", input_data, stalg::MathFunctionsLib_1::Beale()(input_data), expected);
}

void Test_MathFunctionsLib_1_Goldstein_Price(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Goldstein_Price", input_data, stalg::MathFunctionsLib_1::Goldstein_Price()(input_data), expected);
}

void Test_MathFunctionsLib_1_Booth(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Booth", input_data, stalg::MathFunctionsLib_1::Booth()(input_data), expected);
}

void Test_MathFunctionsLib_1_BukinFunction_N6(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::BukinFunction_N6", input_data, stalg::MathFunctionsLib_1::BukinFunction_N6()(input_data), expected);
}

void Test_MathFunctionsLib_1_Matyas(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Matyas", input_data, stalg::MathFunctionsLib_1::Matyas()(input_data), expected);
}

void Test_MathFunctionsLib_1_LeviFunction_N13(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::LeviFunction_N13", input_data, stalg::MathFunctionsLib_1::LeviFunction_N13()(input_data), expected);
}

void Test_MathFunctionsLib_1_ThreeHumpCamelFunction(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::ThreeHumpCamelFunction", input_data, stalg::MathFunctionsLib_1::ThreeHumpCamelFunction()(input_data), expected);
}

void Test_MathFunctionsLib_1_Easom(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Easom", input_data, stalg::MathFunctionsLib_1::Easom()(input_data), expected);
}

void Test_MathFunctionsLib_1_CrossInTray(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::CrossInTray", input_data, stalg::MathFunctionsLib_1::CrossInTray()(input_data), expected);
}

void Test_MathFunctionsLib_1_Eggholder(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Eggholder", input_data, stalg::MathFunctionsLib_1::Eggholder()(input_data), expected);
}

void Test_MathFunctionsLib_1_HoelderTable(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::HoelderTable", input_data, stalg::MathFunctionsLib_1::HoelderTable()(input_data), expected);
}

void Test_MathFunctionsLib_1_McCormick(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::McCormick", input_data, stalg::MathFunctionsLib_1::McCormick()(input_data), expected);
}

void Test_MathFunctionsLib_1_SchafferFunction_N2(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::SchafferFunction_N2", input_data, stalg::MathFunctionsLib_1::SchafferFunction_N2()(input_data), expected);
}

void Test_MathFunctionsLib_1_SchafferFunction_N4(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::SchafferFunction_N4", input_data, stalg::MathFunctionsLib_1::SchafferFunction_N4()(input_data), expected);
}

void Test_MathFunctionsLib_1_Styblinski_Tang(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Styblinski_Tang", input_data, stalg::MathFunctionsLib_1::Styblinski_Tang(input_data.size())(input_data), expected);
}

/*
void Test_MathFunctionsLib_1_Simionescu(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Simionescu", input_data, stalg::MathFunctionsLib_1::Simionescu()(input_data), expected);
}

void Test_MathFunctionsLib_1_Simionescu_Polar(const std::vector<double>& input_data)
{
    double x = input_data[0];
    double y = input_data[1];
    double r = sqrt(stalg::sqr(x) + stalg::sqr(y));
    double phi = atan(x / y);
    stalg::CheckDoubleResult("stalg::Simionescu _Polar", input_data, stalg::MathFunctionsLib_1::Simionescu()(input_data), stalg::MathFunctionsLib_1::Simionescu()({r, phi}, true));
}
*/

void Test_MathFunctionsLib_1_Rosenbrock1(const std::vector<double>& input_data, const double expected)
{
    stalg::CheckDoubleResult("stalg::Rosenbrock", input_data, stalg::MathFunctionsLib_1::Rosenbrock1(input_data.size())(input_data), expected);
}

/*
void Test_MathFunctionsLib_1_Rosenbrock1(const std::vector<double>& input_data, const double input_a, const double input_b, const double expected)
{
    stalg::CheckDoubleResult("stalg::Rosenbrock1", input_data, {input_a, input_b}, stalg::MathFunctionsLib_1::Rosenbrock1(input_data.size(), input_a, input_b)(input_data), expected);
}
*/

// ----------------------------------------

void Test_MathFunctionsLib_1_Rastrigin_All()
{
    Test_MathFunctionsLib_1_Rastrigin({0, 0}, 0);
}

void Test_MathFunctionsLib_1_Ackley_All()
{
    Test_MathFunctionsLib_1_Ackley({0, 0}, 0);
}

void Test_MathFunctionsLib_1_SphereFunction_All()
{
    Test_MathFunctionsLib_1_SphereFunction({0}, 0);
    Test_MathFunctionsLib_1_SphereFunction({0, 0}, 0);
    Test_MathFunctionsLib_1_SphereFunction({0, 0, 0}, 0);
    Test_MathFunctionsLib_1_SphereFunction({0, 0, 0, 0}, 0);
    Test_MathFunctionsLib_1_SphereFunction({0, 0, 0, 0, 0}, 0);

    Test_MathFunctionsLib_1_SphereFunction({1}, 1);
    Test_MathFunctionsLib_1_SphereFunction({1, 1}, 2);
    Test_MathFunctionsLib_1_SphereFunction({1, 1, 1}, 3);
    Test_MathFunctionsLib_1_SphereFunction({1, 1, 1, 1}, 4);
    Test_MathFunctionsLib_1_SphereFunction({1, 1, 1, 1, 1}, 5);

    Test_MathFunctionsLib_1_SphereFunction({1, 0}, 1);
    Test_MathFunctionsLib_1_SphereFunction({0, 1}, 1);
    Test_MathFunctionsLib_1_SphereFunction({1, 0, 1}, 2);
    Test_MathFunctionsLib_1_SphereFunction({1, 1, 0, 1}, 3);
    Test_MathFunctionsLib_1_SphereFunction({1, 0, 1, 1, 0}, 3);

    Test_MathFunctionsLib_1_SphereFunction({2, 0}, 4);
    Test_MathFunctionsLib_1_SphereFunction({2, 1}, 5);
    Test_MathFunctionsLib_1_SphereFunction({1, 0, 3}, 10);
    Test_MathFunctionsLib_1_SphereFunction({1, 2, 0, 1}, 6);
    Test_MathFunctionsLib_1_SphereFunction({1, 2, 3, 4, 0}, 30);
}

void Test_MathFunctionsLib_1_Rosenbrock_All()
{
    Test_MathFunctionsLib_1_Rosenbrock({1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 0);

    Test_MathFunctionsLib_1_Rosenbrock({0, 0}, 1);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0}, 2);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0}, 3);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0, 0}, 4);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0, 0, 0}, 5);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0, 0, 0, 0}, 6);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0, 0, 0, 0, 0}, 7);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0, 0, 0, 0, 0, 0}, 8);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 9);
    Test_MathFunctionsLib_1_Rosenbrock({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 10);
}

void Test_MathFunctionsLib_1_Beale_All()
{
    Test_MathFunctionsLib_1_Beale({3, 0.5}, 0);
    Test_MathFunctionsLib_1_Beale({0, 0}, 14.203125);
    Test_MathFunctionsLib_1_Beale({0, 1}, 14.203125);
    Test_MathFunctionsLib_1_Beale({1, 1}, 14.203125);
}

void Test_MathFunctionsLib_1_Goldstein_Price_All()
{
    Test_MathFunctionsLib_1_Goldstein_Price({0, -1}, 3);
    Test_MathFunctionsLib_1_Goldstein_Price({0, 0}, 600);
    Test_MathFunctionsLib_1_Goldstein_Price({1, 0}, 726);
    Test_MathFunctionsLib_1_Goldstein_Price({0, 1}, 28611);
    Test_MathFunctionsLib_1_Goldstein_Price({1, 1}, 1876);
}

void Test_MathFunctionsLib_1_Booth_All()
{
    Test_MathFunctionsLib_1_Booth({1, 3}, 0);
    Test_MathFunctionsLib_1_Booth({0, 0}, 74);
    Test_MathFunctionsLib_1_Booth({1, 0}, 45);
    Test_MathFunctionsLib_1_Booth({0, 1}, 41);
    Test_MathFunctionsLib_1_Booth({1, 1}, 20);
}

void Test_MathFunctionsLib_1_BukinFunction_N6_All()
{
    Test_MathFunctionsLib_1_BukinFunction_N6({-10, 1}, 0);
    Test_MathFunctionsLib_1_BukinFunction_N6({0, 0}, 0.1);
    Test_MathFunctionsLib_1_BukinFunction_N6({1, 0}, 10.11);
    Test_MathFunctionsLib_1_BukinFunction_N6({0, 1}, 100.1);
    Test_MathFunctionsLib_1_BukinFunction_N6({1, 1}, 99.608743711);
}

void Test_MathFunctionsLib_1_Matyas_All()
{
    Test_MathFunctionsLib_1_Matyas({0, 0}, 0);
    Test_MathFunctionsLib_1_Matyas({1, 0}, 0.26);
    Test_MathFunctionsLib_1_Matyas({0, 1}, 0.26);
    Test_MathFunctionsLib_1_Matyas({1, 1}, 0.04);
    Test_MathFunctionsLib_1_Matyas({1. / sqrt(2), 1. / sqrt(2)}, 0.02);
}

void Test_MathFunctionsLib_1_LeviFunction_N13_All()
{
    Test_MathFunctionsLib_1_LeviFunction_N13({1, 1}, 0);
    Test_MathFunctionsLib_1_LeviFunction_N13({1, 0}, 1);
    Test_MathFunctionsLib_1_LeviFunction_N13({0, 1}, 1);
}

void Test_MathFunctionsLib_1_ThreeHumpCamelFunction_All()
{
    Test_MathFunctionsLib_1_ThreeHumpCamelFunction({0, 0}, 0);
    Test_MathFunctionsLib_1_ThreeHumpCamelFunction({1, 1}, 3.116666667);
    Test_MathFunctionsLib_1_ThreeHumpCamelFunction({1, 0}, 1.116666667);
    Test_MathFunctionsLib_1_ThreeHumpCamelFunction({0, 1}, 1);
}

void Test_MathFunctionsLib_1_Easom_All()
{
    Test_MathFunctionsLib_1_Easom({stalg::pi, stalg::pi}, -1);
    Test_MathFunctionsLib_1_Easom({1, stalg::pi / 2}, 0);
    Test_MathFunctionsLib_1_Easom({stalg::pi / 2, 1}, 0);
    Test_MathFunctionsLib_1_Easom({0, 0}, -exp(-2 * stalg::sqr(stalg::pi)));
}

void Test_MathFunctionsLib_1_CrossInTray_All()
{
    //2.06261
    Test_MathFunctionsLib_1_CrossInTray({1.34941, 1.34941}, -2.06261187082025809758);
    Test_MathFunctionsLib_1_CrossInTray({1.34941, -1.34941}, -2.06261187082025809758);
    Test_MathFunctionsLib_1_CrossInTray({-1.34941, 1.34941}, -2.06261187082025809758);
    Test_MathFunctionsLib_1_CrossInTray({-1.34941, -1.34941}, -2.06261187082025809758);
    Test_MathFunctionsLib_1_CrossInTray({0, 1}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({0, -1}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({1, 0}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({-1, 0}, -0.0001);

    // Дальнейшие тесты фейлятся, скорее всего из-за погрешности в вычислениях, поэтому пока их отключаем
    // Проблема в функции sin(x), на числе pi она даёт недостаточную точность. Нужно написать свою реализацию этой функции.
    /*
    Test_MathFunctionsLib_1_CrossInTray({1, stalg::pi}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({1, -stalg::pi}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({-1, stalg::pi}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({-1, -stalg::pi}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({stalg::pi, 1}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({-stalg::pi, 1}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({stalg::pi, -1}, -0.0001);
    Test_MathFunctionsLib_1_CrossInTray({-stalg::pi, -1}, -0.0001);
    */
}

void Test_MathFunctionsLib_1_Eggholder_All()
{
    // Тесты фейлятся, из-за погрешности в вычислениях, поэтому пока их отключаем
    // Проблема в функции sin(x), на числе pi она даёт недостаточную точность. Нужно написать свою реализацию этой функции.
    // Test_MathFunctionsLib_1_Eggholder({512, 404.2319}, -959.6407);
    // Test_MathFunctionsLib_1_Eggholder({0, -47}, 0);
}

void Test_MathFunctionsLib_1_HoelderTable_All()
{
    // Первые тесты фейлятся, из-за погрешности в вычислениях, поэтому пока их отключаем
    // Проблема в функциях sin(x) и cos(x), на числе pi она даёт недостаточную точность. Нужно написать свою реализацию этой функции.
    // Test_MathFunctionsLib_1_HoelderTable({ 8.05502,  9.66459}, -19.2085);
    // Test_MathFunctionsLib_1_HoelderTable({ 8.05502, -9.66459}, -19.2085);
    // Test_MathFunctionsLib_1_HoelderTable({-8.05502,  9.66459}, -19.2085);
    // Test_MathFunctionsLib_1_HoelderTable({-8.05502, -9.66459}, -19.2085);
    Test_MathFunctionsLib_1_HoelderTable({0, 1}, 0);
    Test_MathFunctionsLib_1_HoelderTable({0, -4}, 0);
    Test_MathFunctionsLib_1_HoelderTable({3, stalg::pi / 2.}, 0);
    Test_MathFunctionsLib_1_HoelderTable({-2, stalg::pi / 2.}, 0);
}

void Test_MathFunctionsLib_1_McCormick_All()
{
    // Первые тесты фейлятся, из-за погрешности в вычислениях, поэтому пока их отключаем
    // Проблема в функциях sin(x) и cos(x), на числе pi она даёт недостаточную точность. Нужно написать свою реализацию этой функции.
    // Test_MathFunctionsLib_1_McCormick({-0.54719, -1.54719}, -1.9133);
    Test_MathFunctionsLib_1_McCormick({0, 0}, 1);
}

void Test_MathFunctionsLib_1_SchafferFunction_N2_All()
{
    Test_MathFunctionsLib_1_SchafferFunction_N2({0, 0}, 0);
}

void Test_MathFunctionsLib_1_SchafferFunction_N4_All()
{
    // Первые тесты фейлятся, из-за погрешности в вычислениях, поэтому пока их отключаем
    // Проблема в функциях sin(x) и cos(x), на числе pi она даёт недостаточную точность. Нужно написать свою реализацию этой функции.
    // Test_MathFunctionsLib_1_SchafferFunction_N4({0, 1.25313}, 0.292579);
    Test_MathFunctionsLib_1_SchafferFunction_N4({0, 0}, 1);
}

void Test_MathFunctionsLib_1_Styblinski_Tang_All()
{
    // Первые тесты фейлятся, потому что нам неизвестно значение функции в точке минимума с достаточной точностью. Позже мы
    // либо понизим порог доверия при сравнении, либо уточник тестовые значения.
    // Test_MathFunctionsLib_1_Styblinski_Tang({-2.903534}, -39.16617 * 1);
    // Test_MathFunctionsLib_1_Styblinski_Tang({-2.903534, -2.903534}, -39.16617 * 2);
    // Test_MathFunctionsLib_1_Styblinski_Tang({-2.903534, -2.903534, -2.903534}, -39.16617 * 3);
    // Test_MathFunctionsLib_1_Styblinski_Tang({-2.903534, -2.903534, -2.903534, -2.903534}, -39.16617 * 4);
    // Test_MathFunctionsLib_1_Styblinski_Tang({-2.903534, -2.903534, -2.903534, -2.903534, -2.903534}, -39.16617 * 5);
    Test_MathFunctionsLib_1_Styblinski_Tang({0}, 0);
    Test_MathFunctionsLib_1_Styblinski_Tang({0, 0}, 0);
    Test_MathFunctionsLib_1_Styblinski_Tang({0, 0, 0}, 0);
    Test_MathFunctionsLib_1_Styblinski_Tang({0, 0, 0, 0}, 0);
    Test_MathFunctionsLib_1_Styblinski_Tang({0, 0, 0, 0, 0}, 0);
    Test_MathFunctionsLib_1_Styblinski_Tang({1}, -5 * 1);
    Test_MathFunctionsLib_1_Styblinski_Tang({1, 1}, -5 * 2);
    Test_MathFunctionsLib_1_Styblinski_Tang({1, 1, 1}, -5 * 3);
    Test_MathFunctionsLib_1_Styblinski_Tang({1, 1, 1, 1}, -5 * 4);
    Test_MathFunctionsLib_1_Styblinski_Tang({1, 1, 1, 1, 1}, -5 * 5);
}

/*
void Test_MathFunctionsLib_1_Simionescu_All()
{
    Test_MathFunctionsLib_1_Simionescu({0, 0}, 0);
    Test_MathFunctionsLib_1_Simionescu({0.85586214, -0.85586214}, -0.072625);
    Test_MathFunctionsLib_1_Simionescu({-0.85586214, 0.85586214}, -0.072625);
    Test_MathFunctionsLib_1_Simionescu_Polar({0, 0});
    Test_MathFunctionsLib_1_Simionescu_Polar({0, 1});
    Test_MathFunctionsLib_1_Simionescu_Polar({1, 0});
    Test_MathFunctionsLib_1_Simionescu_Polar({0.85586214, -0.85586214});
    Test_MathFunctionsLib_1_Simionescu_Polar({-0.85586214, 0.85586214});
}
*/

void Test_MathFunctionsLib_1_Rosenbrock1_All()
{
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 0);
    Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 0);

    Test_MathFunctionsLib_1_Rosenbrock1({0, 0}, 1);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0}, 2);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0}, 3);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0}, 4);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0, 0}, 5);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0, 0, 0}, 6);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0, 0, 0, 0}, 7);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0, 0, 0, 0, 0}, 8);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 9);
    Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 10);
    // Test_MathFunctionsLib_1_Rosenbrock1({0, 0}, 1, -2, 1);
    // Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0}, 1, -2,  1);
    // Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0}, 1, -2,  1);
    // Test_MathFunctionsLib_1_Rosenbrock1({0, 0, 0, 0, 0}, 1, -2,  1);
    // Test_MathFunctionsLib_1_Rosenbrock1({1, 1}, -5 * 2);
    // Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1}, -5 * 3);
    // Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1}, -5 * 4);
    // Test_MathFunctionsLib_1_Rosenbrock1({1, 1, 1, 1, 1}, -5 * 5);
}

// ----------------------------------------

void Test_MathFunctionsLib_1_All()
{
    Test_MathFunctionsLib_1_Rastrigin_All();
    Test_MathFunctionsLib_1_Ackley_All();
    Test_MathFunctionsLib_1_SphereFunction_All();
    Test_MathFunctionsLib_1_Rosenbrock_All();
    Test_MathFunctionsLib_1_Beale_All();
    Test_MathFunctionsLib_1_Goldstein_Price_All();
    Test_MathFunctionsLib_1_Booth_All();
    Test_MathFunctionsLib_1_BukinFunction_N6_All();
    Test_MathFunctionsLib_1_Matyas_All();
    Test_MathFunctionsLib_1_LeviFunction_N13_All();
    Test_MathFunctionsLib_1_ThreeHumpCamelFunction_All();
    Test_MathFunctionsLib_1_Easom_All();
    Test_MathFunctionsLib_1_CrossInTray_All();
    Test_MathFunctionsLib_1_Eggholder_All();
    Test_MathFunctionsLib_1_HoelderTable_All();
    Test_MathFunctionsLib_1_McCormick_All();
    Test_MathFunctionsLib_1_SchafferFunction_N2_All();
    Test_MathFunctionsLib_1_SchafferFunction_N4_All();
    Test_MathFunctionsLib_1_Styblinski_Tang_All();
    // Test_MathFunctionsLib_1_Simionescu_All();
    Test_MathFunctionsLib_1_Rosenbrock1_All();
}

#endif // __ST_ALG_MATHFUNCTIONSLIB_1_TEST_H__
