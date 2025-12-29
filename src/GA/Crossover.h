#ifndef CROSSOVER_h
#define CROSSOVER_h
#include "../TSP/Tour.h"

 class Crossover{
      public : 
        
      static Tour orderCrossover(const Tour& parent1,const Tour& parent2);

      static Tour pmxCrossover(const Tour& parent1,const Tour& parent2);
     
   
      static Tour cycleCrossover(const Tour& parent1, const Tour& parent2);
    
    
      static Tour edgeCrossover(const Tour& parent1, const Tour& parent2);

 private:
   
    static bool containsCity(const City* cities, int size, int cityId);
    
    
    static int findCityPosition(const Tour& tour, int cityId);
};

#endif

