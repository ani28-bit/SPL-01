#ifndef TOUR_H
#define TOUR_H

#include "City.h"
#include <iostream>

#define MAX_CITIES 100

class Tour {
private:
    City cities[MAX_CITIES];
    int cityCount;
    double distance;

public:
    Tour() : cityCount(0), distance(0.0) {}
    
    void setCities(City c[], int n) {
        if (n > MAX_CITIES) {
            std::cerr << "Error: Number of cities exceeds maximum limit!" << std::endl;
            return;
        }
        cityCount = n;
        for (int i = 0; i < n; ++i) {
            cities[i] = c[i];
        }
    }
    
    City* getCities() { return cities; }
    const City* getCities() const { return cities; }  // Add const version
    
    int getCityCount() const { return cityCount; }
    
    void setDistance(double d) { distance = d; }
    double getDistance() const { return distance; }
    
    void printTour() const {
        for (int i = 0; i < cityCount; ++i) {
            std::cout << cities[i].getId() << " -> ";
        }
        if (cityCount > 0) {
            std::cout << cities[0].getId() << std::endl;
        }
    }
};

#endif