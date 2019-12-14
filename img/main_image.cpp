#include <iostream>

#include "../memory/c_array.h"

#include "image.h"

int main(int argc, char* argv[])
{
    /*
    0 0 0 1 1 1 0 0 0
    0 1 1 1 1 1 1 0 0
    1 1 1 0 0 1 1 1 0
    1 1 0 0 0 0 0 1 1
    1 1 0 0 0 0 0 1 1
    1 1 0 0 0 0 0 1 1
    0 1 1 0 0 0 1 1 1
    0 1 1 1 1 1 1 1 1
    0 0 1 1 1 1 1 1 0
    0 0 0 0 0 0 1 1 0
    0 0 0 0 0 0 1 1 0
    0 0 0 0 0 0 1 0 0
    0 0 0 0 0 1 1 0 0
    0 0 0 0 1 1 0 0 0
    0 0 0 0 1 1 0 0 0
    */
    int h = 15;
    int w = 9;
    unsigned char** src = new unsigned char*[h];
    for (int i = 0; i < h; ++i) {
        src[i] = new unsigned char[w];
    }

    src[ 0][0] = 0; src[ 0][1] = 0; src[ 0][2] = 0; src[ 0][3] = 1; src[ 0][4] = 1; src[ 0][5] = 1; src[ 0][6] = 0; src[ 0][7] = 0; src[ 0][8] = 0;
    src[ 1][0] = 0; src[ 1][1] = 1; src[ 1][2] = 1; src[ 1][3] = 1; src[ 1][4] = 1; src[ 1][5] = 1; src[ 1][6] = 1; src[ 1][7] = 0; src[ 1][8] = 0;
    src[ 2][0] = 1; src[ 2][1] = 1; src[ 2][2] = 1; src[ 2][3] = 0; src[ 2][4] = 0; src[ 2][5] = 1; src[ 2][6] = 1; src[ 2][7] = 1; src[ 2][8] = 0;
    src[ 3][0] = 1; src[ 3][1] = 1; src[ 3][2] = 0; src[ 3][3] = 0; src[ 3][4] = 0; src[ 3][5] = 0; src[ 3][6] = 0; src[ 3][7] = 1; src[ 3][8] = 1;
    src[ 4][0] = 1; src[ 4][1] = 1; src[ 4][2] = 0; src[ 4][3] = 0; src[ 4][4] = 0; src[ 4][5] = 0; src[ 4][6] = 0; src[ 4][7] = 1; src[ 4][8] = 1;
    src[ 5][0] = 1; src[ 5][1] = 1; src[ 5][2] = 0; src[ 5][3] = 0; src[ 5][4] = 0; src[ 5][5] = 0; src[ 5][6] = 0; src[ 5][7] = 1; src[ 5][8] = 1;
    src[ 6][0] = 0; src[ 6][1] = 1; src[ 6][2] = 1; src[ 6][3] = 0; src[ 6][4] = 0; src[ 6][5] = 0; src[ 6][6] = 1; src[ 6][7] = 1; src[ 6][8] = 1;
    src[ 7][0] = 0; src[ 7][1] = 1; src[ 7][2] = 1; src[ 7][3] = 1; src[ 7][4] = 1; src[ 7][5] = 1; src[ 7][6] = 1; src[ 7][7] = 1; src[ 7][8] = 1;
    src[ 8][0] = 0; src[ 8][1] = 0; src[ 8][2] = 1; src[ 8][3] = 1; src[ 8][4] = 1; src[ 8][5] = 1; src[ 8][6] = 1; src[ 8][7] = 1; src[ 8][8] = 0;
    src[ 9][0] = 0; src[ 9][1] = 0; src[ 9][2] = 0; src[ 9][3] = 0; src[ 9][4] = 0; src[ 9][5] = 0; src[ 9][6] = 1; src[ 9][7] = 1; src[ 9][8] = 0;
    src[10][0] = 0; src[10][1] = 0; src[10][2] = 0; src[10][3] = 0; src[10][4] = 0; src[10][5] = 0; src[10][6] = 1; src[10][7] = 1; src[10][8] = 0;
    src[11][0] = 0; src[11][1] = 0; src[11][2] = 0; src[11][3] = 0; src[11][4] = 0; src[11][5] = 0; src[11][6] = 1; src[11][7] = 0; src[11][8] = 0;
    src[12][0] = 0; src[12][1] = 0; src[12][2] = 0; src[12][3] = 0; src[12][4] = 0; src[12][5] = 1; src[12][6] = 1; src[12][7] = 0; src[12][8] = 0;
    src[13][0] = 0; src[13][1] = 0; src[13][2] = 0; src[13][3] = 0; src[13][4] = 1; src[13][5] = 1; src[13][6] = 0; src[13][7] = 0; src[13][8] = 0;
    src[14][0] = 0; src[14][1] = 0; src[14][2] = 0; src[14][3] = 0; src[14][4] = 1; src[14][5] = 1; src[14][6] = 0; src[14][7] = 0; src[14][8] = 0;

    int h2;
    int w2;
    std::cout << "Enter h, w : ";
    std::cin >> h2 >> w2;

    // int h2 = 7;
    // int w2 = 7;
    unsigned char** src2 = plls::Allocate2dArray<unsigned char>(h2, w2);
    plls::Set2dArray(src2, h2, w2, 0);
    for (int i = 0; i < h2; ++i)
    {
        for (int j = 0; j < w2; ++j)
        {
            if ((i == j || i+j == h2 - 1) && i >= 2 && i + 2 < h2 && j >= 2 && j + 2 < w2)
            {
                src2[i][j] = 1;
            }
        }
    }
    // src2[0][0] = 1; src2[0][1] = 0; src2[0][2] = 0; src2[0][3] = 0; src2[0][4] = 0; src2[0][5] = 0; src2[0][6] = 0; src2[0][7] = 1;
    // src2[1][0] = 0; src2[1][1] = 1; src2[1][2] = 0; src2[1][3] = 0; src2[1][4] = 0; src2[1][5] = 0; src2[1][6] = 1; src2[1][7] = 0;
    // src2[2][0] = 0; src2[2][1] = 0; src2[2][2] = 1; src2[2][3] = 0; src2[2][4] = 0; src2[2][5] = 1; src2[2][6] = 0; src2[2][7] = 0;
    // src2[3][0] = 0; src2[3][1] = 0; src2[3][2] = 0; src2[3][3] = 1; src2[3][4] = 1; src2[3][5] = 0; src2[3][6] = 0; src2[3][7] = 0;
    // src2[4][0] = 0; src2[4][1] = 0; src2[4][2] = 0; src2[4][3] = 1; src2[4][4] = 1; src2[4][5] = 0; src2[4][6] = 0; src2[4][7] = 0;
    // src2[5][0] = 0; src2[5][1] = 0; src2[5][2] = 1; src2[5][3] = 0; src2[5][4] = 0; src2[5][5] = 1; src2[5][6] = 0; src2[5][7] = 0;
    // src2[6][0] = 0; src2[6][1] = 1; src2[6][2] = 0; src2[6][3] = 0; src2[6][4] = 0; src2[6][5] = 0; src2[6][6] = 1; src2[6][7] = 0;
    // src2[7][0] = 1; src2[7][1] = 0; src2[7][2] = 0; src2[7][3] = 0; src2[7][4] = 0; src2[7][5] = 0; src2[7][6] = 0; src2[7][7] = 1;

    // src2[0][0] = 1; src2[0][1] = 0; src2[0][2] = 0; src2[0][3] = 0; src2[0][4] = 0; src2[0][5] = 0; src2[0][6] = 0; src2[0][7] = 1;
    // src2[1][0] = 1; src2[1][1] = 0; src2[1][2] = 0; src2[1][3] = 0; src2[1][4] = 0; src2[1][5] = 0; src2[1][6] = 0; src2[1][7] = 1;
    // src2[2][0] = 1; src2[2][1] = 0; src2[2][2] = 0; src2[2][3] = 0; src2[2][4] = 0; src2[2][5] = 0; src2[2][6] = 0; src2[2][7] = 1;
    // src2[3][0] = 1; src2[3][1] = 0; src2[3][2] = 0; src2[3][3] = 0; src2[3][4] = 0; src2[3][5] = 0; src2[3][6] = 0; src2[3][7] = 1;
    // src2[4][0] = 1; src2[4][1] = 0; src2[4][2] = 0; src2[4][3] = 0; src2[4][4] = 0; src2[4][5] = 0; src2[4][6] = 0; src2[4][7] = 1;
    // src2[5][0] = 1; src2[5][1] = 0; src2[5][2] = 0; src2[5][3] = 0; src2[5][4] = 0; src2[5][5] = 0; src2[5][6] = 0; src2[5][7] = 1;
    // src2[6][0] = 1; src2[6][1] = 0; src2[6][2] = 0; src2[6][3] = 0; src2[6][4] = 0; src2[6][5] = 0; src2[6][6] = 0; src2[6][7] = 1;
    // src2[7][0] = 1; src2[7][1] = 0; src2[7][2] = 0; src2[7][3] = 0; src2[7][4] = 0; src2[7][5] = 0; src2[7][6] = 0; src2[7][7] = 1;

    plls::img::Image2d img;
    img.printMono();
    double param;
    std::cout << "Enter angle : ";
    std::cin >> param;
    img.InitRotated(src2, h2, w2, param, 0);
    img.CalculateBGBorders(0);
    img.printMono();
    std::cout << "Enter shift : ";
    std::cin >> param;
    img.InitShifted(src2, h2, w2, param, 0);
    img.CalculateBGBorders(0);
    img.printMono();
    return 0;
}
