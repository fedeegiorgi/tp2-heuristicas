#include "ls_swap_neighbour.h"

lsSwapNeighbour::lsSwapNeighbour(double delta, int depo_izq, int depo_der, int vend_izq, int vend_der) {
    _delta = delta;
    _depo_izq = depo_izq;
    _depo_der = depo_der;
    _vend_izq = vend_izq;
    _vend_der = vend_der;
}

double lsSwapNeighbour::getDelta() {
    return _delta;
}

bool lsSwapNeighbour::operator<(const lsSwapNeighbour& other) const {
    return this->_delta < other._delta;
}

bool lsSwapNeighbour::operator>(const lsSwapNeighbour& other) const {
    return this->_delta > other._delta;
}
bool lsSwapNeighbour::operator<=(const lsSwapNeighbour& other) const {
    return this->_delta <= other._delta;
}
bool lsSwapNeighbour::operator>=(const lsSwapNeighbour& other) const {
    return this->_delta >= other._delta;
}

// void lsSwapNeighbour::apply_to_solution(GapSolution &solution) {
//     solution.apply_swap(_depo_izq, _depo_der, _vend_izq, _vend_der);
// }