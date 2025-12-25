 #include "Population.h"
 #include <cstdlib>
 


 Population::Population(int popSize, City cities[], int numCities){

             size = popSize;
             tours = new Tour[size];
    
    
          /* static bool seeded = false;

           if (!seeded) {

           srand(static_cast<unsigned>(time(nullptr)));
             seeded = true;
        }*/
    
    
          for (int i = 0; i < size; ++i) {

                   tours[i] = Tour();
                   tours[i].setCities(cities, numCities);
        
        
           for (int j = numCities - 1; j > 0; --j) {

                    int k = rand() % (j + 1);
                    tours[i].swapCities(j, k);
         }
      }
  }


      Population::~Population(){

             delete[] tours;
     }


      Tour* Population::getBest(){

         if (size == 0){
            
            return nullptr;

         }
    
      Tour* best = &tours[0];

      double bestDistance = tours[0].getDistance();
    
       for (int i = 1; i < size; ++i) {

          double dist = tours[i].getDistance();

        if (dist < bestDistance) {

              bestDistance = dist;
              best = &tours[i];
        }
    }
    
     return best;
 }