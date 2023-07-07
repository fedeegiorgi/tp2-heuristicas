#include "h_bestfit.h"

void BestFitHeuristic::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < _instance.n; j++) {

        int minCapacity = 9999; // INF
        int min_index = 0;

        for (int i = 0; i < _instance.m; i++) {
            int remainCapacity = _solution.getCurrentCapacities()[i] - _instance.demands[i][j];
            if ((isFeasible(i,j)) && (remainCapacity < minCapacity)) {
                min_index = i;
                minCapacity = remainCapacity;
            }
        }

        if (minCapacity < 9999) {
            _solution.assign(min_index, j, _instance.demands[min_index][j]);
            _objective_value += _instance.costs[min_index][j];
        }
        else {
            _objective_value += _instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
            _solution.assign(_solution.getM(), j, 0);
        }
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    _solution_time = duration.count() * 1000;
    _solution.setObjValue(_objective_value);
    _solution.setTime(_solution_time);     
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