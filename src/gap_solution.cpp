#include "gap_solution.h"
#include "vector"

GapSolution::GapSolution() {}

GapSolution::GapSolution(int m, int n, std::vector<int> capacities) {
    this->_m = m;
    this->_n = n;
    this->_depositos = std::vector<std::vector<int>>(m, std::vector<int>());
    this->_currentCapacities = capacities;
}

int GapSolution::getN() const{
    return this->_n;
}

int GapSolution::getM() const{
    return this->_m;
}

std::vector<std::vector<int>> GapSolution::getConj() const{
    return this->_depositos;
}

std::vector<int> GapSolution::getCurrentCapacities() const {
    return this->_currentCapacities;
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

void GapSolution::assign(int deposito, int vendedor, int demandaVendedor) {
    this->_depositos[deposito].push_back(vendedor);
    // std::cout << "deposito " <<  deposito << std::endl;
    // printVector(_depositos[deposito]);
    this->_currentCapacities[deposito] -= demandaVendedor;
}

std::ostream& operator<<(std::ostream& os, const GapSolution& solution) {
    os << "Depósitos: \n";
    for (int i = 0; i < solution.getM(); i++) {
        os << i << ": ";
            printVector(solution.getConj()[i]);
    }
    os << std::endl;
    // Agregar valor de funcion objetivo
    return os;
}