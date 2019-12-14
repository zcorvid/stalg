#ifndef __ST_ALG_AVER_H__
#define __ST_ALG_AVER_H__

/* stalg averager
 * last change: 2019.08.05
 *
 * Функции сглаживания выборки.
 *
 * --
 * Алгоритмы не оптимальны (не используются скользящие статистики).
 * Модуль не протестирован.
 *
 */

#include <vector>

namespace stalg
{
template<typename T>
QVector<T> averager_mean(const QVector<T>& t, const QVector<T>& x, const T& d, const int num)
{
    if(t.size() != x.size()) { qDebug() << "Different argument and variable sizes !"; return x; }
    QVector<T> answer(t.size());

    for(int i = 0; i < t.size(); ++i)
    {
        int weight = 1;
        answer[i]  = x[i];
        for(int j = 1; j <= num; ++j)
        {
            float l_val = 0, l_arg = t[i] - j * d;
            float r_val = 0, r_arg = t[i] + j * d;
            if(l_arg >= t.front())
            {
                ++weight;
                int k = std::upper_bound(t.begin(), t.end(), l_arg) - t.begin() - 1;
                if(fabs(t[k] - l_arg) < 1e-8) l_val = x[k];
                else
                {
                    float eps = (l_arg - t[k]) / (t[k + 1] - t[k]);
                    if (eps < 0) qDebug() << "eps error !" ;
                    l_val = ( (1 - eps) * x[k] + eps * x[k + 1] ) ;
                }
            }
            if(r_arg <= t.back())
            {
                ++weight;
                int k = std::lower_bound(t.begin(), t.end(), r_arg) - t.begin();
                if(fabs(t[k] - r_arg) < 1e-8) r_val = x[k];
                else
                {
                    float eps = (t[k] - r_arg) / (t[k] - t[k - 1]);
                    if(eps < 0) qDebug() << "eps error !" ;
                    r_val = ( eps * x[k - 1] + (1 - eps) * x[k] ) ;
                }
            }
            answer[i] += l_val + r_val;
        }
        answer[i] /= weight;
    }

    return answer;
}
template<class InputIterator>
std::vector<double> averager_mean(InputIterator first, InputIterator last, const int w)
{
    std::vector<double> answer;

    for (InputIterator it = first; it != last; ++it)
    {
        if (it < first + w || it + w >= last)
        {
            answer.push_back(*it);
        }
        else
        {
            double S = 0;
            for (int shift = -w; shift <= w; ++shift)
            {
                S += *(it + shift);
            }
            answer.push_back(S / (2 * w + 1.));
        }
    }

    return answer;
}

template<class TVector>
std::vector<double> averager_mean(const TVector& mas, const unsigned int w)
{
    std::vector<double> answer;

    for (unsigned int i = 0; i < mas.size(); ++i)
    {
        if (i < w || i + w >= mas.size())
        {
            answer.push_back(mas[i]);
        }
        else
        {
            double S = 0;
            for (int shift = -w; shift <= (int)w; ++shift)
            {
                S += mas[i + shift];
            }
            answer.push_back(S / (2 * w + 1.));
        }
    }

    return answer;
}


/*
template<typename T>
std::vector<T> averager_mean(const std::vector<T>& t, const std::vector<T>& x, const T& d, const int num = 2)
{
    if (t.size() != x.size())
    {
        std::cout << "Different argument and variable sizes !" << std::endl;
        // return std::vector<T>();
        return x;
    }
    int n = t.size() - 1;
    std::vector<T> answer(n + 1);

    for (int i = 0; i <= n; ++i)
    {
        int weight = 1;
        answer[i] = x[i];
        for (int j = 1; j <= num; ++j)
        {
            double l_val = 0;
            double r_val = 0;
            double l_arg = t[i] - j * d;
            double r_arg = t[i] + j * d;
            if (l_arg >= t.front())
            {
                ++weight;
                int k = std::upper_bound(t.begin(), t.end(), l_arg) - t.begin() - 1;
                if (fabs(t[k] - l_arg) < stalg::COMPARISON_THRESHOLD)
                {
                    l_val = x[k];
                }
                else
                {
                    double eps = (l_arg - t[k]) / (t[k + 1] - t[k]);
                    if (eps < 0)
                    {
                        std::cout << "eps error !" << std::endl;
                    }
                    l_val = ( (1 - eps) * x[k] + eps * x[k + 1] ) ;
                }
            }
            if (r_arg <= t.back())
            {
                ++weight;
                int k = std::lower_bound(t.begin(), t.end(), r_arg) - t.begin();
                if (fabs(t[k] - r_arg) < stalg::COMPARISON_THRESHOLD)
                {
                    r_val = x[k];
                }
                else
                {
                    double eps = (t[k] - r_arg) / (t[k] - t[k - 1]);
                    if (eps < 0)
                    {
                        std::cout << "eps error !" << std::endl;
                    }
                    r_val = ( eps * x[k - 1] + (1 - eps) * x[k] ) ;
                }
            }
            answer[i] += l_val;
            answer[i] += r_val;
        }
        answer[i] /= weight;
    }

    if (answer.size() != n + 1)
    {
        std::cout << "Error : answer.size() != n + 1" << std::endl;
    }

    return answer;
}

template<typename T>
std::vector<T> averager_integral1(const std::vector<T>& t, const std::vector<T>& x, const T& d)
{
    if (t.size() != x.size())
    {
        std::cout << "Different argument and variable sizes !" << std::endl;
        return std::vector<T>();
    }
    int n = t.size() - 1;
    std::vector<T> answer(n + 1);

    // Считаем массив S
    std::vector<T> S(n);
    S[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        S[i] = S[i - 1] + x[i] * (t[i + 1] - t[i - 1]);
    }

    for (int i = 0; i <= n; ++i)
    {
        int l = ;
        int r = ;
        T D1 = ;
        T D = ;
        answer[i] = 0.5 * ( S[r] - S[l] + D1 - D );
    }

    return answer;
}

template<typename T>
std::vector<T> averager_integral1_naive(const std::vector<T>& t, const std::vector<T>& x, const T& d)
{
    if (t.size() != x.size())
    {
        std::cout << "Different argument and variable sizes !" << std::endl;
        return std::vector<T>();
    }
    int n = t.size() - 1;
    std::vector<T> answer(n + 1);

    for (int i = 0; i <= n; ++i)
    {
        T tl = t[i] - d;
        T tr = t[i] + d;
        int il = -1;
        int ir = -1;
        for (int j = 0; j <= n; ++j)
        {
            if (t[j] > tl)
            {
                break;
            }
            else if (t[j] <= tl && j == n)
            {
                il = j;
                break;
            }
            else if (t[j] <= tl && t[j + 1] > tl)
            {
                il = j;
                break;
            }
        }
        for (int j = n; j >= 0; --j)
        {
            if (t[j] < tr)
            {
                break;
            }
            else if (t[j] >= tr && j == 0)
            {
                ir = j;
                break;
            }
            else if (t[j] >= tr && t[j - 1] < tr)
            {
                ir = j;
                break;
            }
        }
        answer[i] = 0;
        for (int j = il + 1; j <= ir; ++j)
        {
            answer[i] += 0.5 * (x[j - 1] + x[j]) * (t[j] - t[j - 1]);
        }
        if (il != -1)
        {
            answer[0] += 0.5 * (x[il] + ) * (t[il] - tl);
        }
    }

    return answer;
}
*/
}

#endif // __ST_ALG_AVER_H__
