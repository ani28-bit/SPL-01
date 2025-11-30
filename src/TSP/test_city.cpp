#include <iostream>
#include <iomanip>
#include "City.h"

using namespace std;

int main() {
    
    
    // Test 1: default constructor
    cout << "[TEST 1] Default Constructor" << endl;

    City city0;

    cout << "City0: ID=" << city0.getId() 
         << ", X=" << city0.getX() 
         << ", Y=" << city0.getY() << endl;

    if (city0.getId() == 0 && city0.getX() == 0.0 && city0.getY() == 0.0) {

           cout << " Default constructor works" << endl;
    } 
    else {

           cout << "Default constructor fails" << endl;
           return 1;
    }
    
    // Test 2: parameterized constructor

    cout << "[TEST 2] Parameterized Constructor" << endl;

    City city1(1, 10.5, 20.3);

    cout << "City1: ID=" << city1.getId() 
         << ", X=" << city1.getX() 
         << ", Y=" << city1.getY() << endl;

    if (city1.getId() == 1 && city1.getX() == 10.5 && city1.getY() == 20.3) {

           cout << " Parameterized constructor works" << endl;
    } 
    else {
           cout << "Parameterized constructor fails" << endl;
           return 1;
    }
    
    // Test 3: setters

    cout << "[TEST 3] Setters" << endl;
     city0.setId(99);
     city0.setX(5.5);
     city0.setY(7.7);

    cout << "Modified City0: ID=" << city0.getId() 
         << ", X=" << city0.getX() 
         << ", Y=" << city0.getY() << endl;

    if (city0.getId() == 99 && city0.getX() == 5.5 && city0.getY() == 7.7) {
         cout << " Setters work" << endl;
    }
     else {
            cout << " Setters fail" << endl;
            return 1;
    }
    
    // Test 4: Distance Calculation (3-4-5 triangle)
    cout << "[TEST 4] Distance Calculation" << endl;

    City cityA(0, 0.0, 0.0);
    City cityB(1, 3.0, 4.0);

    double distance = cityA.distanceTo(cityB);
    cout << fixed << setprecision(2);

    cout << "CityA (0,0) to CityB (3,4): " << distance << endl;
    cout << "Expected: 5.00" << endl;

    if (distance == 5.0) {
           cout << " Distance calculation correct" << endl;
    } 
    else {
           cout << " Distance should be 5.0" << endl;
           return 1;
    }
    
    // Test 5: distance Symmetry
    cout << "[TEST 5] Distance Symmetry" << endl;

    double distAB = cityA.distanceTo(cityB);
    double distBA = cityB.distanceTo(cityA);

    cout << "Distance A->B: " << distAB << endl;
    cout << "Distance B->A: " << distBA << endl;

    if (distAB == distBA) {

           cout << " Distance is symmetric" << endl;
      } 
    else {
           cout << " Distance should be symmetric" << endl;
           return 1;
      }
     
    // Test 6: Distance to Self
    cout << "[TEST 6] Distance to Self" << endl;
    double distSelf = cityA.distanceTo(cityA);

    cout << "Distance to self: " << distSelf << endl;

     if (distSelf == 0.0) {

            cout << " Distance to self is zero" << endl;
       }
     else {

            cout << "Distance to self should be 0" << endl;
            return 1;
    }
    
    // Test 7: Another Distance Test (6-8-10 triangle)
    cout << "[TEST 7] Another Distance Test" << endl;

     City cityC(2, 0.0, 0.0);
     City cityD(3, 6.0, 8.0);

    double distance2 = cityC.distanceTo(cityD);
    cout << "CityC (0,0) to CityD (6,8): " << distance2 << endl;
    cout << "Expected: 10.00" << endl;

      if (distance2 == 10.0) {

             cout << " Second distance calculation correct" << endl;
         }

     else {
             cout << " Distance should be 10.0" << endl;
             return 1;
       }
    
    
    return 0;
}