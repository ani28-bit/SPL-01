#ifndef TOUR_H
#define TOUR_H

#include "City.h"

#define MAX_CITIES 100

 class Tour {
  private:
     City cities[MAX_CITIES];
     int cityCount;
     double distance;

     void calculateDistance();

    public:

       Tour();
       Tour(const Tour& other);

      ~Tour() {} 

      Tour& operator = (const Tour& other);
    
       void setCities(City c[], int n); 

       bool addCity(const City& city);
       bool removeCity(int idx);
       void swapCities(int idx1,int idx2);  
       void clear();
        
      
    
        City* getCities() {

             return cities; 

         }

        const City* getCities() const {

             return cities;

             }  
    
        int getCityCount() const {

             return cityCount;

          }
    
   
       double getDistance() const { 

             return distance; 

        }

        City& getCity(int idx);
        const City& getCity (int idx)const;

         void setDistance(double d);
         void updateDistance();

         bool containsCity(const City& city) const;

         bool isValid() const;
    
    
         bool operator < (const Tour& other) const;
         bool operator > (const Tour& other) const;
         bool operator == (const Tour& other) const;
         bool operator <= (const Tour& other) const;
         bool operator >= (const Tour& other) const;
    
          void printTour() const;
          void printDetailed()const;
       
};

#endif