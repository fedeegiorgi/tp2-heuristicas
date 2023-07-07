#include "h_bestfit.h"

void BestFitHeuristic::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < _instance.n; j++) {

        double minCapacity = 9999; // INF
        int min_index = 0;

        for (int i = 0; i < _instance.m; i++) {
            double remainCapacity = _solution.getCurrentCapacities()[i] - _instance.demands[i][j];
            if ((isFeasible(i,j)) && (remainCapacity - minCapacity < -1e-6)) { // remainCapacity < minCapacity
                min_index = i;
                minCapacity = remainCapacity;
            }
        }

        if (minCapacity - 9999 < -1e-6) { // minCapacity < 9999
            _solution.assign(min_index, j);
            _objective_value += _instance.costs[min_index][j];
        }
        else {
            _objective_value += _instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
            _solution.assign(_solution.getM(), j);
        }
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    _solution_time = duration.count();
    _solution.setObjValue(_objective_value);
    _solution.setTime(_solution_time);     
}