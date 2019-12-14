#ifndef __ST_ALG_HEAP_H__
#define __ST_ALG_HEAP_H__

/* stalg heap
 * last change: 2019.08.05
 *
 * Реализация класса "Куча" общего назначения.
 *
 * Руководство по использованию.
 *
 * Создание кучи:
 *
 *     Heap<T, ComparatorType> heap(comparator, ich_observer)
 *
 *     T              - тип хранимых значений
 *     ComparatorType - тип компаратора (по умолчанию std::less<T>)
 *     comparator     - объект-компаратор (по умолчанию ComparatorType() )
 *     ich_observer   - функция оповещения об изменении индекса (имеет
 *                      сигнатуру void(const T &element, size_t new_element_index),
 *                      по умолчанию ничего не делает)
 *
 * Простейший вариант кучи:
 *
 *     Heap<int> heap;
 *
 *         Самая обычная куча целых чисел. Не поддерживает удаление по значению (о том, как добавить
 *         поддержку такого удаления - ниже).
 *
 * Функции:
 *
 *     size_t push(const T &value)
 *         Добавляет в кучу значение value, возвращает индекс, на который оно попадёт. Сложность O(logN).
 *
 *     void erase(size_t index)
 *         Удаляет из кучи по ключу (по индексу, не по значению!). Сложность O(logN)
 *
 *     const T& top() const
 *         Доступ к вершине кучи (минимум???). Сложность O(1).
 *
 *     void pop()
 *         Удаляет вершину кучи. Сложность O(1).
 *
 *     size_t size() const
 *         Возвращает размер кучи. Сложность O(1).
 *
 *     bool empty() const
 *         Проверяет, пуста ли куча. Сложность O(1).
 *
 * Как добавить поддержку удаления по значению за O(logN).
 *
 *     <Потом допишу>
 *
 * ----------
 *
 * Доделать: (1) Политика выброса исключений (наверное нужно поубирать все проверки на out of range).
 *           (2) Добавить инициализацию кучи из массива (heapify).
 *           (3) Возможно, стоит шаблонизировать несущий контейнер (сейчас std::vector).
 *           (4) Возможно, стоит добавить аллокатор.
 *
 */

#include <functional>
#include <iostream>
#include <vector>

namespace stalg
{

template <class T, class Compare = std::less<T>>
class Heap
{
public:
    using IndexChangeObserver = std::function<void(const T &element, size_t new_element_index)>;

    static constexpr size_t kNullIndex = static_cast<size_t>(-1);

    explicit Heap(    Compare             compare               = Compare            ()
                    , IndexChangeObserver index_change_observer = IndexChangeObserver()
                  ) : compare_              (compare)
                    , index_change_observer_(index_change_observer) {}

    size_t push(const T &value)
    {
        size_t index = elements_.size();
        elements_.push_back(value);
        NotifyIndexChange(value, index);
        index = SiftUp(index);
        index = SiftDown(index);
        return index;
    }

    void erase(size_t index)
    {
        if (index < size())
        {
            SwapElements(index, size () - 1);
            NotifyIndexChange(elements_.back(), kNullIndex);
            elements_.pop_back();
            if (index < size())
            {
                SiftDown(SiftUp(index));
            }
        }
        else
        {
//            throw std::runtime_error ("Erasing of non-existing element of heap !");
            std::cerr << "Erasing of non-existing element of heap !" << std::endl;
        }
    }

    const T& top() const
    {
        if (!empty())
        {
            return elements_[0];
        }
        else
        {
//            throw std::runtime_error ("Request of top for empty heap !");
            std::cerr << "Request of top for empty heap !" << std::endl;
        }
    }

    void pop()
    {
        erase(0);
    }

    size_t size() const
    {
        return elements_.size();
    }

    bool empty() const
    {
        return elements_.empty();
    }

    void UpdateTop()
    {
        SiftDown(0);
    }

private:
    IndexChangeObserver index_change_observer_;
    Compare             compare_              ;
    std::vector<T>      elements_             ;

    size_t Parent(size_t index) const
    {
        if (index)
        {
            return (index - 1) / 2;
        }
        return kNullIndex;
    }

    size_t LeftSon(size_t index) const
    {
        size_t ind = 2 * index + 1;
        if (ind < size())
        {
            return ind;
        }
        else
        {
            return kNullIndex;
        }
    }

    size_t RightSon(size_t index) const
    {
        size_t ind = 2 * index + 2;
        if (ind < size())
        {
            return ind;
        }
        else
        {
            return kNullIndex;
        }
    }

    bool CompareElements(size_t first_index, size_t second_index) const
    {
        if (first_index >= size())
        {
//            throw std::runtime_error ("Bad index of heap !");
            std::cerr << "Bad index of heap !" << std::endl;
        }
        if (second_index >= size())
        {
//            throw std::runtime_error ("Bad index of heap !");
            std::cerr << "Bad index of heap !" << std::endl;
        }
        if (first_index < 0)
        {
//            throw std::runtime_error ("Bad index of heap !");
            std::cerr << "Bad index of heap !" << std::endl;
        }
        if (second_index < 0)
        {
//            throw std::runtime_error ("Bad index of heap !");
            std::cerr << "Bad index of heap !" << std::endl;
        }
        return compare_(elements_[first_index], elements_[second_index]);
    }

    void NotifyIndexChange(const T &element, size_t new_element_index)
    {
        index_change_observer_(element, new_element_index);
    }

    void SwapElements(size_t first_index, size_t second_index)
    {
        if (first_index >= size())
        {
//            throw std::runtime_error ("Swapping of non-existing elements in heap !");
            std::cerr << "Swapping of non-existing elements in heap !" << std::endl;
        }
        if (second_index >= size())
        {
//            throw std::runtime_error ("Swapping of non-existing elements in heap !");
            std::cerr << "Swapping of non-existing elements in heap !" << std::endl;
        }
        if (first_index < 0)
        {
//            throw std::runtime_error ("Swapping of non-existing elements in heap !");
            std::cerr << "Swapping of non-existing elements in heap !" << std::endl;
        }
        if (second_index < 0)
        {
//            throw std::runtime_error ("Swapping of non-existing elements in heap !");
            std::cerr << "Swapping of non-existing elements in heap !" << std::endl;
        }
        std::swap(elements_[first_index], elements_[second_index]);
        NotifyIndexChange(elements_[first_index], first_index);
        NotifyIndexChange(elements_[second_index], second_index);
    }

    size_t SiftUp(size_t index)
    {
        while (Parent(index) != kNullIndex && CompareElements(index, Parent(index)))
        {
            SwapElements(Parent(index), index);
            index = Parent(index);
        }
        return index;
    }

    size_t SiftDown(size_t index)
    {
        while (LeftSon(index) != kNullIndex)
        {
            size_t left = LeftSon(index);
            size_t right = RightSon(index);
            // index for swapping
            size_t red_index = left;
            if (right != kNullIndex && CompareElements(right, left))
            {
                red_index = right;
            }
            if (CompareElements(index, red_index))
            {
                return index;
            }
            else
            {
                SwapElements(index, red_index);
                index = red_index;
            }
        }
        return index;
    }
};

}

#endif // __ST_ALG_HEAP_H__
