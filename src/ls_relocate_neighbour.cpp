#include "ls_relocate_neighbour.h"

lsRelocateNeighbour::lsRelocateNeighbour(double delta, int d_i, int d_ins, int cliente) {
    _delta = delta;
    _d_i = d_i;
    _d_ins = d_ins;
    _cliente = cliente;
}

double lsRelocateNeighbour::getDelta() {
    return _delta;
}

int lsRelocateNeighbour::d_i() {
    return _d_i;
}

int lsRelocateNeighbour::d_ins() {
    return _d_ins;
}

int lsRelocateNeighbour::cliente() {
    return _cliente;
}

bool lsRelocateNeighbour::operator<(const lsRelocateNeighbour& other) const {
    return this->_delta - other._delta < -1e-6; // this->_delta < other._delta
}

bool lsRelocateNeighbour::operator>(const lsRelocateNeighbour& other) const {
    return -1e-6 > other._delta - this->_delta; // this->_delta > other._delta
}