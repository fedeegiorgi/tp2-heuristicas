#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

#include "gap_instance.h"
#include "gap_solution.h"
#include "gap_solver.h"
#include "h_mincost.h"
#include "h_bestfit.h"
#include "h_mt.h"
#include "vnd.h"

// para debugging ---------------------------------------------------------
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

std::pair<bool,int> check_fact(GapSolution solution, GapInstance instance){
        int costs = 0;
        for (int i = 0; i < solution.getDeposits().size(); i++){
            int demands = 0;
            if (i == solution.getM()){
                for (int j = 0; j < solution.getDeposit(i).size(); j++){
                    costs += 3 * instance.maxCost;
                }
            }
            else{
                for (int j = 0; j < solution.getDeposit(i).size(); j++){
                    int cliente = solution.getDeposit(i)[j];
                    costs += instance.costs[i][cliente];
                    demands += instance.demands[i][cliente];
                }
                if (instance.capacities[i] < demands){
                    return {false, costs};
                }
            }
        }
        return {true, costs};
}

// para resultados ---------------------------------------------------------

struct Result {
    std::string type_instance;
    std::string instance;
    int m;
    int n;
    // constructiva
    double ov_mincost;
    double st_mincost;
    double ov_bestfit;
    double st_bestfit;
    double ov_mt;
    double st_mt;

    // construtiva + local search

    // mincost
    double ov_mincost_relocate;
    double st_mincost_relocate;
    double ov_mincost_swap;
    double st_mincost_swap;

    // bestFit
    double ov_bestfit_relocate;
    double st_bestfit_relocate;
    double ov_bestfit_swap;
    double st_bestfit_swap;

    // MT
    double ov_mt_relocate;
    double st_mt_relocate;
    double ov_mt_swap;
    double st_mt_swap;

    // metaheuristicas VND

    // mincost
    double ov_mincost_relocate_swap;
    double st_mincost_relocate_swap;
    double ov_mincost_swap_relocate;
    double st_mincost_swap_relocate;

    // bestFit
    double ov_bestfit_relocate_swap;
    double st_bestfit_relocate_swap;
    double ov_bestfit_swap_relocate;
    double st_bestfit_swap_relocate;

    // MT
    double ov_mt_relocate_swap;
    double st_mt_relocate_swap;
    double ov_mt_swap_relocate;
    double st_mt_swap_relocate;
};

void exportToCSV(const std::vector<Result>& results, const std::string& filename) {
    std::ofstream file(filename);

    // Chequeamos que el archivo se abra correctamente.
    if (!file) {
        std::cerr << "Error abriendo el archivo." << std::endl;
        return;
    }

    // Seteamos los headers para las columnas
    file << "type_instance,instance,m,n,ov_mincost,st_mincost,ov_bestfit,st_bestfit,ov_mt,st_mt,";
    file << "ov_mincost_relocate,st_mincost_relocate,ov_mincost_swap,st_mincost_swap,";
    file << "ov_bestfit_relocate,st_bestfit_relocate,ov_bestfit_swap,st_bestfit_swap,";
    file << "ov_mt_relocate,st_mt_relocate,ov_mt_swap,st_mt_swap,";
    file << "ov_mincost_relocate_swap,st_mincost_relocate_swap,ov_mincost_swap_relocate,st_mincost_swap_relocate,";
    file << "ov_bestfit_relocate_swap,st_bestfit_relocate_swap,ov_bestfit_swap_relocate,st_bestfit_swap_relocate,";
    file << "ov_mt_relocate_swap,st_mt_relocate_swap,ov_mt_swap_relocate,st_mt_swap_relocate\n";

    // Escribimos el resultado para una asignación dada.
    for (const auto& result : results) {
        file << result.type_instance << "," << result.instance << "," << result.m << "," << result.n << ","
             << result.ov_mincost << "," << result.st_mincost << "," << result.ov_bestfit << "," << result.st_bestfit << "," << result.ov_mt << "," << result.st_mt << ","
             << result.ov_mincost_relocate << "," << result.st_mincost_relocate << "," << result.ov_mincost_swap << "," << result.st_mincost_swap << ","
             << result.ov_bestfit_relocate << "," << result.st_bestfit_relocate << "," << result.ov_bestfit_swap << "," << result.st_bestfit_swap << ","
             << result.ov_mt_relocate << "," << result.st_mt_relocate << "," << result.ov_mt_swap << "," << result.st_mt_swap << ","
             << result.ov_mincost_relocate_swap << "," << result.st_mincost_relocate_swap << "," << result.ov_mincost_swap_relocate << "," << result.st_mincost_swap_relocate << ","
             << result.ov_bestfit_relocate_swap << "," << result.st_bestfit_relocate_swap << "," << result.ov_bestfit_swap_relocate << "," << result.st_bestfit_swap_relocate << ","
             << result.ov_mt_relocate_swap << "," << result.st_mt_relocate_swap << "," << result.ov_mt_swap_relocate << "," << result.st_mt_swap_relocate <<"\n";
    }

    // Cierre del archivo.
    file.close();

    std::cout << "Los resultados fueron exportados a " << filename << " satisfactoriamente." << std::endl;
}

void getResults(const std::string& directoryPath, std::vector<Result> &results) {
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            getResults(entry.path().string(), results);
        } else {
            std::string filePath = entry.path().string();
            std::string fileName = entry.path().filename().string();

            GapInstance instance(filePath);

            std::cout << "filePath: " << filePath << std::endl;
            std::cout << "fileName: " << fileName << std::endl;

            Result resultado;
            resultado.type_instance = fileName[0];
            resultado.instance = fileName;
            resultado.m = instance.m;
            resultado.n = instance.n;

            // ------------------------- constructivas ------------------------------------
            std::cout << "Constructivas..." << std::endl;

            MinCostHeuristic greedyMinCost(instance);
            greedyMinCost.solve();
            resultado.ov_mincost = greedyMinCost.getObjectiveValue();
            resultado.st_mincost = greedyMinCost.getSolutionTime();

            BestFitHeuristic greedyBestFit(instance);
            greedyBestFit.solve();
            resultado.ov_bestfit = greedyBestFit.getObjectiveValue();
            resultado.st_bestfit = greedyBestFit.getSolutionTime();

            MartelloTothHeuristic MT(instance);
            MT.solve();
            resultado.ov_mt = MT.getObjectiveValue();
            resultado.st_mt = MT.getSolutionTime();

            // ------------------------- Local Search - Swap ------------------------------------
            std::cout << "Local Search - Swap" << std::endl;
            // mincost
            VND minCostSwap(instance, greedyMinCost.getSolution(), {"swap"});
            minCostSwap.solve();
            resultado.ov_mincost_swap = minCostSwap.getObjectiveValue();
            resultado.st_mincost_swap = minCostSwap.getSolutionTime();

            // bestFit
            VND bestFitSwap(instance, greedyBestFit.getSolution(), {"swap"});
            bestFitSwap.solve();
            resultado.ov_bestfit_swap = bestFitSwap.getObjectiveValue();
            resultado.st_bestfit_swap = bestFitSwap.getSolutionTime();

            // MT
            VND mtSwap(instance, MT.getSolution(), {"swap"});
            mtSwap.solve();
            resultado.ov_mt_swap = mtSwap.getObjectiveValue();
            resultado.st_mt_swap = mtSwap.getSolutionTime();

            // ------------------------- Local Search - Relocate ------------------------------------
            std::cout << "Local Search - Relocate" << std::endl;
            // mincost
            VND minCostRelocate(instance, greedyMinCost.getSolution(), {"relocate"});
            minCostRelocate.solve();
            resultado.ov_mincost_relocate = minCostRelocate.getObjectiveValue();
            resultado.st_mincost_relocate = minCostRelocate.getSolutionTime();

            // bestFit
            VND bestFitRelocate(instance, greedyBestFit.getSolution(), {"relocate"});
            bestFitRelocate.solve();
            resultado.ov_bestfit_relocate = bestFitRelocate.getObjectiveValue();
            resultado.st_bestfit_relocate = bestFitRelocate.getSolutionTime();

            // MT
            VND mtRelocate(instance, MT.getSolution(), {"relocate"});
            mtRelocate.solve();
            resultado.ov_mt_relocate = mtRelocate.getObjectiveValue();
            resultado.st_mt_relocate = mtRelocate.getSolutionTime();

            // ------------------------- VND(relocate, swap) ------------------------------------
            std::cout << "VND(relocate, swap)" << std::endl;
            // mincost
            VND minCostRelocateSwap(instance, greedyMinCost.getSolution(), {"relocate", "swap"});
            minCostRelocateSwap.solve();
            resultado.ov_mincost_relocate_swap = minCostRelocateSwap.getObjectiveValue();
            resultado.st_mincost_relocate_swap = minCostRelocateSwap.getSolutionTime();

            // bestFit
            VND bestFitRelocateSwap(instance, greedyBestFit.getSolution(), {"relocate", "swap"});
            bestFitRelocateSwap.solve();
            resultado.ov_bestfit_relocate_swap = bestFitRelocateSwap.getObjectiveValue();
            resultado.st_bestfit_relocate_swap = bestFitRelocateSwap.getSolutionTime();

            // MT
            VND mtRelocateSwap(instance, MT.getSolution(), {"relocate", "swap"});
            mtRelocateSwap.solve();
            resultado.ov_mt_relocate_swap = mtRelocateSwap.getObjectiveValue();
            resultado.st_mt_relocate_swap = mtRelocateSwap.getSolutionTime();

            // ------------------------- VND(swap, relocate) ------------------------------------
            std::cout << "VND(swap, relocate)" << std::endl;
            // mincost
            VND minCostSwapRelocate(instance, greedyMinCost.getSolution(), {"swap", "relocate"});
            minCostSwapRelocate.solve();
            resultado.ov_mincost_swap_relocate = minCostSwapRelocate.getObjectiveValue();
            resultado.st_mincost_swap_relocate = minCostSwapRelocate.getSolutionTime();

            // bestFit
            VND bestFitSwapRelocate(instance, greedyBestFit.getSolution(), {"swap", "relocate"});
            bestFitSwapRelocate.solve();
            resultado.ov_bestfit_swap_relocate = bestFitSwapRelocate.getObjectiveValue();
            resultado.st_bestfit_swap_relocate = bestFitSwapRelocate.getSolutionTime();

            // MT
            VND mtSwapRelocate(instance, MT.getSolution(), {"swap", "relocate"});
            mtSwapRelocate.solve();
            resultado.ov_mt_swap_relocate = mtSwapRelocate.getObjectiveValue();
            resultado.st_mt_swap_relocate = mtSwapRelocate.getSolutionTime();

            results.push_back(resultado);
        }
    }
}

int main(int argc, char** argv) {
    // toma de resultados gap

    std::vector<Result> results_gap;
    getResults("instances/gap/test", results_gap);
    exportToCSV(results_gap, "output_test.csv");

    // toma de resultados real

    // std::vector<Result> results_real;
    // getResults("instances/real", results_real);
    // exportToCSV(results_real, "output_real.csv");

    // correr una sola instancia
    // std::string filename = "instances/gap/gap_b/b20200";
    // std::cout << "Reading file \n" << filename << std::endl;

    // GapInstance instance(filename);

    // test de heuristicas constructivas

    // MinCostHeuristic greedyMinCost(instance);
    // greedyMinCost.solve();
    // std::cout << greedyMinCost.getSolution();

    // BestFitHeuristic greedyBestFit(instance);
    // greedyBestFit.solve();
    // std::cout << greedyBestFit.getSolution();

    // MartelloTothHeuristic MT(instance);
    // MT.solve();
    // std::cout << MT.getSolution();

    // VND metaheuristicVnd(instance, MT.getSolution(), {"swap", "relocate"});
    // metaheuristicVnd.solve();
    // std::cout << metaheuristicVnd.getSolution();
    // std::cout << metaheuristicVnd.getSolution().getObjValue() << std::endl;
    // std::cout << metaheuristicVnd.getObjectiveValue() << std::endl;

    // chequeo creación de instancia

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