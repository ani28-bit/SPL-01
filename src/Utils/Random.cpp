#include "Random.h"
#include <chrono>
#include <algorithm>

// Initialize static members
std::mt19937 Random::generator;
bool Random::initialized = false;

// Initialize random seed
void Random::initialize(unsigned int seed) {
    if (seed == 0) {
        // Use current time as seed
        seed = static_cast<unsigned int>(
            std::chrono::system_clock::now().time_since_epoch().count()
        );
    }
    generator.seed(seed);
    initialized = true;
}

// Get random integer in range [min, max]
int Random::getInt(int min, int max) {
    if (!initialized) {
        initialize();
    }
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// Get random double in range [0.0, 1.0)
double Random::getDouble() {
    if (!initialized) {
        initialize();
    }
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// Get random double in range [min, max)
double Random::getDouble(double min, double max) {
    if (!initialized) {
        initialize();
    }
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

// Get random boolean
bool Random::getBool(double probability) {
    if (!initialized) {
        initialize();
    }
    return getDouble() < probability;
}

// Shuffle an array
void Random::shuffle(int arr[], int size) {
    if (!initialized) {
        initialize();
    }
    
    // Fisher-Yates shuffle
    for (int i = size - 1; i > 0; i--) {
        int j = getInt(0, i);
        std::swap(arr[i], arr[j]);
    }
}