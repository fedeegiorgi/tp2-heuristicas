#ifndef VND_H
#define VND_H

#include <iostream>
#include <string>

#include "gap_solver.h"

#include "h_mincost.h"
#include "h_bestfit.h"
#include "h_mt.h"

#include "ls_swap.h"
#include "ls_swap_neighbour.h"

#include "ls_relocate.h"
#include "ls_relocate_neighbour.h"

class VND : public GapSolver {

    public:
        using GapSolver::GapSolver;
        VND(GapInstance &instance, GapSolution initial_solution, std::vector<std::string> ls_operators);

        void solve();
        std::vector<std::string> _ls_operators;
};


#endif