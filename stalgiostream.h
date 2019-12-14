#ifndef __ST_ALG_IOSTREAM_H__
#define __ST_ALG_IOSTREAM_H__

// stalg iostream
// 30.09.2016

#include <ostream>
#include <vector>

#include "fraction/fraction.h"

// Для следующего оператора не помешала бы специализация для T = std::string
template<class T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& mas)
{
    out << "{";
    for (size_t i = 0; i < mas.size(); ++i)
    {
        out << mas[i];
        if (i + 1 < mas.size())
        {
            out << ", ";
        }
    }
    out << "}";
    return out;
}

template<class T>
std::ostream& operator << (std::ostream& out, const stalg::fraction<T>& frac)
{
    out << "fraction{" << frac.Numerator() << " / " << frac.Denominator() << "}";
    return out;
}

namespace stalg {
}

#endif // __ST_ALG_IOSTREAM_H__
