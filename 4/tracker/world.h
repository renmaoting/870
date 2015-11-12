#include <string>
#include <vector>
#include "ioManager.h"
#include "frame.h"
#include "viewport.h"

class World {
public:
  World(const std::vector<std::string>& name, const std::vector<int>& fact); 
  //World(const std::string& name, int fact);
  // ~World() { ; } // The frame will be deleted by the FrameFactory
  void update();
  void draw(int i) const;
  unsigned int getWorldWidth(){ return worldWidth;}
  unsigned int getWorldHeight(){ return worldHeight;}
private:
  std::vector<Frame*> frame;
  std::vector<int> factor;
  std::vector<unsigned> frameWidth;
  std::vector<unsigned> frameHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  std::vector<float> viewX;
  std::vector<float> viewY;
  const Viewport & view;
  World(const World&);
  World& operator=(const World&);
};
