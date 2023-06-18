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

// Idea sacada del paper "A class of greedy algorithms"
void GapSolver::MTHeuristic() {

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

void GapSolver::SwapLs(GapSolution &feasibleSol, GapInstance &instance){
    int dpivot = 0; // deposito pivote
    bool betterNeighbour = true;
    int valor_obj_actual = this->_objective_value; // feasibleSol->getObjValue();
    std::pair<std::pair<int, int>, std::pair<int,int>> best_swap_index = {{-1,-1}, {-1,-1}};
    while (betterNeighbour){
        while (dpivot < feasibleSol.getM()-1){
            // std::cout << this->getSolution().getConj()[dpivot].size() << std::endl;
            for (int vpivot = 0; vpivot < this->getSolution().getConj()[dpivot].size(); vpivot++){ // vendedor dentro del deposito pivote.
                int dcomp = dpivot+1; // deposito a comparar contra pivote.
                // std::cout << dcomp << "," << vpivot << std::endl;
                while(dcomp < feasibleSol.getM()){ 
                    // std::cout << dcomp << std::endl;
                    for(int vcomp = 0; vcomp < this->getSolution().getConj()[dpivot].size(); vcomp++){ // vendedor dentro del deposito a comparar.
                        int valor_obj_swap = valor_obj_actual - instance.costs[dpivot][vpivot] - instance.costs[dcomp][vcomp] + instance.costs[dpivot][vcomp] + instance.costs[dcomp][vpivot];
                        bool capacities_fact = instance.capacities[dpivot] - instance.demands[dpivot][vpivot] + instance.demands[dpivot][vcomp] >= 0 && instance.capacities[dcomp] - instance.demands[dcomp][vcomp] + instance.demands[dcomp][vpivot] >= 0;
                        if (valor_obj_actual > valor_obj_swap && capacities_fact){
                            std::cout << "holi" << std::endl;
                            valor_obj_actual = valor_obj_swap;
                            best_swap_index = {{dpivot, vpivot}, {dcomp, vcomp}};
                        }
                    }
                    dcomp += 1;
                }
            }
            dpivot += 1;
        }
        if (best_swap_index.first.first != -1){
            this->_objective_value = valor_obj_actual;
            int dpivot = best_swap_index.first.first;
            int vpivot = best_swap_index.first.second;
            int dcomp = best_swap_index.second.first;
            int vcomp = best_swap_index.second.second;
            this->_solution.assign(dpivot, vcomp, instance.demands[dpivot][vcomp]);
            this->_solution.unassign(dpivot, vpivot, instance.demands[dpivot][vpivot]);
            this->_solution.assign(dcomp, vpivot, instance.demands[dcomp][vpivot]);
            this->_solution.unassign(dcomp, vcomp, instance.demands[dcomp][vpivot]);
        }
        else {
            betterNeighbour = false;
        }
    }
}
