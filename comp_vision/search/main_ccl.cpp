#include <time.h>
#include <iostream>
// #include <unordered_map>

#include "../../svalka.h"

#include "ccl.h"

// int main(int argc, char* argv[])
int main()
{
    int h;
    int w;
    std::cin >> h;
    std::cin >> w;
    int size = h * w;
    int length = h * w;
    int** img = stalg::alloc2dVec<int>(h, w);
    int** label_level1 = stalg::alloc2dVec<int>(h, w);
    stalg::set2dVec(label_level1, h, w, 0);
    int* label_level2 = new int[length];
    for (int i = 0; i < length; ++i)
    {
        label_level2[i] = i;
    }
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cin >> img[i][j];
        }
    }

    int number = -1;
    int repeat_count = 1000000;
    // std::unordered_map<int, int> xi;
    unsigned int timtim = clock();
    for (int i = 0; i < repeat_count; ++i)
    {
        number = stalg::ccl8(img, label_level1, h, w);
        // number = stalg::ccl8_xi(img, label_level1, h, w, xi);
    }
    timtim = clock() - timtim;
    std::cout << "#Time = " << timtim * 1. / repeat_count << " ms" << std::endl;

    stalg::print2dVecNonZero(label_level1, h, w);

    for (int i = 0; i <= number; ++i)
    {
        // std::cout << "l[" << i << "] = " << label_level2[i] << std::endl;
    }

    return 0;
}
