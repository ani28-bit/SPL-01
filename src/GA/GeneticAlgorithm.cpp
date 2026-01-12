#include "GeneticAlgorithm.h"
#include "Selection.h"
#include "Crossover.h"
#include "Mutation.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cfloat>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(City cities[], int numCities,int popSize, int gens,
                               double crossRate, double mutRate,int elitism, int tournSize){



                   this->cities = cities;
                   this->numCities = numCities;
                   this->populationSize = popSize;
                   this->generations = gens;
                   this->crossoverRate = crossRate;
                   this->mutationRate = mutRate;
                   this->elitismCount = elitism;
                   this->tournamentSize = tournSize;

                     bestDistance = DBL_MAX;
                     srand(time(NULL));
      }



               void GeneticAlgorithm::run(){


               cout << "GA TSP Solver Started."<< endl;

               Population* population = new Population(populationSize, cities, numCities);

               population->sortByFitness();

               bestTour = *(population->getBest());
               bestDistance = bestTour.getDistance();

               for (int gen = 0; gen < generations; gen++){

                 Population* newPopulation = evolvePopulation(population);

                  delete population;
                  population = newPopulation;

               Tour* currentBest = population->getBest();
               double dist = currentBest->getDistance();

               if (dist < bestDistance){

                 bestDistance = dist;
                 bestTour = *currentBest;
             }

               if (gen % 50 == 0){

                    cout << "Gen "<< gen<< " Best: "<< bestDistance << std::endl;
            }
         }

                  delete population;
      }



         Population* GeneticAlgorithm::evolvePopulation(Population* pop){

             pop->sortByFitness();

             Tour* newTours = new Tour[populationSize];

             for (int i = 0; i < elitismCount; i++){

                   newTours[i] = (*pop)[i];

             }


         for (int i = elitismCount; i < populationSize; i++){

            newTours[i] = createOffspring(pop);

         }

           Population* newPop =new Population(populationSize, cities, numCities);
 
          for (int i = 0; i < populationSize; i++) {

           City* temp = new City[numCities];

           for (int j = 0; j < numCities; j++){

            temp[j] = newTours[i].getCity(j);

         }
            

          (*newPop)[i].setCities(temp, numCities);
           delete[] temp;
      }

           delete[] newTours;
           return newPop;
   }



   Tour GeneticAlgorithm::createOffspring(Population* pop){

      Tour* tours = pop->getTours();

       Tour p1 = Selection::tournamentSelection(tours, pop->getSize(), tournamentSize);

       Tour p2 = Selection::tournamentSelection (tours, pop->getSize(), tournamentSize);

        Tour child;

        double r = (double)rand() / RAND_MAX;

        if (r < crossoverRate){

                child = Crossover::orderCrossover(p1, p2);
       }

       else {

                child = p1;

                Mutation::applyMutation(child, mutationRate);
                
          }

          return child;
       }   



            Tour GeneticAlgorithm::getBestTour() const{
            return bestTour;

          }

             double GeneticAlgorithm::getBestDistance() const{
              return bestDistance;
         }

           void GeneticAlgorithm::printResults() const{

           cout << "Best Distance: "<< bestDistance<< endl;

           bestTour.printTour();
}