#include "gap_solution.h"

GapSolution::GapSolution() {}

GapSolution::GapSolution(int n, int m) {
    this->_n = n;
    this->_m = m;
    this->_conjuntos = std::vector<std::vector<int>>(m, {});
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

void GapSolution::assign(int vendedor, int deposito) {
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
    os << "depositos: ";
    for (int i = 0; i < solution.getM(); i++)
        os << i << " ";
    os << std::endl;
    for (int i = 0; i < solution.getM(); i++) {
        printVector(solution.getConj()[i]);
    }
    return os;
}