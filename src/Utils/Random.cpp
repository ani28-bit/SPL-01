 #include "Random.h"
 #include <cstdlib>   


 bool Random::initialized = false;


  void Random::initialize(unsigned int seed) {

        srand(seed);          
        initialized = true;
   }


     int Random::getInt(int min, int max) {

          return min + rand() % (max - min + 1);
    }


     double Random::getDouble() {

          return (double) rand() / RAND_MAX;
   }


      double Random::getDouble(double min, double max) {

              return min + (max - min) * getDouble();
    }


        bool Random::getBool(double probability) {

              return getDouble() < probability;
   }


      void Random::shuffle(int arr[], int size) {

        for (int i = size - 1; i > 0; i--) {

              int j = getInt(0, i);

               int temp = arr[i];
                arr[i] = arr[j];
                 arr[j] = temp;

     }
  }
