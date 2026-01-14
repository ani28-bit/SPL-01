 #include "Timer.h"
 #include <ctime>   

Timer::Timer() : running(false), startTime(0), endTime(0) {}


  void Timer::start() {

      startTime = clock();
      running = true;
  }


    void Timer::stop() {

      endTime = clock();
      running = false;
  }


      double Timer::getElapsedSeconds() const {

         clock_t currentTime = running ? clock() : endTime;
         return double(currentTime - startTime) / CLOCKS_PER_SEC;

  }

 
         double Timer::getElapsedMilliseconds() const {

             return getElapsedSeconds() * 1000.0;

         }


          void Timer::reset() {
          running = false;
          startTime = 0;
           endTime = 0;

      }
