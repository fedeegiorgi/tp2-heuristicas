#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "gap_instance.h"
#include "ls_swap_neighbour.h"
#include "ls_relocate_neighbour.h"

class lsSwapNeighbour;
class lsRelocateNeighbour;

class GapSolution {
    public:
        GapSolution();
        GapSolution(int n, int m, GapInstance &instance);

        // getters
        int getN() const;
        int getM() const;
        std::vector<std::vector<int>> getDeposits() const;
        std::vector<int> getDeposit(int deposit) const;
        std::vector<int> getCurrentCapacities() const;
        double getObjValue();
        double getSolutionTime();

        // métodos generales
        void assign(int deposito, int vendedor, int demandaVendedor);
        void unassign(int deposito, int vendedor, int demandaVendedor);
        void setObjValue(double objValue);
        void setTime(double solutionTime);

        // métodos para local search
        void apply_swap(lsSwapNeighbour bestNeighbour);
        void apply_relocate(lsRelocateNeighbour bestNeighbour);

        friend std::ostream& operator<<(std::ostream& os, const GapSolution& solution);

    private:
        int _n;
        int _m;
        std::vector<std::vector<int>> _depositos;
        GapInstance _instance;
        std::vector<int> _currentCapacities;
        double _objective_value;
        double _solution_time;
};

#endif