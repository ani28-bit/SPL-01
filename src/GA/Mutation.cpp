 #include "Mutation.h"
 #include <iostream>
 #include <cstdlib>
 #include <algorithm>


 void Mutation::swapMutation(Tour& tour) {

     int size = tour.getCityCount();
    
     if (size < 2){
          
         return;
     } 
    
   
     int pos1 = rand() % size;
     int pos2 = rand() % size;
    
    
     while (pos1 == pos2) {

        pos2 = rand() % size;
     }
   
        tour.swapCities(pos1, pos2);
  }


    void Mutation::inversionMutation(Tour& tour) {

       int size = tour.getCityCount();
    
         if (size < 2){

          return;

         } 
    
    
           int start = rand() % size;
           int end = rand() % size;
    
           if (start > end) {

              std::swap(start, end);
        }
    
    
            if (end - start < 1) {

                end = (start + 1) % size;
         }
    
    
            while (start < end) {

              tour.swapCities(start, end);
              start++;
              end--;
         }
    }


         void Mutation::insertionMutation(Tour& tour) {

               int size = tour.getCityCount();
    
               if (size < 2){

                 return;
               } 
    
   
              int fromPos = rand() % size;
              int toPos = rand() % size;
    
              while (fromPos == toPos) {

                    toPos = rand() % size;
           }
    
   
              City cityToMove = tour.getCity(fromPos);
    
  
               if (fromPos < toPos) {

                 for (int i = fromPos; i < toPos; i++) {

                      City temp = tour.getCity(i + 1);
                      tour.getCity(i) = temp;
                }
            } 
            else {

                     for (int i = fromPos; i > toPos; i--) {

                        City temp = tour.getCity(i - 1);
                        tour.getCity(i) = temp;
                   }
                }
    
    
                  tour.getCity(toPos) = cityToMove;
                  tour.updateDistance();
           }


            void Mutation::scrambleMutation(Tour& tour) {

               int size = tour.getCityCount();
    
               if (size < 2){

                   return;
              } 
    
   
              int start = rand() % size;
              int end = rand() % size;
    
              if (start > end) {

                  std::swap(start, end);
              }
    
    
             if (end - start < 1) {

                  end = (start + 1) % size;
              }
    
    
              for (int i = end; i > start; i--) {

                   int j = start + rand() % (i - start + 1);

                   tour.swapCities(i, j);
             }
         }


             void Mutation::applyMutation(Tour& tour,
                             double mutationRate,
                             std::string& mutationName) {

              double random = (double)rand() / RAND_MAX;

              if (random < mutationRate) {

                      int mutationType = rand() % 4;

         switch (mutationType) {

            case 0:
                mutationName = "Swap Mutation";
                swapMutation(tour);
                break;

            case 1:
                mutationName = "Inversion Mutation";
                inversionMutation(tour);
                break;

            case 2:
                mutationName = "Insertion Mutation";
                insertionMutation(tour);
                break;

            case 3:
                mutationName = "Scramble Mutation";
                scrambleMutation(tour);
                break;
        }
    }

          else {

                 mutationName = "No Mutation";
      }
  }
