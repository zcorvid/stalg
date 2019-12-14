#ifndef __STALG_MERGE_H__
#define __STALG_MERGE_H__

namespace stalg
{
template<class T1, class T2>
T1 merge(const T1 &mas1, const T2 &mas2)
{
    T1 mas;
    int i1 = 0;
    int i2 = 0;
    for (; i1 < mas1.size() && i2 < mas2.size(); ++i1, ++i2)
    {
        if (mas1[i1] <= mas2[i2])
        {

        }
    }
}
}

#endif // __STALG_MERGE_H__
