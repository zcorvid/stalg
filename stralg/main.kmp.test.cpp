#include <iostream>

#include <vector>
#include <string>

#include <stdexcept>

#include "../stalgiostream.h"

#include "kmp.h"

int main(int argc, char* argv[])
{
    std::string str1("aaaaa");
    std::string str2("aaabaab");
    std::string str3("abacaba");

    std::vector<int> z_str1 = {0, 4, 3, 2, 1};
    std::vector<int> z_str2 = {0, 2, 1, 0, 2, 1, 0};
    std::vector<int> z_str3 = {0, 0, 1, 0, 3, 0, 1};

    std::vector<std::string> str;
    str.push_back(str1);
    str.push_back(str2);
    str.push_back(str3);

    std::vector<std::vector<int>> z_str;
    z_str.push_back(z_str1);
    z_str.push_back(z_str2);
    z_str.push_back(z_str3);

    for (int i = 0; i < str.size(); ++i)
    {
        std::vector<int> z_f = stalg::z_function(str[i]);
        if (z_str[i] != z_f)
        {
            std::cout << "str = " << str[i] << ", z = " << z_str[i] << ", got = " << z_f << std::endl;
            throw std::runtime_error("Test failed!");
        }
    }

    std::cout << "All tests passed!" << std::endl;

    std::cout << stalg::search_kmp<std::string>("abab", "cabababcacabacabab", "#") << std::endl;
    std::cout << stalg::search_kmp<std::string>("abab", "cabababcacabacabab") << std::endl;

    return 0;
}
