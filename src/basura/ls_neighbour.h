#ifndef LS_NEIGHBOUR_H
#define LS_NEIGHBOUR_H

#include <iostream>

class GapSolution;

class lsNeighbour {
    public:
        lsNeighbour(double delta);
        double getDelta();

        virtual void apply_to_solution(GapSolution &solution);

        bool operator<(const lsNeighbour& other) const;
        bool operator>(const lsNeighbour& other) const;
        bool operator<=(const lsNeighbour& other) const;
        bool operator>=(const lsNeighbour& other) const;
    protected:
        double _delta;
};

#endif