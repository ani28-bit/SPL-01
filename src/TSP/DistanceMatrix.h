#ifndef DISTANCEMATRIX_H
#define DISTANCEMATRIX_H

#include <vector>
#include "City.h"

class DistanceMatrix {
private:

    std::vector<std::vector<double>> matrix;
    int numCities;

public:
    

    DistanceMatrix(const std::vector<City>& cities);
    
    // get distance between two cities by their indices

    double getDistance(int cityIndex1, int cityIndex2) const;
    
    // get total number of cities

    int getNumCities() const;
    
    // total distance for a tour

    double calculateTourDistance(const std::vector<int>& tour) const;
    
    // print the distance matrix 

    void print() const;

};

#endif