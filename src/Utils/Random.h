#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
private:
    static std::mt19937 generator;
    static bool initialized;

public:
    // Initialize random seed
    static void initialize(unsigned int seed = 0);
    
    // Get random integer in range [min, max] (inclusive)
    static int getInt(int min, int max);
    
    // Get random double in range [0.0, 1.0)
    static double getDouble();
    
    // Get random double in range [min, max)
    static double getDouble(double min, double max);
    
    // Get random boolean with given probability of being true
    static bool getBool(double probability = 0.5);
    
    // Shuffle an array of integers
    static void shuffle(int arr[], int size);
};

#endif