#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "collisionStrategy.h"

class ExplodingSprite;
class TwoWayMultiSprite : public Drawable {
public:
  TwoWayMultiSprite(const std::string&);
 
  virtual ~TwoWayMultiSprite(); 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual void setDirection(bool Right){ right = Right;}
  virtual int getDirection(){ return right== true?1:(-1);}
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  bool collidedWith(const Drawable* d) const {
    return strategy->execute(*this, *d);
  }
  void setCollisionStrategy(int index) {
    strategy = strategies[index];
  }
  virtual float getScale()const{ return scale;}
  void explode();
  virtual void reset();

protected:
  ExplodingSprite* explosion;
  std::vector<CollisionStrategy*> strategies;
  CollisionStrategy * strategy;
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
  int scale;

  void advanceFrame(Uint32 ticks);
  TwoWayMultiSprite(const TwoWayMultiSprite&);
  TwoWayMultiSprite& operator=(const TwoWayMultiSprite&);
  int getDistance(const TwoWayMultiSprite*) const;
};
#endif
