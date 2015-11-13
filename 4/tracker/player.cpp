#include "player.h"
#include <vector>
#include "ioManager.h"
#include "extractSurface.h"
#include "frameFactory.h"
#include "gamedata.h"

Player::Player( const std::string& name) :
    TwoWayMultiSprite(name)
{ 
    setVelocity(Vector2f(0,0));
    X(worldWidth/3);
    Y(worldHeight/3);
}

void Player::goLeft()
{
    velocityX(-200);
    setDirection(false);
}

void Player::goRight()
{
    setDirection(true);
    velocityX(200);
}

void Player::goUp()
{
    velocityY(-200);
}

void Player::goDown()
{
    velocityY(200);
}

void Player::stop()
{
    setVelocity(Vector2f(0,0));
}

void Player::update(Uint32 ticks) { 
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if ( Y() < 0) {
    velocityY( abs( 0 ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( 0 ) );
  }

  if ( X() < 0) {
    velocityX( abs(0) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs(0  ) );
  }  
}
