#include "multisprite.h"
#include <vector>
#include "ioManager.h"
#include "extractSurface.h"
#include "frameFactory.h"
#include "gamedata.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  explosion(NULL),
  expFlag(false),
  strategies(),
  strategy( NULL ),
  frames( FrameFactory::getInstance().getFrames(name)),
  starFrames(),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ 
    strategies.push_back( new MidPointCollisionStrategy );
    strategies.push_back( new RectangularCollisionStrategy );
    strategies.push_back( new PerPixelCollisionStrategy );
    strategy = strategies[0];
}

MultiSprite::~MultiSprite()
{
    for(Uint32 i = 0; i < strategies.size(); i++)
        delete strategies[i];
    if(explosion)
        delete explosion;
}

void MultiSprite::explode() { 
  expFlag = true;
  if ( explosion ) return;
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite); 
}

void MultiSprite::reset()
{
    setVelocity(Vector2f(Gamedata::getInstance().getXmlInt(getName()+"/speedX") + rand()%30,
        Gamedata::getInstance().getXmlInt(getName()+"/speedY") + rand()%30));
     
    X( rand() % worldWidth );
    Y(rand()% worldHeight);
    timeSinceLastFrame = 0;
}

void MultiSprite::draw() const { 
  if (explosion) {
    explosion->draw();
    return;
  }

  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void MultiSprite::update(Uint32 ticks) { 
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
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
