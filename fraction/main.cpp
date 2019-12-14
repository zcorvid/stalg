#include <iostream>
#include <string>

#include "fraction.test.h"

int main(int argc, char* argv[])
{
    if (argc == 2 && argv[1] == std::string("--test")) {
        TestFraction_All();
    } else {
        std::cout << "Use option --test for testing fraction module." << std::endl;
    }
	return 0;
}

