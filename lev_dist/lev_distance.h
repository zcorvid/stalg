#ifndef __ST_ALG_LEV_DISTANCE_H__
#define __ST_ALG_LEV_DISTANCE_H__

/* stalg Levenshtein distance
 * last change: 28.02.2017
 *
 * Расстояние Левенштейна.
 *
 */

#include <string>
#include <algorithm>

#include <iostream>

namespace stalg
{
    template<class T>
    int eq_ld(const T& a1, const T& a2)
    {
        if (a1 == a2) {
            return 0;
        } else {
            return 1;
        }
    }

    template<class T1, class T2>
    int lev_distance(const T1& m1, const T2& m2)
    {
        const int s1 = m1.size();
        const int s2 = m2.size();
        int** d = new int*[s1 + 1];
        for (int i = 0; i <= s1; ++i) {
            d[i] = new int[s2 + 1];
        }
        d[0][0] = 0;
        for (int i = 1; i <= s1; ++i) {
            d[i][0] = i;
        }
        for (int j = 1; j <= s2; ++j) {
            d[0][j] = j;
        }
        for (int i = 1; i <= s1; ++i ) {
            for (int j = 1; j <= s2; ++j) {
                d[i][j] = std::min({d[i][j - 1] + 1, d[i - 1][j] + 1, d[i - 1][j - 1] + eq_ld(m1[i], m2[j])});
            }
        }
        const int answer = d[s1][s2];
        for (int i = 0; i <= s1; ++i) {
            delete[] d[i];
        }
        delete[] d;
        return answer;
    }

    int lev_distance_s(const std::string& m1, const std::string& m2)
    {
        return lev_distance<std::string, std::string>(m1, m2);
    }
}

#endif // __ST_ALG_LEV_DISTANCE_H__
