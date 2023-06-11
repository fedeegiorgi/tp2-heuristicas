#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include<vector>
#include<iostream>

class GapSolution
{
    public:
    GapSolution();
    GapSolution(int n, int m);
    friend std::ostream& operator<<(std::ostream& os, const GapSolution& solution);

    private:
}