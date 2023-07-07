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

// Para debugging ---------------------------------------------------------
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

std::pair<bool,double> check_fact(GapSolution solution, GapInstance instance){
        double costs = 0;
        for (int i = 0; i < solution.getDeposits().size(); i++){
            double demands = 0;
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

// Para resultados ---------------------------------------------------------

struct Result {
    std::string type_instance;
    std::string instance;
    int m;
    int n;
    // Constructiva
    double ov_mincost;
    double st_mincost;
    double ov_bestfit;
    double st_bestfit;
    double ov_mt;
    double st_mt;

    // Constructiva + Local Search

    // minCost
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

    // Metaheuristicas VND

    // minCost
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
            // minCost
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
            // minCost
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
            // minCost
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
            // minCost
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
    // Para guardar los resultados de las instancias de testing "gap" con las distintas heuristicas descomentar las siguientes 3 lineas.

    // std::vector<Result> results_gap;
    // getResults("instances/gap", results_gap);
    // exportToCSV(results_gap, "output_gap.csv");

    // Para guardar los resultados de la instancia real con las distintas heuristicas descomentar las siguientes 3 lineas.

    // std::vector<Result> results_real;
    // getResults("instances/real", results_real);
    // exportToCSV(results_real, "output_real.csv");

    // Para probar una una sola instancia descomentar las siguientes tres lineas y las 3 lineas de la heuristica a utilizar.
    // Para ademas usar Local Search con algun operador o VND, descomentar las lineas que definen metaheuristicVnd y en el vector de strings escribir los operadores 
    // a usar en el orden deseado (de querer usar local search con uno solo, escribir solo el operador deseado.).

    // std::string filename = "instances/real/real_instance"; // -> Insertar el path a la instancia deseada.
    // std::cout << "Reading file \n" << filename << std::endl;
    // GapInstance instance(filename);

    // Selector de Heuristica Constructiva

    // MinCostHeuristic greedyMinCost(instance);
    // greedyMinCost.solve();
    // std::cout << greedyMinCost.getSolution();

    // BestFitHeuristic greedyBestFit(instance);
    // greedyBestFit.solve();
    // std::cout << greedyBestFit.getSolution();

    // MartelloTothHeuristic MT(instance);
    // MT.solve();
    // std::cout << MT.getSolution();

    // Selector Local Search / VND

    // Importante, el constructor de VND recibe una instancia y una solucion. Donde esta el .getSolution() completar con la heuristica usada.

    // MESSI: Metaheuristic for Efficient Solving using Solution Improvement

    // VND MESSI(instance, MT.getSolution(), {"swap", "relocate"});
    // MESSI.solve();
    // std::cout << MESSI.getSolution();

    return 0;
}