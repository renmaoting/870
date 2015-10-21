#include <SDL.h>
#include <string>
#include <deque>
#include "vector2f.h"

class Manager;

class Clock {
public:
  static Clock& getInstance();  // This class is a Singleton
  unsigned int getTicksSinceInit() const { return sumOfTicks; }

  void toggleSloMo();
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  int getFps() const;
  int getSeconds() const;

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
  int pausedSpan;
  bool sloMo;
  unsigned int sumOfTicks;
  unsigned int totalTicks;
  Vector2f secondPos;
  Vector2f FPSPos;
  Vector2f namePos;
  int pojPos;

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
  unsigned int getTicksSinceLastFrame() const;
  friend class Manager;
};
