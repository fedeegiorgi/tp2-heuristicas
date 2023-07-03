#include "gap_solver.h"
#include "chrono"
#include <algorithm>

GapSolver::GapSolver() {}

GapSolver::GapSolver(GapInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_time = 0;
    this->_solution = GapSolution(this->_instance.m, this->_instance.n, this->_instance.capacities);
}

double GapSolver::getObjectiveValue() {
    return this->_objective_value;
}

double GapSolver::getSolutionTime() {
    return this->_solution_time;
}

GapSolution GapSolver::getSolution() {
    return this->_solution;
}

void GapSolver::SwapLs(GapSolution &feasibleSol, GapInstance &instance){
    bool betterNeighbour = true;
    while (betterNeighbour){
        
        std::pair<std::pair<int, int>, std::pair<int,int>> best_swap_index = {{-1,-1}, {-1,-1}}; 
        int best_obj_value = this->_objective_value; // feasibleSol->getObjValue();
        int dpivot = 0; // deposito pivote

        std::cout << best_obj_value << std::endl;
        // std::cout << this->_solution << std::endl;
        // std::cout << this->_solution.getCurrentCapacities()[0] << ", " << this->_solution.getCurrentCapacities()[1] << ", " << this->_solution.getCurrentCapacities()[2] <<std::endl;

        while (dpivot < feasibleSol.getM()-1){
            // std::cout << this->getSolution().getConj()[dpivot].size() << std::endl;
            for (int vpivot = 0; vpivot < this->getSolution().getConj()[dpivot].size(); vpivot++){ // vendedor dentro del deposito pivote.
                int dcomp = dpivot+1; // deposito a comparar contra pivote.
                // std::cout << dcomp << "," << vpivot << std::endl;
                while(dcomp < feasibleSol.getM()){ 
                    // std::cout << dcomp << std::endl;
                    for(int vcomp = 0; vcomp < this->getSolution().getConj()[dcomp].size(); vcomp++){ // vendedor dentro del deposito a comparar.

                        int vpitot_i = this->_solution.getConj()[dpivot][vpivot];
                        int vcomp_i = this->_solution.getConj()[dcomp][vcomp];

                        int valor_obj_swap = this->_objective_value - instance.costs[dpivot][vpitot_i] - instance.costs[dcomp][vcomp_i] + instance.costs[dpivot][vcomp_i] + instance.costs[dcomp][vpitot_i];
                        bool capacities_fact = (this->_solution.getCurrentCapacities()[dpivot] + instance.demands[dpivot][vpitot_i] - instance.demands[dpivot][vcomp_i] >= 0) && (this->_solution.getCurrentCapacities()[dcomp] + instance.demands[dcomp][vcomp_i] - instance.demands[dcomp][vpitot_i] >= 0);

                        if (best_obj_value > valor_obj_swap && capacities_fact){
                            // std::cout << "holi :)" << std::endl;
                            // std::cout << this->_solution.getCurrentCapacities()[dpivot] - instance.demands[dpivot][vpivot] + instance.demands[dpivot][vcomp] << std::endl;
                            // std::cout << this->_solution.getCurrentCapacities()[dcomp] - instance.demands[dcomp][vcomp] + instance.demands[dcomp][vpivot] << std::endl;
                            best_obj_value = valor_obj_swap;
                            best_swap_index = {{dpivot, vpivot}, {dcomp, vcomp}};
                        }
                    }
                    dcomp += 1;
                }
            }
            dpivot += 1;
        }

        if (best_swap_index.first.first != -1){
            std::cout << "holi :)" << std::endl;
            this->_objective_value = best_obj_value;
            int dpivot = best_swap_index.first.first;
            int vpivot = best_swap_index.first.second;
            int dcomp = best_swap_index.second.first;
            int vcomp = best_swap_index.second.second;

            // std::cout << best_swap_index.first.first << std::endl;
            // std::cout << best_swap_index.first.second << std::endl;
            // std::cout << best_swap_index.second.first << std::endl;
            // std::cout << best_swap_index.second.second << std::endl;

            std::cout << "Vendedores que se intercambian: " << this->_solution.getConj()[dpivot][vpivot] << ", " << this->_solution.getConj()[dcomp][vcomp] << std::endl;
            
            this->_solution.assign(dpivot, this->_solution.getConj()[dcomp][vcomp], instance.demands[dpivot][this->_solution.getConj()[dcomp][vcomp]]);
            this->_solution.assign(dcomp, this->_solution.getConj()[dpivot][vpivot], instance.demands[dcomp][this->_solution.getConj()[dpivot][vpivot]]);

            this->_solution.unassign(dpivot, vpivot, instance.demands[dpivot][this->_solution.getConj()[dpivot][vpivot]]);
            this->_solution.unassign(dcomp, vcomp, instance.demands[dcomp][this->_solution.getConj()[dcomp][vcomp]]);

            std::cout << "Capacidades = [";    
            for(int l=0;l<this->_solution.getCurrentCapacities().size();l++){
                std::cout << this->_solution.getCurrentCapacities()[l];
                if (l != this->_solution.getCurrentCapacities().size()- 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "]" << std::endl;
        }
        else {
            std::cout << "bye ;(" << std::endl;
            betterNeighbour = false;
        }
    }
}
