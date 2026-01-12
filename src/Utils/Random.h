#ifndef RANDOM_H
#define RANDOM_H

 #include <cstdlib>   

 class Random {
  private:

    static bool initialized;

 public:
    
    static void initialize(unsigned int seed) {

        srand(seed);         
        initialized = true;
    }

    
    static int getInt(int min, int max) {

          return min + rand() % (max - min + 1);
    }

    
    static double getDouble() {

           return (double) rand() / RAND_MAX;
    }

   
    static double getDouble(double min, double max) {

          return min + (max - min) * getDouble();
    }

   
    static bool getBool(double probability = 0.5) {

          return getDouble() < probability;
    }

   
    static void shuffle(int arr[], int size) {

        for (int i = size - 1; i > 0; i--) {

            int j = getInt(0, i);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
     }
  };

  #endif
