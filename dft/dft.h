#ifndef __ST_ALG_DFT_H__
#define __ST_ALG_DFT_H__

/* stalg discrete Fourier transform
 * last change: 2019.08.05
 *
 * Дискретное преобразование Фурье.
 *
 * Асимптотика O(n*logn).
 *
 * Необходимо сделать: (1)
 *                     (2) Дать оценку константы в БПФ
 *                     (3) Универсализировать код, оставив одну функцию, вместо двух (прямое и обратное)
 *                     (4) Реализовать различные виды свёрток
 *                     (5) Свёртки по действию группы (это уже намного сложнее)
 *
 */

#if __cplusplus >= 201103L

#include <vector>
#include <complex>

#include "../stalgconst.h"
#include "../stalgcommon.h"

namespace stalg
{
/* Дискретное преобразование Фурье "в лоб", квадратичный алгоритм
 */
std::vector<std::complex<double>> dft_direct(const std::vector<double>& mas)
{
    const int N = mas.size();
    std::vector<std::complex<double>> answer(N);
    for (size_t i = 0; i < answer.size(); ++i)
    {
        answer[i] = 0;
        for (int j = 0; j < N; ++j)
        {
            answer[i] += mas[j] * std::polar(1., -2 * stalg::pi * i * j * 1. / N);
        }
    }
    return answer;
}
/* Обратное дискретное преобразование Фурье "в лоб", квадратичный алгоритм
 */
std::vector<std::complex<double>> inverse_dft_direct(const std::vector<std::complex<double>>& mas)
{
    const int N = mas.size();
    std::vector<std::complex<double>> answer(N);
    for (size_t i = 0; i < answer.size(); ++i)
    {
        answer[i] = 0;
        for (int j = 0; j < N; ++j)
        {
            answer[i] += mas[j] * std::polar(1., 2 * stalg::pi * i * j * 1. / N);
        }
        answer[i] /= N;
    }
    return answer;
}
/* Далее - быстрое дискретное преобразование Фурье, асимптотика O(nlogn).
 */
/* N - обязательно должно быть равно степени двойки
 * mas - массив, в котором памяти выделено не менее, чем на N элементов с шагом step
 */
void fft(std::complex<double> *mas, const int N, const int step = 1)
{
    if (N > 1)
    {
        fft(mas           , N / 2, 2 * step);
        fft(mas + 1 * step, N / 2, 2 * step);
        std::complex<double> *tmas = new std::complex<double>[N];
        for (int i = 0; i < N / 2; ++i)
        {
            std::complex<double> y0 = *(mas +      2 * i  * step);
            std::complex<double> y1 = *(mas + (1 + 2 * i) * step);
            *(tmas +          i ) = y0 + std::polar(1., -2 * stalg::pi * i * 1. / N) * y1;
            *(tmas + (N / 2 + i)) = y0 - std::polar(1., -2 * stalg::pi * i * 1. / N) * y1;
        }
        for (int i = 0; i < N; ++i)
        {
            *(mas + i * step) = *(tmas + i);
        }
        delete[] tmas;
    }
}
template<class InputIterator>
void fft(InputIterator begin, InputIterator end)
{
    fft(&(*begin), end - begin);
}
template<class TContainer>
void fft(TContainer &mas)
{
//    fft(mas.begin(), mas.end());
    fft(mas.data(), mas.size());
}
/* Возвращает массив нормированных амплитуд преобразования Фурье. Очень маленькие значения
 * заменяет нулём.
 */
std::vector<double> abs_mas_normed(const std::vector<std::complex<double>> &mas)
{
    std::vector<double> mas_amp;
    mas_amp.reserve(mas.size());
    for (size_t i = 0; i < mas.size(); ++i)
    {
        if (std::abs(mas[i]) < stalg::COMPARISON_THRESHOLD)
        {
            mas_amp.push_back(0);
        }
        else
        {
            mas_amp.push_back(std::abs(mas[i]) / mas.size());
        }
    }
    return mas_amp;
}
std::vector<std::complex<double>> get_fft(const std::vector<double> &mas)
{
    std::vector<std::complex<double>> answer;
    for (size_t i = 0; i < mas.size(); ++i)
    {
        answer.push_back(mas[i]);
    }
    fft(answer);
    return answer;
}
std::vector<std::complex<double>> get_fft(const std::vector<std::complex<double>> &mas)
{
    std::vector<std::complex<double>> answer(mas);
    fft(answer);
    return answer;
}
}

#endif // __cplusplus >= 201103L

#endif // __ST_ALG_DFT_H__
