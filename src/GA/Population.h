#ifndef POPULATION_H
#define POPULATION_H

#include "../TSP/Tour.h"

  class Population {

      private:

         Tour* tours;
          int size;

      public:
    
          Population(int popSize, City cities[], int numCities);
    
    
          ~Population();
    
    
           Tour* getBest();
            Tour* getWorst();
             double getAvgFitness() const;
               void sortByFitness();
    
   
            int getSize() const {

                    return size;

            }
    
    
          Tour& operator[](int idx) {


                   return tours[idx];

         }
    
           const Tour& operator[](int idx) const {

                   return tours[idx];

          }

          Tour* getTours(){

                 return tours;
          }
    
   
           Population(const Population&) = delete;

           Population& operator=(const Population&) = delete;

     };

     #endif 