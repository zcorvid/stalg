#ifndef __ST_ALG_GAUSS_H__
#define __ST_ALG_GAUSS_H__

#include <cmath>

#include "../stalgcommon.h"

namespace stalg
{
template<typename T>
void swap_rows(T **A, int ind1, int ind2, int m, int n, int start)
{
    if (ind1 != ind2)
    {
        for (int i = start; i < n; ++i)
        {
            T tmp      = A[ind1][i];
            A[ind1][i] = A[ind2][i];
            A[ind2][i] = tmp       ;
        }
    }
}

template<typename T>
bool get_nonzero(T **A, int i, int j, int m, int n)
{
    for (int ind = i; ind < m; ++ind)
    {
        if (fabs(A[ind][j]) > stalg::COMPARISON_THRESHOLD)
        {
            swap_rows(A, i, ind, m, n, j);
            return true;
        }
    }
    return false;
}

template<typename T>
void make_zero_under(T **A, int si, int sj, int m, int n)
{
    for (int i = si + 1; i < m; ++i)
    {
        T coef = -A[i][sj] / A[si][sj];
        for (int j = sj; j < n; ++j)
        {
            A[i][j] += A[si][j] * coef;
        }
    }
}

template<typename T>
void make_echelon(T **A, int m, int n)    // строк, столбцов
{
    for (int i = 0, j = 0; i < m && j < n; ++i, ++j)   // Перебираем строки
    {
        while (j < n && !get_nonzero(A, i, j, m, n))            // Ненулим уголок ступеньки
        {
            ++j;
        }
        if (j < n)
        {
            make_zero_under(A, i, j, m, n);
        }
    }
}
}

#endif // __ST_ALG_GAUSS_H__
