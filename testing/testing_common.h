#ifndef __ST_ALG_TESTING_COMMON_H__
#define __ST_ALG_TESTING_COMMON_H__

// stalg testing common functions
// 10.10.2016

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

#include "../stalgiostream.h"
#include "../stalgcommon.h"
#include "../math/stalgmath.h"

namespace stalg
{
    template<class U>
    void CheckDoubleResult(const std::string& message, const U& input_data, const double result, const double expected)
    {
        if (!(stalg::abs(result - expected) < stalg::COMPARISON_THRESHOLD)) {
            std::cout << "#Testing: " << message << std::endl;
            std::cout << "--------------Testing report------------" << std::endl;
//            std::cout << std::fixed << std::setprecision(20);
            std::cout << "For input : " << input_data << std::endl <<
                         "expected  : " << expected << std::endl <<
                         "but got   : " << result << std::endl;
            std::cout << "-------------------End------------------" << std::endl;
            throw std::runtime_error("Test failed");
        }
    }

    /*
    template<class U, class P>
    void CheckDoubleResult(const std::string& message, const U& input_data, const std::vector<double>& parameters, const double result, const double expected)
    {
        if (!(stalg::abs(result - expected) < stalg::COMPARISON_THRESHOLD)) {
            std::cout << "#Testing: " << message << std::endl;
            std::cout << "#Parameters: " << parameters << std::endl;
            std::cout << "--------------Testing report------------" << std::endl;
            std::cout << "For input : " << input_data << std::endl <<
                         "expected  : " << expected << std::endl <<
                         "but got   : " << result << std::endl;
            std::cout << "-------------------End------------------" << std::endl;
            throw std::runtime_error("Test failed");
        }
    }
    */

    template<class U, class V, class W>
    void CheckResult(const std::string& message, const U& input_data, const V& result, const W& expected)
    {
        if (!(result == expected)) {
            std::cout << "#Testing: " << message << std::endl;
            std::cout << "--------------Testing report------------" << std::endl;
            std::cout << "For input : " << input_data << std::endl <<
                         "expected  : " << expected << std::endl <<
                         "but got   : " << result << std::endl;
            std::cout << "-------------------End------------------" << std::endl;
            throw std::runtime_error("Test failed");
        }
    }

    template<class U1, class U2, class V, class W>
    void CheckResult(const std::string& message, const U1& input1, const U2& input2, const V& result, const W& expected)
    {
        if (!(result == expected)) {
            std::cout << "#Testing: " << message << std::endl;
            std::cout << "--------------Testing report------------" << std::endl;
            std::cout << "For input : " << input1 << ", " << input2 << std::endl <<
                         "expected  : " << expected << std::endl <<
                         "but got   : " << result << std::endl;
            std::cout << "-------------------End------------------" << std::endl;
            throw std::runtime_error("Test failed");
        }
    }
}

#endif // __ST_ALG_TESTING_COMMON_H__

