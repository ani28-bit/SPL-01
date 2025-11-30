#include "DistanceMatrix.h"
#include <iostream>
using namespace std;


string intToString(int n) {
    if (n == 0) return "0";
    string s = "";
    bool neg = false;

    if (n < 0) {
        neg = true;
        n = -n;
    }

    while (n > 0) {
        s = char('0' + (n % 10)) + s;
        n /= 10;
    }

    if (neg) s = "-" + s;
    return s;
 }


 string doubleTo2Decimal(double x) {
    int intPart = (int)x;
    double frac = x - intPart;

    int twoDigit = (int)(frac * 100 + 0.5); 

    return intToString(intPart) + "." + (twoDigit < 10 ? "0" : "") + intToString(twoDigit);
 }


 string pad8(string s) {
    while (s.length() < 8) s = " " + s;
    return s;
 }

 DistanceMatrix::DistanceMatrix(const vector<City>& cities) {
    numCities = cities.size();
    matrix.resize(numCities, vector<double>(numCities, 0.0));

    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            if (i == j) matrix[i][j] = 0.0;
            else matrix[i][j] = cities[i].distanceTo(cities[j]);
        }
    }
 }

 double DistanceMatrix::getDistance(int cityIndex1, int cityIndex2) const {

    if (cityIndex1 < 0 || cityIndex1 >= numCities ||
        cityIndex2 < 0 || cityIndex2 >= numCities) {

        cout << "Error: Invalid city index!" << endl;
        return -1.0;
    }

    return matrix[cityIndex1][cityIndex2];
}

int DistanceMatrix::getNumCities() const {

    return numCities;
 }

 double DistanceMatrix::calculateTourDistance(const vector<int>& tour) const {

    double total = 0.0;

    for (size_t i = 0; i < tour.size() - 1; i++)

        total += getDistance(tour[i], tour[i + 1]);

    if (tour.size() > 1)
        total += getDistance(tour.back(), tour[0]);

    return total;
 }

void DistanceMatrix::print() const {

    cout << "Distance Matrix (" << numCities << "x" << numCities << "):"<<endl;

    cout << "        ";

    for (int i = 0; i < numCities; i++) {

        cout << pad8("City" + intToString(i));
    }

    cout << endl;

    for (int i = 0; i < numCities; i++) {

        cout << "City" << i << " ";

        for (int j = 0; j < numCities; j++) {
            
            string val = doubleTo2Decimal(matrix[i][j]);
            cout << pad8(val);
        }
        cout << "\n";
    }
}
