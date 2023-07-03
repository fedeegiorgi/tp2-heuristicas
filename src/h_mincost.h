#ifndef H_MINCOST_H
#define H_MINCOST_H

#include "gap_solver.h"

class MinCostHeuristic : public GapSolver {

    public:
        using GapSolver::GapSolver;
        void solve();

};

#endif