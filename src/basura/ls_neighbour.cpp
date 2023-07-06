#include "ls_neighbour.h"

lsNeighbour::lsNeighbour(double delta) {
    _delta = delta;
}

double lsNeighbour::getDelta() {
    return _delta;
}

bool lsNeighbour::operator<(const lsNeighbour& other) const {
    return this->_delta < other._delta;
}

bool lsNeighbour::operator>(const lsNeighbour& other) const {
    return this->_delta > other._delta;
}
bool lsNeighbour::operator<=(const lsNeighbour& other) const {
    return this->_delta <= other._delta;
}
bool lsNeighbour::operator>=(const lsNeighbour& other) const {
    return this->_delta >= other._delta;
}

void lsNeighbour::apply_to_solution(GapSolution &solution) {
    std::cout << "apply_to_solution de lsNeighbour" << std::endl;
}