#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  ticks(0),
  started(false), 
  paused(false), 
  sloMo(false), 
  sumOfTicks(SDL_GetTicks()),
  totalTicks(0)
  {
  start();
}

void Clock::draw() const { 
  // Not drawing anything yet!
  IOManager::getInstance()->printMessageValueAt("Avg fps: ", getFps(), 10, 10);
  IOManager::getInstance()->printMessageValueAt("Seconds: ", getSeconds(), 10, 40);
  IOManager::getInstance()->printMessageCenteredAt("Project #1 Solution ", 10);
  IOManager::getInstance()->printMessageAt("Maoting Ren's Project", 10, 400);
}

void Clock::update() {
  if(paused == true)
  {
    ticks = 0;

    return;
  }
  if(sloMo == true) {
    ticks = 0;
    return;
  }

  totalTicks = SDL_GetTicks();
  ticks = totalTicks- sumOfTicks;
  sumOfTicks += ticks;
}

unsigned int Clock::getTicksSinceLastFrame() const {
  return ticks;
}

void Clock::toggleSloMo() {
  sloMo = !sloMo;
}

int Clock::getFps() const { 
  if(ticks > 0) 
    return 1000/ticks;
  else return 0;
}

void Clock::start() { 
  started = true; 
  paused = false; 
}

void Clock::pause() { 
  paused = !paused;
}

void Clock::unpause() { 
  paused = false;
}

