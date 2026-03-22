 #include "CplexSolver.h"
 #include <iostream>
 #include <cmath>
 #ifdef USE_CPLEX
 #include <ilcplex/ilocplex.h>
 
 #endif

  using namespace std;

   CplexSolver::CplexSolver(City cities[], int numCities) 
    : cities(cities), numCities(numCities), distanceMatrix(nullptr) {

         buildDistanceMatrix();
    }

     CplexSolver::~CplexSolver() {
     freeDistanceMatrix();

   } 

   void CplexSolver::buildDistanceMatrix() {

    
             distanceMatrix = new double*[numCities];

                for (int i = 0; i < numCities; i++) {

                         distanceMatrix[i] = new double[numCities];
                 }
    
   
               for (int i = 0; i < numCities; i++) {

                      for (int j = 0; j < numCities; j++) {
                              if (i == j) {

                                    distanceMatrix[i][j] = 0.0;
                             } 
                             else {

                                      distanceMatrix[i][j] = cities[i].distanceTo(cities[j]);
                                }
                             }
                          }
                       }

                            void CplexSolver::freeDistanceMatrix() {

                                 if (distanceMatrix) {

                                          for (int i = 0; i < numCities; i++) {

                                                    delete[] distanceMatrix[i];
                                      }

                                             delete[] distanceMatrix;
                                             distanceMatrix = nullptr;
                                     }
                                 }

                                     bool CplexSolver::isCplexAvailable() {

                                                #ifdef USE_CPLEX
                                                        return true;
                                                #else
                                                        return false;
                                               #endif
                                          }

                              double CplexSolver::solve(int optimalTour[], double timeLimit) {

                                         #ifdef USE_CPLEX
                                                    try {
                                                           IloEnv env;
                                                           IloModel model(env);
        
        
                                                          IloArray<IloNumVarArray> x(env, numCities);
                                                          for (int i = 0; i < numCities; i++) {

                                                                 x[i] = IloNumVarArray(env, numCities, 0, 1, ILOBOOL);
                                                              }
        
       
                                                          IloExpr objExpr(env);
                                                               for (int i = 0; i < numCities; i++) {

                                                                   for (int j = 0; j < numCities; j++) {
                                                                       if (i != j) {

                                                                            objExpr += distanceMatrix[i][j] * x[i][j];
                                                                       }
                                                                  }
                                                             }
                                                             model.add(IloMinimize(env, objExpr));
                                                             objExpr.end();
        
        
                                               for (int i = 0; i < numCities; i++) {
                                                          IloExpr sumOut(env);
                                                 for (int j = 0; j < numCities; j++) {

                                                      if (i != j) {

                                                            sumOut += x[i][j];
                                                     }
                                                 }
                                                          model.add(sumOut == 1);
                                                          sumOut.end();
                                                }
        
        
                                            for (int j = 0; j < numCities; j++) {
                                                    IloExpr sumIn(env);
                                             for (int i = 0; i < numCities; i++) {

                                                    if (i != j) {
                                                        sumIn += x[i][j];
                                                    }
                                                }
                                                     model.add(sumIn == 1);
                                                     sumIn.end();
                                               }
        
        
                         IloNumVarArray u(env, numCities, 0, numCities - 1, ILOFLOAT);
                             for (int i = 1; i < numCities; i++) {
                               for (int j = 1; j < numCities; j++) {

                                    if (i != j) {

                                           model.add(u[i] - u[j] + numCities * x[i][j] <= numCities - 1);
                                       }
                                   }
                               }
        
        
                             IloCplex cplex(model);
        
        
                             cplex.setParam(IloCplex::Param::TimeLimit, timeLimit);
        
        
                             cplex.setParam(IloCplex::Param::MIP::Display, 2);
        
                             cout <<endl;
                             cout << " CPLEX TSP Solver" << endl;
                             cout << endl;
                             cout << "Cities: " << numCities << endl;
                             cout << "Time limit: " << timeLimit << " seconds" << endl;
                             cout << "\nSolving..." << endl;
        
               
                         if (cplex.solve()) {

                                  double optimalDistance = cplex.getObjValue();
            
                                  cout << "\nCPLEX Solution Found!" << endl;
                                  cout << "Status: " << cplex.getStatus() << endl;
                                  cout << "Optimal Distance: " << optimalDistance << endl;
            
           
                             int currentCity = 0;
                             bool* visited = new bool[numCities];

                           for (int i = 0; i < numCities; i++) {

                                       visited[i] = false;
                           }
            
                          for (int step = 0; step < numCities; step++) {

                                     optimalTour[step] = currentCity;
                                     visited[currentCity] = true;
                
                
                          for (int j = 0; j < numCities; j++) {

                                  if (!visited[j] && cplex.getValue(x[currentCity][j]) > 0.5) {

                                          currentCity = j;
                                          break;
                         }
                     }
                   }
            
                                   delete[] visited;
            
                                   env.end();
            
                                  return optimalDistance;
            
                        }
                         else {

                                   cout << "\nCPLEX could not find solution" << endl;
                                   cout << "Status: " << cplex.getStatus() << endl;
                                   env.end();
                                   return -1.0;
                            }
        
                          } 
                          catch (IloException& e) {

                                    cout << "CPLEX Error: " << e.getMessage() << endl;
                                    return -1.0;
                              }
    
            #else
            cout << endl;
            cout << "   CPLEX NOT AVAILABLE" << endl;
            cout << endl;
            
            return -1.0;
            #endif
  }