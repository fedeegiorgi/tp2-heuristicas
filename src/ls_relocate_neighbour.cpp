#include "ls_relocate_neighbour.h"

lsRelocateNeighbour::lsRelocateNeighbour(double delta, int d_i, int d_ins, int c_j) {
    _delta = delta;
    _d_i = d_i;
    _d_ins = d_ins;
    _c_j = c_j;
}

double lsRelocateNeighbour::getDelta() {
    return _delta;
}

bool lsRelocateNeighbour::operator<(const lsRelocateNeighbour& other) const {
    return this->_delta < other._delta;
}

bool lsRelocateNeighbour::operator>(const lsRelocateNeighbour& other) const {
    return this->_delta > other._delta;
}
bool lsRelocateNeighbour::operator<=(const lsRelocateNeighbour& other) const {
    return this->_delta <= other._delta;
}
bool lsRelocateNeighbour::operator>=(const lsRelocateNeighbour& other) const {
    return this->_delta >= other._delta;
}

// void lsRelocateNeighbour::apply_to_solution(GapSolution &solution) {
//     solution.apply_Relocate(_d_i, _d_ins, _c_j, _vend_der);
// }