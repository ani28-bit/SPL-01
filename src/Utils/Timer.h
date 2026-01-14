 #ifndef TIMER_H
 #define TIMER_H
 #include <ctime>

  class Timer {

   private:

    clock_t startTime = 0;
    clock_t endTime = 0;
    bool running = false;

   public:

       Timer();

       void start();                   
        void stop();                   
         double getElapsedSeconds() const;       
          double getElapsedMilliseconds() const;  
            void reset();    

    };

   #endif
