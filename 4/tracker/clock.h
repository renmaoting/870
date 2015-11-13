#ifndef Clock_H
#define Clock_H

#include <SDL.h>
#include <string>
#include <deque>
#include "vector2f.h"

class Manager;

class Clock {
public:
  static Clock& getInstance();  // This class is a Singleton
  unsigned int getTicksSinceInit() const { return sumOfTicks; }
  unsigned int getSeconds() const { return sumOfTicks/1000; }

  void toggleSloMo();
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  int getFps() const;

  void start();
  void pause();
  void unpause();
  void draw() const;  // For debugging

private:
  unsigned int ticks;
  unsigned int totalTicks;
  bool started;
  bool paused;
  bool sloMo;
  unsigned int sumOfTicks;
  Vector2f pos;

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
  friend class Manager;
  void update();  // Increments time/ticks
  unsigned int getTicksSinceLastFrame() const;
};
#endif
