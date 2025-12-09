  #include "Tour.h"
  #include "City.h"
  #include <iostream>
  using namespace std;

    void printSeparator() {

       cout << endl;
   }

    void testBasicOperations() {

       cout << "Test 1: Basic Operations :" << endl;

        printSeparator();
    
    
       City c1(1, 0, 0);
       City c2(2, 3, 4);
       City c3(3, 6, 8);
       City c4(4, 10, 0);
    
    
        Tour tour;
        cout << "Adding cities -" << endl;

               tour.addCity(c1);
                tour.addCity(c2);
                 tour.addCity(c3);
                  tour.addCity(c4);
    
      
       tour.printTour();
       tour.printDetailed();
    
       cout << "\nCity count: " << tour.getCityCount() << endl;
       cout << "Total distance: " << tour.getDistance() << endl;

    }

       void testSetCities() {
       cout << "\nTest 2: Set Multiple Cities at Once :" << endl;
       printSeparator();
    
       City cities[5];
            cities[0] = City(1, 0, 0);
             cities[1] = City(2, 1, 1);
              cities[2] = City(3, 2, 2);
               cities[3] = City(4, 3, 3);
                cities[4] = City(5, 4, 4);
    
       Tour tour;
       tour.setCities(cities, 5);
    
         tour.printTour();
         cout << "Distance: " << tour.getDistance() << endl;
   }

       void testRemoveCity() {

       cout << "\nTest 3: Remove City :" << endl;
       printSeparator();
    
           City c1(1, 0, 0);
            City c2(2, 5, 0);
             City c3(3, 5, 5);
              City c4(4, 0, 5);
    
          Tour tour;
           tour.addCity(c1);
            tour.addCity(c2);
             tour.addCity(c3);
              tour.addCity(c4);
    
         cout <<"Original tour:"<< endl;
         tour.printTour();
    
         cout << "Removing city at index 2."<< endl;
         tour.removeCity(2);
         tour.printTour();
  }

         void testSwapCities() {

         cout << "\nTest 4: Swap Cities :"<< endl;
         printSeparator();
    
           City c1(1, 0, 0);
            City c2(2, 3, 4);
             City c3(3, 6, 8);
              City c4(4, 9, 12);
    
          Tour tour;
           tour.addCity(c1);
            tour.addCity(c2);
             tour.addCity(c3);
              tour.addCity(c4);
    
         cout <<"Original tour:"<< endl;
         tour.printTour();
    
         cout <<"Swapping cities at index 1 and 3."<< endl;
         tour.swapCities(1, 3);
         tour.printTour();
    }

         void testCopyConstructor() {
         cout << "\nTest 5: Copy Constructor :" << endl;
         printSeparator();
    
          City c1(1, 0, 0);
           City c2(2, 3, 4);
            City c3(3, 6, 8);
    
          Tour tour1;
           tour1.addCity(c1);
            tour1.addCity(c2);
             tour1.addCity(c3);
    
         cout << "Original tour:" << endl;
         tour1.printTour();
    
   
          Tour tour2 = tour1;
    
           cout << "Copied tour:" << endl;
           tour2.printTour();
    
    
            cout << "Adding city to original tour." << endl;
             City c4(4, 10, 12);
              tour1.addCity(c4);
    
             cout << "Original tour after modification:" << endl;
              tour1.printTour();
    
              cout << "Copied tour :" << endl;

               tour2.printTour();


   }

           void testAssignmentOperator() {
           cout << "\nTest6: Assignment Operator :" << endl;
           printSeparator();
    
             City c1(1, 0, 0);
             City c2(2, 5, 0);
    
               Tour tour1;
                tour1.addCity(c1);
                 tour1.addCity(c2);
    
                 Tour tour2;
                 City c3(3, 10, 10);
                  tour2.addCity(c3);
    
                   cout << "Tour 1:" << endl;
                    tour1.printTour();
    
                    cout << "\nTour 2 before assignment:" << endl;
                     tour2.printTour();
    
   
                        tour2 = tour1;
     
                        cout << "\nTour 2 after assignment:" << endl;
                         tour2.printTour();


       }

                   void testValidation() {
                    cout << "\nTest 7: Validation Methods :" << endl;
                     printSeparator();
    
                       City c1(1, 0, 0);
                        City c2(2, 3, 4);
                        City c3(3, 6, 8);
    
                         Tour tour;
    
  
                      cout << "Empty tour is valid?" << endl;

                       if(tour.isValid()){

                           cout<<"Yes"<<endl;

                      }

                      else{

                            cout<<"No"<< endl;

                      }
    
    
                      tour.addCity(c1);
                       tour.addCity(c2);
                        tour.addCity(c3);
    
                        cout<<"Tour with 3 cities is valid? "<<endl;
                        
                           if(tour.isValid()){

                              cout<<"Yes"<<endl;

                          } 

                           else {

                                  cout<<"No"<<endl;

                            }
    
    
                            cout << "Contains city with ID 2? "<<endl;

                               if(tour.containsCity(c2)){

                                      cout<< "Yes"<<endl;

                            } 

                            else {
                                
                                      cout<<"No"<<endl;
                            }
    
                              City c4(4, 10, 10);
                              cout << "Contains city with ID 4?" <<endl;

                                if(tour.containsCity(c4)){

                                       cout<< "Yes"<<endl;

                               } 
                              
                                else {

                                        cout<<"No"<< endl;

                              }

                 }

                              void testComparison() {

                                cout << "\nTest 8: Comparison Operators :"<< endl;
                                printSeparator();
    
                                   City c1(1, 0, 0);
                                    City c2(2, 3, 0);
                                      City c3(3, 3, 4);
    
                                       Tour tour1, tour2;
    
    
                                         tour1.addCity(c1);
                                          tour1.addCity(c2);
                                           tour1.addCity(c1);  
    
    
                                             tour2.addCity(c1);
                                              tour2.addCity(c2);
                                               tour2.addCity(c3);
    
                                                cout << "Tour 1:" << endl;
                                                  tour1.printTour();
    
                                               cout << "\nTour 2:" << endl;

                                                 tour2.printTour();
    
                                                 cout << "\nComparisons:" << endl;
                                                 cout << "Tour1 < Tour2: " <<endl;

                                               if(tour1 < tour2 ){

                                                   cout <<"True" <<endl;
                                          
                                          }

                                          else{

                                                  cout<<"False"<< endl;
                                          }

                                       cout << "Tour1 > Tour2: " << endl;
                                       if(tour1 > tour2){

                                        cout<<"True" <<endl;
                                        
                                       }
                                       else{
                                        cout<<"False"<< endl;


                                       }

                                     cout << "Tour1 == Tour2: " << endl;

                                     if(tour1 == tour2){

                                         cout<<"True"<<endl;

                                    } 
                                    
                                    
                                    else{

                                          cout<<"False"<< endl;
                                    }
        }

                 void testClear() {

                 cout << "\nTest9: clear Tour :" << endl;

                              printSeparator();
    
                               City c1(1, 0, 0);
                                City c2(2, 3, 4);
                                 City c3(3, 6, 8);
    
                                   Tour tour;
                                   tour.addCity(c1);
                                   tour.addCity(c2);
                                   tour.addCity(c3);
    
                   cout <<"Tour before clear:"<< endl;
                   tour.printTour();
    
                   tour.clear();
    
                  cout << "\nTour after clear:"<< endl;
                  cout << "City count:"<< tour.getCityCount()<< endl;
                  cout << "Distance: " << tour.getDistance() << endl;


            }

              void testGetCity() {
              cout << "\nTest 10: get individual City :" << endl;
              printSeparator();
    
                  City c1(1, 0, 0);
                  City c2(2, 3, 4);
                  City c3(3, 6, 8);
    
                   Tour tour;
                   tour.addCity(c1);
                   tour.addCity(c2);
                   tour.addCity(c3);
    
                   cout << "Cities in tour:" << endl;

                   for (int i = 0; i < tour.getCityCount(); i++) {

                   City city = tour.getCity(i);
                   cout << "City " << i << ": ID=" << city.getId()  << ", X=" << city.getX()  << ", Y=" << city.getY() << endl;

            }

    }

               void testErrorHandling() {

                cout << "\nTest 11: Error Handling :" << endl;
                printSeparator();
    
                     Tour tour;
                     City c1(1, 0, 0);
    
                 cout << "Test 1: Remove from empty tour :" << endl;
                 tour.removeCity(0);
    
                   cout << "\nTest 2: Access invalid index :" << endl;
                    tour.getCity(10);
    
                  cout << "\nTest 3: Swap with invalid indices :" << endl;

                      tour.addCity(c1);
                      tour.swapCities(0, 10);
    
                   cout << "\nTest 4: Add too many cities :" << endl;

                          Tour bigTour;
                            for (int i = 0; i < 102; i++) {

                                   City c(i, i, i);

                                  if (!bigTour.addCity(c)) {


                                        cout << "Failed to add city"<<i<< endl;
                                         break;

                   }
             }
      }

            void testRealWorldScenario() {

             cout << "\nTest 12: Real-World TSP Scenario :" << endl;
             printSeparator();
    
    
              City cities[5] = {
                                  City(1, 0, 0),   
                                  City(2, 4, 0),    
                                  City(3, 4, 3),    
                                  City(4, 0, 3),    
                                  City(5, 2, 1.5)   

                               };
    
                            Tour tour;
                            tour.setCities(cities, 5);
    
                             cout << "Initial tour:" << endl;
                              tour.printDetailed();
    
   
                            cout << "\nTrying optimization by swapping cities 2 and 4."<< endl;

                            double oldDistance = tour.getDistance();

                            tour.swapCities(1, 3);

                            double newDistance = tour.getDistance();
    
                            cout << "New tour after swap:" << endl;
                            tour.printTour();
    
                          if (newDistance < oldDistance) {

                                cout << "Improvement! Distance reduced by: " << (oldDistance - newDistance) << endl;
                          } 
                          else {

                                 cout << "No improvement. Distance increased by: "<< (newDistance - oldDistance) << endl;

                               }
                          }

         int main() {
   
              cout << "Tour Class Testing-"<< endl;
    
    
              testBasicOperations();
              testSetCities();
              testRemoveCity();
              testSwapCities();
              testCopyConstructor();
              testAssignmentOperator();
              testValidation();
              testComparison();
              testClear();
              testGetCity();
              testErrorHandling();
              testRealWorldScenario();
    
   
            cout <<"All Tests Completed." << endl;

    
            return 0;


    }