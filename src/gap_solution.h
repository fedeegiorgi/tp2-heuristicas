#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include <vector>
#include <iostream>

class GapSolution
{
    public:
    GapSolution();
    GapSolution(int n, int m);
    int getN() const;
    int getM() const;
    std::vector<std::vector<int>> getConj() const;
    void assign(int vendedor, int deposito);

    friend std::ostream& operator<<(std::ostream& os, const GapSolution& solution);

    private:
    int _n;
    int _m;
    std::vector<std::vector<int>> _conjuntos;
};

#endif