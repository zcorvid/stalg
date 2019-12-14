#ifndef __ST_ALG_MATH_H__
#define __ST_ALG_MATH_H__

/* stalg math
 * last change: 2019.08.05
 *
 * Сборник математических процедур.
 *
 */

#include <vector>
#include <algorithm>

// #include "../stalgcommon.h"
// #include "../stalgsvalka.h"

namespace stalg
{
    template<typename T>
    T zero_element()
    {
        return T(0);
    }

    template<typename T>
    T unit_element()
    {
        return T(1);
    }

    template<typename T>
    T abs(const T& argument)
    {
        if (argument < 0)
        {
            return -argument;
        }
        else
        {
            return argument;
        }
    }

    template<typename T>
    T sqr(const T& argument)
    {
        return argument * argument;
    }

    template<typename T>
    T cube(const T& argument)
    {
        return argument * argument * argument;
    }

    template<typename T>
    T power(const T& base, const unsigned int exponent)
    {
        T answer = unit_element<T>();
        for (unsigned int i = 0; i < exponent; ++i)
        {
            answer *= base;
        }
        return answer;
    }

    template<typename T>
    T bin_power_recursive(const T& base, unsigned int exponent)
    {
        if (!exponent)
        {
            return unit_element<T>();
        }
        else
        {
            return exponent & 1 ? sqr(bin_power(base, exponent >> 1)) * base : sqr(bin_power(base, exponent >> 1));
        }
    }

    template<typename T>
    T bin_power(const T& base, const unsigned int exponent)
    {
        T current_base = base;
        unsigned int current_exponent = exponent;
        T answer = unit_element<T>();
        while (current_exponent)
        {
            if (current_exponent & 1)
            {
                answer *= current_base;
            }
            current_base *= current_base;
            current_exponent >>= 1;
        }
        return answer;
    }

    template<class T>
    int sign_custom(const T& arg)
    {
        return arg < 0 ? -1 : 1;
    }

    /* Наибольший общий делитель (алгоритм Евклида).
     */
    template<class T>
    T gcd(T a, T b)
    {
        a *= sign_custom(a);
        b *= sign_custom(b);
        while(a && b)
        {
            T min_num = a < b ? a : b;
            T max_num = a < b ? b : a;
            a = max_num - min_num;
            b = min_num;
        }
        return a ? a : b;
    }

    /* Округление до ближайшего целого.
     */
    int round(const double arg)
    {
        int answer;
        if (arg >= 0)
        {
            answer = arg + 0.5;
        }
        else
        {
            answer = arg - 0.5;
        }
        return answer;
    }

    /*
    // Функция не протестирована! Использовать на свой страх и риск!
    template<class T>
    T lcm(const T& a, const T& b)
    {
        return a * b / gcd(a, b);
    }

    // Функция не протестирована! Использовать на свой страх и риск!
    // Наименьшее общее кратное чисел массива.
    int lcm_v(const std::vector<int>& mas)
    {
        std::vector<int> mas_d = mas;
        int answer = 0;
        if (mas.size() == 0)
        {
            answer = 1;
        } else if (mas.size() == 1)
        {
            answer = mas[0];
        }
        else
        {
            for (;!AllEquals(mas_d);)
            {
                int index_of_minimum = std::min_element(mas_d.begin(), mas_d.end()) - mas_d.begin();
                mas_d[index_of_minimum] += mas[index_of_minimum];
            }
            answer = mas_d[0];
        }
        return answer;
    }

    // Функция не протестирована! Использовать на свой страх и риск!
    // Наименьшее общее кратное чисел массива.
    // При использовании явно указывать шаблонный параметр.
    template<class T>
    T lcm_v(typename std::vector<T>::const_iterator begin, typename std::vector<T>::const_iterator end)
    {
        T answer = 0;
        int len = end - begin;
        if (len == 1)
        {
            answer = *begin;
        } else {
            int half = len / 2;
            answer = lcm(lcm_v<T>(begin, begin + half), lcm_v<T>(begin + half, end));
        }
    }*/

    bool is_power_of_two(const size_t x)
    {
        return x && !(x & (x - 1));
    }
}

#endif // __ST_ALG_MATH_H__
