#include <vector>
#include <stdexcept>
#include <iostream>

#include "sort.h"

template<typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vec)
{
    os << "{";
    for (int i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i + 1 < vec.size())
        {
            os << ",";
        }
    }
    return os << "}";
}

template<typename T, typename U, typename V>
void CheckResult(T input, U result, V expected)
{
    if (!(result == expected))
    {
        std::cerr << "For input " << input
                  << " expected " << expected
                  << " but got " << result
                  << std::endl;
        throw std::runtime_error("Test failed.");
    }
}

template<typename T>
void TestSort(const std::vector<T>& input, const std::vector<T>& expected)
{
    std::vector<T> sorted = input;
    tst_sort(sorted.begin(), sorted.end());
    CheckResult(input, sorted, expected);
}

void TestSortAll()
{
    // int
    TestSort<int>({}, {});
    TestSort<int>({1}, {1});
    TestSort<int>({1, 2, 3}, {1, 2, 3});
    TestSort<int>({3, 2, 1}, {1, 2, 3});
    TestSort<int>({4, 8, 9, 2, 4, 3, 9, -3}, {-3, 2, 3, 4, 4, 8, 9, 9});
    // double
    TestSort<double>({}, {});
    TestSort<double>({1.}, {1.});
    TestSort<double>({1., 2., 3.}, {1., 2., 3.});
    TestSort<double>({3., 2., 1.}, {1., 2., 3.});
    TestSort<double>({4., 8., 9., 2., 4., 3., 9., -3.}, {-3., 2., 3., 4., 4., 8., 9., 9.});
}

void TestAll()
{
    TestSortAll();
}

int main()
{
    TestAll();
    std::cout << "Test OK." << std::endl;
    return 0;
}

