#include <algorithm>
#include "stalgsort.h"

template<class RandomIt>
void tst_sort(RandomIt begin_it, RandomIt end_it)
{
    CombSort(&(*begin_it), end_it - begin_it);
}

