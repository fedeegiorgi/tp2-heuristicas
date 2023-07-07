#include "gap_solver.h"
#include "chrono"
#include <algorithm>

GapSolver::GapSolver(GapInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_time = 0;
    this->_solution = GapSolution(this->_instance.m, this->_instance.n, this->_instance);
}

double GapSolver::getObjectiveValue() {
    return this->_objective_value;
}

double GapSolver::getSolutionTime() {
    return this->_solution_time;
}

GapSolution GapSolver::getSolution() {
    return this->_solution;
}

bool GapSolver::isFeasible(int deposito, int vendedor) {
    return _solution.getCurrentCapacities()[deposito] >= _instance.demands[deposito][vendedor];
}
