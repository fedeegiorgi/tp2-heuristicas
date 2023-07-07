#include "gap_solution.h"

GapSolution::GapSolution() {}

GapSolution::GapSolution(int m, int n, GapInstance &instance) {
    this->_m = m;
    this->_n = n;
    this->_depositos = std::vector<std::vector<int>>((m+1), std::vector<int>());
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

std::vector<double> GapSolution::getCurrentCapacities() const {
    return this->_currentCapacities;
}

void GapSolution::assign(int deposito, int vendedor) {
    if (deposito == this->getM()){
        this->_depositos[deposito].push_back(vendedor);
    }

    else{
        this->_depositos[deposito].push_back(vendedor);
        this->_currentCapacities[deposito] -= this->_instance.demands[deposito][vendedor];
    }
}

void GapSolution::unassign(int deposito, int vendedor) {
    if (deposito == this->getM()){
        auto it = std::find(_depositos[deposito].begin(), _depositos[deposito].end(), vendedor);
        int position;
        if (it != _depositos[deposito].end()) {
            position = std::distance(_depositos[deposito].begin(), it);
        }
        this->_depositos[deposito].erase(_depositos[deposito].begin() + position);
    }

    else{
        auto it = std::find(_depositos[deposito].begin(), _depositos[deposito].end(), vendedor);
        int position;
        if (it != _depositos[deposito].end()) {
            position = std::distance(_depositos[deposito].begin(), it);
        }
        this->_depositos[deposito].erase(_depositos[deposito].begin() + position);
        this->_currentCapacities[deposito] += this->_instance.demands[deposito][vendedor];
    }
}

double GapSolution::getObjValue() {
    return this->_objective_value;
}

double GapSolution::getSolutionTime() {
    return this->_solution_time;
}

GapInstance GapSolution::getInstance() {
    return this->_instance;
}

void GapSolution::setObjValue(double objValue) {
    this->_objective_value = objValue;
}

void GapSolution::setTime(double solutionTime) {
    this->_solution_time = solutionTime;
}

void GapSolution::apply_swap(lsSwapNeighbour bestNeighbour) {
    int depo_izq = bestNeighbour.depo_izq();
    int depo_der = bestNeighbour.depo_der();
    int vend_izq = bestNeighbour.vend_izq();
    int vend_der = bestNeighbour.vend_der();

    this->assign(depo_izq, vend_der);
    this->assign(depo_der, vend_izq);
    this->unassign(depo_izq, vend_izq);
    this->unassign(depo_der, vend_der);

    _objective_value += bestNeighbour.getDelta();
}

void GapSolution::apply_relocate(lsRelocateNeighbour bestNeighbour){
    int d_i = bestNeighbour.d_i();
    int d_ins = bestNeighbour.d_ins();
    int cliente = bestNeighbour.cliente();

    this->assign(d_ins, cliente);
    this->unassign(d_i, cliente);
    
    _objective_value += bestNeighbour.getDelta();
}

// imprimir solucion

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
    os << "Asignación de depósitos: \n";
    for (int i = 0; i < solution.getM()+1; i++) {
        if (i == solution.getM()) {
            os << "No asignados: ";
        } 
        else {
            os << i << ": ";
        }
        printVector(solution.getDeposits()[i]);
    }
    os << "Valor objetivo: " << solution._objective_value << "\n";
    os << "Tiempo solución: " << solution._solution_time << "\n";
    os << std::endl;
    return os;
}