#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "../TSP/Tour.h"
#include "../TSP/City.h"
#include "Population.h"


 class GeneticAlgorithm {

 private:

    int populationSize,generations,elitismCount,tournamentSize;
    double crossoverRate, mutationRate;
   
    
      City* cities;
      int numCities;
    
       Tour bestTour;
       double bestDistance;
    
    
    public:
    
       GeneticAlgorithm(City cities[], int numCities,int popSize = 100,int gens = 500,
                     double crossRate = 0.8,
                     double mutRate = 0.02,
                     int elitism = 2,
                     int tournSize = 5);
    
    
          void run();
    
   
          Tour getBestTour() const;
    
           double getBestDistance() const;
           void printResults() const;
    
    
     private:

         Population* evolvePopulation(Population* pop);
    
         Tour createOffspring(Population* pop);
 };

      #endif