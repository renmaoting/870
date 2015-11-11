#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "drawable.h"

class Player : public Drawable {
public:
  Player (const std::string&);
  virtual ~Player () { } 

  void setDirection(bool flag){ right = flag; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  const std::vector<Frame *> frames;
  std::vector<Frame*> starFrames;
  std::string frameName;
  int worldWidth;
  int worldHeight;
  bool right;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  Player (const Player &);
  Player & operator=(const Player &);
};
#endif
