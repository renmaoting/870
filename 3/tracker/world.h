#include <string>
#include "ioManager.h"
#include "frame.h"
#include "viewport.h"

class World {
public:
  World(const std::string& name, int fact);
  // ~World() { ; } // The frame will be deleted by the FrameFactory
  void update();
  void draw() const;
  unsigned int getWorldWidth(){ return worldWidth;}
  unsigned int getWorldHeight(){ return worldHeight;}
private:
  const IOManager& io;
  SDL_Surface* const surface;
  Frame* frame;
  int factor;
  unsigned frameWidth;
  unsigned frameHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  float viewX;
  float viewY;
  const Viewport & view;
  World(const World&);
  World& operator=(const World&);
};
