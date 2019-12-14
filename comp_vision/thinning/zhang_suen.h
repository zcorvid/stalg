#ifndef __ST_ALG_ZHANG_SUEN_H__
#define __ST_ALG_ZHANG_SUEN_H__

#include "../../svalka.h"

namespace stalg
{

template<typename T>
bool isBorder(const int i, const int j, T** img, const int height, const int width)
{
    // !!!!!!!!!
}

template<typename T>
bool ZhangSuen_step(T** img, T** buffer, const int height, const int width)
{
    bool flag = false;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (isBorder(i, j, img, height, width))
            {
                buffer[i][j] = 0;
                flag = true;
            } else {
                buffer[i][j] = img[i][j];
            }
        }
    }
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            img[i][j] = buffer[i][j];
        }
    }
    return flag;
}

template<typename T>
void ZhangSuen(T** img, const int height, const int width)
{
    bool flag = true;
    T** = buffer = stalg::alloc2dVec<T>(height, width);
    while (flag)
    {
        flag = ZhangSuen_step(img, buffer, height, width);
    }
    stalg::free2dVec(buffer);
}

}

#endif // __ST_ALG_ZHANG_SUEN_H__
