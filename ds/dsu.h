#ifndef __ST_ALG_DSU_H__
#define __ST_ALG_DSU_H__

/* stalg disjoint-set union (DSU)
 * last change: 2019.08.05
 *
 * Реализация класса системы непересекающихся множеств.
 * (disjoint set union - DSU).
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

class DSU
{
private:
    int  capacity_;
    int* parent_  ;
    int* rank_    ;
    bool preallocated_data_;

private:
    DSU() = delete;
    DSU(const DSU&) = delete;

public:
    /* Создаёт dsu-индексатор, capacity - максимальный индекс, parent и rank - память для его работы,
     * можно самому заранее выделить и передать, чтобы DSU-класс не занимался выделением памяти
     * самостоятельно.
     */
    explicit DSU(const int capacity, int* parent = 0, int* rank = 0) : capacity_(capacity), parent_(parent), rank_(rank)
    {
        if (parent_ && rank_)
        {
            preallocated_data_ = true;
        }
        else
        {
            preallocated_data_ = false             ;
            parent_            = new int[capacity_];
            rank_              = new int[capacity_];
        }
    }

    ~DSU()
    {
        if (!preallocated_data_)
        {
            delete [] parent_;
            delete [] rank_  ;
        }
    }

    /* Создаёт множество из 1 индекса x.
     */
    void MakeSet(const int x)
    {
        parent_[x] = x;
        rank_  [x] = 0;
    }
    /* Надо бы удалить рекурсию, она теоретически может оказаться слишком глубокой.
     * Требуется дать оценку глубины рекурсии, её можно превратить в цикл, но тогда
     * потребуется второй пробег для реализации эвристики сжатия путей.
     * Возможно этот второй пробег будет занимать времени не больше, чем время
     * раскрутки стека рекурсивных вызовов.
     * Заменить рекурсию на циклы имеет смысл лишь при слишком большой ожидаемой
     * глубине рекурсии.
     */
    /* Ищет канонического представителя множества, в котором присутствует индекс x.
     */
    int Find(int x)
    {
        if (x != parent_[x])
        {
            parent_[x] = Find(parent_[x]);
        }
        return parent_[x];
    }
    /* Объединяет два множества, которые содержат индексы x и y.
     */
    void Union(const int x, const int y)
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
            }
        }
    }
};

}

#endif // __ST_ALG_DSU_H__
