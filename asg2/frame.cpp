#include "SDL/SDL_rotozoom.h"
#include "ioManager.h"
#include "frame.h"

// The next constructor s/ only be used when the Frames's surface
// starts at (0, 0) in the sprite sheet, and the frame uses the 
// entire sheet. For example, a Frame for an orb or a background.
Frame::Frame( const std::string& name, SDL_Surface* surf ) : 
  screen(IOManager::getInstance()->getScreen()),
  width(Gamedata::getInstance()->getXmlInt(name+"/width")), 
  height(Gamedata::getInstance()->getXmlInt(name+"/height")),
  surface( surf )
{ }

Frame& Frame::operator=(const Frame& rhs) {
  if ( this == &rhs ) return *this;
  screen = rhs.screen;
  width = rhs.width;
  height = rhs.height;
  surface = rhs.surface;
  return *this;
}

void Frame::draw(Sint16 x, Sint16 y) const {
  Sint16 zero = 0;
  SDL_Rect src = { zero, zero, width, height };    
  SDL_Rect dest = {x, y, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const {
  SDL_Rect src = { sx, sy, width, height };    
  SDL_Rect dest = {dx, dy, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 x, Sint16 y, double angle) const {
  SDL_Surface* tmp = rotozoomSurface(surface, angle, 1, 1);
  Sint16 zero = 0;
  Uint16 uzero = 0;
  Uint16 w = tmp->w;
  Uint16 h = tmp->h;
  SDL_Rect src = { zero, zero, w, h };    
  SDL_Rect dest = {x, y, uzero, uzero };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}
