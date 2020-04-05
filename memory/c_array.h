#ifndef __ST_ALG_C_ARRAY_H__
#define __ST_ALG_C_ARRAY_H__

/* stalg c array
 * last change: 12.04.2017
 *
 * Средства для работы с си-массивами
 *
 * >>> stalg2 <<<
 */

namespace stalg
{
/* Выделить память для двумерного массива d1 строк на d2 столбцов, тип ячеек - шаблонный параметр.
 * Пример использования: int     **mas = Allocate2dArray<int    >(10, 5  );
 *                       MyClass **mas = Allocate2dArray<MyClass>(40, 500);
 *
 * Автоматической очистки памяти нету. Используйте функцию Free2dArray<>().
 */
template<class T>
T** Allocate2dArray(const int d1, const int d2)
{
    T **ptr = new T*[d1];
    for (int i = 0; i < d1; ++i)
    {
        ptr[i] = new T[d2];
    }
    return ptr;
}
/* Вариант с непрерывным размещением.
 */
template<class T>
T** Allocate2dArrayCont(const int d1, const int d2)
{
    T **ptr      = new T*[d1];
    T  *ptr_data = new T [d1 * d2];
    for (int i = 0; i < d1; ++i)
    {
        ptr[i] = ptr_data + i * d2;
    }
    return ptr;
}

/* Очистить память, выделенную для двумерного массива d1 строк на d2 столбцов.
 */
template<class T>
void Free2dArray(T **ptr, const int d1, const int d2)
{
    (void)d2;
    for (int i = 0; i < d1; ++i)
    {
        delete[] ptr[i];
    }
    delete ptr;
}
/* Очистить память, выделенную для двумерного массива d1 строк на d2 столбцов.
 * Непрерывное размещение.
 */
template<class T>
void Free2dArrayCont(T **ptr)
{
    delete[] ptr[0];
    delete[] ptr;
}

/* Заполнить двумерный массив заданным значением
 */
template<class T, class TValue>
void Set2dArray(T **mas, const int d1, const int d2, const TValue &value)
{
    for (int i = 0; i < d1; ++i)
    {
        for (int j = 0; j < d2; ++j)
        {
            mas[i][j] = value;
        }
    }
}
/* Напечатать двумерный массив.
 */
template<class T>
void Print2dArray(T **mas, const int d1, const int d2)
{
    for (int i = 0; i < d1; ++i)
    {
        for (int j = 0; j < d2; ++j)
        {
            std::cout << mas[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
}

#endif // __ST_ALG_C_ARRAY_H__
