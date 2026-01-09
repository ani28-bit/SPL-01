#ifndef SELECTION_H
#define SELECTION_H

#include "../TSP/Tour.h"

class Selection {

 public:
    
    static Tour tournamentSelection(Tour population[],int populationSize,int tournamentSize = 5);

   
    static Tour rouletteWheelSelection(Tour population[],int populationSize);

    static Tour rankSelection(Tour population[],int populationSize);
    
    static Tour randomSelection(Tour population[],int populationSize);

 };

#endif
