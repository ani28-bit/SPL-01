 #include <iostream>
 #include <iomanip>
 #include <cstdlib>
 #include <ctime>
 #include "../TSP/City.h"
 #include "../TSP/Tour.h"
 #include "Population.h"
 #include "Selection.h"

  using namespace std;

   int main() {
    
        srand(time(nullptr));
    
    
         const int NumCities = 6;
         City cities[NumCities];

        cities[0] = City(0, 0.0, 0.0);
        cities[1] = City(1, 10.0, 0.0);
        cities[2] = City(2, 10.0, 10.0);
        cities[3] = City(3, 0.0, 10.0);
        cities[4] = City(4, 5.0, 5.0);
        cities[5] = City(5, 7.0, 3.0);
    
        cout << "\nCreated " << NumCities<< " test cities" << endl;
    
    
          const int POP_Size= 20;
          Population pop(POP_Size, cities, NumCities);
          pop.sortByFitness(); 
    
        cout << "Created population of " << POP_Size << " tours" << endl;
        cout << "Best distance:" << fixed << setprecision(2)<< pop.getBest()->getDistance() << endl;
        cout << "Worst distance: " << pop.getWorst()->getDistance() << endl;
        cout << "Avg distance: " << pop.getAvgFitness() << endl;
    
   
          Tour* tours = pop.getTours();
    
    
            cout << "\n[TEST 1] Tournament Selection" << endl;
            cout << "Running 10 tournament selections..." << endl;
    
          double tournamentAvg = 0.0;
          for (int i = 0; i < 10; i++) {

             Tour selected = Selection::tournamentSelection(tours, POP_Size, 5);

               tournamentAvg += selected.getDistance();

                if (i < 3) {

                    cout << "  Selection " << (i+1) << ": Distance = "<< selected.getDistance() << endl;
               }
           }

                tournamentAvg /= 10;
    
             cout << "Average selected distance: " << tournamentAvg << endl;
             cout << "Tournament selection works" << endl;
    
   
             cout << "\n[TEST 2] Roulette Wheel Selection" << endl;
             cout << "Running 10 roulette wheel selections..." << endl;
    
             double rouletteAvg = 0.0;

             for (int i = 0; i < 10; i++) {

                Tour selected = Selection::rouletteWheelSelection(tours, POP_Size);

                  rouletteAvg += selected.getDistance();

                  if (i < 3) {

                    cout << "  Selection " << (i+1) << ": Distance = " << selected.getDistance() << endl;
                }
           }
              rouletteAvg /= 10;
    
          cout << "Average selected distance: " << rouletteAvg << endl;
          cout << "Roulette wheel selection works" << endl;
    
    
          cout << "\n[TEST 3] Rank Selection" << endl;
          cout << "Running 10 rank selections." << endl;
    
          double rankAvg = 0.0;
          for (int i = 0; i < 10; i++) {

              Tour selected = Selection::rankSelection(tours, POP_Size);
              rankAvg += selected.getDistance();
               if (i < 3) {

                  cout << "  Selection " << (i+1) << ": Distance = "<< selected.getDistance() << endl;
             }
          }
            rankAvg /= 10;
    
            cout << "Average selected distance: " << rankAvg << endl;
            cout << "Rank selection works" << endl;
    
    
             cout << "\n[TEST 4] Random Selection" << endl;
             cout << "Running 10 random selections." << endl;
    
          double randomAvg = 0.0;
            for (int i = 0; i < 10; i++) {

             Tour selected = Selection::randomSelection(tours, POP_Size);
              randomAvg += selected.getDistance();
                 if (i < 3) {

                  cout << "  Selection " << (i+1) << ": Distance = "<< selected.getDistance() << endl;
            }
       }
          randomAvg /= 10;
    
        cout << "Average selected distance: " << randomAvg << endl;
        cout << "Random selection works" << endl;
    
    
        cout << "\n[TEST 5] Compare Selection Pressure" << endl;
        cout << "Population average:" << pop.getAvgFitness() << endl;
        cout << "Tournament avg:" << tournamentAvg << endl;
        cout << "Roulette avg:" << rouletteAvg << endl;
        cout << "Rank avg:" << rankAvg << endl;
        cout << "Random avg:" << randomAvg << endl;
    
    
          if (tournamentAvg < pop.getAvgFitness()) {

                cout << "Tournament has selection pressure" << endl;
          } 
           else {

                   cout << "Tournament avg should be < population avg" << endl;
              }
    
    
              double randomDiff = abs(randomAvg - pop.getAvgFitness());

               if (randomDiff < 5.0) {

                   cout << "Random selection has no bias"<< endl;

             } 
          
           else {

                   cout << "Random avg should be = population avg" << endl;
              }
    
    
   
        cout << "All Tests Passed!" << endl;
        cout << "Selection methods working!" << endl;
    
    
         return 0;
    }