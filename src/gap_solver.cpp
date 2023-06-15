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
    return this->_solution_time
}

GapSolution GapSolver::getSolution(){
    return this->_solution;
}

void GapSolver::HeuristicCost(){
    
}