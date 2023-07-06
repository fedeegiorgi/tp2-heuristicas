#include "vnd.h"

VND::VND(GapInstance &instance, GapSolution initial_solution, std::vector<std::string> ls_operators) : GapSolver(instance) {
    _instance = instance;
    _solution = initial_solution;
    _objective_value = initial_solution.getObjValue();
    _solution_time = initial_solution.getSolutionTime();
    _ls_operators = ls_operators;
}

void VND::solve() {
    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    bool didImprove = true;
    double eps = 1e-6;
    while (didImprove) {
        didImprove = false;

        for (int i = 0; i < _ls_operators.size();i++) {

            if(_ls_operators[i] == "swap"){

                lsSwapOperator swapOperator(_solution, _instance);
                lsSwapNeighbour best_neighbour = swapOperator.getBestNeighbour();

                if (best_neighbour.getDelta() < eps) {
                    std::cout << best_neighbour.getDelta() << std::endl;
                    didImprove = true;
                    _solution.apply_swap(best_neighbour);
                    break;
                }

            }
            // else if(_ls_operators[i] == "relocate"){

            // }
        }
        
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}










/// por si hacemos grasp(?

    // if (_initial_solution == "mincost") {
    //     MinCostHeuristic greedyMinCost(_instance);
    //     greedyMinCost.solve();

    //     _solution = greedyMinCost.getSolution();
    //     _solution_time = greedyMinCost.getSolutionTime();
    //     _objective_value = greedyMinCost.getObjectiveValue();
    // }
    // else if (_initial_solution == "bestfit") {
    //     BestFitHeuristic greedyBestFit(_instance);
    //     greedyBestFit.solve();

    //     _solution = greedyBestFit.getSolution();
    //     _solution_time = greedyBestFit.getSolutionTime();
    //     _objective_value = greedyBestFit.getObjectiveValue();
    // }
    // else if (_initial_solution == "mt") {
    //     MartelloTothHeuristic MT(_instance);
    //     MT.solve();

    //     _solution = MT.getSolution();
    //     _solution_time = MT.getSolutionTime();
    //     _objective_value = MT.getObjectiveValue();
    // }