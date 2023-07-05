#include <string>
#include <iostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "gap_solver.h"
#include "h_mincost.h"
#include "h_bestfit.h"
#include "h_mt.h"

// para debugging --------------------------------------------------------------------------------------
void printVecctor(const std::vector<int>& vec){
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
};

int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;

    // Aca empieza la magia.

    GapInstance instance(filename);

    GapSolution solution(instance.m, instance.n, instance.capacities);

    GapSolver solver(instance);

    // MinCostHeuristic greedyMinCost(instance);
    // greedyMinCost.solve();
    // std::cout << greedyMinCost.getSolution();
    // std::cout << greedyMinCost.getObjectiveValue() << std::endl;

    // BestFitHeuristic greedyBestFit(instance);
    // greedyBestFit.solve();
    // std::cout << greedyBestFit.getSolution();
    // std::cout << greedyBestFit.getObjectiveValue() << std::endl;

    MartelloTothHeuristic MT(instance);
    MT.solve();
    std::cout << MT.getSolution();
    std::cout << MT.getObjectiveValue() << std::endl;
    std::cout << MT.getSolution().getSolutionTime() << std::endl;

    // solver.SwapLs(solution, instance);
    // std::cout << solver.getSolution();
    // std::cout << solver.getObjectiveValue() << std::endl;

    // solver.costHeuristic();
    // std::cout << solver.getSolution() << std::endl;
    // std::cout << solver.getObjectiveValue() << std::endl;

    // solver.MTHeuristic();
    // std::cout << solver.getSolution() << std::endl;
    // std::cout << solver.getObjectiveValue() << std::endl;

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