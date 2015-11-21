#include "twoWayMultisprite.h"
#include <vector>
#include "ioManager.h"
#include "extractSurface.h"
#include "frameFactory.h"
#include "gamedata.h"
#include <cmath> 
#include "explodingSprite.h"

void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
        if(right == true)
            currentFrame = (currentFrame+1) % (numberOfFrames/2);
        else
            currentFrame = (currentFrame+1) % (numberOfFrames/2) + numberOfFrames/2;
		timeSinceLastFrame = 0;
	}
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX") + rand()%30,
                    Gamedata::getInstance().getXmlInt(name+"/speedY") + rand()%30)
           ),
  explosion(NULL),
  strategies(),
  strategy( NULL ),
  frames( FrameFactory::getInstance().getFrames(name)),
  starFrames(),
  frameName(name),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  right(true),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  scale(Gamedata::getInstance().getXmlInt(name+"/scale"))
{ 
    X( worldWidth/3 + sin(rand()%300)  );
    Y(rand()% worldHeight);
    strategies.push_back( new MidPointCollisionStrategy );
    strategies.push_back( new RectangularCollisionStrategy );
    strategies.push_back( new PerPixelCollisionStrategy );
    strategy = strategies[0];
}

void TwoWayMultiSprite::draw() const { 
  if (explosion) {
    explosion->draw();
    return;
  }

  //std::cout << "MultiSprite" <<std::endl;
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void TwoWayMultiSprite::explode() { 
  if ( explosion ) return;
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite); 
}

void TwoWayMultiSprite::update(Uint32 ticks) { 
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }

  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
    right = true;
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
    right = false;
  }  
}

