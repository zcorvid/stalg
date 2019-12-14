#ifndef __ST_ALG_SORT_H__
#define __ST_ALG_SORT_H__

// stalg sort
// 2.08.2016

namespace stalg
{
    template<typename T>
    void swap_values(T& first, T& second)
    {
        T tmp_val = first;
        first = second;
        second = tmp_val;
    }

    template<typename T>
    void Merge(T* data, const int length, const int border)
    {
        T* begin_first = data;
        T* begin_second = data + border;
        T* end_first = data + border;
        T* end_second = data + length;
        T* buffer = new T[length];
        int index;
        for (index = 0; begin_first != end_first && begin_second != end_second; ++index)
        {
            if (*begin_first <= *begin_second)
            {
                buffer[index] = *begin_first;
                ++begin_first;
            }
            else
            {
                buffer[index] = *begin_second;
                ++begin_second;
            }
        }
        while (begin_first != end_first)
        {
            buffer[index] = *begin_first;
            ++begin_first;
            ++index;
        }
        while (begin_second != end_second)
        {
            buffer[index] = *begin_second;
            ++begin_second;
            ++index;
        }
        for (int i = 0; i < length; ++i)
        {
            data[i] = buffer[i];
        }
        delete[] buffer;
    }

    template<typename T>
    void BubbleSort(T* data, const int length)
    {
        bool flag = true;
        for (int i = length; i > 0 && flag; --i)
        {
            flag = false;
            for (int j = 0; j + 1 < i; ++j)
            {
                if (data[j] > data[j + 1])
                {
                    swap_values(data[j], data[j + 1]);
                    flag = true;
                }
            }
        }
    }

    template<typename T>
    void CombSort(T* data, const int length)
    {
        // Множитель понижения, лучше его вынести в аргумент функции и сделать связь с константой золотого сечения
        const double factor = 0.801711847;
        int step = (length - 1) * factor;
        while (step > 1)
        {
            for (int i = 0; i + step < length; ++i)
            {
                if (data[i] > data[i + step])
                {
                    swap_values(data[i], data[i + step]);
                }
            }
            step *= factor;
        }
        BubbleSort(data, length);
    }

    template<typename T>
    void MergeSort(T* data, const int length)
    {
        if (length <= 1)
        {
            return;
        }
        else
        {
            const int mid = length / 2;
            MergeSort(data, mid);
            MergeSort(data + mid, length - mid);
            Merge(data, length, mid);
        }
    }
}

#endif // __ST_ALG_SORT_H__
