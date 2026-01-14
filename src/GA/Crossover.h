 #ifndef CROSSOVER_H
 #define CROSSOVER_H
 #include "../TSP/Tour.h"
 #include<string>

 class Crossover{
     
      public : 
        
      static Tour orderCrossover(const Tour& parent1,const Tour& parent2);

      static Tour pmxCrossover(const Tour& parent1,const Tour& parent2);
     
   
      static Tour cycleCrossover(const Tour& parent1, const Tour& parent2);

      static Tour randomCrossover(const Tour& parent1,
                                   const Tour& parent2,
                                    std::string& crossoverName);
      

  private:
   
       static bool containsCity(const City* cities, int size, int cityId);
    
    
       static int findCityPosition(const Tour& tour, int cityId);

   };

   #endif

