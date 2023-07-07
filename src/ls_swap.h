#ifndef LS_SWAP_H
#define LS_SWAP_H

#include "gap_solver.h"
#include "ls_swap_neighbour.h"
#include <set>


class lsSwapOperator : public GapSolver {

    public:
        using GapSolver::GapSolver;
        lsSwapOperator(GapSolution &feasibleSol, GapInstance &instance);
        lsSwapNeighbour getBestNeighbour();

    private:
        bool isSwapFeasible(int dpivot, int dcomp, int vend_izq, int vend_der);
        
};  

#endif