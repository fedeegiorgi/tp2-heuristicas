#include "h_mincost.h"

void MinCostHeuristic::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    int n = _instance.n;
    int m = _instance.m;
    
    for (int j = 0; j < n; j++){
        int min_cost = 9999; // INF
        int min_index = m + 1;
        
        for (int i = 0; i < m; i++){
            if ((_instance.costs[i][j] < min_cost) && (isFeasible(i,j))){
                min_cost = _instance.costs[i][j];
                min_index = i;
            } 
        }

        if (min_index <= m){
            _solution.assign(min_index, j, _instance.demands[min_index][j]);
            _objective_value += _instance.costs[min_index][j];
        } 
        else {
            _objective_value += _instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
            std::cout << "penalidad\n";
        }
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    _solution_time = duration.count() * 1000; 
}