#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "explodingSprite.h"

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  virtual ~MultiSprite() ; 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  bool collidedWith(const Drawable* d) const {
    return strategy->execute(*this, *d);
  }
  void setCollisionStrategy(int index) {
    strategy = strategies[index];
  }

  virtual void reset();
  void explode();
  virtual bool ifDelete(){ return expFlag && !explosion;}
  bool getExplosion() { return expFlag;}

protected:
  ExplodingSprite* explosion;
  bool expFlag;
  std::vector<CollisionStrategy*> strategies;
  CollisionStrategy * strategy;
  const std::vector<Frame *> frames;
  std::vector<Frame*> starFrames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  MultiSprite(const MultiSprite&);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
