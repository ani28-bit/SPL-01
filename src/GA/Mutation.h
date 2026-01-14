#ifndef MUTATION_H
#define MUTATION_H

#include "../TSP/Tour.h"
#include<string>

class Mutation {

  public:
    
      static void swapMutation(Tour& tour);
    
    
       static void inversionMutation(Tour& tour);
    
   
        static void insertionMutation(Tour& tour);
    
   
         static void scrambleMutation(Tour& tour);
    
    
           static void applyMutation(Tour& tour, double mutationRate, std::string& mutationName);


        };

        #endif