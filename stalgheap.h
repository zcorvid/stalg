#ifndef __ST_ALG_HEAP_H__
#define __ST_ALG_HEAP_H__

/* stalg heap
 * last change: 31.08.2017
 *
 * Двоичная куча. На вершине кучи минимум.
 *
 */

#include <vector>
#include <iostream>
#include <iomanip>

namespace stalg
{
    template<class T/*, class TComparator*/>
    class Heap
    {
    private:
        std::vector<T> data_;
        // TComparator comparator_;
        int ParentPos(const int index) const
        {
            return (index - 1) / 2;
        }
        int LeftPos(const int index) const
        {
            return 2 * index + 1;
        }
        int RightPos(const int index) const
        {
            return 2 * index + 2;
        }
        void SiftUp(int index)
        {
            while (data_[index] < data_[ParentPos(index)])
            {
                std::swap(data_[index], data_[ParentPos(index)]);
                index = ParentPos(index);
            }
        }
        void SiftDown(int index)
        {
            while (LeftPos(index) < size())
            {
                int swap_index = LeftPos(index);
                if (RightPos(index) < size() && data_[RightPos(index)] < data_[LeftPos(index)])
                {
                    swap_index = RightPos(index);
                }
                if (data_[index] > data_[swap_index])
                {
                    std::swap(data_[index], data_[swap_index]);
                    index = swap_index;
                }
                else
                {
                    break;
                }
            }
        }

    public:
        void Add(const T& element)
        {
            data_.push_back(element);
            SiftUp(size() - 1);
        }
        T Pop()
        {
            T val = Top();
            data_.front() = data_.back();
            data_.pop_back();
            SiftDown(0);
            return val;
        }
        const T& Top() const
        {
            return data_.front();
        }
        bool empty() const
        {
            return data_.empty();
        }
        size_t size() const
        {
            return data_.size();
        }
        /* Глубина кучи, depth = log(N)
         * Базовая сложность log(N), но можно сделать loglog(N), если использовать
         * бинарный поиск по двоичной записи N.
         * Можно использовать функцию логарифма из математической библиотеки, но
         * тогда сложность совершенно непонятна.
         */
        size_t depth() const
        {
            if (empty())
            {
                return 0;
            }
            else
            {
                size_t depth = 1;
                size_t upN = 2;
                while (upN <= size())
                {
                    ++depth;
                    upN = upN << 1;
                }
                return depth;
            }
        }
        void PrintAsHeap() const
        {
            for (size_t level = 0, beg_pos = 0, end_pos = 1; level < depth(); ++level)
            {
                for (int i = 0; i < (depth() - level); ++i)
                {
                    std::cout << "    ";
                }
                for (int i = beg_pos; i < end_pos && i < size(); ++i)
                {
                    std::cout << std::setw(8 * (depth() - level)) << std::internal << data_[i] << "";
                }
                beg_pos = end_pos;
                end_pos = LeftPos(beg_pos);
                std::cout << std::endl;
            }
        }
        void Report() const
        {
            std::cout << "**********" << std::endl;
            std::cout << "stalg::Heap : " << std::endl;
            std::cout << "size  = " << size() << std::endl;
            std::cout << "depth = " << depth() << std::endl;
            PrintAsHeap();
            std::cout << "**********" << std::endl;
        }
    };
}

#endif // __ST_ALG_HEAP_H__
