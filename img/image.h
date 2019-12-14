#ifndef __ST_ALG_IMG_IMAGE_H__
#define __ST_ALG_IMG_IMAGE_H__

/* stalg image
 * last change: 2019.08.05
 *
 * Работа с изображениями.
 *
 */

#include <stdio.h>

#include <iostream>
#include <cmath>
#include <deque>
#include <algorithm>

#include "../stalgconst.h"
#include "../math/stalgmath.h"
#include "../memory/c_array.h"
#include "../algorithm/mstat.h"

namespace stalg
{
namespace img
{
/* Класс изображения.
 */
class Image2d
{
private:
    unsigned char** data_;
    int height_;
    int width_;

    Image2d(const Image2d& other);

    void allocate(const int height, const int width)
    {
        height_ = height;
        width_ = width;
        data_ = new unsigned char*[height_];
        for (int i = 0; i < height; ++i)
        {
            data_[i] = new unsigned char[width_];
        }
    }

public:
    /* Границы, где изображение непустое (рассчитываются по запросу).
     */
    int upper_bound;
    int lower_bound;
    int left_bound ;
    int right_bound;

    Image2d() : data_      ( 0)
              , height_    (-1)
              , width_     (-1)
              , upper_bound(-1)
              , lower_bound(-1)
              , left_bound (-1)
              , right_bound(-1)
    {}

    ~Image2d()
    {
        clear();
    }

    void clear()
    {
        if (data_)
        {
            for (int i = 0; i < height_; ++i)
            {
                delete[] data_[i];
            }
            delete[] data_;
        }
        data_       =  0;
        height_     = -1;
        width_      = -1;
        upper_bound = -1;
        lower_bound = -1;
        left_bound  = -1;
        right_bound = -1;
    }

    void realloc(const int height, const int width)
    {
        clear();
        allocate(height, width);
    }

    unsigned char** Data() const
    {
        return data_;
    }

    /* Заполняет изображение заданным цветом.
     */
    void fill(const char color)
    {
        for (int i = 0; i < height_; ++i)
        {
            for (int j = 0; j < width_; ++j)
            {
                data_[i][j] = color;
            }
        }
    }

    /* Создаёт изображение из исходника, добавляя поворот на заданный угол.
     */
    void InitRotated(unsigned char** src, const int srcHeight, const int srcWidth, const double angle, const int bgColor = 255)
    {
        double phi = angle * stalg::pi / 180.;
        double cp = cos(phi);
        double sp = sin(phi);

        // Находим размеры повёрнутого изображения
        int srcRotatedHeight = (srcWidth - 1) * fabs(sp) + (srcHeight - 1) * fabs(cp) + 1.;
        int srcRotatedWidth  = (srcWidth - 1) * fabs(cp) + (srcHeight - 1) * fabs(sp) + 1.;
        realloc(srcRotatedHeight, srcRotatedWidth);
        fill(bgColor);

        // Находим координаты центров
        double yC = (srcHeight - 1.) / 2.;
        double xC = (srcWidth  - 1.) / 2.;
        double yC_new = (srcRotatedHeight - 1.) / 2.;
        double xC_new = (srcRotatedWidth  - 1.) / 2.;

        for (int y = 0; y < srcRotatedHeight; ++y)
        {
            for (int x = 0; x < srcRotatedWidth; ++x)
            {
                double xS = x - xC_new;
                double yS = y - yC_new;

                double xxF = ( xS * cp - yS * sp) + xC;
                double yyF = ( xS * sp + yS * cp) + yC;

                // int xx = xxF + 0.5 * stalg::sign_custom(xxF);
                // int yy = yyF + 0.5 * stalg::sign_custom(yyF);
                int xx = stalg::round(xxF);
                int yy = stalg::round(yyF);

                if (xx >= 0 && yy>= 0 && xx < srcWidth && yy < srcHeight)
                {
                    data_[y][x] = src[yy][xx];
                }
            }
        }
    }

    /* Создаёт изображение из исходника, добавляя сдвиг на заданный коэффициент.
     */
    void InitShifted(unsigned char** src, const int srcHeight, const int srcWidth, const double shift, const int bgColor = 255)
    {
        // Находим размеры сдвинутого изображения
        int srcShiftedHeight = srcHeight;
        int srcShiftedWidth  = srcWidth + fabs(shift) * srcHeight;
        realloc(srcShiftedHeight, srcShiftedWidth);
        fill(bgColor);

        int xC = ((shift >= 0) ? 0 : -shift * (srcHeight - 1));

        for (int y = 0; y < srcShiftedHeight; ++y)
        {
            for (int x = 0; x < srcShiftedWidth; ++x)
            {
                // double xxF = x - shift * ((shift >= 0) ? (srcShiftedHeight - y - 1) : y);
                double xxF = x - xC - shift * y;
                double yyF = y;

                // int xx = xxF + 0.5 * stalg::sign_custom(xxF);
                // int yy = yyF + 0.5 * stalg::sign_custom(yyF);
                int xx = stalg::round(xxF);
                int yy = stalg::round(yyF);

                if (xx >= 0 && yy>= 0 && xx < srcWidth && yy < srcHeight)
                {
                    data_[y][x] = src[yy][xx];
                }
            }
        }
    }

    /* Рассчитывает границы "реального" изображения (вне рассчитанного прямоугольника цвет фона).
     */
    void CalculateBGBorders(const int bgColor = 255)
    {
        upper_bound = -1;
        lower_bound = -1;
        left_bound  = -1;
        right_bound = -1;
        for (int i = 0; i < height_ && upper_bound < 0; ++i)
        {
            for (int j = 0; j < width_ && upper_bound < 0; ++j)
            {
                if (data_[i][j] != bgColor)
                {
                    upper_bound = i;
                }
            }
        }
        for (int i = height_ - 1; i >= 0 && lower_bound < 0; --i)
        {
            for (int j = 0; j < width_ && lower_bound < 0; ++j)
            {
                if (data_[i][j] != bgColor)
                {
                    lower_bound = i;
                }
            }
        }
        for (int j = 0; j < width_ && left_bound < 0; ++j)
        {
            for (int i = 0; i < height_ && left_bound < 0; ++i)
            {
                if (data_[i][j] != bgColor)
                {
                    left_bound = j;
                }
            }
        }
        for (int j = width_ - 1; j >= 0 && right_bound < 0; --j)
        {
            for (int i = 0; i < height_ && right_bound < 0; ++i)
            {
                if (data_[i][j] != bgColor)
                {
                    right_bound = j;
                }
            }
        }
    }

    void printInfo() const
    {
        std::cout << "stalg::img::Image2d info : " << std::endl;
        std::cout << "height = " << height_ << ", width = " << width_ << std::endl;
        if (1)
        {
            std::cout << "upper_bound = " << upper_bound << std::endl;
            std::cout << "lower_bound = " << lower_bound << std::endl;
            std::cout << "left_bound  = " << left_bound  << std::endl;
            std::cout << "right_bound = " << right_bound << std::endl;
        }
        std::cout << "**********" << std::endl;
    }

    void printMono() const
    {
        std::cout << "height = " << height_ << ", width = " << width_ << std::endl;
        if (1)
        {
            std::cout << "upper_bound = " << upper_bound << std::endl;
            std::cout << "lower_bound = " << lower_bound << std::endl;
            std::cout << "left_bound  = " << left_bound  << std::endl;
            std::cout << "right_bound = " << right_bound << std::endl;
        }
        for (int i = 0; i < height_; ++i)
        {
            for (int j = 0; j < width_; ++j)
            {
                std::cout << (data_[i][j] ? 'X' : '.');
            }
            std::cout << std::endl;
        }
        std::cout << "**********" << std::endl;
    }
};

/* Применяет к изображению фильтр Кэнни.
 */
template<class T>
void cannyFilter(T **src, T **dst, int width, int height) //!< Фильтр Кэнни
{
    int mask[5][5] = {  {2,  4,  5,  4, 2}
                      , {4,  9, 12,  9, 4}
                      , {5, 12, 15, 12, 5}
                      , {4,  9, 12,  9, 4}
                      , {2,  4,  5,  4, 2}
                     };
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (y >= 5 && y + 5 < height && x >= 5 && x + 5 < width)
            {
                int S = 0;
                for (int i = -2; i < 2; ++i)
                {
                    for (int j = -2; j < 2; ++j)
                    {
                        S += mask[i + 2][j + 2] * src[y + i][x + j];
                    }
                }
                dst[y][x] = S / 159.;
            }
            else
            {
                dst[y][x] = src[y][x];
            }
        }
    }
}

/* Фильтр средним арифметическим, квадратное изображение.
 */
template<class T>
void MeanFilter(T **src, double **dst, int N, int n)
{
    T **cumulArr = new T*[N + 1] + 1;
    for (int i = -1; i < N; ++i)
    {
        cumulArr[i] = new T[N + 1] + 1;
        memset(cumulArr[i] - 1, 0, (N + 1) * sizeof(int));
    }

    // Заполняем массив кумулятивных сумм
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cumulArr[i][j] = cumulArr[i - 1][j] + cumulArr[i][j - 1] - cumulArr[i - 1][j - 1] + src[i][j];
        }
    }

    // Считаем средние арифметические
    double sq = stalg::squared(2*n + 1);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int l = std::max(-1, i - n - 1);
            int r = std::min(N - 1, i + n);
            int t = std::max(-1, j - n - 1);
            int b = std::min(N - 1, j + n);
            dst[i][j] = (cumulArr[b][r] - cumulArr[t][r] - cumulArr[b][l] + cumulArr[t][l]) / sq;
        }
    }

    // Удаляем память
    for (int i = -1; i < N; ++i)
    {
        delete[] (cumulArr[i] - 1);
    }
    delete[] (cumulArr - 1);
}

/* Фильтр минимумом.
 */
template<class T>
void minFilter(T **src, T **dst, int width, int height, int ww, int wh, int wshift = 0) //!< Фильтр минимумом
{
    int wwF = 2 * ww + 1;
    int whF = 2 * wh + 1;

    T **tmp = stalg::Allocate2dArrayCont<T>(height, width - wwF + 1);

    for (int y = 0; y < height; ++y)
    {
        stalg::moving::min(src[y], width, 1, tmp[y], 1, wwF);
    }
    for (int x = 0; x < width - wwF + 1; ++x)
    {
        stalg::moving::min(tmp[0] + x, height, width - wwF + 1, dst[wh] + ww + x, width + wshift, whF);
    }

    stalg::Free2dArrayCont(tmp);
}

/* Медианный фильтр.
 */
template<class T>
void medianFilter(T *src, T *dst, int width, int height,int ws ,int ww, int wh) //!< медианный фильр
{
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            QVector<T> mas;
            for (int xx = std::max(x - ww, 0); xx <= std::min(x + ww, width - 1); ++xx)
            {
                for (int yy = std::max(y - wh, 0); yy <= std::min(y + wh, height - 1); ++yy)
                {
                    mas.push_back(src[ws*yy + xx]);
                }
            }
            qSort(mas.begin(), mas.end());
            dst[ws*y + x] = mas[mas.size() / 2];
        }
    }
}

}
}

#endif // __ST_ALG_IMG_IMAGE_H__
