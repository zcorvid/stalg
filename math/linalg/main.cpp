#include <iostream>
#include <cmath>

// -----------------------------------------------------------------------------------
// Далее везде A - матрица, размером m x n, размеры всегда будут иметь имена m и n ,
// m - сколько строк, n - столбцов.
// -----------------------------------------------------------------------------------

// Далее перед каждой функцией идёт её описание.

// Меняет местами строки с номерами ind1 и ind2, начиная со столбца с номером start
// (считается, что до номера start в обеих строках только нулевые элементы).
void swap_rows(double **A, int ind1, int ind2, int m, int n, int start)
{
    if (ind1 != ind2)     // Если просят помять местами строку с собой - ничего не надо делать
    {
        for (int i = start; i < n; ++i)
        {
            double tmp = A[ind1][i];
            A[ind1][i] = A[ind2][i];
            A[ind2][i] = tmp       ;
        }
    }
}

// Пытается найти ненулевой элемент вниз от позиции (i, j), если находит - меняет его
// местами с i-й строкой и возвращает true, если не находит - возвращает false и не
// меняет матрицу. Если функция вернула true, значит в позиции (i, j) точно ненулевой
// элемент.
bool get_nonzero(double **A, int i, int j, int m, int n)
{
    for (int ind = i; ind < m; ++ind)
    {
        if (fabs(A[ind][j]) >= 0.000001)
        {
            swap_rows(A, i, ind, m, n, j);
            return true;
        }
    }
    return false;
}

// Зануляет все элементы матрицы под элементом (si, sj). Предполагается, что в позиции
// (si, sj) стоит ненулевой элемент.
void make_zero_under(double **A, int si, int sj, int m, int n)
{
    for (int i = si + 1; i < m; ++i)
    {
        double coef = -A[i][sj] / A[si][sj];
        for (int j = sj; j < n; ++j)
        {
            A[i][j] += A[si][j] * coef;
        }
    }
}

// Преобразует принятую матрицу к ступенчатому виду
void make_echelon(double **A, int m, int n)
{
    for (int i = 0, j = 0; i < m && j < n; ++i, ++j)  // Перебираем строки
    {
        while (j < n && !get_nonzero(A, i, j, m, n))  // Делаем ненулевым уголок ступеньки
        {
            ++j;
        }
        if (j < n)                                    // Если удалось найти ступеньку - нулим всё под ней
        {
            make_zero_under(A, i, j, m, n);
        }
    }
}

int main(int argc, char* argv[])
{
    int m;
    int n;

    // Читаем размеры матрицы
    std::cin >> m >> n;

    // Выделяем память под матрицу
    double **A = new double*[m];
    for (int i = 0; i < m; ++i)
    {
        A[i] = new double[n];
    }

    // Читаем матрицу
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cin >> A[i][j];
        }
    }

    // Приводим матрицу к ступенчатому виду
    make_echelon(A, m, n);

    // Выводим матрицу на экран
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Освобождаем память
    for (int i = 0; i < m; ++i)
    {
        delete[] A[i];
    }
    delete[] A;
    return 0;
}
