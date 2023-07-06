#include <string>
#include <iostream>
#include <vector>
#include "gap_instance.h"
#include "gap_solution.h"
#include "gap_solver.h"
#include "h_mincost.h"
#include "h_bestfit.h"
#include "h_mt.h"
#include "ls_swap.h"
#include "vnd.h"

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
    // std::string filename = "instances/real/real_instance";
    std::cout << "Reading file " << filename << std::endl;

    // Aca empieza la magia.

    GapInstance instance(filename);

    GapSolver solver(instance);

    // test de heuristicas constructivas

    MinCostHeuristic greedyMinCost(instance);
    greedyMinCost.solve();
    // std::cout << greedyMinCost.getSolution();
    // std::cout << greedyMinCost.getObjectiveValue() << std::endl;

    // BestFitHeuristic greedyBestFit(instance);
    // greedyBestFit.solve();
    // std::cout << greedyBestFit.getSolution();
    // std::cout << greedyBestFit.getObjectiveValue() << std::endl;

    // MartelloTothHeuristic MT(instance);
    // MT.solve();
    // std::cout << MT.getSolution();
    // std::cout << MT.getObjectiveValue() << std::endl;
    // std::cout << MT.getSolution().getSolutionTime() << std::endl;

    GapSolution solution_previa = greedyMinCost.getSolution();
    // solver.SwapLs(solution_previa, instance);
    std::cout << solution_previa << std::endl;
    std::cout << solution_previa.getObjValue() << std::endl;
    // std::cout << solver.getObjectiveValue() << std::endl;


    VND metaheuristicVnd(instance, solution_previa, {"relocate"});
    metaheuristicVnd.solve();
    std::cout << metaheuristicVnd.getSolution();
    std::cout << metaheuristicVnd.getSolution().getObjValue() << std::endl;

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