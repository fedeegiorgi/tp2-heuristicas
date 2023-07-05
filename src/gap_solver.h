#ifndef GAP_SOLVER_H
#define GAP_SOLVER_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "chrono"

#include "gap_solution.h"
#include "gap_instance.h"

class GapSolver {

    public:
        GapSolver();
        GapSolver(GapInstance &instance);
        double getObjectiveValue();
        double getSolutionTime();
        GapSolution getSolution();
        
        void SwapLs(GapSolution &feasibleSol, GapInstance &instance);
    /*
        void RelocateLs();
        void SwapRelocate();
        void RelocateSwap();
        void MetaHeuristic();
    */
    protected:
        GapInstance _instance;
        GapSolution _solution;
        double _objective_value;
        double _solution_time;
        bool isFeasible(int deposito, int vendedor);
};

#endif