#ifndef COMPARISON_H
#define COMPARISON_H

#include "../TSP/Tour.h"

class Comparison {
public:
    // Compare GA and CPLEX results
    static void compareResults(const Tour& gaTour, double gaDistance,
                              const int cplexTour[], double cplexDistance,
                              int numCities);
    
    // Save comparison to file
    static void saveComparison(const Tour& gaTour, double gaDistance,
                              const int cplexTour[], double cplexDistance,
                              int numCities,
                              double gaTime, double cplexTime,
                              const char* filename = "CPLEX/Summary.txt");
    
    // Calculate optimality gap
    static double calculateGap(double gaDistance, double optimalDistance);
};

#endif