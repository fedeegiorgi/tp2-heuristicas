#include "gap_solver.h"

GapSolver::GapSolver() {}

GapSolver::GapSolver(GapInstance instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_time = 0;
    this->_solution = GapSolution(this->_instance);
}

int GapSolver::getObjectiveValue(){
    return this->_objective_value;
}

int GapSolver::getSolutionTime(){
    return this->_solution_time;
}

GapSolution GapSolver::getSolution(){
    return this->_solution;
}

void GapSolver::HeuristicCost(){
    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    n = this->_instance.getN()
    m = this->_instance.getM()
    
    for (int j = 0; j < n; j++){
        int min_cost = 9999; // INF
        int min_index = m + 1;
        for (int i = 0; i < m; i++){
            if ((this->_instance->costs[i][j] < min_cost) && (this->_solution->_currentCapacities[i] >= this->_instance->demands[i][j])){
                int min_cost = this->_instance->costs[i][j]
                int min_index = i;
            } 
        }
        if (min_index <= m){
            this->_solution.assign(min_index, j, this->_instance->demands[min_index][j]);
            this->_objective_value += this->_instance->costs[i][j];
        }
        else {
            this->_objective_value += this->_instance->maxCost * 3 // Sumo la penalidad de no poder asignar al vendedor.
        }    
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    this->_solution_time = duration.count() * 1000; 
}

