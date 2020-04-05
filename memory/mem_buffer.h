#ifndef __ST_ALG_MEM_BUFFER_H__
#define __ST_ALG_MEM_BUFFER_H__

/* stalg Memory Buffer
 * last change: 04.05.2018
 *
 * Буффер памяти. Выделяет фиксированное число массивов заданного размера.
 * Не поддерживает изменение размера и числа буфферов.
 *
 * Примеры использования: (1) MemBuffer<int, 4> buffer(1024);      // Выделено 4 int-массива по 1024 ячейки каждый
 *                        (2) MemBuffer<double, 32> buffer(512);   // Выделено 32 double-массива по 512 ячеек каждый
 *                        (3) MemBuffer<MyClass, 8> buffer(2048);  // Выделено 8 массивов MyClass по 2048 ячеек каждый
 *
 * >>> stalg2 <<<
 */

#include <iostream>

namespace stalg
{

template<typename T, int TBuffersCount>
class MemBuffer
{
private:
    T* buffer_[TBuffersCount];
    const int buffer_count_;
    const int buffer_size_;

    void allocate_buffers()
    {
        for (int buf_num = 0; buf_num < buffer_count_; ++buf_num)
        {
            buffer_[buf_num] = new T[buffer_size_];
        }
    }
    void free()
    {
        for (int buf_num = 0; buf_num < buffer_count_; ++buf_num)
        {
            delete[] buffer_[buf_num];
        }
    }
    void reallocate_buffers()
    {
        free();
        allocate_buffers();
    }

private:
    MemBuffer();

public:
    explicit MemBuffer(const int buffer_size) : buffer_count_(TBuffersCount), buffer_size_(buffer_size)
    {
        allocate_buffers();
    }
    ~MemBuffer()
    {
        free();
    }
    T* get_buffer(const int buffer_id)
    {
        return buffer_[buffer_id];
    }

public:
    void PrintState()
    {
        std::cout << "#stalg::MemBuffer: " << buffer_count_ << " buffers, "  << buffer_size_ << " size" << std::endl;
        for (int buf_num = 0; buf_num < buffer_count_; ++buf_num)
        {
            std::cout << "#stalg::MemBuffer: buffer number " << buf_num << std::endl;
            std::cout << "{";
            for (int i = 0; i < buffer_size_; ++i)
            {
                std::cout << buffer_[buf_num][i];
                if (i + 1 < buffer_size_)
                {
                    std::cout << ", ";
                }
            }
            std::cout << "}" << std::endl;
        }
    }
};

}

#endif // __ST_ALG_MEM_BUFFER_H__
