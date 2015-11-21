#include <cmath>
#include "drawable.h"

class CollisionStrategy {
public:
  virtual bool execute(const Drawable&, const Drawable&) const = 0;
  virtual void draw() const = 0;
  virtual ~CollisionStrategy() {}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
  virtual void draw() const;
};

class MidPointCollisionStrategy : public CollisionStrategy {
public:
  MidPointCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
  virtual void draw() const;
  float distance(float, float, float, float) const;
};

class PerPixelCollisionStrategy : public CollisionStrategy {
public:
  PerPixelCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
  virtual void draw() const;
private:
  bool isVisible(Uint32, SDL_Surface*) const;
};

