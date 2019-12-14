#ifndef __ST_ALG_KMP_H__
#define __ST_ALG_KMP_H__

/* stalg kmp
 * last change: 4.12.2016
 *
 * Алгоритм Кнута-Морриса-Пратта поиска подстроки в строке, основанный на Z-функции.
 * Линейная асимптотика работы O(m + n), константа = 2 .
 */

#include <vector>
#include <algorithm>

namespace stalg
{
template<class T>
std::vector<int> z_function(const T& str)
{
    int n = str.size();
    std::vector<int> answer(n, 0);
    int l, r;
    l = 0;
    r = 1;
    for (int i = 1; i < n; ++i)
    {
        if (i < r)
        {
            answer[i] = std::min(r - i, answer[i - l]);
        }
        while ( ( i + answer[i] < n ) && ( str[answer[i]] == str[i + answer[i]]) )
        {
            ++answer[i];
        }
        if ( i + answer[i] > r)
        {
            l = i;
            r = i + answer[i];
        }
    }
    return answer;
}

template<class T>
std::vector<int> search_kmp(const T& pattern, const T& text, const T& marker = T("#"))
{
    std::vector<int> zf = stalg::z_function(pattern + marker + text);
    int ps = pattern.size();
    int ts = text.size();
    std::vector<int> answer;
    answer.reserve(ts);
    for (int i = 0; i + ps - 1 < text.size(); ++i)
    {
        if (zf[i + ps + 1] == ps)
        {
            answer.push_back(i);
        }
    }
    return answer;
}
}

#endif // __ST_ALG_KMP_H__
