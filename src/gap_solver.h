#ifndef GAP_SOLVER_H
#define GAP_SOLVER_H

#include <vector>
#include <iostream>
#include "gap_solution.h"
#include "gap_instance.h"

class GapSolver
{
    public:
    GapSolver();
    GapSolver(GapInstance &instance);
    int getObjectiveValue();
    int getSolutionTime();
    GapSolution getSolution();
    void costHeuristic();
    void bestFitHeuristic();
    void MTHeuristic();
    void SwapLs(GapSolution &feasibleSol, GapInstance &instance);

/*
    void RelocateLs();
    void SwapRelocate();
    void RelocateSwap();
    void MetaHeuristic();
*/

    private:
    GapInstance _instance;
    GapSolution _solution;
    int _objective_value;
    int _solution_time;
};

#endif