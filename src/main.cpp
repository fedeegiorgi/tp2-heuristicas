#include <string>
#include <iostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "gap_solver.h"

int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;

    // Aca empieza la magia.

    GapInstance instance(filename);

    GapSolution solution(instance.m, instance.n, instance.capacities);

    GapSolver solver(instance);

    solver.costHeuristic();
    std::cout << solver.getSolution() << std::endl;
    std::cout << solver.getObjectiveValue() << std::endl;

    solver.SwapLs(solution, instance);
    std::cout << solver.getSolution() << std::endl;
    std::cout << solver.getObjectiveValue() << std::endl;

/*
    solver.costHeuristic();
    std::cout << solver.getSolution() << std::endl;
    std::cout << solver.getObjectiveValue() << std::endl;

    solver.MTHeuristic();
    std::cout << solver.getSolution() << std::endl;
    std::cout << solver.getObjectiveValue() << std::endl;
*/

    // chequeo

    // std::cout << instance.m << " " << instance.n << "\n" <<std::endl;

    // std::cout << "Costos: " << std::endl;
    // int i = 1;
    // for (const auto& array : instance.costs) {
    //     std::cout << "Depósito " << i << std::endl;
    //     for (const auto& element : array) {
    //         std::cout << element << " ";
    //     }
    //     std::cout << std::endl;
    //     i += 1;
    // }
    // std::cout << "\nDemandas: " << std::endl;
    // i = 1;
    // for (const auto& array : instance.demands) {
    //     std::cout << "Depósito " << i << std::endl;
    //     for (const auto& element : array) {
    //         std::cout << element << " ";
    //     }
    //     std::cout << std::endl;
    //     i += 1;
    // }
    // std::cout << "\nCapacidades: " << std::endl;
    // for (const auto& c : instance.capacities) {
    //     std::cout << c << " ";
    // }
    // std::cout << std::endl;

    return 0;
}