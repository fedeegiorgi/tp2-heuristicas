#include "gap_solution.h"

GapSolution::GapSolution() {}

GapSolution::GapSolution(int m, int n) {
    this->_m = m;
    this->_n = n;
    this->_conjuntos = std::vector<std::vector<int>>(m);

    for (auto deposito : _conjuntos) {
        deposito.push_back({});
    }
}

int GapSolution::getN() const{
    return this->_n;
}

int GapSolution::getM() const{
    return this->_m;
}

std::vector<std::vector<int>> GapSolution::getConj() const{
    return this->_conjuntos;
}

void GapSolution::assign(int deposito, int vendedor) {
    this->_conjuntos[deposito].push_back(vendedor);
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
        // for (int i = 0; i < solution.getM(); i++) {
            printVector(solution.getConj()[i]);
        // }
    }
    os << std::endl;
    return os;
}