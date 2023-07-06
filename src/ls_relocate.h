#ifndef LS_RELOCATE_H
#define LS_RELOCATE_H

#include "gap_solver.h"
#include "ls_relocate_neighbour.h"
#include <set>


class lsRelocateOperator : public GapSolver {

    public:
        using GapSolver::GapSolver;
        lsRelocateOperator(GapSolution &feasibleSol, GapInstance &instance);
        lsRelocateNeighbour getBestNeighbour();

    private:
        bool lsRelocateOperator::isRelocateFeasible(int d_i, int d_ins, int c_j);
};  

#endif