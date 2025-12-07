#include <iostream>
using namespace std;


class City {
private:
    int id;
    double x, y;
 public:
    City() : id(0), x(0), y(0) {}
    City(int id_, double x_, double y_) : id(id_), x(x_), y(y_) {}

      int getId() { return id; }
      double getX() { return x; }
     double getY() { return y; }
  };

 
  double round2(double x) {
    return (int)(x * 100 + 0.5) / 100.0;
 }

 double manualSqrt(double n) {
    if (n == 0) return 0;

    double x = n, y = 1.0, e = 0.00001;
    while ((x - y > e) || (y - x > e)) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

double calcDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return manualSqrt(dx * dx + dy * dy);
}


class DistanceMatrix {
private:
    int nCities;
    double** matrix;

public:
    DistanceMatrix(City cities[], int n) {
        nCities = n;
        matrix = new double*[nCities];
        for (int i = 0; i < nCities; i++)
            matrix[i] = new double[nCities];

        for (int i = 0; i < nCities; i++) {
            for (int j = 0; j < nCities; j++) {
                matrix[i][j] = round2(calcDistance(
                    cities[i].getX(), cities[i].getY(),
                    cities[j].getX(), cities[j].getY()
                ));
            }
        }
    }

    ~DistanceMatrix() {
        for (int i = 0; i < nCities; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    int getNumCities() { return nCities; }
    double getDistance(int i, int j) { return matrix[i][j]; }

    double calculateTourDistance(int tour[], int size) {
        double total = 0.0;
        for (int i = 0; i < size - 1; i++)
            total += matrix[tour[i]][tour[i + 1]];
        total += matrix[tour[size - 1]][tour[0]]; 
        return round2(total);
    }

    void print() {
        for (int i = 0; i < nCities; i++) {
            for (int j = 0; j < nCities; j++)
                cout << matrix[i][j] << "\t";
            cout << endl;
        }
    }
};


int main() {
    cout << "TESTING DISTANCEMATRIX CLASS" << endl << endl;

    City cities[4] = {
        City(0, 0.0, 0.0),
        City(1, 4.0, 0.0),
        City(2, 4.0, 3.0),
        City(3, 0.0, 3.0)
    };

    cout << "[TEST 1] Creating Cities" << endl;
    for (int i = 0; i < 4; i++)
        cout << "City " << cities[i].getId() << ": ("
             << cities[i].getX() << ", " << cities[i].getY() << ")" << endl;
    cout << "Created 4 cities" << endl << endl;

    cout << "[TEST 2] Building Distance Matrix" << endl;
    DistanceMatrix distMatrix(cities, 4);
    cout << " Distance matrix created" << endl << endl;

    cout << "[TEST 3] Getting Number of Cities" << endl;

    int numCities = distMatrix.getNumCities();
    cout << "Number of cities: " << numCities << endl;

    if (numCities == 4) {
    cout << " Pass" << endl << endl;
    }
    else {
         cout << " Fail" << endl;
          return 1;
         }

    cout << "[TEST 4] Testing Specific Distances" << endl;
    double d01 = distMatrix.getDistance(0, 1);
    double d12 = distMatrix.getDistance(1, 2);
    double d02 = distMatrix.getDistance(0, 2);

    cout << "Distance 0->1: " << d01 << " (expected 4.00)" << endl;
    cout << "Distance 1->2: " << d12 << " (expected 3.00)" << endl;
    cout << "Distance 0->2: " << d02 << " (expected 5.00)" << endl;

    if (d01 != 4.0 || d12 != 3.0 || d02 != 5.0) 
    return 1;

    cout << "\n[TEST 5] Testing Symmetry" << endl;

    if (distMatrix.getDistance(0, 1) == distMatrix.getDistance(1, 0)){

        cout << "Distances are symmetric" << endl;
    }
    else{ 
        return 1;
    }

    cout << "\n[TEST 6] Testing Distance to Self" << endl;
    if (distMatrix.getDistance(0, 0) == 0.0){

        cout << "✓ Distance to self is zero" << endl;
    }
    else{
         return 1;
    }

    cout << "\n[TEST 8] Printing Distance Matrix" << endl;
    distMatrix.print();
    cout << "✓ Matrix printed successfully" << endl;

    cout << "\nALL TESTS PASSED!" << endl;
    cout << "DistanceMatrix is working perfectly!" << endl;

    return 0;
}
