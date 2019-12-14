#include <iostream>
#include <vector>

#include "clust.h"
#include "../math/metric.h"
#include "../stalgiostream.h"

#include "../math/geom.h"

int main(int argc, char* argv[])
{
//    std::vector<double> mas = {-99.5, -99.2, 21, 22, 23, 21.3, 21.7};
    std::vector<stalg::point2d<double>> mas = {{1, 1}, {1., 1.2}, {0.9, 0.95}, {0, 0}, {100, 66}};
    double border = 1.5;
//    std::vector<int> mark = stalg::clusterize<double>(mas, border, stalg::metric::standard_distance<double>);
    std::vector<int> mark = stalg::clusterize<std::vector<stalg::point2d<double>>, stalg::point2d<double>>
                                      (mas, border, stalg::metric::standard_distance_2d_mink2<stalg::point2d<double>>);
    std::cout << mark << std::endl;
    return 0;
}
