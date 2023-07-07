#include "h_mt.h"

// Idea sacada del paper "A class of greedy algorithms" de los autores Martello and Toth
void MartelloTothHeuristic::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<int, double>> vendedores;
    for (int j = 0; j < _instance.n; j++) {

        double first_min = 9999; // INF
        double second_min = 9999;
        int best_index = 0;
        int second_best_index = 0;

        for (int i = 0; i < _instance.m; i++) {
            if (_instance.costs[i][j] - first_min < -1e-6 && _instance.costs[i][j] - second_min < -1e-6) { // _instance.costs[i][j] < first_min && _instance.costs[i][j] < second_min
                second_min = first_min;
                first_min = _instance.costs[i][j];
                second_best_index = best_index;
                best_index = i;
            }
            else if (-1e-6 > first_min - _instance.costs[i][j] && _instance.costs[i][j] - second_min < -1e-6) { // _instance.costs[i][j] > first_min && _instance.costs[i][j] < second_min
                second_min = _instance.costs[i][j];
                second_best_index = i;
            }
        }
        std::pair<int, double> vendedor(j, second_min-first_min);
        vendedores.push_back(vendedor);
    }

    std::sort(vendedores.begin(), vendedores.end(), [](const auto& p1, const auto& p2) {
        return (-1e-6 > p2.second - p1.second); // p1.second > p2.second
    });

    for (std::pair<int, int> k : vendedores) {
        int j = k.first;
        double min_cost = 9999; // INF
        int min_index = _instance.m + 1;

        for (int i = 0; i < _instance.m; i++){
            if ((_instance.costs[i][j] - min_cost < -1e-6) && (isFeasible(i,j))) { // _instance.costs[i][j] < min_cost) && (isFeasible(i,j)
                min_cost = _instance.costs[i][j];
                min_index = i;
            } 
        }
        if (min_index <= _instance.m){
            _solution.assign(min_index, j);
            _objective_value += _instance.costs[min_index][j];
        } 
        else {
            _solution.assign(_solution.getM(), j);
            _objective_value += _instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
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