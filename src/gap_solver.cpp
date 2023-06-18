#include "gap_solver.h"
#include "chrono"
#include <algorithm>

GapSolver::GapSolver() {}

GapSolver::GapSolver(GapInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_time = 0;
    this->_solution = GapSolution(this->_instance.m, this->_instance.n, this->_instance.capacities);
}

int GapSolver::getObjectiveValue() {
    return this->_objective_value;
}

int GapSolver::getSolutionTime() {
    return this->_solution_time;
}

GapSolution GapSolver::getSolution() {
    return this->_solution;
}

void GapSolver::costHeuristic() {

    // Reinicio el objective_value y el solution_time antes de resolver el problema.
    this->_objective_value = 0;
    this->_solution_time = 0;

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    int n = this->_instance.n;
    int m = this->_instance.m;
    
    for (int j = 0; j < n; j++){
        int min_cost = 9999; // INF
        int min_index = m + 1;
        
        for (int i = 0; i < m; i++){
            if ((this->_instance.costs[i][j] < min_cost) && (this->_solution.getCurrentCapacities()[i] >= this->_instance.demands[i][j])){
                min_cost = this->_instance.costs[i][j];
                min_index = i;
            } 
        }

        if (min_index <= m){
            this->_solution.assign(min_index, j, this->_instance.demands[min_index][j]);
            this->_objective_value += this->_instance.costs[min_index][j];
        } 
        else {
            this->_objective_value += this->_instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
        }
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    this->_solution_time = duration.count() * 1000; 
}

void GapSolver::bestFitHeuristic() {

    // Reinicio el objective_value y el solution_time antes de resolver el problema.
    this->_objective_value = 0;
    this->_solution_time = 0;

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < this->_instance.n; j++) {

        int minCapacity = 9999; // INF
        int min_index = 0;

        for (int i = 0; i < this->_instance.m; i++) {
            int remainCapacity = this->_solution.getCurrentCapacities()[i];
            if ((remainCapacity >= this->_instance.demands[i][j]) && (this->_instance.demands[i][j] < minCapacity)) {
                min_index = i;
                minCapacity = this->_instance.demands[i][j];
            }
        }

        if (minCapacity < 9999) {
            this->_solution.assign(min_index, j, this->_instance.demands[min_index][j]);
            this->_objective_value += this->_instance.costs[min_index][j];
        }
        else {
            this->_objective_value += this->_instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
        }
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    this->_solution_time = duration.count() * 1000;     
}


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

// Idea sacada del paper "A class of greedy algorithms"
void GapSolver::MTHeuristic() {

    // Reinicio el objective_value y el solution_time antes de resolver el problema.
    this->_objective_value = 0;
    this->_solution_time = 0;

    std::vector<std::pair<int, int>> vendedores;
    for (int j = 0; j < this->_instance.n; j++) {

        int first_min = 9999; // INF
        int second_min = 9999;
        int best_index = 0;
        int second_best_index = 0;

        for (int i = 0; i < this->_instance.m; i++) {
            if (this->_instance.costs[i][j] < first_min && this->_instance.costs[i][j] < second_min) {
                second_min = first_min;
                first_min = this->_instance.costs[i][j];
                second_best_index = best_index;
                best_index = i;
            }
            else if (this->_instance.costs[i][j] > first_min && this->_instance.costs[i][j] < second_min) {
                second_min = this->_instance.costs[i][j];
                second_best_index = i;
            }
        }
        std::pair<int, int> vendedor(j, second_min-first_min);
        vendedores.push_back(vendedor);
    }

    std::sort(vendedores.begin(), vendedores.end(), [](const auto& p1, const auto& p2) {
        return p1.second > p2.second;
    });

    for (std::pair<int, int> k : vendedores) {
        int j = k.first;
        int min_cost = 9999; // INF
        int min_index = this->_instance.m + 1;

        for (int i = 0; i < this->_instance.m; i++){
            if ((this->_instance.costs[i][j] < min_cost) && (this->_solution.getCurrentCapacities()[i] >= this->_instance.demands[i][j])){
                min_cost = this->_instance.costs[i][j];
                min_index = i;
            } 
        }
        if (min_index <= this->_instance.m){
            this->_solution.assign(min_index, j, this->_instance.demands[min_index][j]);
            this->_objective_value += this->_instance.costs[min_index][j];
        } 
        else {
            this->_objective_value += this->_instance.maxCost * 3; // Sumo la penalidad de no poder asignar al vendedor.
        }
    }
}

