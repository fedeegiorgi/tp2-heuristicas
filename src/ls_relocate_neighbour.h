#ifndef LS_RELOCATE_NEIGHBOUR_H
#define LS_RELOCATE_NEIGHBOUR_H

#include "gap_solution.h"

class lsRelocateNeighbour {
    public:
        lsRelocateNeighbour(double delta, int d_i, int d_ins, int cliente);
        double getDelta();
        int d_i();
        int d_ins();
        int cliente();

    private:
        double _delta;
        int _d_i; 
        int _d_ins; 
        int _cliente; 
        bool operator<(const lsRelocateNeighbour& other) const;
        bool operator>(const lsRelocateNeighbour& other) const;
        
};

#endif