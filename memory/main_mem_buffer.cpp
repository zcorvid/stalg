#include <iostream>

#include "mem_buffer.h"

int main()
{
    stalg::MemBuffer<int, 4> buf(8);

    buf.PrintState();

    buf.get_buffer(0)[0] = 1;
    buf.get_buffer(0)[1] = 1;
    buf.get_buffer(0)[2] = 1;
    buf.get_buffer(0)[3] = 1;
    buf.get_buffer(0)[4] = 1;
    buf.get_buffer(0)[5] = 1;
    buf.get_buffer(0)[6] = 1;
    buf.get_buffer(0)[7] = 1;

    buf.get_buffer(1)[0] = 0;
    buf.get_buffer(1)[1] = 1;
    buf.get_buffer(1)[2] = 2;
    buf.get_buffer(1)[3] = 3;
    buf.get_buffer(1)[4] = 4;
    buf.get_buffer(1)[5] = 5;
    buf.get_buffer(1)[6] = 6;
    buf.get_buffer(1)[7] = 7;

    buf.get_buffer(2)[0] = 0 * 2;
    buf.get_buffer(2)[1] = 1 * 2;
    buf.get_buffer(2)[2] = 2 * 2;
    buf.get_buffer(2)[3] = 3 * 2;
    buf.get_buffer(2)[4] = 4 * 2;
    buf.get_buffer(2)[5] = 5 * 2;
    buf.get_buffer(2)[6] = 6 * 2;
    buf.get_buffer(2)[7] = 7 * 2;

    buf.get_buffer(3)[0] = 0 + 10;
    buf.get_buffer(3)[1] = 1 + 10;
    buf.get_buffer(3)[2] = 2 + 10;
    buf.get_buffer(3)[3] = 3 + 10;
    buf.get_buffer(3)[4] = 4 + 10;
    buf.get_buffer(3)[5] = 5 + 10;
    buf.get_buffer(3)[6] = 6 + 10;
    buf.get_buffer(3)[7] = 7 + 10;

    buf.PrintState();

    return 0;
}
