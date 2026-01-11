#include "Tour.h"
#include<iostream>
using namespace std;

void Tour :: calculateDistance(){
    distance = 0.0;

    for(int i=0;i< cityCount -1;i++){

          distance += cities[i].distanceTo(cities[i+1]);
    }

    if(cityCount > 0){

          distance += cities[cityCount-1].distanceTo(cities[0]);
     }
 }

  Tour :: Tour(): cityCount(0),distance(0.0){}


  Tour:: Tour(const Tour& other) : cityCount(other.cityCount),distance(other.distance){

        for(int i = 0;i < cityCount;i++){

        cities[i]= other.cities[i];
     }
 }


  Tour& Tour::operator=(const Tour& other) {

      if (this != &other) {

          cityCount = other.cityCount;
          distance = other.distance;

        for (int i = 0; i < cityCount; ++i) {

             cities[i] = other.cities[i];
         }
     }

     return *this;
 }


 void Tour::setCities(City c[], int n) {

        if (n > MAX_CITIES) {

        cout<< "Error" <<endl;
        return;
    }

      cityCount = n;
      for (int i = 0; i < n; ++i) {

        cities[i] = c[i];
    }

        calculateDistance();
  }


  bool Tour::addCity(const City& city) {

    if (cityCount >= MAX_CITIES) {

        cout<< "Error" <<endl;

        return false;
    }

        cities[cityCount] = city;

         cityCount++;
          calculateDistance();

           return true;
     }


     bool Tour::removeCity(int idx) {


       if (idx < 0 || idx >= cityCount) {

        cout<< " Invalid city index!" <<endl;
        return false;

     }
    

       for (int i = idx; i < cityCount - 1; ++i) {

             cities[i] = cities[i + 1];
      }

        cityCount--;
        calculateDistance();
        return true;
   }


       void Tour::swapCities(int idx1, int idx2) {

          if (idx1 >= 0 && idx1 < cityCount && idx2 >= 0 && idx2 < cityCount) {

        
               City temp = cities[idx1];
               cities[idx1] = cities[idx2];
               cities[idx2] = temp;

                calculateDistance();
           }
     }


            void Tour::clear() {

            cityCount = 0;
            distance = 0.0;
   }


         City& Tour::getCity(int idx) {

         if (idx < 0 || idx >= cityCount) {

         cout<< "Invalid city index!" <<endl;

          static City dummy;
          return dummy;
       }

        return cities[idx];
  }


     const City& Tour::getCity(int idx) const {

         if (idx < 0 || idx >= cityCount) {

         cout<< "Invalid city index!" <<endl;

          static City dummy;
          return dummy;
      }

          return cities[idx];
  }


       void Tour::setDistance(double d) {

        distance = d;
  }


    void Tour::updateDistance() {
        calculateDistance();
  }


  bool Tour::containsCity(const City& city) const {

    for (int i = 0; i < cityCount; ++i) {

        if (cities[i].getId() == city.getId()) {
            return true;
        }
    }

    return false;
}


  bool Tour::isValid() const {

    if (cityCount == 0) {

        return false;
    }
    
    
    for (int i = 0; i < cityCount; ++i) {
        for (int j = i + 1; j < cityCount; ++j) {
            if (cities[i].getId() == cities[j].getId()) {
                return false;
            }
        }
    }
             return true;
  }


        bool Tour::operator<(const Tour& other) const {

        return distance < other.distance;
   }

        bool Tour::operator>(const Tour& other) const {

        return distance > other.distance;
    }

        bool Tour::operator==(const Tour& other) const {

        return distance == other.distance;
    }

        bool Tour::operator<=(const Tour& other) const {

        return distance <= other.distance;
   }
 
        bool Tour::operator>=(const Tour& other) const {

        return distance >= other.distance;
   }


       void Tour::printTour() const {

              cout << "Tour: ";

        for (int i = 0; i < cityCount; ++i) {

              cout << cities[i].getId();

        if (i < cityCount - 1) {

              cout << " -> ";
        }
    }

       if (cityCount > 0) {

            cout << " -> " << cities[0].getId();

       }

            cout << " | Distance: " << distance << std::endl;
   }

       void Tour::printDetailed() const {

       cout << "Tour Details" << endl;
       cout << "Number of cities: " << cityCount <<endl;
       cout << "Total distance: " << distance <<endl;

        cout << "Route: ";

        for (int i = 0; i < cityCount; ++i) {

             cout << cities[i].getId();

           if (i < cityCount - 1) {

              cout << " -> ";
        }
    }

        if (cityCount > 0) {


             cout << " -> " << cities[0].getId();

    }

             cout << endl;
         
}