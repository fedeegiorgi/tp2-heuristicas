#ifndef H_MT_H
#define H_MT_H

#include "gap_solver.h"

class MartelloTothHeuristic : public GapSolver {

    public:
        using GapSolver::GapSolver;
        void solve();

};

#endif