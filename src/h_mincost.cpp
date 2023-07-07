#include "h_mincost.h"

void MinCostHeuristic::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    int n = _instance.n;
    int m = _instance.m;
    
    for (int j = 0; j < n; j++){
        double min_cost = 9999; // INF
        int min_index = m + 1;
        
        for (int i = 0; i < m; i++){
            if ((_instance.costs[i][j] - min_cost < -1e-6) && (isFeasible(i,j))) { // _instance.costs[i][j] < min_cost
                min_cost = _instance.costs[i][j];
                min_index = i;
            } 
        }

        if (min_index <= m){
            _solution.assign(min_index, j, _instance.demands[min_index][j]);
            _objective_value += _instance.costs[min_index][j];
        } 
        else {
            _solution.assign(m, j, 0);
            _objective_value += _instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
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