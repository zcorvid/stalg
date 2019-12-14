#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include <cmath>

#include "differential_evolution.h"
#include "simulated_annealing.h"
#include "brute_force.h"
#include "MathFunctionsLib_1.h"
#include "MathFunctionsLib_1.test.h"

int main(int argc, char* argv[])
{
    if (argc == 2 && argv[1] == std::string("--test")) {
        Test_MathFunctionsLib_1_All();
    } else {
        std::function<double(const std::vector<double>&)> himmelblau =
                [](const std::vector<double>& arg) {
                    double x = arg[0];
                    double y = arg[1];
                    double value = stalg::sqr(x * x + y - 11.) + 100 * stalg::sqr(x + y * y - 7);
                    return value;
                };

        stalg::Optimizer_DifferentialEvolution<double, double> optimizer_SE(3, stalg::MathFunctionsLib_1::Rastrigin(3), {-5.12, -5.12, -5.12}, {5.12, 5.12, 5.12});
        optimizer_SE.SetMaxSteps(50);
        optimizer_SE.SetFParameter();
        optimizer_SE.SetMutationProbability();
        optimizer_SE.SetSizeOfPopulation(20);
        optimizer_SE.Init();
        optimizer_SE.Work();
        optimizer_SE.SayHello();

        stalg::Optimizer_BruteForce<double, double> optimizer_BF(3, stalg::MathFunctionsLib_1::Rastrigin(3), {-1.12, -1.12, -1.12}, {1.12, 1.12, 1.12});
        double epsilonka_x = 0.1;
        double epsilonka_y = 0.1;
        double epsilonka_z = 0.1;
        optimizer_BF.SetAccuracy({epsilonka_x, epsilonka_y, epsilonka_z});
        optimizer_BF.Work();
        optimizer_BF.SayHello();

        std::cout << "ПРЕВЕД МЕДВЕД !!!" << std::endl;

        // stalg::Optimizer_SimulatedAnnealing<double, double> optimizer_SA(2, stalg::MathFunctionsLib_1::Rastrigin(), {-5.12, -5.12}, {5.12, 5.12});
        // optimizer_SA.SetStartPoint();
        // optimizer_SA.SetStartTemperature(100.);
        // optimizer_SA.Init();
        // optimizer_SA.Work();
        // optimizer_SA.SayHello();
    }
    return 0;
}

