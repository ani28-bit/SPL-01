#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>         
#include "TSP/City.h"
#include "GA/GeneticAlgorithm.h"
#include "CPLEX/CplexSolver.h"      
#include "CPLEX/Comparison.h"      
#include "Utils/Timer.h"

using namespace std;

#define MAX_CITIES 100

bool loadCitiesFromFile(const string& filename, City cities[], int &numCities) {

    ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    double x, y;
    string line;
    numCities = 0;

    while (getline(file, line)) {
        istringstream iss(line);

        if (!(iss >> x >> y)) {
            continue;
        }
        cities[numCities] = City(numCities, x, y);
        numCities++;

        if (numCities >= MAX_CITIES) {
               break;
        }
    }

        file.close();
        return numCities > 0;
  }

  void createCircularCities(City cities[], int &numCities, int totalCities) {

    double radius = 50.0;
    double centerX = 50.0;
    double centerY = 50.0;

    numCities = totalCities;

    for (int i = 0; i < numCities; ++i) {

        double angle = 2.0 * M_PI * i / numCities;
        double x = centerX + radius * cos(angle);
        double y = centerY + radius * sin(angle);
        cities[i] = City(i, x, y);
    }
 }

 int main(int argc, char* argv[]) {

    srand(time(0));

    string filename = "cities.txt"; 
    City cities[MAX_CITIES];
    int numCities = 0;

    
    bool useCplex = false;
    if (argc > 1 && strcmp(argv[1], "--cplex") == 0) {

             useCplex = true;
     }

    
    if (!loadCitiesFromFile(filename, cities, numCities)) {

                int defaultCities = 10;
                cout << "File not found. Generating " << defaultCities << " circular cities.\n";
                createCircularCities(cities, numCities, defaultCities);
    } 
    else {
                cout << "Loaded " << numCities << " cities from " << filename << endl;
    }

    
    int populationSize = 100;
    int generations = 500;
    double crossoverRate = 0.8;
    double mutationRate = 0.05;
    int elitism = 1;
    int tournamentSize = 5;

   
      cout << endl;
      cout << " Running Genetic Algorithm" << endl;
      cout << endl;

     GeneticAlgorithm ga(cities, numCities, populationSize,
                        generations, crossoverRate, mutationRate,
                        elitism, tournamentSize);

           Timer gaTimer;
           gaTimer.start();

            ga.run();  
  
            gaTimer.stop();

            Tour gaBestTour = ga.getBestTour();
             double gaDistance = ga.getBestDistance();
              double gaTime = gaTimer.getElapsedSeconds();

                  cout << "\nGA completed." << endl;
                  cout << "Best Distance: " << gaDistance << endl;
                  cout << "Execution Time: " << gaTime << " seconds." << endl;
                  cout << "To save GA output as CSV: ./tsp_solver > results/ga_results.csv\n";

          if (useCplex) {

                 cout << endl;
                 cout << "Running CPLEX Solver" << endl;
                 cout << endl;

             if (CplexSolver::isCplexAvailable()) {

                     CplexSolver cplexSolver(cities, numCities);
                     int* cplexTour = new int[numCities];

                     Timer cplexTimer;
                     cplexTimer.start();

                 double cplexDistance = cplexSolver.solve(cplexTour, 300.0);

                 cplexTimer.stop();
                 double cplexTime = cplexTimer.getElapsedSeconds();

                 cout << "CPLEX Distance: " << cplexDistance << endl;
                 cout << "CPLEX Execution Time: " << cplexTime << " seconds." << endl;

          
                 Comparison::compareResults(gaBestTour, gaDistance,
                                             cplexTour, cplexDistance, numCities);

           
                 Comparison::saveComparison(gaBestTour, gaDistance,
                                            cplexTour, cplexDistance, numCities,
                                            gaTime, cplexTime);

                          delete[] cplexTour;
                 } 
                 else {

                         cout << "\nCPLEX is not available. Skipping comparison." << endl;
                        

        }
     } 

     else {

               cout << "\nTo compare with CPLEX, run:" << endl;
               cout << "  ./tsp_solver --cplex" << endl;
       }

               return 0;
   }
