 #ifndef TIMER_H
 #define TIMER_H

 #include <ctime>   

 class Timer {

  private:

    clock_t startTime;
    clock_t endTime;
    bool running;

  public:

     Timer();

      void start();

       void stop();

       double getElapsedSeconds() const;

       double getElapsedMilliseconds() const;

       void reset();
   };

  #endif
