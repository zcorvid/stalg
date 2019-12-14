#include <iostream>
#include <vector>

#include "stalgcollis.h"

int main(int argc, char* argv[])
{
    stalg::obstruction<double> ob;
    ob.x = 55.7699984;
    ob.y = 37.6475691;
    ob.R =  0.0004502;

    std::vector<stalg::victim<double>> vic(6);

    vic[0].x  = 55.7705582;
    vic[0].y  = 37.6468473;
    vic[0].vx =  0.0000592;
    vic[0].vy =  0.0000280;

    vic[1].x  = 55.7706079;
    vic[1].y  = 37.6468442;
    vic[1].vx =  0.0000180;
    vic[1].vy =  0.0000283;

    vic[2].x  = 55.7706119;
    vic[2].y  = 37.6468463;
    vic[2].vx =  0.0000694;
    vic[2].vy =  0.0000093;

    vic[3].x  = 55.7705239;
    vic[3].y  = 37.6468286;
    vic[3].vx =  0.0000050;
    vic[3].vy =  0.0000035;

    vic[4].x  = 55.7704599;
    vic[4].y  = 37.6467821;
    vic[4].vx =  0.0000054;
    vic[4].vy =  0.0000041;

    vic[5].x  = 55.7704998;
    vic[5].y  = 37.6468107;
    vic[5].vx =  0.0000077;
    vic[5].vy =  0.0000057;

    int ind = stalg::GetNearestVictim(ob, vic);

    std::cout << ind << std::endl;

    return 0;
}
