#ifndef __ST_ALG_CCL_H__
#define __ST_ALG_CCL_H__

/* stalg Connected-component labeling
 * last change: 2019.08.05
 *
 * Алгоритм выделения объектов на бинарном изображении.
 *
 * Алгоритм работает по маске:     ?           ??
 *                                ?O    или    ?O
 *
 * Алгоритм является однопроходным, представляя собой сканирование изображения
 * слева направо, сверху вниз (построчно). Асимптотика базового алгоритма O(n).
 *
 * Алгоритм допускает модификацию, позволяющую за тот же проход подсчитать
 * какую-нибудь характеристику объектов изображения, например площадь, периметр,
 * эйлерову характеристику. Модификация будет работать как правило за O(n),
 * в более сложном случае время работы будет O(k*n), где k - асимптотика
 * дополнительной обработки одного шага сканирования (для вышеперечисленных
 * параметров k = O(1), вся сложность уйдёт в O-константу).
 *
 * Указанная модификация пока не реализована.
 *
 * Необходимые доработки: (1) Модификация для автоматического подсчёта параметра
 *                        (2) Нормализация меток         (чтобы они все были
 *                            от 1 до N - количества объектов)
 *
 * На входе двумерный массив img для анализа, в label_level1 кладётся таблица
 * разметки (ответ), dsu_size - ожидаемое максимальное количество объектов,
 * если его превысим - будет ошибка.
 */

#include "../../ds/dsu.h"
// #include "../../ds/dsu_t.h"

namespace stalg
{
/* Нормализовать лабельки
 *      <временно исключена из библиотеки>
 */
/*
void ccl_normalize_labels(int* label_level2, int number)
{
    int* new_labels = new int[number + 1];
    int label = 0;
    for (int i = 0; i <= number; ++i)
    {
        new_labels[i] = 0;
    }
    for (int i = 1; i <= number; ++i)
    {
        if (new_labels[label_level2[i]])
        {
            label_level2[i] = new_labels[label_level2[i]];
        }
        else
        {
            ++label;
            new_labels[label_level2[i]] = label;
        }
    }
    for (int i = 1; i <= number; ++i)
    {
        label_level2[i] = new_labels[i];
    }
    delete[] new_labels;
}
*/
/* 4-связный поиск
 *                                .?.
 *                  зависимость:  ?O?
 *                                .?.
 */
template<typename T>
int ccl4(T** img, int** label_level1, const int height, const int width, const int dsu_size = 1000)
{
    int number = 1;
    stalg::DSU dsu(dsu_size);
    dsu.MakeSet(0);
    // (1) Обработать img[0][0]
    if (img[0][0])
    {
        label_level1[0][0] = number;

        if (number >= dsu_size)
        {
            return -1;  // Превысили допустимое число объектов
        }

        dsu.MakeSet(number);
        ++number;
    }
    // (2) Обработать img[0][*] первую строку
    for (int j = 1; j < width; ++j)
    {
        if (img[0][j])
        {
            if (img[0][j - 1])
            {
                label_level1[0][j] = label_level1[0][j - 1];
            }
            else
            {
                label_level1[0][j] = number;

                if (number >= dsu_size)
                {
                    return -1;  // Превысили допустимое число объектов
                }

                dsu.MakeSet(number);
                ++number;
            }
        }
    }
    // (3) Обработать img[*][0] первый столбец
    for (int i = 1; i < height; ++i)
    {
        if (img[i][0])
        {
            if (img[i - 1][0])
            {
                label_level1[i][0] = label_level1[i - 1][0];
            }
            else
            {
                label_level1[i][0] = number;

                if (number >= dsu_size)
                {
                    return -1;  // Превысили допустимое число объектов
                }

                dsu.MakeSet(number);
                ++number;
            }
        }
    }
    // (4) Обработать оставшееся изображение
    for (int i = 1; i < height; ++i)
    {
        for (int j = 1; j < width; ++j)
        {
            if (img[i][j])
            {
                int leftNeighbour = label_level1[i][j - 1];
                int upNeighbour = label_level1[i - 1][j];
                if (leftNeighbour && upNeighbour)
                {
                    // Отождествить два индекса
                    dsu.Union(leftNeighbour, upNeighbour);
                }
                if (leftNeighbour || upNeighbour)
                {
                    if (leftNeighbour)
                    {
                        label_level1[i][j] = leftNeighbour;
                    }
                    else
                    {
                        label_level1[i][j] = upNeighbour;
                    }
                }
                else
                {
                    label_level1[i][j] = number;

                    if (number >= dsu_size)
                    {
                        return -1;  // Превысили допустимое число объектов
                    }

                    dsu.MakeSet(number);
                    ++number;
                }
            }
        }
    }
    // (5) Объединить индексы
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            label_level1[i][j] = dsu.Find(label_level1[i][j]);
        }
    }
    return number;
}
/* 8-связный поиск
 *                                ???
 *                  зависимость:  ?O?
 *                                ???
 */
template<typename T>
int ccl8(T** img, int** label_level1, const int height, const int width, const int dsu_size = 1000)
{
    int number = 1;
    stalg::DSU dsu(dsu_size);
    dsu.MakeSet(0);
    // (1) Обработать img[0][0]
    if (img[0][0])
    {
        label_level1[0][0] = number;

        if (number >= dsu_size)
        {
            return -1;  // Превысили допустимое число объектов
        }

        dsu.MakeSet(number);
        ++number;
    }
    // (2) Обработать img[0][*] первую строку
    for (int j = 1; j < width; ++j)
    {
        if (img[0][j])
        {
            if (img[0][j - 1])
            {
                label_level1[0][j] = label_level1[0][j - 1];
            }
            else
            {
                label_level1[0][j] = number;

                if (number >= dsu_size)
                {
                    return -1;  // Превысили допустимое число объектов
                }

                dsu.MakeSet(number);
                ++number;
            }
        }
    }
    // (3) Обработать img[*][0] первый столбец
    for (int i = 1; i < height; ++i)
    {
        if (img[i][0])
        {
            if (img[i - 1][0])
            {
                label_level1[i][0] = label_level1[i - 1][0];
            }
            else
            {
                label_level1[i][0] = number;

                if (number >= dsu_size)
                {
                    return -1;  // Превысили допустимое число объектов
                }

                dsu.MakeSet(number);
                ++number;
            }
        }
    }
    // (4) Обработать оставшееся изображение
    for (int i = 1; i < height; ++i)
    {
        for (int j = 1; j < width; ++j)
        {
            int lNeighbour = label_level1[i][j - 1];
            int uNeighbour = label_level1[i - 1][j];
            int luNeighbour = label_level1[i - 1][j - 1];
            if (lNeighbour && uNeighbour)
            {
                // Отождествить два индекса
                dsu.Union(lNeighbour, uNeighbour);
            }
            if (img[i][j])
            {
                if (lNeighbour || uNeighbour || luNeighbour)
                {
                    if (lNeighbour)
                    {
                        label_level1[i][j] = lNeighbour;
                    }
                    else if (uNeighbour)
                    {
                        label_level1[i][j] = uNeighbour;
                    }
                    else
                    {
                        label_level1[i][j] = luNeighbour;
                    }
                }
                else
                {
                    label_level1[i][j] = number;

                    if (number >= dsu_size)
                    {
                        return -1;  // Превысили допустимое число объектов
                    }

                    dsu.MakeSet(number);
                    ++number;
                }
            }
        }
    }
    // (5) Объединить индексы
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            label_level1[i][j] = dsu.Find(label_level1[i][j]);
        }
    }
    return number;
}
/* Выделение объектов и подсчёт их эйлеровой характеристики.
 * Эта функция также может считать площадь или периметр объектов.
 *
 * <Функция не доработана, и поэтому пока исключена из библиотеки>
 *
 */
/*
template<typename T>
int ccl8_xi(T** img, int** label_level1, const int height, const int width, std::unordered_map<int, int>& par)
{
    int number = 1;
    stalg::DSU_t dsu(1000);
    dsu.MakeSet(0, 1000);
    // (1) Обработать img[0][0]
    if (img[0][0])
    {
        label_level1[0][0] = number;
        dsu.MakeSet(number, 1);
        ++number;
    }

    // (2) Обработать img[0][*] первую строку
    for (int j = 1; j < width; ++j)
    {
        if (img[0][j])
        {
            if (img[0][j - 1])
            {
                label_level1[0][j] = label_level1[0][j - 1];
                // ++dsu.par_[label_level1[0][j]];
            }
            else
            {
                label_level1[0][j] = number;
                dsu.MakeSet(number, 1);
                ++number;
            }
        }
    }
    // (3) Обработать img[*][0] первый столбец
    for (int i = 1; i < height; ++i)
    {
        if (img[i][0])
        {
            if (img[i - 1][0])
            {
                label_level1[i][0] = label_level1[i - 1][0];
                // ++dsu.par_[label_level1[i][0]];
            }
            else
            {
                label_level1[i][0] = number;
                dsu.MakeSet(number, 1);
                ++number;
            }
        }
    }
    // (4) Обработать оставшееся изображение
    for (int i = 1; i < height; ++i)
    {
        for (int j = 1; j < width; ++j)
        {
            int lNeighbour = label_level1[i][j - 1];
            int uNeighbour = label_level1[i - 1][j];
            int luNeighbour = label_level1[i - 1][j - 1];
            if (lNeighbour && uNeighbour && !luNeighbour)
            {
                // Отождествить два индекса
                --dsu.par_[lNeighbour];
                if (dsu.Find(lNeighbour) != dsu.Find(uNeighbour))
                {
                    dsu.Union(lNeighbour, uNeighbour);
                }
            }
            if (img[i][j])
            {
                if (lNeighbour || uNeighbour || luNeighbour)
                {
                    if (lNeighbour)
                    {
                        label_level1[i][j] = lNeighbour;
                    }
                    else if (uNeighbour)
                    {
                        label_level1[i][j] = uNeighbour;
                    }
                    else
                    {
                        label_level1[i][j] = luNeighbour;
                    }
                    // ++dsu.par_[dsu.Find(label_level1[i][j])];
                }
                else
                {
                    label_level1[i][j] = number;
                    dsu.MakeSet(number, 1);
                    ++number;
                }
            }
        }
    }
    // (5) Объединить индексы котана
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            label_level1[i][j] = dsu.Find(label_level1[i][j]);
            // par.emplace(label_level1[i][j], dsu.par_[label_level1[i][j]]);
            // par[label_level1[i][j]] = dsu.par_[label_level1[i][j]];
        }
    }
    // (6) Выведем генусы
    // for (auto it = genus.cbegin(); it != genus.cend(); ++it)
    // for (const auto& it : genus)
    // {
    //     std::cout << "g[" << it.first << "] = " << it.second << std::endl;
    // }
    return number;
}
*/
}

#endif // __ST_ALG_CCL_H__
