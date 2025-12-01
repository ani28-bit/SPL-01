
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
    
    // get distance between two cities by their indices

    double getDistance(int cityIndex1, int cityIndex2) const;
    
    // get total number of cities

    int getNumCities() const;
    
    // total distance for a tour

    double calculateTourDistance(const int* tour,int tourSize) const;
    
    // print the distance matrix 

    void print() const;

};

#endif