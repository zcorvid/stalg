#ifndef __ST_ALG_MSTAT_H__
#define __ST_ALG_MSTAT_H__

/* stalg mstat
 * last change: 2019.08.05
 *
 * Функции скользящих статистик.
 *
 */

#include <deque>

#include "../math/stalgmath.h"

namespace stalg
{
namespace moving
{
/* Скользящий минимум. Входящие параметры: src (массив данных), N (размер массива
 * данных), src_tep (шаг в массиве данных). Такми образом, последний элемент из
 * массива данных будет rc[0 + (N - 1) * src_step].
 *
 * Выходные данные:
 * dst и dst_step используются аналогично src, в dst будет положен массив скользящих
 * минимумов, размер dst предполагается достаточным для размещения массива минимумов,
 * его размер не проверяется.
 *
 * w - размер окна.
 *
 * Линейное время работы. Используются деки.
 */
template<class T>
void min(T *src, int N, int src_step, T *dst, int dst_step, int w)
{
    std::deque<int> dq;
    for (int i = 0; i < w; ++i)
    {
        while (!dq.empty() && src[dq.back() * src_step] > src[i * src_step] )
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    dst[0 * dst_step] = src[dq.front() * src_step];

    for (int i = w; i < N; ++i)
    {
        if (dq.front() == i - w)
        {
            dq.pop_front();
        }
        while (!dq.empty() && src[dq.back() * src_step] > src[i * src_step] )
        {
            dq.pop_back();
        }
        dq.push_back(i);
        dst[(i - w + 1) * dst_step] = src[dq.front() * src_step];
    }
}
} // namespace moving
} // namespace stalg

#endif // __ST_ALG_MSTAT_H__
