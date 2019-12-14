#include <iostream>

#include "gauss.h"

int main(int argc, char* argv[])
{
    int m;
    int n;
    std::cin >> m >> n;
    double **A = new double*[m];
    for (int i = 0; i < m; ++i)
    {
        A[i] = new double[n];
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cin >> A[i][j];
        }
    }

    stalg::make_echelon(A, m, n);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < m; ++i)
    {
        delete[] A[i];
    }
    delete[] A;
    return 0;
}
