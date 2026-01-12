#include "Selection.h"
#include<iostream>
#include <cstdlib>



Tour Selection::tournamentSelection(Tour population[],int populationSize,int tournamentSize){

         if(tournamentSize > populationSize){

               tournamentSize = populationSize;
         }



         Tour best = population[rand() % populationSize];
         double bestDistance = best.getDistance();


         for(int i=1; i < tournamentSize; i++){

                 int randomIndex = rand()% populationSize;
                 Tour candidate = population[randomIndex];
                
                 double candidateDistance = candidate.getDistance();
                    if(candidateDistance < bestDistance){

                             best = candidate;
                             bestDistance = candidateDistance;
                    }
            }
            return best;
     }

     Tour Selection::rouletteWheelSelection(Tour population[], int populationSize) {
    
             double totalFitness = 0.0;
             double* fitness = new double[populationSize];
    
            for (int i = 0; i < populationSize; i++) {

                   double distance = population[i].getDistance();

                   fitness[i] = 1.0 / (1.0 + distance); 

                   totalFitness += fitness[i];
              }
    
    
             double randomValue = ((double)rand() / RAND_MAX) * totalFitness;
    
    
               double cumulativeFitness = 0.0;
               Tour selected = population[0]; 
    
             for (int i = 0; i < populationSize; i++) {

                   cumulativeFitness += fitness[i];

                   if (cumulativeFitness >= randomValue) {

                         selected = population[i];
                         break;
                  }
             }
    
                 delete[] fitness;
                 return selected;
         }



         Tour Selection::rankSelection(Tour population[], int populationSize) {
    
                 int totalRank = (populationSize * (populationSize + 1)) / 2;
    
    
                 int randomValue = rand() % totalRank;
                 int cumulativeRank = 0;

              for (int i = 0; i < populationSize; i++) {
       
                     int rank = populationSize - i;
                     cumulativeRank += rank;
        
                if (cumulativeRank >= randomValue) {

                    return population[i];
               }
            }
    
   
                    return population[0];
          }


            Tour Selection::randomSelection(Tour population[], int populationSize) {

                  int randomIndex = rand() % populationSize;
                  return population[randomIndex];

         }