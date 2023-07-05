#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include <vector>
#include <iostream>
#include <algorithm>

class GapSolution {
    public:
        GapSolution();
        GapSolution(int n, int m, std::vector<int> capacities);

        // getters
        int getN() const;
        int getM() const;
        std::vector<std::vector<int>> getConj() const;
        std::vector<int> getCurrentCapacities() const;

        // metodos
        void assign(int deposito, int vendedor, int demandaVendedor);
        void unassign(int deposito, int vendedor, int demandaVendedor);

        friend std::ostream& operator<<(std::ostream& os, const GapSolution& solution);

    private:
        int _n;
        int _m;
        std::vector<std::vector<int>> _depositos;
        std::vector<int> _currentCapacities;
};

#endif