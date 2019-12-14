#ifndef __ST_ALG_CLUST_H__
#define __ST_ALG_CLUST_H__

#include <vector>
#include <functional>

#include "../ds/dsu.h"
#include "../math/metric.h"

namespace stalg
{
// Графовая кластеризация с фиксированным порогом
template<typename TMas, typename T>
std::vector<int> clusterize(  const TMas &mas, const double border
                            , std::function<double(const T&, const T&)> distance)
{
    std::vector<int> mark;
    stalg::DSU dsu(mas.size());
    for (int i = 0; i < mas.size(); ++i)
    {
        mark.push_back(i);
        dsu.MakeSet(i);
    }
    for (int i = 0; i < mas.size(); ++i)
    {
        for (int j = i + 1; j < mas.size(); ++j)
        {
            if (distance(mas[i], mas[j]) < border)
            {
                dsu.Union(i, j);
            }
        }
    }
    for (int i = 0; i < mark.size(); ++i)
    {
        mark[i] = dsu.Find(mark[i]);
    }
    return mark;
}

// Иерархическая кластеризация, метод графа дистанций, расстояние по среднему
template<typename TMas, typename T>
QVector<int> clusterize2(  const TMas &mas
                         , std::function<double(const T&, const T&)> distance)
{
    Q_UNUSED(mas);
    Q_UNUSED(distance);
//    int
    return QVector<int>();
}

//
//template<typename TMas, typename T>
QVector<int> clusterize3(  const QVector<QPoint> &mas
                         , std::function<double(const QPoint&, const QPoint&)> distance)
{
    // Если точек слишком мало - не работаем
    if (mas.size() < 2)
    {
        return QVector<int>();
    }
    int N = mas.size();
    QVector<QPoint> centroid(mas);
    QVector<int>    centSize(N, 1);
    // 1. Инициализирование таблицы попарных дистанций
    /* Для ускорения будем заполнять только d[i][j] для i < j (в 2 раза меньше считать)
     */
    double **d = stalg::Allocate2dArray<double>(N, N);
    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            d[i][j] = distance(mas[i], mas[j]);
        }
    }
    stalg::DSU dsu(N + 1);
    // 2. Ищем наименьшую дистанцию d[][]
    int iMin = 0;
    int jMin = iMin + 1;
    double dMin = d[iMin][jMin];
    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            double dCurr = d[i][j];
            if (dCurr < dMin - stalg::COMPARISON_THRESHOLD)
            {
                iMin = i;
                jMin = j;
                dMin = dCurr;
            }
        }
    }
    // Объединяем два ближайших кластера
    dsu.Union(iMin, jMin);
    // Хочется как-то гарантировать, что parent[x] <= x , это правда ???????????????


    // Пересчитываем центр нового кластера
    centroid[iMin]  = centroid[iMin] * centSize[iMin] + centroid[jMin] * centSize[jMin];
    centroid[iMin] /= centSize[iMin] + centSize[jMin];
//    centroid[jMin]  = centroid[iMin];
    // Обновляем размер нового кластера
    centSize[iMin] += centSize[jMin];
//    centSize[jMin]  = centSize[iMin];
    stalg::Free2dArray(d, N, N);
    return QVector<int>();
}

// Кластеризация методом k-средних
template<typename TWeight>
QVector<int> clusterize1(  const QVector<TWeight> &mas
                         , std::function<double(const TWeight&, const TWeight&)> distance
                         , int clustNum
                         )
{
    const int k = std::min(clustNum, mas.size());
    if (k < clustNum)
    {
        std::cout << "Number of clusters is more than points. There will be empty clusters!" << std::endl;
    }
    // Инициализация начальных значений
    QVector<int> mark(mas.size());
    QVector<TWeight> centroidPrev;
    QVector<TWeight> centroidNext;
    QVector<int> clustSize;
    for (int i = 0; i < k; ++i)
    {
        centroidNext.push_back(mas[i]);
    }
    // Основной цикл алгоритма
    do
    {
        centroidPrev = centroidNext;
        // Соотносим точки
        for (int i = 0; i < mas.size(); ++i)
        {
            mark[i] = 0;
            double min_dist = distance(mas[i], centroidPrev[0]);
            for (int j = 1; j < centroidPrev.size(); ++j)
            {
                double curr_dist = distance(mas[i], centroidPrev[j]);
                if (curr_dist < min_dist)
                {
                    min_dist = curr_dist;
                    mark[i] = j;
                }
            }
        }
        // Пересчитываем центроиды
        centroidNext = QVector< TWeight>(k, stalg::zeroVector<TWeight>());
        clustSize = QVector<int>(k, 0);
        for (int i = 0; i < mark.size(); ++i)
        {
            clustSize[mark[i]]++;
            centroidNext[mark[i]] += mas[i];
        }
        for (int i = 0; i < k; ++i)
        {
            if (clustSize[i] > 0)
            {
                centroidNext[i] /= (double)clustSize[i];
            }
        }
    }
    while (centroidPrev != centroidNext);
    return mark;
}
}

#endif // __ST_ALG_CLUST_H__
