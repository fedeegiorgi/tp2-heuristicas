#ifndef GAP_INSTANCE_H
#define GAP_INSTANCE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class GapInstance
{
    public:
    // Métodos para inicializar la instancia.
    GapInstance();
    GapInstance(std::string filename);
    void ReadFile(std::string filename);

    // Variables de la instancia.
    int m; // Número de depositos.
    int n; // Número de vendedores.
    int maxCost; // c_max definido en la consigna.
    std::vector<std::vector<int>> demands; // matriz m x n: linea = deposito, columna = vendedor. pos ij = demanda del vendedor j al deposito i.
    std::vector<std::vector<int>> costs; // matriz m x n: linea = deposito, columna = vendedor. pos ij = costo de asignar el vendedor j al deposito i.
    std::vector<int> capacities; // vector de tamaño m. pos i = capacidad del deposito i.
    private:

};

#endif