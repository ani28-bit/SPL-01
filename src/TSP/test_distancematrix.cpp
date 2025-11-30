#include <iostream>
#include <vector>
#include <iomanip>
#include "City.h"
#include "DistanceMatrix.h"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "    TESTING DISTANCEMATRIX CLASS" << endl;
    cout << "========================================" << endl;
    
    // Create test cities (forming a square)
    vector<City> cities;
    cities.push_back(City(0, 0.0, 0.0));   // Bottom-left
    cities.push_back(City(1, 4.0, 0.0));   // Bottom-right
    cities.push_back(City(2, 4.0, 3.0));   // Top-right
    cities.push_back(City(3, 0.0, 3.0));   // Top-left
    
    cout << "\n[TEST 1] Creating Cities" << endl;
    for (const auto& city : cities) {
        cout << "City " << city.getId() 
             << ": (" << city.getX() << ", " << city.getY() << ")" << endl;
    }
    cout << "✓ PASS: Created " << cities.size() << " cities" << endl;
    
    // Create distance matrix
    cout << "\n[TEST 2] Building Distance Matrix" << endl;
    DistanceMatrix distMatrix(cities);
    cout << "✓ PASS: Distance matrix created" << endl;
    
    // Test getNumCities
    cout << "\n[TEST 3] Getting Number of Cities" << endl;
    int numCities = distMatrix.getNumCities();
    cout << "Number of cities: " << numCities << endl;
    if (numCities == 4) {
        cout << "✓ PASS: Correct number of cities" << endl;
    } else {
        cout << "✗ FAIL: Expected 4 cities" << endl;
        return 1;
    }
    
    // Test specific distances
    cout << "\n[TEST 4] Testing Specific Distances" << endl;
    cout << fixed << setprecision(2);
    
    // Distance from City0 to City1 (horizontal: 4 units)
    double dist01 = distMatrix.getDistance(0, 1);
    cout << "Distance City0->City1: " << dist01 << " (expected: 4.00)" << endl;
    if (dist01 == 4.0) {
        cout << "✓ PASS" << endl;
    } else {
        cout << "✗ FAIL" << endl;
        return 1;
    }
    
    // Distance from City1 to City2 (vertical: 3 units)
    double dist12 = distMatrix.getDistance(1, 2);
    cout << "Distance City1->City2: " << dist12 << " (expected: 3.00)" << endl;
    if (dist12 == 3.0) {
        cout << "✓ PASS" << endl;
    } else {
        cout << "✗ FAIL" << endl;
        return 1;
    }
    
    // Distance from City0 to City2 (diagonal: 5 units by Pythagorean theorem)
    double dist02 = distMatrix.getDistance(0, 2);
    cout << "Distance City0->City2: " << dist02 << " (expected: 5.00)" << endl;
    if (dist02 == 5.0) {
        cout << "✓ PASS" << endl;
    } else {
        cout << "✗ FAIL" << endl;
        return 1;
    }
    
    // Test symmetry
    cout << "\n[TEST 5] Testing Distance Symmetry" << endl;
    double dist10 = distMatrix.getDistance(1, 0);
    cout << "Distance City0->City1: " << dist01 << endl;
    cout << "Distance City1->City0: " << dist10 << endl;
    if (dist01 == dist10) {
        cout << "✓ PASS: Distance is symmetric" << endl;
    } else {
        cout << "✗ FAIL: Distance should be symmetric" << endl;
        return 1;
    }
    
    // Test distance to self
    cout << "\n[TEST 6] Testing Distance to Self" << endl;
    double distSelf = distMatrix.getDistance(0, 0);
    cout << "Distance City0->City0: " << distSelf << endl;
    if (distSelf == 0.0) {
        cout << "✓ PASS: Distance to self is zero" << endl;
    } else {
        cout << "✗ FAIL: Distance to self should be 0" << endl;
        return 1;
    }
    
    // Test tour distance calculation
    cout << "\n[TEST 7] Testing Tour Distance Calculation" << endl;
    vector<int> tour = {0, 1, 2, 3};  // Square perimeter: 4+3+4+3 = 14
    double tourDist = distMatrix.calculateTourDistance(tour);
    cout << "Tour: 0->1->2->3->0" << endl;
    cout << "Tour distance: " << tourDist << " (expected: 14.00)" << endl;
    if (tourDist == 14.0) {
        cout << "✓ PASS: Tour distance correct" << endl;
    } else {
        cout << "✗ FAIL: Expected tour distance 14.0" << endl;
        return 1;
    }
    
    // Print the matrix
    cout << "\n[TEST 8] Printing Distance Matrix" << endl;
    distMatrix.print();
    cout << "✓ PASS: Matrix printed successfully" << endl;
    
    // Final summary
    cout << "\n========================================" << endl;
    cout << "    ALL TESTS PASSED! ✓✓✓" << endl;
    cout << "    DistanceMatrix is working correctly!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}