#include "ls_relocate.h"

lsRelocateOperator::lsRelocateOperator(GapSolution &feasibleSol, GapInstance &instance) : GapSolver(instance) {
    _instance = instance;
    _solution = feasibleSol;
    _objective_value = feasibleSol.getObjValue();
    _solution_time = feasibleSol.getSolutionTime(); // hace falta??
}

lsRelocateNeighbour lsRelocateOperator::getBestNeighbour() {
    lsRelocateNeighbour bestNeighbour(0, -1, -1, -1);

    for (int d_i = 0; d_i < _solution.getM() - 1; d_i++) {
        for (int c_j = 0; c_j < _solution.getDeposit(d_i).size(); c_j++) {
            int cliente = _solution.getDeposit(d_i)[c_j];
            for (int d_ins = 0; d_ins < _solution.getM(); d_ins++) {
                if (d_i == d_ins) {
                    continue;
                }

                double valor_obj_Relocate = _objective_value - _instance.costs[d_i][cliente] + _instance.costs[d_ins][cliente];

                if (isRelocateFeasible(d_i, d_ins, cliente)) {
                    double delta = valor_obj_Relocate - _objective_value;
                    lsRelocateNeighbour new_neighbour(delta, d_i, d_ins, cliente);
                    if (bestNeighbour.getDelta() > new_neighbour.getDelta()) {
                        bestNeighbour = new_neighbour;
                    }
                }
            }
        }
    }
    return bestNeighbour;
}

bool lsRelocateOperator::isRelocateFeasible(int d_i, int d_ins, int cliente) {
    return _solution.getCurrentCapacities()[d_ins] - _instance.demands[d_i][cliente] >= 0;
}