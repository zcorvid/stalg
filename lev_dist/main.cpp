#include <iostream>

#include "lev_distance.h"

int main(int argc, char* argv[])
{
    std::cout << stalg::lev_distance_s("a", "a") << std::endl;
    std::cout << stalg::lev_distance_s("a", "ab") << std::endl;
    std::cout << stalg::lev_distance_s("a", "ac") << std::endl;
    std::cout << stalg::lev_distance_s("a", "abc") << std::endl;
    std::cout << stalg::lev_distance_s("abc", "adc") << std::endl;
    std::cout << stalg::lev_distance_s("abc", "abdc") << std::endl;
    std::cout << stalg::lev_distance_s("abc", "adbc") << std::endl;
    std::cout << stalg::lev_distance_s("abc", "adeec") << std::endl;
    std::cout << stalg::lev_distance_s("ab", "a") << std::endl;
    return 0;
}
