#ifndef __ST_ALG_FRACTION_TEST_H__
#define __ST_ALG_FRACTION_TEST_H__

#include <iostream>

#include "fraction.h"
#include "../stalgiostream.h"
#include "../testing/testing_common.h"

template<class T>
void TestPlus(const stalg::fraction<T>& lhs, const stalg::fraction<T>& rhs, const stalg::fraction<T>& sum)
{
    stalg::CheckResult("stalg::fraction Addition", lhs, rhs, lhs + rhs, sum);
}

template<class T>
void TestMinus(const stalg::fraction<T>& lhs, const stalg::fraction<T>& rhs, const stalg::fraction<T>& diff)
{
    stalg::CheckResult("stalg::fraction Substraction", lhs, rhs, lhs - rhs, diff);
}

template<class T>
void TestMultiply(const stalg::fraction<T>& lhs, const stalg::fraction<T>& rhs, const stalg::fraction<T>& mult)
{
    stalg::CheckResult("stalg::fraction Multiplication", lhs, rhs, lhs * rhs, mult);
}

template<class T>
void TestDivide(const stalg::fraction<T>& lhs, const stalg::fraction<T>& rhs, const stalg::fraction<T>& quotient)
{
    stalg::CheckResult("stalg::fraction Division", lhs, rhs, lhs / rhs, quotient);
}

void TestPlus_All()
{
    // Общие тесты
    TestPlus<int>({1, 1}, {1, 1}, 2);
    TestPlus<int>({1, 1}, 1, 2);
    TestPlus<int>({1, 1}, {0, 1}, 1);
    TestPlus<int>({1, 1}, 0, 1);
    TestPlus<int>({1, 2}, 1, {3, 2});
    TestPlus<int>({-1, 2}, 1, {1, 2});
    // Тесты с нулём в ответе
    TestPlus<int>({1, 1}, {-1, 1}, 0);
    TestPlus<int>({1, 2}, {-1, 2}, 0);
    TestPlus<int>({5, 3}, {-5, 3}, 0);
    TestPlus<int>({1, 1}, -1, 0);
    TestPlus<int>(-1, {1, 1}, 0);
}

void TestMinus_All()
{
    // Общие тесты
    TestMinus<int>({1, 1}, {1, 1}, 0);
    TestMinus<int>({1, 1}, 1, 0);
    TestMinus<int>({1, 1}, {0, 1}, 1);
    TestMinus<int>({1, 1}, 0, 1);
    TestMinus<int>({1, 2}, 1, {-1, 2});
    TestMinus<int>({-1, 2}, 1, {-3, 2});
    // Тесты с нулём в ответе
    TestMinus<int>({1, 1}, {1, 1}, 0);
    TestMinus<int>({1, 2}, {1, 2}, 0);
    TestMinus<int>({5, 3}, {5, 3}, 0);
    TestMinus<int>({1, 1}, 1, 0);
    TestMinus<int>(1, {1, 1}, 0);
}

void TestMultiply_All()
{
    // Общие тесты
    TestMultiply<int>({1, 1}, {1, 1}, 1);
    TestMultiply<int>({1, 1}, 1, 1);
    TestMultiply<int>({1, 1}, {0, 1}, 0);
    TestMultiply<int>({1, 1}, 0, 0);
    TestMultiply<int>({1, 2}, 1, {1, 2});
    TestMultiply<int>({-1, 2}, 1, {-1, 2});
    TestMultiply<int>({1, 1}, {1, 1}, 1);
    TestMultiply<int>({1, 2}, {1, 2}, {1, 4});
    TestMultiply<int>({5, 3}, {5, 3}, {25, 9});
    TestMultiply<int>({1, 1}, 1, 1);
    TestMultiply<int>(1, {1, 1}, 1);
}

void TestDivide_All()
{
    // Общие тесты
    TestDivide<int>({1, 1}, {1, 1}, 1);
    TestDivide<int>({1, 1}, 1, 1);
    TestDivide<int>({1, 1}, {2, 1}, {1, 2});
    TestDivide<int>({1, 1}, {1, 2}, 2);
    TestDivide<int>(1, {1, 2}, 2);
    TestDivide<int>({1, 2}, {1, 3}, {3, 2});
    TestDivide<int>({-1, 2}, 1, {-1, 2});
    TestDivide<int>({1, 1}, {1, 1}, 1);
    TestDivide<int>({1, 2}, {1, 2}, 1);
    TestDivide<int>({5, 3}, {3, 5}, {25, 9});
    TestDivide<int>({1, 1}, 1, 1);
    TestDivide<int>(1, {1, 1}, 1);
}

void TestArithmeticOperations_All()
{
    TestPlus_All();
    TestMinus_All();
    TestMultiply_All();
    TestDivide_All();
}

void TestFraction_All()
{
    TestArithmeticOperations_All();

    std::cout << "OK" << std::endl;
}

#endif // __ST_ALG_FRACTION_TEST_H__
