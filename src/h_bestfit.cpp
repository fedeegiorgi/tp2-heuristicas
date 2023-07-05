#include "h_bestfit.h"

void BestFitHeuristic::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < this->_instance.n; j++) {

        int minCapacity = 9999; // INF
        int min_index = 0;

        for (int i = 0; i < this->_instance.m; i++) {
            int remainCapacity = this->_solution.getCurrentCapacities()[i] - this->_instance.demands[i][j];
            if ((isFeasible(i,j)) && (remainCapacity < minCapacity)) {
                min_index = i;
                minCapacity = remainCapacity;
            }
        }

        if (minCapacity < 9999) {
            this->_solution.assign(min_index, j, this->_instance.demands[min_index][j]);
            this->_objective_value += this->_instance.costs[min_index][j];
        }
        else {
            this->_objective_value += this->_instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
            std::cout << "penalidad\n";
        }
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    this->_solution_time = duration.count() * 1000;     
}

/*
void printVectorPairs(const std::vector<std::pair<int, int>>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "(" <<vec[i].first << "," << vec[i].second << ")";
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
*/