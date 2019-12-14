#include <iostream>
#include "stalgheap.h"

int main(int argc, char* argv[])
{
    stalg::Heap<int> mas;
    mas.Report();
    mas.Add(5);
    mas.Add(1);
    mas.Add(8);
    mas.Add(0);
    for (int i = 0; i < 10; ++i)
    {
        mas.Add(i);
    }
    mas.Report();
    return 0;
}
