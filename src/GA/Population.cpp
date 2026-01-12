  #include "Population.h"
  #include <iostream>
  #include <cstdlib>
 


 Population::Population(int popSize, City cities[], int numCities){

             size = popSize;
             tours = new Tour[size];
    
    
    
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

  Tour* Population::getWorst(){
      if(size == 0){
         return nullptr;
      }

      Tour* worst = &tours[0];
       double worstDistance = tours[0].getDistance();

       for(int i=1;i<size;++i){
          double dist = tours[i].getDistance();

          if(dist > worstDistance){
              worstDistance = dist;
              worst = &tours[i];
          }
       }
       return worst;
  }

     double Population::getAvgFitness() const{
          if(size == 0){

            return 0.0;
          }

          double sum = 0.0;

          for(int i=0;i<size;++i){

              sum+= tours[i].getDistance();
          }

          return sum/size;
     }

        void Population:: sortByFitness(){
             
         for(int i=0;i<size-1;++i){
              for(int j=0;j<size-i-1;++j){
                   if(tours[j].getDistance() > tours[j+1].getDistance()){
                           Tour temp = tours[j];
                            tours[j] = tours[j+1];
                            tours[j+1] = temp; 

                   }
              }
         }
     }
 


 