#ifndef H_BESTFIT_H
#define H_BESTFIT_H

#include "gap_solver.h"

class BestFitHeuristic : public GapSolver {

    public:
        using GapSolver::GapSolver;
        void solve();

};

#endif