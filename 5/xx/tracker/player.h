#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "drawable.h"
#include "twoWayMultisprite.h"

class Player : public TwoWayMultiSprite{
public:
  Player (const std::string&);
  virtual ~Player () { } 
//  void setDirection(bool flag){ right = flag; }
  virtual void update(Uint32 ticks); 
  void goLeft();
  void goRight();
  void goUp();
  void goDown();
  void stop();
  void reset();
  bool ifDelete() {return false;}

protected:
  Player (const Player &);
  Player & operator=(const Player &);
};
#endif
