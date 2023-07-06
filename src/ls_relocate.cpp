#include "ls_relocate.h"

lsRelocateOperator::lsRelocateOperator(GapSolution &feasibleSol, GapInstance &instance) : GapSolver(instance) {
    _instance = instance;
    _solution = feasibleSol;
    _objective_value = feasibleSol.getObjValue();
    _solution_time = feasibleSol.getSolutionTime(); // hace falta??
}

lsRelocateNeighbour lsRelocateOperator::getBestNeighbour() {
    int d_i = 0; // deposito i
    lsRelocateNeighbour bestNeighbour(0, -1, -1, -1);

    while (d_i < _solution.getM()-1){

        for (int c_j = 0; c_j < _solution.getDeposits()[d_i].size(); c_j++){ // posición del cliente j dentro del deposito i.

            int d_ins = 0; // deposito a insertar el cliente j

            while(d_ins < _solution.getM()){ 

                if (d_i == d_ins) {
                    d_ins +=1;
                }

                int cliente = _solution.getDeposit(d_i)[c_j];
                double valor_obj_Relocate = _objective_value - _instance.costs[d_i][cliente] + _instance.costs[d_ins][cliente];

                if (isRelocateFeasible(d_i, d_ins, c_j)) {
                    double delta = _objective_value - valor_obj_Relocate;
                    lsRelocateNeighbour new_neighbour(delta, d_i, d_ins, c_j);
                    if(bestNeighbour.getDelta() > new_neighbour.getDelta()) {
                        bestNeighbour = new_neighbour;
                    }
                }
                d_ins += 1;
            }
        }
        d_i += 1;
    }
    return bestNeighbour;
}

bool lsRelocateOperator::isRelocateFeasible(int d_i, int d_ins, int c_j) {
    return _solution.getCurrentCapacities()[d_ins] + _instance.demands[d_i][c_j] >= 0;
}