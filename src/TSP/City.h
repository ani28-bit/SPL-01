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
    
    
    int getId()const;
    double getX()const;
    double getY()const;
    

    void setId(int idVal);
    void setX(double xVal);
    void setY(double yVal);
    
    
     double distanceTo(const City& other)
     const;
  };

 #endif

