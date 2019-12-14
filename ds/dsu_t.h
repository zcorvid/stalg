#ifndef __ST_ALG_DSU_T_H__
#define __ST_ALG_DSU_T_H__

/* stalg disjoint-set union (DSU)
 * last change: 13.03.2017
 *
 * Реализация класса системы непересекающихся множеств.
 *
 * Реализован небезопасно, не производится никаких проверок на корректности.
 * К использованию категорически не рекомендован (если только вы не понимаете,
 * что именно происходит в коде класса).
 *
 * Отсутствие проверок сделано для достижения более высокой скорости работы.
 *
 * Применены оптимизации: (1) Эвристика сжатия путей
 *                        (2) Ранговая эвристика по глубине дерева
 *
 * Возможные оптимизации: (1) Можно ещё запилить ранговую на основе размера дерева
 *
 */

#include "../stalgcommon.h"

namespace stalg
{

class DSU_t
{
private:
    int capacity_;
    int* parent_;
    int* rank_;

public:
    int* par_;

private:
    DSU_t();

public:
    explicit DSU_t(const int capacity) : capacity_(capacity)
    {
        parent_ = new int[capacity_];
        rank_ = new int[capacity_];

        par_ = new int[capacity_];
    }

    ~DSU_t()
    {
        delete[] parent_;
        delete[] rank_;
    }

    void MakeSet(const int x, const int start_par = 0)
    {
        parent_[x] = x;
        rank_[x] = 0;
        par_[x] = start_par;
    }
    /* Надо бы удалить рекурсию, она теоретически может оказаться слишком глубокой.
     * Требуется дать оценку глубины рекурсии, её можно превратить в цикл, но тогда
     * потребуется второй пробег для реализации эвристики сжатия путей.
     * Возможно этот второй пробег будет занимать времени не больше, чем время
     * раскрутки стека рекурсивных вызовов.
     * Заменить рекурсию на циклы имеет смысл лишь при слишком большой ожидаемой
     * глубине рекурсии.
     *
     */
    int Find(int x)
    {
        if (x != parent_[x])
        {
            parent_[x] = Find(parent_[x]);
        }
        return parent_[x];
    }
    void Union(const int x, const int y, const int shift_par = 0)
    {
        if (x != y)
        {
            int x_parent = Find(x);
            int y_parent = Find(y);
            if (x_parent != y_parent)
            {
                if (rank_[x_parent] < rank_[y_parent])
                {
                    stalg::swap(x_parent, y_parent);
                }
                parent_[y_parent] = x_parent;
                if (rank_[x_parent] == rank_[y_parent])
                {
                    ++rank_[x_parent];
                }
                par_[x_parent] += par_[y_parent];
            }
            par_[x_parent] += shift_par;
        }
    }
};

}

#endif // __ST_ALG_DSU_T_H__
