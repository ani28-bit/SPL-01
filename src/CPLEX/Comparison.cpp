#include "Comparison.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void Comparison::compareResults(const Tour& gaTour, double gaDistance,
                               const int cplexTour[], double cplexDistance,
                               int numCities) {
    
    cout << "\n========================================" << endl;
    cout << "   GA vs CPLEX COMPARISON" << endl;
    cout << "========================================" << endl;
    
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
        if (i < numCities - 1) cout << " -> ";
    }
    cout << " -> " << cplexTour[0] << endl;
    
    double gap = calculateGap(gaDistance, cplexDistance);
    
    cout << "\nComparison:" << endl;
    cout << "  Optimality Gap: " << gap << "%" << endl;
    
    if (gap < 0.01) {
        cout << "  ✓ GA found OPTIMAL solution!" << endl;
    } else if (gap < 5.0) {
        cout << "  ✓ GA found EXCELLENT solution (< 5% gap)" << endl;
    } else if (gap < 10.0) {
        cout << "  ✓ GA found GOOD solution (< 10% gap)" << endl;
    } else {
        cout << "  ⚠ GA solution has " << gap << "% gap from optimal" << endl;
    }
    
    cout << "========================================" << endl;
}

void Comparison::saveComparison(const Tour& gaTour, double gaDistance,
                               const int cplexTour[], double cplexDistance,
                               int numCities,
                               double gaTime, double cplexTime,
                               const char* filename) {
    
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Warning: Could not save comparison to " << filename << endl;
        return;
    }
    
    file << "========================================\n";
    file << "   GA vs CPLEX COMPARISON REPORT\n";
    file << "========================================\n\n";
    
    file << fixed << setprecision(2);
    
    file << "PROBLEM SIZE:\n";
    file << "  Cities: " << numCities << "\n\n";
    
    file << "GENETIC ALGORITHM RESULTS:\n";
    file << "  Distance: " << gaDistance << "\n";
    file << "  Execution Time: " << gaTime << " seconds\n";
    file << "  Tour: ";
    for (int i = 0; i < gaTour.getCityCount(); i++) {
        file << gaTour.getCity(i).getId();
        if (i < gaTour.getCityCount() - 1) file << " -> ";
    }
    file << " -> " << gaTour.getCity(0).getId() << "\n\n";
    
    file << "CPLEX (OPTIMAL) RESULTS:\n";
    file << "  Distance: " << cplexDistance << "\n";
    file << "  Execution Time: " << cplexTime << " seconds\n";
    file << "  Tour: ";
    for (int i = 0; i < numCities; i++) {
        file << cplexTour[i];
        if (i < numCities - 1) file << " -> ";
    }
    file << " -> " << cplexTour[0] << "\n\n";
    
    double gap = calculateGap(gaDistance, cplexDistance);
    
    file << "COMPARISON METRICS:\n";
    file << "  Optimality Gap: " << gap << "%\n";
    file << "  Distance Difference: " << (gaDistance - cplexDistance) << "\n";
    file << "  Speed Ratio (CPLEX/GA): " << (cplexTime / gaTime) << "x\n\n";
    
    file << "QUALITY ASSESSMENT:\n";
    if (gap < 0.01) {
        file << "  ★★★★★ OPTIMAL - GA found the optimal solution!\n";
    } else if (gap < 1.0) {
        file << "  ★★★★☆ EXCELLENT - Gap < 1%\n";
    } else if (gap < 5.0) {
        file << "  ★★★☆☆ VERY GOOD - Gap < 5%\n";
    } else if (gap < 10.0) {
        file << "  ★★☆☆☆ GOOD - Gap < 10%\n";
    } else {
        file << "  ★☆☆☆☆ ACCEPTABLE - Gap > 10%\n";
    }
    
    file << "\n========================================\n";
    file.close();
    
    cout << "\n✓ Comparison saved to: " << filename << endl;
}

double Comparison::calculateGap(double gaDistance, double optimalDistance) {
    if (optimalDistance <= 0.0) return 0.0;
    return ((gaDistance - optimalDistance) / optimalDistance) * 100.0;
}