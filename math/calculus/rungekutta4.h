#ifndef __ST_ALG_RUNGEKUTTA4__H__
#define __ST_ALG_RUNGEKUTTA4__H__

/* stalg rungekutta4
 * last change: 01.11.2017
 *
 * Численное интегрирование таблично заданной функции методом Рунге-Кутты 4 порядка.
 * На входе указатели begin, end, вещественное h - удвоенный шаг сетки. (разница между
 * отсчётами mas[i] и mas[i+2]). Возвращаемое значение - интеграл функции.
 */

namespace stalg
{
double rungekutta4(double* first_pos, double* last_pos, double h)
{
    double* mas = first_pos;
    int size = last_pos - first_pos;
    double S = 0.;
    for (int i = 0; i + 2 < size;  i += 2)
    {
        double k1 = mas[i];
        double k2 = mas[i + 1];
        double k3 = mas[i + 1];
        double k4 = mas[i + 2];
        double delta = (h / 6.) * (k1 + 2 * k2 + 2 * k3 + k4);
        S += delta;
    }
    return S;
}
}

#endif // __ST_ALG_RUNGEKUTTA4__H__
