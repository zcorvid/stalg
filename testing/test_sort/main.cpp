#include <vector>
#include <iostream>

#include "sort.h"

int main()
{
    std::vector<int> vec = {4, 2, 1};
    tst_sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ",";
    }
    std::cout << std::endl;
    return 0;
}

