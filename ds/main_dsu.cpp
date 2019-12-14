#include <iostream>

#include "dsu.h"
#include "dsu_t.h"

// int main(int argc, char* argv[])
int main()
{
    stalg::DSU_t dsu(100);
    for (int i = 0; i < 10; ++i)
    {
        dsu.MakeSet(i);
    }
    dsu.Union(0, 1);
    dsu.Union(2, 3);
    dsu.Union(0, 2);
    // dsu.Union(1, 3);
    // dsu.Union(4, 9);
    // dsu.Union(5, 6);
    // dsu.Union(6, 8);
    // dsu.Union(7, 8);
    /* {0, 1, 2, 3}. {4, 9}, {5, 6, 7, 8}
     *
     */
    for (int i = 0; i < 10; ++i)
    {
        std::cout << dsu.Find(i) << ", ";
    }
    std::cout << std::endl;
    return 0;
}
