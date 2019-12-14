#ifndef __ST_ALG_WEIGHT_H__
#define __ST_ALG_WEIGHT_H__

/* stalg weight
 * last change: 22.11.2016
 *
 * Сборник весовых функций сигнатуры T(const T&).
 * Этим функциям осмысленно давать лишь неотрицательные аргументы, иначе могут быть
 * отрицательные веса. Возможно в дальнейшем этот недостаток будет убран (или превращён
 * в фичу).
 *
 * Список функций:     1) Стандартный вес (тождественная функция)
 *                     2) Квадратичный вес
 *                     3) (пока нету) Экспоненциальный вес
 */

#include "stalgmath.h"

namespace stalg
{
namespace weight
{
    template<class T>
    T standard_weight(const T& arg)
    {
        return arg;
    }

    template<class T>
    T squared_weight(const T& arg)
    {
        return arg * arg;
    }
}

namespace ml_weight {
    template<class T>
    T biquadratic_weight(const T& arg)
    {
        if (stalg::abs(arg) > 1)
        {
            return 0;
        }
        else
        {
            return stalg::sqr(1 - stalg::sqr(arg));
        }
    }
}
}

#endif // __ST_ALG_WEIGHT_H__
