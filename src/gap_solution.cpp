#include "gap_solution.h"

GapSolution::GapSolution() {}

GapSolution::GapSolution(int m, int n, GapInstance &instance) {
    this->_m = m;
    this->_n = n;
    this->_depositos = std::vector<std::vector<int>>(m, std::vector<int>());
    this->_currentCapacities = instance.capacities;
    this->_instance = instance;
}

int GapSolution::getN() const{
    return this->_n;
}

int GapSolution::getM() const{
    return this->_m;
}

std::vector<std::vector<int>> GapSolution::getDeposits() const{
    return this->_depositos;
}

std::vector<int> GapSolution::getDeposit(int deposit) const {
    return this->_depositos[deposit];
}

std::vector<int> GapSolution::getCurrentCapacities() const {
    return this->_currentCapacities;
}

void GapSolution::assign(int deposito, int vendedor, int demandaVendedor) {
    this->_depositos[deposito].push_back(vendedor);
    // this->_currentCapacities[deposito] -= demandaVendedor;
    this->_currentCapacities[deposito] -= this->_instance.demands[deposito][vendedor];
}

void GapSolution::unassign(int deposito, int vendedor, int demandaVendedor) {
    // this->_depositos[deposito].erase(this->_depositos[deposito].begin() + vendedor);
    // this->_currentCapacities[deposito] += demandaVendedor;
    auto it = std::find(_depositos[deposito].begin(), _depositos[deposito].end(), vendedor);
    int position;
    if (it != _depositos[deposito].end()) {
        position = std::distance(_depositos[deposito].begin(), it);
    }
    this->_depositos[deposito].erase(_depositos[deposito].begin() + position);

    // this->_currentCapacities[deposito] += demandaVendedor;
    this->_currentCapacities[deposito] += this->_instance.demands[deposito][vendedor];
}

double GapSolution::getObjValue() {
    return this->_objective_value;
}

double GapSolution::getSolutionTime() {
    return this->_solution_time;
}

void GapSolution::setObjValue(double objValue) {
    this->_objective_value = objValue;
}

void GapSolution::setTime(double solutionTime) {
    this->_solution_time = solutionTime;
}

void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const GapSolution& solution) {
    os << "Depósitos: \n";
    for (int i = 0; i < solution.getM(); i++) {
        os << i << ": ";
            printVector(solution.getDeposits()[i]);
    }
    os << std::endl;
    // Agregar valor de funcion objetivo
    return os;
}

void GapSolution::apply_swap(lsSwapNeighbour bestNeighbour) {

    // this->_solution.assign(dpivot, this->_solution.getDeposits()[dcomp][vcomp], instance.demands[dpivot][this->_solution.getDeposits()[dcomp][vcomp]]);
    // this->_solution.assign(dcomp, this->_solution.getDeposits()[dpivot][vpivot], instance.demands[dcomp][this->_solution.getDeposits()[dpivot][vpivot]]);
    // this->_solution.unassign(dpivot, this->_solution.getDeposits()[dpivot][vpivot], instance.demands[dpivot][this->_solution.getDeposits()[dpivot][vpivot]]);
    // this->_solution.unassign(dcomp, this->_solution.getDeposits()[dcomp][vcomp], instance.demands[dcomp][this->_solution.getDeposits()[dcomp][vcomp]]);

    int depo_izq = bestNeighbour._depo_izq;
    int depo_der = bestNeighbour._depo_der;
    int vend_izq = bestNeighbour._vend_izq;
    int vend_der = bestNeighbour._vend_der;
    
    std::cout << "apply_swap" << std::endl;
    std::cout << "Chequeo: \n" << depo_izq << ", " << vend_der << "\n"
                        << depo_der << ", " << vend_izq << std::endl;

    this->assign(depo_izq, vend_der, 0);
    this->assign(depo_der, vend_izq, 0);

    this->unassign(depo_izq, vend_izq, 0);
    this->unassign(depo_der, vend_der, 0);
}

void GapSolution::apply_relocate(lsRelocateNeighbour bestNeighbour){
    int d_i = bestNeighbour._d_i;
    int d_ins = bestNeighbour._d_ins;
    int c_j = bestNeighbour._c_j;

    this->assign(d_ins, c_j, 0);
    this->unassign(d_i, c_j, 0);
}