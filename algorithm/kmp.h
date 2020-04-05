#ifndef __ST_ALG_KMP_H__
#define __ST_ALG_KMP_H__

/* stalg kmp
 * last change: 2019.08.05
 *
 * Алгоритм Кнута-Морриса-Пратта поиска подстроки в строке, основанный на Z-функции.
 * Линейная асимптотика работы O(m + n), константа = 2 .
 *
 * >>> Перенесено в stalg2 <<<
 */

#include <vector>
#include <algorithm>

namespace stalg
{
/* Вычисляет z-функцию входного массива (обычно строки). Возвращает массив значений
 * z-ункции. Линейное время работы.
 *
 * Для подсчёта используется динамическое программирование.
 */
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

/* Выполняет поиск образца в тексте. Образец, который ищем - pattern, текст,
 * в котором ищем - text. Аргумент marker нужен в качестве разделителя, он
 * должен быть таким, который не встречается ни в образце ни в тексте в
 * качестве символа. Также он должен быть односимвольным. По умолчанию в
 * качестве маркера используется символ решётка '#'.
 *
 * Возвращает массив индексов, начиная с которых имеет место вхождение
 * образца в текст, это значит, что если некое число k есть в возвращённом
 * массиве, то начиная с индекса k подстрока в тексте text совпадает с
 * образцом.
 *
 * Алгоритм Кнута-Морриса-Пратта, линейное время работы.
 */
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
