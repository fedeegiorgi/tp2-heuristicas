#include "gap_instance.h"

GapInstance::GapInstance() {}

GapInstance::GapInstance(std::string filename) {
    this->ReadFile(filename);
}

void GapInstance::ReadFile(std::string filename){
    std::ifstream inputFile(filename);

    inputFile >> this->m >> this->n;
    
    this->costs = std::vector<std::vector<double>>(this->m, std::vector<double>(this->n));
    this->demands = std::vector<std::vector<int>>(this->m, std::vector<int>(this->n));
    this->capacities = std::vector<double>(this->m);
    this->maxCost = -1;

    // lectura de c_ij el costo incurrido si j es asignado a i
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            inputFile >> this->costs[i][j];
            if (this->maxCost < this->costs[i][j]) {
                this->maxCost = this->costs[i][j];
            }
        }
    }

    // lectura de d_ij la demanda del vendedor j al depósito i
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            inputFile >> this->demands[i][j];
        }
    }

    // lectura de c_i capacidad máxima de recepción del depósito i
    for (int i = 0; i < this->m; ++i) {
        inputFile >> this->capacities[i];
    }

    inputFile.close();
}
