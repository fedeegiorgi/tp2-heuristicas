#ifndef LS_SWAP_NEIGHBOUR_H
#define LS_SWAP_NEIGHBOUR_H

#include "gap_solution.h"

class lsSwapNeighbour {
    public:
        lsSwapNeighbour(double delta, int depo_izq, int depo_der, int vend_izq, int vend_der);
        double getDelta();
        int depo_izq();
        int depo_der();
        int vend_izq();
        int vend_der();
    private:
        double _delta;
        int _depo_izq;
        int _depo_der;
        int _vend_izq;
        int _vend_der;
        bool operator<(const lsSwapNeighbour& other) const;
        bool operator>(const lsSwapNeighbour& other) const;
};

#endif