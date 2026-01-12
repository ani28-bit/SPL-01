  #include <iostream>
  #include <iomanip>
  #include <cstdlib>
  #include <ctime>
  #include "../TSP/City.h"
  #include "../TSP/Tour.h"
  #include "Crossover.h"

   using namespace std;

   int main() {
    
           srand(time(nullptr));
    
    
             const int Num_Cities = 8;
              City cities[Num_Cities];

               cities[0] = City(0, 0.0, 0.0);
                cities[1] = City(1, 10.0, 0.0);
                 cities[2] = City(2, 10.0, 10.0);
                   cities[3] = City(3, 0.0, 10.0);
                    cities[4] = City(4, 5.0, 5.0);
                      cities[5] = City(5, 7.0, 3.0);
                       cities[6] = City(6, 3.0, 7.0);
                         cities[7] = City(7, 8.0, 8.0);
    
              cout << "\nCreated " << Num_Cities<< " test cities" << endl;
    
   
                Tour parent1, parent2;
                 parent1.setCities(cities, Num_Cities);
                  parent2.setCities(cities, Num_Cities);
    
    
                 for (int i = Num_Cities - 1; i > 0; i--) {

                  parent1.swapCities(i, rand() % (i + 1));
                  parent2.swapCities(i, rand() % (i + 1));
             }
    
               cout << fixed << setprecision(2);
    
               cout << "\nParent 1: ";
               parent1.printTour();
    
               cout << "Parent 2: ";
               parent2.printTour();
    
    
               cout << "\n[TEST 1] Order Crossover (OX)" << endl;

               Tour child1 = Crossover::orderCrossover(parent1, parent2);
    
               cout << "Child: ";
               child1.printTour();
    
              if (child1.isValid()) {

                cout << "OX child is valid" << endl;
            } 

          else {

                  cout << "OX child is invalid" << endl;
                  return 1;
            }
    
    
                  cout << "\n[TEST 2] Partially Mapped Crossover (PMX)" << endl;

                  Tour child2 = Crossover::pmxCrossover(parent1, parent2);
    
                   cout << "Child: ";
                   child2.printTour();
    
                 if (child2.isValid()) {

                       cout << "PMX child is valid" << endl;
               } 
               else {

                      cout << "PMX child is invalid" << endl;
                      return 1;
              }
    
    
               cout << "\n[TEST 3] Cycle Crossover (CX)" << endl;
               Tour child3 = Crossover::cycleCrossover(parent1, parent2);
    
                 cout << "Child:";
                 child3.printTour();
    
                if (child3.isValid()) {

                    cout << "CX child is valid" << endl;
            }
            else {

                   cout << "CX child is invalid" << endl;
                   return 1;
             }
    
    
             cout << "\n[TEST 4] Multiple OX Crossovers" << endl;
             int validCount = 0;
    
              for (int i = 0; i < 10; i++) {

                  Tour child = Crossover::orderCrossover(parent1, parent2);

                  if (child.isValid()) {

                     validCount++;
             }
         }
    
               cout << "Valid children: " << validCount << "/10" << endl;
    
              if (validCount == 10) {

                     cout << "All OX children valid" << endl;
           } 
            else {

                    cout << " Some children invalid" << endl;
                    return 1;
              }
    
   
                cout << "\n[TEST 5] Compare Parent and Child Distances" << endl;

                cout << "Parent 1 distance: " << parent1.getDistance() << endl;
                cout << "Parent 2 distance: " << parent2.getDistance() << endl;
                cout << "Child 1 distance:  " << child1.getDistance() << endl;
                cout << "Child 2 distance:  " << child2.getDistance() << endl;
                cout << "Child 3 distance:  " << child3.getDistance() << endl;
    
                 double avgParent = (parent1.getDistance() + parent2.getDistance()) / 2;
                 cout << "\nAverage parent distance: " << avgParent << endl;
    
   
                 cout << "Distance comparison done" << endl;
    
    
                  cout << "All Tests Passed!" << endl;
                  cout << "Crossover methods working!" << endl;
   
    
                   return 0;

           }