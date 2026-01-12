#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "TSP/City.h"
#include "GA/GeneticAlgorithm.h"
#include "Utils/Timer.h"

using namespace std;


void createTestCities(City cities[], int numCities) {
    double radius = 50.0;
    double centerX = 50.0;
    double centerY = 50.0;
    
    for (int i = 0; i < numCities; i++) {

        double angle = (2.0 * 3.14159265359 * i) / numCities;
        double x = centerX + radius * cos(angle);
        double y = centerY + radius * sin(angle);
        cities[i] = City(i, x, y);
    }
}


 bool loadCitiesFromFile(const char* filename, City*& cities, int& numCities) {

      ifstream file(filename);
      if (!file.is_open()) {

        cerr << "Error: Cannot open file " << filename << endl;

        return false;
    }
    
   
      file >> numCities;
    
    if (numCities <= 0 || numCities > 1000) {

        cout << "Error: Invalid number of cities: " << numCities << endl;
        return false;
    }
    
    cities = new City[numCities];
    
    
    for (int i = 0; i < numCities; i++) {
        int id;
        double x, y;
        file >> id >> x >> y;
        cities[i] = City(id, x, y);
    }
    
        file.close();
        return true;
  }

  int main(int argc, char* argv[]) {

     
      cout << "  TSP GENETIC ALGORITHM SOLVER" << endl;
      cout<<endl;
    
    
         City* cities = nullptr;
         int numCities = 0;
         bool useFile = false;
    
   
        if (argc > 1) {

           cout << "\nLoading cities from file: " << argv[1] << endl;
           useFile = loadCitiesFromFile(argv[1], cities, numCities);
        
           if (!useFile) {

              cout << "Failed to load from file. Using default test cities." << endl;
           }
        }
    
    
       if (!useFile) {

            numCities = 10;

            cities = new City[numCities];
            createTestCities(cities, numCities);
            cout << "\nUsing " << numCities << " test cities" << endl;

      }
    
   
            cout << "\nCity coordinates:" << endl;

            int displayLimit = (numCities > 10) ? 10 : numCities;

            for (int i = 0; i < displayLimit; i++) {

             cout << "  City " << cities[i].getId()<< ": (" << fixed << setprecision(2) << cities[i].getX() << ", " 
             << cities[i].getY() << ")" << endl;

      }

         if (numCities > 10) {

                cout << "  ... (" << (numCities - 10) << " more cities)" << endl;
         }
       
   
             int populationSize = 100;
             int generations = 500;
             double crossoverRate = 0.8;
             double mutationRate = 0.02;
             int elitismCount = 2;
             int tournamentSize = 5;
    
    
           if (numCities > 20) {

               populationSize = 200;
               generations = 1000;

               cout << "\n[Auto-adjusted parameters for larger problem]" << endl;
          }

           if (numCities > 50) {

              populationSize = 300;
              generations = 2000;
              mutationRate = 0.01;

              cout << "\n[Auto-adjusted parameters for very large problem]" << endl;

           }
    
   
           cout << "  Configuration" << endl;
   
           cout << "Problem size: " << numCities << " cities" << endl;
           cout << "Population: " << populationSize << endl;
           cout << "Generations: " << generations << endl;
           cout << "Crossover rate: " << (crossoverRate * 100) << "%" << endl;
           cout << "Mutation rate: " << (mutationRate * 100) << "%" << endl;
           cout << "Elitism: " << elitismCount << " best tours preserved" << endl;
           cout << "Tournament size: " << tournamentSize << endl;
    
    
           Timer timer;
           timer.start();
    
    
    
          cout << "  Starting Genetic Algorithm." << endl;
          cout<<endl;
   
    
         GeneticAlgorithm ga(cities, numCities, populationSize,generations,crossoverRate,mutationRate,elitismCount,tournamentSize);
    
   
            ga.run();
            timer.stop();
            ga.printResults();
    
    
   
            cout << "  Performance Statistics :" << endl;
            cout<<endl;
    
            cout << "Total execution time: " << fixed << setprecision(3) << timer.getElapsedSeconds() << " seconds" << endl;
            cout << " (" << fixed << setprecision(1) << timer.getElapsedMilliseconds() << " ms)" << endl;
    
               double timePerGeneration = timer.getElapsedSeconds() / generations;
               cout << "Time per generation:  " << fixed << setprecision(4)<< timePerGeneration << " seconds" << endl;
    
   
               cout << "  Solver completed successfully!" << endl;
    
    
   
              cout << "\nUsage:" << endl;
              cout << "  ./tsp_solver              - Run with default 10 test cities" << endl;
              cout << "  ./tsp_solver cities.txt   - Run with custom city file" << endl;
              cout << "\nCity file format:" << endl;
              cout << "  Line 1: <number_of_cities>" << endl;
              cout << "  Line 2+: <city_id> <x_coordinate> <y_coordinate>" << endl;
    
    
              delete[] cities;
    
              return 0;

     }