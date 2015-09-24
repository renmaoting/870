#include <SDL.h>
#include <string>
#include <deque>

class Manager;

class Clock {
public:
  static Clock& getInstance();  // This class is a Singleton
  unsigned int getTicksSinceInit() const { return sumOfTicks; }

  void toggleSloMo();
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  int getFps() const;
  int getSeconds() const{ return sumOfTicks/1000; }

  void start();
  void pause();
  void unpause();
  void draw() const;  // For debugging
  void update();  // Increments time/ticks

private:
  unsigned int ticks;
  bool started;
  bool paused;
  int pausedTime;
  bool sloMo;
  unsigned int sumOfTicks;
  unsigned int totalTicks;
  unsigned int getTicksSinceLastFrame() const;


  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
  friend class Manager;
};
