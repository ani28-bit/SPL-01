 #include "Comparison.h"
 #include <iostream>
 #include <fstream>
 #include <iomanip>
 #include <cmath>

 using namespace std;

  void Comparison::compareResults(const Tour& gaTour, double gaDistance,
                                  const int cplexTour[], double cplexDistance,
                                   int numCities) {
    
    
    cout << "   GA vs CPLEX comparison " << endl;
     cout  << endl;
    
    cout << fixed << setprecision(2);
    
     cout << "\nGA Result:" << endl;
     cout << "  Distance: " << gaDistance << endl;
     cout << "  Tour: ";
     gaTour.printTour();
    
    cout << "\nCPLEX Result:" << endl;
    cout << "  Distance: " << cplexDistance << endl;
    cout << "  Tour: ";

    for (int i = 0; i < numCities; i++) {

             cout << cplexTour[i];

             if (i < numCities - 1) {

                   cout << " -> ";
             }
        }

        cout << " -> " << cplexTour[0] << endl;
    
        double gap = calculateGap(gaDistance, cplexDistance);
    
         cout << "\nComparison:" << endl;
         cout << "  Optimality Gap: " << gap << "%" << endl;
    
           if (gap < 0.01) {

                    cout << " GA found OPTIMAL solution!" << endl;

            } 
            else if (gap < 5.0) {

                     cout << "GA found EXCELLENT solution (< 5% gap)" << endl;

            } 
             else if (gap < 10.0) {

                          cout << "GA found Good solution (< 10% gap)" << endl;

                } 
              else {

                          cout << " GA solution has " << gap << "% gap from optimal" << endl;

                  } 
    
                           cout << endl;
             }

          void Comparison::saveComparison(const Tour& gaTour, double gaDistance,
                                           const int cplexTour[], double cplexDistance,
                                            int numCities, double gaTime, 
                                            double cplexTime,const char* filename) {
    
                        ofstream file(filename);

                         if (!file.is_open()) {

                                 cout << "Could not save comparison to " << filename << endl;
                                  return ;


                      }
    
                           file << endl;
                           file << " GA vs CPLEX comparison report\n";

                           file << endl;
    
                           file << fixed << setprecision(2);
    
                           file << "Problem Size:\n";
                           file << "  Cities: " << numCities << "\n\n";
    
                           file << "Genetic Algorithm Result:\n";

                           file << "  Distance: " << gaDistance << "\n";
                           file << "  Execution Time: " << gaTime << " seconds\n";
                           file << "  Tour: ";

                        for (int i = 0; i < gaTour.getCityCount(); i++) {

                                file << gaTour.getCity(i).getId();

                                   if (i < gaTour.getCityCount() - 1) {

                                               file << " -> ";
                                   }
                               }

                           file << " -> " << gaTour.getCity(0).getId() << "\n\n";
    
                           file << "CPLEX (optimal) Results:\n";
                           file << "  Distance: " << cplexDistance << "\n";
                           file << "  Execution Time: " << cplexTime << " seconds\n";
                           file << "  Tour: ";

                              for (int i = 0; i < numCities; i++) {

                                       file << cplexTour[i];
                                        if (i < numCities - 1) {

                                                file << " -> ";
                                        }
                                    }

                               file << " -> " << cplexTour[0] << "\n\n";
    
                               double gap = calculateGap(gaDistance, cplexDistance);
    
                              file << "Comparison Metrices:\n";
                              file << "  Optimality Gap: " << gap << "%\n";
                              file << "  Distance Difference: " << (gaDistance - cplexDistance) << "\n";
                              file << "  Speed Ratio (CPLEX/GA): " << (cplexTime / gaTime) << "x\n\n";
    
                              file << "Quality Assessment:\n";

                               if (gap < 0.01) {

                                            file << " OPTIMAL - GA found the optimal solution!\n";

                                } 
                                else if (gap < 1.0) {

                                             file << " Excelent - Gap < 1%\n";
                                        } 
                                        else if (gap < 5.0) {

                                                    file << " Very Good- Gap < 5%\n";

                                          } 
                                          else if (gap < 10.0) {

                                                        file << "Good - Gap < 10%\n";
                                                  } 
                                                  else {

                                                        file << " Acceptable- Gap > 10%\n";

                                                  }
    
                                     file << "\n\n";
                                     file.close();
    
                                        cout << " Comparison saved to: " << filename << endl;
                          }

                           double Comparison::calculateGap(double gaDistance, double optimalDistance) {

                             if (optimalDistance <= 0.0) {
                                      return 0.0;
                             }

                             double gap = ((gaDistance - optimalDistance) / optimalDistance) * 100.0;

   
                              if (fabs(gap) < 1e-6){
                                     gap = 0.0;
                              }

                              return gap;
             }
