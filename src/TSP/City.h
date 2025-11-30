 #ifndef CITY_H
 #define CITY_H

 class City {
 private:
    int id;
    double x;
    double y;

 public:
    
    City();
    City(int idVal, double xVal, double yVal);
    
    
    int getId() 
     const;
    double getX() 
     const;
    double getY()
     const;
    

    void setId(int idVal);
    void setX(double xVal);
    void setY(double yVal);
    
    
    double distanceTo(const City& other)
     const;
};

#endif















/*
#ifndef CITY_H
#define CITY_H

class City {
    
private:
    int id;
    double x;
    double y;

public:
    City() : id(0), x(0.0), y(0.0) {}
    City(int idVal, double xVal, double yVal) : id(idVal), x(xVal), y(yVal) {}
    
    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }
    
    void setId(int idVal) { id = idVal; }
    void setX(double xVal) { x = xVal; }
    void setY(double yVal) { y = yVal; }
};

#endif */