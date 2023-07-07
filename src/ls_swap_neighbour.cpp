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

int lsSwapNeighbour::depo_izq() {
    return _depo_izq;
}

int lsSwapNeighbour::depo_der() {
    return _depo_der;
}

int lsSwapNeighbour::vend_izq() {
    return _vend_izq;
}

int lsSwapNeighbour::vend_der() {
    return _vend_der;
}

bool lsSwapNeighbour::operator<(const lsSwapNeighbour& other) const {
    return this->_delta - other._delta < -1e-6; // this->_delta < other._delta
}

bool lsSwapNeighbour::operator>(const lsSwapNeighbour& other) const {
    return -1e-6 > other._delta - this->_delta; // this->_delta > other._delta
}