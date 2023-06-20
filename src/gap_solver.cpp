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
    bool betterNeighbour = true;
    while (betterNeighbour){
        
        std::pair<std::pair<int, int>, std::pair<int,int>> best_swap_index = {{-1,-1}, {-1,-1}}; 
        int best_obj_value = this->_objective_value; // feasibleSol->getObjValue();
        int dpivot = 0; // deposito pivote

        std::cout << best_obj_value << std::endl;
        // std::cout << this->_solution << std::endl;
        // std::cout << this->_solution.getCurrentCapacities()[0] << ", " << this->_solution.getCurrentCapacities()[1] << ", " << this->_solution.getCurrentCapacities()[2] <<std::endl;

        while (dpivot < feasibleSol.getM()-1){
            // std::cout << this->getSolution().getConj()[dpivot].size() << std::endl;
            for (int vpivot = 0; vpivot < this->getSolution().getConj()[dpivot].size(); vpivot++){ // vendedor dentro del deposito pivote.
                int dcomp = dpivot+1; // deposito a comparar contra pivote.
                // std::cout << dcomp << "," << vpivot << std::endl;
                while(dcomp < feasibleSol.getM()){ 
                    // std::cout << dcomp << std::endl;
                    for(int vcomp = 0; vcomp < this->getSolution().getConj()[dcomp].size(); vcomp++){ // vendedor dentro del deposito a comparar.

                        int vpitot_i = this->_solution.getConj()[dpivot][vpivot];
                        int vcomp_i = this->_solution.getConj()[dcomp][vcomp];

                        int valor_obj_swap = this->_objective_value - instance.costs[dpivot][vpitot_i] - instance.costs[dcomp][vcomp_i] + instance.costs[dpivot][vcomp_i] + instance.costs[dcomp][vpitot_i];
                        bool capacities_fact = (this->_solution.getCurrentCapacities()[dpivot] + instance.demands[dpivot][vpitot_i] - instance.demands[dpivot][vcomp_i] >= 0) && (this->_solution.getCurrentCapacities()[dcomp] + instance.demands[dcomp][vcomp_i] - instance.demands[dcomp][vpitot_i] >= 0);

                        if (best_obj_value > valor_obj_swap && capacities_fact){
                            // std::cout << "holi :)" << std::endl;
                            // std::cout << this->_solution.getCurrentCapacities()[dpivot] - instance.demands[dpivot][vpivot] + instance.demands[dpivot][vcomp] << std::endl;
                            // std::cout << this->_solution.getCurrentCapacities()[dcomp] - instance.demands[dcomp][vcomp] + instance.demands[dcomp][vpivot] << std::endl;
                            best_obj_value = valor_obj_swap;
                            best_swap_index = {{dpivot, vpivot}, {dcomp, vcomp}};
                        }
                    }
                    dcomp += 1;
                }
            }
            dpivot += 1;
        }

        if (best_swap_index.first.first != -1){
            std::cout << "holi :)" << std::endl;
            this->_objective_value = best_obj_value;
            int dpivot = best_swap_index.first.first;
            int vpivot = best_swap_index.first.second;
            int dcomp = best_swap_index.second.first;
            int vcomp = best_swap_index.second.second;

            // std::cout << best_swap_index.first.first << std::endl;
            // std::cout << best_swap_index.first.second << std::endl;
            // std::cout << best_swap_index.second.first << std::endl;
            // std::cout << best_swap_index.second.second << std::endl;

            std::cout << "Vendedores que se intercambian: " << this->_solution.getConj()[dpivot][vpivot] << ", " << this->_solution.getConj()[dcomp][vcomp] << std::endl;
            
            this->_solution.assign(dpivot, this->_solution.getConj()[dcomp][vcomp], instance.demands[dpivot][this->_solution.getConj()[dcomp][vcomp]]);
            this->_solution.assign(dcomp, this->_solution.getConj()[dpivot][vpivot], instance.demands[dcomp][this->_solution.getConj()[dpivot][vpivot]]);

            this->_solution.unassign(dpivot, vpivot, instance.demands[dpivot][this->_solution.getConj()[dpivot][vpivot]]);
            this->_solution.unassign(dcomp, vcomp, instance.demands[dcomp][this->_solution.getConj()[dcomp][vcomp]]);

            std::cout << "Capacidades = [";    
            for(int l=0;l<this->_solution.getCurrentCapacities().size();l++){
                std::cout << this->_solution.getCurrentCapacities()[l];
                if (l != this->_solution.getCurrentCapacities().size()- 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "]" << std::endl;
        }
        else {
            std::cout << "bye ;(" << std::endl;
            betterNeighbour = false;
        }
    }
}
