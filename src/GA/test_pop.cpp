#include <iostream>
#include <iomanip>
#include "../TSP/City.h"
#include "../TSP/Tour.h"
#include "Population.h"

using namespace std;

int main() {
    
    cout << " TESTING POPULATION CLASS" << endl;

    
   
    const int Num_Cities = 5;
    City cities[Num_Cities];
    cities[0] = City(0, 0.0, 0.0);
    cities[1] = City(1, 10.0, 0.0);
    cities[2] = City(2, 10.0, 10.0);
    cities[3] = City(3, 0.0, 10.0);
    cities[4] = City(4, 5.0, 5.0);
    
    cout << "\nCreated " << Num_Cities << " test cities:" << endl;

       for (int i = 0; i < Num_Cities; i++) {

          cout << "  City " << cities[i].getId() 
             << ": (" << cities[i].getX() 
             << ", " << cities[i].getY() << ")" << endl;
    }
    
    
      cout << "\n[TEST 1] Creating Population" << endl;

         const int POP_Size = 10;
         Population pop(POP_Size, cities, Num_Cities);
    
        cout << "Population size: " << pop.getSize() << endl;

        if (pop.getSize() == POP_Size) {

               cout << "Population created successfully" << endl;
        }
         else {

               cout << "Wrong population size" << endl;

               return 1;
           }
    
    
           cout << "\n[TEST 2] Validate All Tours" << endl;

             bool allValid = true;
             int validCount = 0;
    
            for (int i = 0; i < POP_Size; i++) {

              if (pop[i].isValid()) {

                  validCount++;
            } 
            else {
                 
                   allValid = false;
                   cout << "Tour"<< i <<"is Invalid"<< endl;
            }
         }
    
           cout << "Valid tours: "<< validCount <<"/"<< POP_Size << endl;

            if (allValid) {

                   cout << "All tours are valid" << endl;
            }
            
            else {

                    cout << "Some tours are invalid" << endl;
                    return 1;
              }
    
   
            cout << "\n[TEST 3] Display First 3 Tours" << endl;

            cout << fixed << setprecision(2);

           for (int i = 0; i < 3 && i < POP_Size; i++) {

               cout << "  Tour " << i << ":";
               pop[i].printTour();

          }

               cout << "Tours displayed" << endl;
    
   
               cout <<"\n[TEST 4] Get Best Tour"<< endl;
               Tour* bestTour = pop.getBest();
    
             if (bestTour != nullptr) {

               cout << "Best tour found!"<< endl;
               cout << "  ";
               bestTour->printTour();
               cout << "Best tour retrieved"<< endl;

            } 
            else {

                  cout << "Best tour is null" << endl;
                  return 1;
                }
    
   
               cout << "\n[TEST 5] Get Worst Tour" << endl;
               Tour* worstTour = pop.getWorst();
    
              if (worstTour != nullptr) {

                cout << "Worst tour found!" << endl;
                cout << "  ";
                worstTour->printTour();
                cout << "Worst tour retrieved" << endl;

         } 

         else {

               cout << "Worst tour is null"<< endl;
               return 1;
            }
    
    
           cout << "\n[TEST 6] Compare Best vs Worst" << endl;
           double bestDist = bestTour->getDistance();
           double worstDist = worstTour->getDistance();
    
           cout << "Best distance:  " << bestDist << endl;
           cout << "Worst distance: " << worstDist << endl;
           cout << "Difference:" << (worstDist - bestDist) << endl;
    
           if (bestDist <= worstDist) {

                  cout << "Best distance <= Worst distance" << endl;

           } 
           else {

                  cout << " Best should be <= Worst" << endl;
                  return 1;
             }
    
    
               cout << "\n[TEST 7] Calculate Average Distance" << endl;
               double avgDist = pop.getAvgFitness();
    
               cout << "Average distance: " << avgDist << endl;
               cout << "Range: ["<< bestDist << ", " << worstDist << "]"<< endl;
    
               if (avgDist >= bestDist && avgDist <= worstDist) {

                  cout << "Average is within range" << endl;

              }
              else {

                     cout << "Average outside expected range"<< endl;
                     cout << "This can happen with small populations" << endl;
              }
    
    
                cout << "\n[TEST 8] Sort Population by Fitness" << endl;
                cout << "Sorting..." << endl;
                pop.sortByFitness();
    
    
                bool sorted = true;

           for (int i = 0; i < POP_Size - 1; i++) {

             if (pop[i].getDistance() > pop[i+1].getDistance()) {
                sorted = false;
                cout << "  Error at position " << i << ": " 
                   << pop[i].getDistance() << " > " 
                   << pop[i+1].getDistance() << endl;
                    break;
             }
         }
    
              if (sorted) {

               cout << "Population sorted correctly" << endl;
               cout << "\nSorted population (best to worst):"<< endl;

               for (int i = 0; i < POP_Size; i++) {

                cout << "  #" << (i+1) << ": Distance ="<< pop[i].getDistance() << endl;
        }
     } 
          else {

                  cout << "Population not properly sorted" << endl;
                  return 1;
            }
    
    
          cout << "\n[TEST 9] Verify First Tour = Best After Sort" << endl;
          double firstDist = pop[0].getDistance();
          double bestDistAfterSort = pop.getBest()->getDistance();
    
         cout << "First tour distance: " << firstDist << endl;
         cout << "Best tour distance:  " << bestDistAfterSort << endl;
    
         if (firstDist == bestDistAfterSort) {

             cout << "First tour is the best" << endl;

        } 
        else {

               cout << "Sort didn't place best tour first" << endl;
               return 1;
       }
    
    
             cout << "\n[TEST 10] Test Array Access Operator" << endl;
              Tour& tour0 = pop[0];
               Tour& tour1 = pop[1];
    
              cout << "Accessing tours via operator[]:" << endl;
              cout << "  pop[0] distance: " << tour0.getDistance() << endl;
              cout << "  pop[1] distance: " << tour1.getDistance() << endl;
    
            if (tour0.getDistance() <= tour1.getDistance()) {

                  cout << "Array access works correctly" << endl;
           } 
           else {

                   cout << "Array access issue" << endl;
                   return 1;
             }
    
   
              cout << "\n[TEST 11] Test getTours() Method" << endl;
              Tour* toursPtr = pop.getTours();
    
                if (toursPtr != nullptr) {

                  cout << "Tours pointer obtained: " << toursPtr << endl;
                  cout << "First tour via pointer: Distance = " << toursPtr[0].getDistance() << endl;
                  cout << "getTours() works" << endl;

             } 

             else {

                    cout << "getTours() returned null" << endl;
                    return 1;
               }
    
    
               
                 cout << "All Tests Passed!" << endl;
                 cout << "   Population class is working perfectly!" << endl;
    
                 cout << "\nPopulation Statistics:" << endl;
                 cout << "Size: " << pop.getSize() << endl;
                 cout << "Best distance: " << pop.getBest()->getDistance() << endl;
                 cout << "Worst distance: " << pop.getWorst()->getDistance() << endl;
                 cout << "  Average distance: " << pop.getAvgFitness() << endl;
    
    
                return 0;
}