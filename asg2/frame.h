#ifndef FRAME__H
#define FRAME__H

#include <string>
#include <SDL.h>

class Frame {
public:
  // The next constructor s/ only be used when the Frames's surface
  // starts at (0, 0) in the sprite sheet, and the frame uses the
  // entire sheet. For example, a Frame containing a background.
  // The surface is passed from FrameFactory and width & height
  // are obtained using the XML file.
  Frame( const std::string&, SDL_Surface*);

  // When using the next constructor, we pass src_x, and src_y, width,
  // and height; usually used to get a frame for a scaled sprite:
  Frame( SDL_Surface* surf, Sint16 src_x, Sint16 src_y, Sint16 w, Sint16 h);

  Frame(const Frame&);
  Frame& operator=(const Frame&);

  // We're storing the surface in the FrameFactory for consistency.
  // Therefore, this class stores nothing on the heap, and object 
  // deletion will be faster if the system does it. 
  //~Frame() { ; }  

  SDL_Surface* getSurface() const { return surface; }
  void draw(Sint16 x, Sint16 y) const;
  void draw(Sint16 x, Sint16 y, double angle) const;
  void draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const;

  Uint16 getWidth()  const { return width; }
  Uint16 getHeight() const { return height; }

private:
  SDL_Surface * screen;
  Uint16 width;
  Uint16 height;
  SDL_Surface * surface;

  Frame();
};

#endif
