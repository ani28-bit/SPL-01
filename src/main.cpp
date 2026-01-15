 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <cmath>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 #include "TSP/City.h"
 #include "GA/GeneticAlgorithm.h"
 #include "Utils/Timer.h"

  using namespace std;

  #define  MAX_CITIES  100

    bool loadCitiesFromFile(const string& filename, City cities[],int &numCities) {

           ifstream file(filename);
         
           if (!file.is_open()){

                return false;
           }


               double x, y;
                string line;
                 int id = 0;

                while (getline(file, line)) {

                      istringstream iss(line);

                      if (!(iss >> x >> y)) {

                        continue;

                      }

                            cities[numCities] = City(numCities, x, y);
                              numCities++;


                  }

                           file.close();
                           return  numCities > 0;

            }

                           void createCircularCities(City cities[], int &numCities,int totalCities) {
                              double radius = 50.0;
                               double centerX = 50.0;
                                double centerY = 50.0;

                                    numCities = totalCities;

                                 for (int i = 0; i < numCities; ++i) {

                                        double angle = 2.0 * M_PI * i / numCities;
                                         double x = centerX + radius * cos(angle);
                                          double y = centerY + radius * sin(angle);
                                           cities[i]= City(i,x,y);


                                    }

                               }

                                  int main() {

                                        srand(time(0));
                                        string filename = "cities.txt"; 
                                         City cities[MAX_CITIES];
                                         int numCities = 0; 
    
                                         if (!loadCitiesFromFile(filename, cities,numCities)) {

                                                    int defaultCities = 10;
                                                    cout << "File not found. Generating " << defaultCities << " circular cities.\n";
                                                    createCircularCities(cities, numCities,defaultCities);

                                                } 
                                                
                                                else {


                                                           
                                                           cout << "Loaded " << numCities << " cities from " << filename <<endl;

                                                 }

                                                   int populationSize = 100;
                                                    int generations = 500;
                                                     double crossoverRate = 0.8;
                                                      double mutationRate = 0.05;
                                                       int elitism = 1;
                                                        int tournamentSize = 5;

                                         GeneticAlgorithm ga(cities, numCities, populationSize,
                                                              generations, crossoverRate, mutationRate,
                                                               elitism, tournamentSize);

                                                     Timer timer;
                                                     timer.start();

                                            cout << "\n  GA  Output : \n";
                                              ga.run();  
                                              timer.stop();

                                            cout << "\nExecution Time: " << timer.getElapsedSeconds() << " seconds."<<endl;
                                            cout << "GA completed. To save output as CSV, run:"<<endl;
                                            cout << "./tsp_solver > results/ga_results.csv"<<endl;

                                          return 0;



                    }