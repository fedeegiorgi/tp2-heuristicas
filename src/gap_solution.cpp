#include "gap_solution.h"

GapSolution::GapSolution() {}

GapSolution::GapSolution(int n, int m) {
    this->_n = n;
    this->_m = m;
    this->conjuntos = std::vector<std::vector<int>>(m, {});
}

int GapSolution::getN(){
    return this->_n;
}

int GapSolution::getM(){
    return this->_m;
}

void GapSolution::assign(int vendedor, int deposito) {
    this->conjuntos[deposito].push_back(vendedor);
}

std::ostream& operator<<(std::ostream& os, const GapSolution& solution) {
    return os;
}