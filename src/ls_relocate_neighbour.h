#ifndef LS_RELOCATE_NEIGHBOUR_H
#define LS_RELOCATE_NEIGHBOUR_H

#include "gap_solution.h"

class lsRelocateNeighbour {
    public:
        lsRelocateNeighbour(double delta, int d_i, int d_ins, int cliente);
        // void apply_to_solution(GapSolution &solution);
        double getDelta();
        // Pasar a privado dsp.
        double _delta;
        int _d_i; 
        int _d_ins; 
        int _cliente; 
    private:
        bool operator<(const lsRelocateNeighbour& other) const;
        bool operator>(const lsRelocateNeighbour& other) const;
        // bool operator<=(const lsRelocateNeighbour& other) const;
        // bool operator>=(const lsRelocateNeighbour& other) const;
};

#endif