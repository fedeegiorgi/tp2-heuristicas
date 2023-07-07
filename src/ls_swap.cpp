#include "ls_swap.h"

lsSwapOperator::lsSwapOperator(GapSolution &feasibleSol, GapInstance &instance) : GapSolver(instance) {
    _instance = instance;
    _solution = feasibleSol;
    _objective_value = feasibleSol.getObjValue();
    _solution_time = feasibleSol.getSolutionTime(); // hace falta??
}

lsSwapNeighbour lsSwapOperator::getBestNeighbour() {
    int dpivot = 0; // deposito pivote
    double valor_obj_swap = 0.0;
    lsSwapNeighbour bestNeighbour(0, -1, -1, -1, -1);

    while (dpivot < _solution.getM()){
        for (int vpivot = 0; vpivot < _solution.getDeposits()[dpivot].size(); vpivot++){ // posición de vendedor dentro del deposito pivote.

            int dcomp = dpivot+1; // deposito a comparar contra pivote.

            while(dcomp < _solution.getM()+1){ 
                
                for(int vcomp = 0; vcomp < _solution.getDeposit(dcomp).size(); vcomp++){ // posición del vendedor dentro del deposito a comparar.

                    int vend_izq = _solution.getDeposit(dpivot)[vpivot];
                    int vend_der = _solution.getDeposit(dcomp)[vcomp];

                    if (dcomp == _solution.getM()){
                        valor_obj_swap = _objective_value - _instance.costs[dpivot][vend_izq] - _instance.maxCost*3 
                                            + _instance.costs[dpivot][vend_der] + _instance.maxCost*3;
                    }
                    else{
                        valor_obj_swap = _objective_value - _instance.costs[dpivot][vend_izq] - _instance.costs[dcomp][vend_der] 
                                            + _instance.costs[dpivot][vend_der] + _instance.costs[dcomp][vend_izq];
                    }

                    if (isSwapFeasible(dpivot, dcomp, vend_izq, vend_der)) {
                        double delta = valor_obj_swap - _objective_value;
                        lsSwapNeighbour new_neighbour(delta, dpivot, dcomp, vend_izq, vend_der);
                        if(bestNeighbour.getDelta() > new_neighbour.getDelta()) {
                            bestNeighbour = new_neighbour;
                        }
                    }
                }
                dcomp += 1;
            }
        }
        dpivot += 1;
    }
    
    return bestNeighbour;
}

bool lsSwapOperator::isSwapFeasible(int dpivot, int dcomp, int vend_izq, int vend_der) {
    bool deposit_izq = true;
    bool deposit_der = true;
    
    if (dcomp == _solution.getM()){
        deposit_izq = _solution.getCurrentCapacities()[dpivot] + _instance.demands[dpivot][vend_izq] - _instance.demands[dpivot][vend_der] >= 0;
        deposit_der = true;
    }

    else{
        deposit_izq = _solution.getCurrentCapacities()[dpivot] + _instance.demands[dpivot][vend_izq] - _instance.demands[dpivot][vend_der] >= 0;
        deposit_der = _solution.getCurrentCapacities()[dcomp] + _instance.demands[dcomp][vend_der] - _instance.demands[dcomp][vend_izq] >= 0;
    }

    return deposit_izq && deposit_der;
}