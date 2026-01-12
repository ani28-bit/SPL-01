#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "../TSP/City.h"
#include "../TSP/Tour.h"
#include "Mutation.h"

using namespace std;

int main() {
   
    srand(time(nullptr));
    
    
    const int NUM_CITIES = 8;
    City cities[NUM_CITIES];
    cities[0] = City(0, 0.0, 0.0);
    cities[1] = City(1, 10.0, 0.0);
    cities[2] = City(2, 10.0, 10.0);
    cities[3] = City(3, 0.0, 10.0);
    cities[4] = City(4, 5.0, 5.0);
    cities[5] = City(5, 7.0, 3.0);
    cities[6] = City(6, 3.0, 7.0);
    cities[7] = City(7, 8.0, 8.0);
    
    cout << "\nCreated " << NUM_CITIES << " test cities" << endl;
    cout << fixed << setprecision(2);
    
   
    cout << "\n[TEST 1] Swap Mutation" << endl;
    Tour tour1;
    tour1.setCities(cities, NUM_CITIES);
    
    cout << "Before: ";
    tour1.printTour();
    
    Mutation::swapMutation(tour1);
    
    cout << "After:  ";
    tour1.printTour();
    
    if (tour1.isValid()) {

            cout << "Swap mutation produces valid tour" << endl;
    } 
    else {
           cout << "Invalid tour after swap mutation" << endl;
           return 1;
    }
    
    
    cout << "\n[TEST 2] Inversion Mutation" << endl;
    Tour tour2;
    tour2.setCities(cities, NUM_CITIES);
    
    cout << "Before: ";
    tour2.printTour();
    
    Mutation::inversionMutation(tour2);
    
    cout << "After:  ";
    tour2.printTour();
    
    if (tour2.isValid()) {

              cout << " Inversion mutation produces valid tour" << endl;
    } 

    else {
             cout << " Invalid tour after inversion mutation" << endl;
             return 1;
    }
    
     cout << "\n[TEST 3] Insertion Mutation" << endl;
     Tour tour3;
     tour3.setCities(cities, NUM_CITIES);
    
    cout << "Before: ";
    tour3.printTour();
    
    Mutation::insertionMutation(tour3);
    
    cout << "After:  ";
    tour3.printTour();
    
    if (tour3.isValid()) {
         cout << " Insertion mutation produces valid tour" << endl;
    } 
    else {
           cout << "✗ FAIL: Invalid tour after insertion mutation" << endl;
           return 1;
    }
    
   
    cout << "\n[TEST 4] Scramble Mutation" << endl;
    Tour tour4;
    tour4.setCities(cities, NUM_CITIES);
    
    cout << "Before: ";
    tour4.printTour();
    
    Mutation::scrambleMutation(tour4);
    
    cout << "After:  ";
    tour4.printTour();
    
    if (tour4.isValid()) {

          cout << "Scramble mutation produces valid tour" << endl;
    } 
    else {

          cout << "Invalid tour after scramble mutation" << endl;
          return 1;
    }
    
    
    cout << "\n[TEST 5] Multiple Mutations (100 iterations)" << endl;
    int validCount = 0;
    Tour testTour;
    testTour.setCities(cities, NUM_CITIES);
    
    for (int i = 0; i < 100; i++) {
        Tour temp = testTour;
        
        int mutType = rand() % 4;
        switch(mutType) {

            case 0: Mutation::swapMutation(temp); break;
            case 1: Mutation::inversionMutation(temp); break;
            case 2: Mutation::insertionMutation(temp); break;
            case 3: Mutation::scrambleMutation(temp); break;
        }
        
        if (temp.isValid()) {
            validCount++;
        }
    }
    
    cout << "Valid tours after mutation: " << validCount << "/100" << endl;
    
    if (validCount == 100) {

        cout << " All mutations produce valid tours" << endl;
    } 
    else {
          cout << "Some mutations produce invalid tours" << endl;
          return 1;
    }
    
   
       cout << "\n[TEST 6] Apply Mutation with Probability" << endl;
    
       double mutationRate = 0.5; 
       int mutatedCount = 0;
    
    for (int i = 0; i < 100; i++) {

        Tour temp;
        temp.setCities(cities, NUM_CITIES);
        double beforeDist = temp.getDistance();
        
        Mutation::applyMutation(temp, mutationRate);
        double afterDist = temp.getDistance();
        
        if (beforeDist != afterDist) {
            mutatedCount++;
        }
    }
    
    cout << "Mutations applied: " << mutatedCount << "/100" << endl;
    cout << "Expected: ~50 (with 50% mutation rate)" << endl;
    
   
     if (mutatedCount >= 35 && mutatedCount <= 65) {
        cout << "Mutation rate working correctly" << endl;
     }
     else {
        cout << "Mutation rate seems off (but may be random)" << endl;
    }
    
    
    cout << "\n[TEST 7] Distance Change Analysis" << endl;
    Tour originalTour;
    originalTour.setCities(cities, NUM_CITIES);
    double originalDist = originalTour.getDistance();
    
    cout << "Original distance: " << originalDist << endl;
    
    int improved = 0, worsened = 0, same = 0;
    
    for (int i = 0; i < 50; i++) {
        Tour temp = originalTour;
        Mutation::swapMutation(temp);
        double newDist = temp.getDistance();
        
        if (newDist < originalDist) improved++;
        else if (newDist > originalDist) worsened++;
        else same++;
    }
    
    cout << "After 50 swap mutations:" << endl;
    cout << "  Improved: " << improved << endl;
    cout << "  Worsened: " << worsened << endl;
    cout << "  Same:     " << same << endl;
    
    cout << " Distance analysis complete" << endl;
    
    
    cout << endl;
    cout << "   All Tests Passed! " << endl;
    cout << "   Mutation methods working!" << endl;
    
    
    return 0;
}