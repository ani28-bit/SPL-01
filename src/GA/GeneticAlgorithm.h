#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "../TSP/Tour.h"
#include "../TSP/City.h"
#include "Population.h"
#include <string>

class GeneticAlgorithm {
private:
    int populationSize;
    int generations;
    int elitismCount;
    int tournamentSize;
    double crossoverRate;
    double mutationRate;

    City* cities;
    int numCities;

    Tour bestTour;
    double bestDistance;

    
    Tour createOffspring(Population* pop, std::string& crossoverUsed, std::string& mutationUsed);

      public:
  
             GeneticAlgorithm(City cities[], int numCities,
                               int popSize = 99,
                                int gens = 500,
                                 double crossRate = 0.9,
                                  double mutRate = 0.05,
                                   int elitism = 2,
                                    int tournSize = 5);

    
             
                                   void run();             
                                    Tour getBestTour() const;
                                     double getBestDistance() const;
                                     void printResults() const;

                  };

                  #endif
