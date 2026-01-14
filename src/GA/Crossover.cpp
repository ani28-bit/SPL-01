  #include "Crossover.h"
  #include <iostream>
  #include <string>
  #include <cstdlib>
  #include <algorithm>


     bool Crossover::containsCity(const City* cities, int size, int cityId) {

         for (int i = 0; i < size; i++) {

             if (cities[i].getId() == cityId) {

                 return true;
           }
       }
          return false;
    }


      int Crossover::findCityPosition(const Tour& tour, int cityId) {

           int size = tour.getCityCount();

           for (int i = 0; i < size; i++) {

              if (tour.getCity(i).getId() == cityId) {

                return i;
            }
         }
             return -1;
     }


       Tour Crossover::orderCrossover(const Tour& parent1, const Tour& parent2) {
        int size = parent1.getCityCount();
         Tour child;
    
    
          City* childCities = new City[size];
           bool* used = new bool[size];
    
    
            for (int i = 0; i < size; i++) {
             used[i] = false;
          }
    
   
           int start = rand() % size;
           int end = rand() % size;
    
           if (start > end) {

               std::swap(start, end);
       }
    
  
           for (int i = start; i <= end; i++) {

              childCities[i] = parent1.getCity(i);

              used[parent1.getCity(i).getId()] = true;
          }
    
    
             int currentPos = (end + 1) % size;
             int parent2Pos = (end + 1) % size;
    
         while (currentPos != start) {

         City city = parent2.getCity(parent2Pos);
        
         if (!used[city.getId()]) {

               childCities[currentPos] = city;
               used[city.getId()] = true;
               currentPos = (currentPos + 1) % size;
         }
        
               parent2Pos = (parent2Pos + 1) % size;
      }
    
    
              child.setCities(childCities, size);
    
              delete[] childCities;
              delete[] used;
    
              return child;
       }


           Tour Crossover::pmxCrossover(const Tour& parent1, const Tour& parent2) {
           int size = parent1.getCityCount();
           Tour child;
    
             City* childCities = new City[size];
    
    
               for (int i = 0; i < size; i++) {

                childCities[i] = parent1.getCity(i);
           }
    
    
              int start = rand() % size;
              int end = rand() % size;
    
                  if (start > end) {

                     std::swap(start, end);
              }
    
    
               int* mapping = new int[size];

               for (int i = 0; i < size; i++) {

                mapping[i] = i; 
            }
    
    
    for (int i = start; i <= end; i++) {

        int p1Id = parent1.getCity(i).getId();
        int p2Id = parent2.getCity(i).getId();
        
        if (p1Id != p2Id) {
           
            for (int j = 0; j < size; j++) {
                if (childCities[j].getId() == p2Id) {
                    std::swap(childCities[i], childCities[j]);
                    break;
                }
            }
        }
    }
    
              child.setCities(childCities, size);
    
               delete[] childCities;
               delete[] mapping;
    
               return child;
        }


         Tour Crossover::cycleCrossover(const Tour& parent1, const Tour& parent2) {
           int size = parent1.getCityCount();
            Tour child;
    
            City* childCities = new City[size];
              bool* taken = new bool[size];
    
               for (int i = 0; i < size; i++) {

                 taken[i] = false;
         }
    
   
             int pos = 0;
             bool useParent1 = true;
    
              while (!taken[pos]) {

               if (useParent1) {

                     childCities[pos] = parent1.getCity(pos);
           }

         else {

                     childCities[pos] = parent2.getCity(pos);

                }
        
                     taken[pos] = true;
        
        
                     int cityId = parent2.getCity(pos).getId();
                     pos = findCityPosition(parent1, cityId);
        
        
                    if (taken[pos]) {

                       useParent1 = !useParent1;
                       for (int i = 0; i < size; i++) {

                         if (!taken[i]) {

                              pos = i;
                              break;
                     }
                }
            }
         }
    
                    child.setCities(childCities, size);
    
                    delete[] childCities;
                    delete[] taken;
    
                    return child;
    }



        Tour Crossover::randomCrossover(const Tour& parent1,
                                const Tour& parent2,
                                std::string& crossoverName) {

             int choice = rand() % 3;   

             Tour child;

            if (choice == 0) {

                 crossoverName = "Order Crossover";
                   child = orderCrossover(parent1, parent2);
            }

           else if (choice == 1) {

                  crossoverName = "PMX Crossover";
                  child = pmxCrossover(parent1, parent2);

             }

            else {

                     crossoverName = "Cycle Crossover";
                     child = cycleCrossover(parent1, parent2);
              }

                     return child;
         }
