#ifndef SELECTION_H
#define SELECTION_H

#include "Individual.h"

class Selection {
public:
    // Tournament Selection
    static Individual tournamentSelection(Individual population[],
                                          int populationSize);

    // Roulette Wheel Selection
    static Individual rouletteWheelSelection(Individual population[],
                                             int populationSize);
};

#endif
