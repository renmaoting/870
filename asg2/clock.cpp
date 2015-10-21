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
  pausedTime(0), 
  pausedSpan(0), 
  sloMo(false), 
  sumOfTicks(SDL_GetTicks()),
  totalTicks(0),
  secondPos(Gamedata::getInstance()->getXmlInt("clock/secondX"),
            Gamedata::getInstance()->getXmlInt("clock/secondX")),
  FPSPos(Gamedata::getInstance()->getXmlInt("clock/FPSX"),
            Gamedata::getInstance()->getXmlInt("clock/FPSY")),
  namePos(Gamedata::getInstance()->getXmlInt("clock/namePosX"),
            Gamedata::getInstance()->getXmlInt("clock/namePosY")),
  pojPos(Gamedata::getInstance()->getXmlInt("clock/pojPos"))
  {
  start();
}

void Clock::draw() const { 
  IOManager::getInstance()->printMessageValueAt("Avg fps: ", getFps(), FPSPos[0], FPSPos[1]);
  IOManager::getInstance()->printMessageValueAt("Seconds: ", getSeconds(), secondPos[0], secondPos[1]);
  IOManager::getInstance()->printMessageCenteredAt("Project #1 Solution ", pojPos);
  IOManager::getInstance()->printMessageAt("Maoting Ren's Project", namePos[0], namePos[1]);
}

void Clock::update() {
  totalTicks = SDL_GetTicks();
  if(paused == true)
  {
    ticks = 0;
    return;
  }
  if(sloMo == true) {
    ticks = totalTicks- sumOfTicks - pausedSpan;
    sumOfTicks += ticks;
    ticks = 1;
    return;
  }
  
  ticks = totalTicks- sumOfTicks - pausedSpan;
  sumOfTicks += ticks;
}

unsigned int Clock::getTicksSinceLastFrame() const {
  return ticks;
}

int Clock::getSeconds() const
{ 
    return sumOfTicks/1000; 
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
  pausedTime = totalTicks;
  paused = true;
}

void Clock::unpause() { 
  pausedSpan += (totalTicks - pausedTime);
  paused = false;
}

