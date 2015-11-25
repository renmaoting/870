#include <iostream>
#include <cmath>
#include "SDL/SDL_rotozoom.h"
#include "scaledSprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "ioManager.h"

ScaledSprite::ScaledSprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/loc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/loc/y")), 
           Vector2f((rand()%2?1:-1)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speed/x")),
                    (rand()%2?1:-1)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speed/y"))
                   )
  ), 
  surface(IOManager::getInstance().loadAndSet(Gamedata::getInstance().getXmlStr("bubble/file"),
            Gamedata::getInstance().getXmlBool("bubble/transparency")) ),
  scale(getRandFloat(Gamedata::getInstance().getXmlFloat(name+"/scale/min"),
                     Gamedata::getInstance().getXmlFloat(name+"/scale/max"))
  ),
  scaledSurface( rotozoomSurface(surface, 0, scale, SMOOTHING_ON) ),
  frame( new Frame(scaledSurface, scaledSurface->w, scaledSurface->h,
                   Gamedata::getInstance().getXmlInt(name+"/src/x"), 
                   Gamedata::getInstance().getXmlInt(name+"/src/y"))
  ),
  //frame(FrameFactory::getInstance().getFrame(name)),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ 
  X( rand()% worldWidth );
  Y( rand() % worldHeight);  
  velocityY(-abs( velocityY())); 
  velocityX( abs(velocityY())%20); 
}

ScaledSprite::ScaledSprite(const ScaledSprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  surface(s.surface),
  scale(s.scale),
  scaledSurface(s.scaledSurface),
  frame(s.frame),
  frameWidth(s.frameWidth),
  frameHeight(s.frameHeight),
  worldWidth(s.worldWidth),
  worldHeight(s.worldHeight)
{
}

ScaledSprite& ScaledSprite::operator=(const ScaledSprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  scale = rhs.scale;
  scaledSurface = rhs.scaledSurface;
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

ScaledSprite::~ScaledSprite() {
  SDL_FreeSurface( scaledSurface );
  SDL_FreeSurface( surface);
  delete frame;
}

void ScaledSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

unsigned ScaledSprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}


void ScaledSprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    Y(worldHeight);
  }

  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
