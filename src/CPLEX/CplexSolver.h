#ifndef CPLEXSOLVER_H
#define CPLEXSOLVER_H

#include "../TSP/City.h"
#include "../TSP/Tour.h"

class CplexSolver {
private:
    City* cities;
    int numCities;
    double** distanceMatrix;
    
    // Build distance matrix
    void buildDistanceMatrix();
    
    // Free memory
    void freeDistanceMatrix();

public:
    CplexSolver(City cities[], int numCities);
    ~CplexSolver();
    
    // Solve TSP using CPLEX
    // Returns: optimal distance, fills optimalTour array
    double solve(int optimalTour[], double timeLimit = 300.0);
    
    // Check if CPLEX is available
    static bool isCplexAvailable();
};

#endif