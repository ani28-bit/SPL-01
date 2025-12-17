#ifndef POPULATION_H
#define POPULATION_H

#include "src/TSP/Tour.h"

class Population {
private:
    Tour* tours;
    int size;

 public:
    
     Population(int popSize, City cities[], int numCities);
    
    
      ~Population();
    
    
      Tour* getBest();
    
   
      int getSize() const {

              return size;
         }
    
    
    Tour& operator[](int idx) {


              return tours[idx];

    }
    
    const Tour& operator[](int idx) const {

              return tours[idx];

    }
    
   
     Population(const Population&) = delete;

     Population& operator=(const Population&) = delete;
  };

  #endif 