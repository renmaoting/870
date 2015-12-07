#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "collisionStrategy.h"

class ExplodingSprite;
class Sprite : public Drawable {
public:
  Sprite(const std::string&);
  Sprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
  Sprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  Sprite(const Sprite& s);
  virtual ~Sprite(){ }
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;

  bool collidedWith(const Drawable* d) const {
    return strategy.execute(*this, *d);
  }
  void setCollisionStrategy(int index) {
    std::cout <<index <<  " Sprite::setCollisionStrategy() have been deleted" << std::endl;
  }

  virtual void update(Uint32 ticks);
  void explode();

private:
  ExplodingSprite* explosion;
  MidPointCollisionStrategy strategy; 
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Sprite*) const;
};
#endif
