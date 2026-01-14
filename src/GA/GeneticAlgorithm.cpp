#include "GeneticAlgorithm.h"
#include "Selection.h"
#include "Crossover.h"
#include "Mutation.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cfloat>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(City cities[], int numCities,int popSize,
                                                  int gens,double crossRate,
                                                  double mutRate,int elitism, int tournSize){


                      this->cities = cities;
                      this->numCities = numCities;
                      this->populationSize = popSize;
                      this->generations = gens;
                      this->crossoverRate = crossRate;
                      this->mutationRate = mutRate;
                      this->elitismCount = elitism;
                      this->tournamentSize = tournSize;

                       bestDistance = DBL_MAX;
                       srand(time(0));

       }

        void GeneticAlgorithm::run(){

            cout << "GA TSP Solver Started."<<endl;

             Population* population = new Population(populationSize, cities, numCities);
              population->sortByFitness();

               cout << "Initial Population:"<<endl;

                 for (int i = 0; i < populationSize; i++){

                        cout << "Tour " << i << ": ";
                         (*population)[i].printTour();

                        cout << "Distance: "<< fixed << setprecision(2)  << (*population)[i].getDistance() << endl;


                 }

                       bestTour = *(population->getBest());
                       bestDistance = bestTour.getDistance();

                        clock_t startTime = clock();

                        for (int gen = 0; gen < generations; gen++){
       
                             int orderCount = 0, pmxCount = 0, cycleCount = 0;
                             int noMut = 0, swapMut = 0, scrambleMut = 0, insertMut = 0;

                              Tour* newTours = new Tour[populationSize];

        
                               for (int i = 0; i < elitismCount; i++){

                                  newTours[i] = (*population)[i];

                               }

                                    for (int i = elitismCount; i < populationSize; i++){

                                          string crossUsed, mutUsed;
                                           newTours[i] = createOffspring(population, crossUsed, mutUsed);

            
                                       if (crossUsed == "Order"){

                                                  orderCount ++;
                                          } 

                                      else if (crossUsed == "PMX"){

                                                   pmxCount++;

                                         }
                                      else if (crossUsed == "Cycle"){

                                         cycleCount++;

                                      }

           
                                      if (mutUsed == "No Mutation"){

                                               noMut++;

                                      }
                                      else if (mutUsed == "Swap"){

                                               swapMut++;

                                      }
                                      else if (mutUsed == "Scramble") {

                                               scrambleMut++;
                   
                                      }
                                      else if (mutUsed == "Insertion") {

                                                insertMut++;
                                      }
                                    
                                
                     }

                         Population* newPopulation =  new Population(populationSize, cities, numCities);

                         for (int i = 0; i < populationSize; i++) {

                             City* temp = new City[numCities];

                              for (int j = 0; j < numCities; j++){

                               temp[j] = newTours[i].getCity(j);

                         }

                               (*newPopulation)[i].setCities(temp, numCities);
                                  delete[] temp;

                 }

                        delete[] newTours;
                        delete population;
                        population = newPopulation;
                        population->sortByFitness();

                        Tour* currentBest = population->getBest();
                        if (currentBest->getDistance() < bestDistance){

                               bestDistance = currentBest->getDistance();
                                bestTour = *currentBest;
                  }

                     if (gen % 50 == 0 || gen == generations - 1) {

                          cout << "\nGeneration " << gen << " Summary\n";
                           cout << "Order  : " << orderCount << endl;
                            cout << "PMX    : " << pmxCount << endl;
                              cout << "Cycle  : " << cycleCount << endl;

                               cout << "No Mutation : " << noMut << endl;
                                cout << "Swap       : " << swapMut << endl;
                                 cout << "Scramble  : " << scrambleMut << endl;
                                  cout << "Insertion  : " << insertMut << endl;

                                   cout << "Best Distance: " << fixed << setprecision(2) << bestDistance << endl;

                         }
                      }

                           clock_t endTime = clock();
                           double elapsedSeconds =  double(endTime - startTime) / CLOCKS_PER_SEC;

                             cout << "\nFinal Best Tour: ";
                               bestTour.printTour();
                                cout << "Distance: " << bestDistance << endl;

                                cout << "Execution Time: " << elapsedSeconds << " seconds\n";

                                 delete population;

                 }



                 Tour GeneticAlgorithm::createOffspring(Population* pop,string& crossoverUsed, string& mutationUsed){

                           Tour* tours = pop->getTours();

                            Tour p1 = Selection::tournamentSelection(tours, pop->getSize(), tournamentSize);
                            Tour p2 =Selection::tournamentSelection(tours, pop->getSize(), tournamentSize);

                             Tour child;
                              int type = rand() % 3;

                               if (type == 0){

                                    child = Crossover::orderCrossover(p1, p2);
                                    crossoverUsed = "Order";

                                }

                                else if (type == 1) {

                                    child = Crossover::pmxCrossover(p1, p2);
                                    crossoverUsed = "PMX";

                             }
                               
                                else{

                                       child = Crossover::cycleCrossover(p1, p2);
                                       crossoverUsed = "Cycle";

                         }

                               Mutation::applyMutation(child, mutationRate, mutationUsed);
                               return child;
                     }



                       Tour GeneticAlgorithm::getBestTour() const{

                                    return bestTour;
                            }

                        double GeneticAlgorithm::getBestDistance() const{

                                    return bestDistance;

            }
