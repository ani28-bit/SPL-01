
#ifndef DISTANCEMATRIX_H
#define DISTANCEMATRIX_H

#include "City.h"

class DistanceMatrix {
private:

    double** matrix;
    int numCities;

public:
    

    DistanceMatrix(const City* cities,int n);
    ~DistanceMatrix();
    
    

    double getDistance(int cityIndex1, int cityIndex2) const;
    
   

    int getNumCities() const;
    
    

    double calculateTourDistance(const int* tour,int tourSize) const;
    
   
    void print() const;

 };

#endif