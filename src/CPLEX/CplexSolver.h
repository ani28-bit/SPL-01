#ifndef CPLEXSOLVER_H
#define CPLEXSOLVER_H

#include "../TSP/City.h"
#include "../TSP/Tour.h"

class CplexSolver {
private:
    City* cities;
    int numCities;
    double** distanceMatrix;
    
    
    void buildDistanceMatrix();
    
   
    void freeDistanceMatrix();

 public:
 
    CplexSolver(City cities[], int numCities);
    ~CplexSolver();
    
   
    double solve(int optimalTour[], double timeLimit = 300.0);
    
    static bool isCplexAvailable();
  };

  #endif