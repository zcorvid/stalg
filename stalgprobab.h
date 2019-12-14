#ifndef __ST_ALG_PROBAB_H__
#define __ST_ALG_PROBAB_H__

// stalg probability
// 10.08.2016

// Реализует вероятностные испытания. Использует генератор псевдослучайных чисел языка C.
// Перед первым обращением к модулю необходимо вручную выполнить инициализацию рандомайзера,
// автоматически он инициализирован не будет.

namespace stalg
{
    bool TryBernoulli(const double p_parameter);
    bool TryBernoulli(const int p_numerator, const int p_denominator);
}

#endif // __ST_ALG_PROBAB_H__
