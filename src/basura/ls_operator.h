#ifndef LS_OPERATOR_H
#define LS_OPERATOR_H

#include "gap_solver.h"
#include "ls_neighbour.h"
#include <set>

class lsNeighbour;

class lsOperator : public GapSolver {

    public:
        using GapSolver::GapSolver;
        lsOperator(GapSolution &feasibleSol, GapInstance &instance);
        virtual lsNeighbour getBestNeighbour() = 0;
};

#endif
