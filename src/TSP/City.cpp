#include "City.h"
#include <iostream> 
#include <cmath>

// default value
City::City() : id(0), x(0.0), y(0.0) {}


City::City(int idVal, double xVal, double yVal) 
    : id(idVal), x(xVal), y(yVal) {}

    //City c(5, 10.5, 20.7);


// getters
int City::getId() const { 
    return id; 
}

double City::getX() const { 
    return x; 
}

double City::getY() const { 
    return y; 
}

// setters
void City::setId(int idVal) { 
    id = idVal; 
}

void City::setX(double xVal) { 
    x = xVal; 
}

void City::setY(double yVal) { 
    y = yVal; 
}

// calculate Euclidean distance
double City::distanceTo(const City& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}