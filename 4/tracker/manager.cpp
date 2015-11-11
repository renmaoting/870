#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "multisprite.h"
#include "twoWayMultisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "extractSurface.h"

Manager::~Manager() { 
  std::vector<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
  
  std::vector<Drawable*>::const_iterator ptrB = bubbleSprites.begin();
  while ( ptrB !=bubbleSprites.end() ) {
    delete (*ptrB);
    ++ptrB;
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("superbg", Gamedata::getInstance().getXmlInt("superbg/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("fish10")),

  sprites(),
  bubbleSprites(),
  currentSprite(),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);

  sprites.push_back(player);
  sprites.push_back( new MultiSprite("fish7"));
  sprites.push_back( new TwoWayMultiSprite("fish1"));
  sprites.push_back( new TwoWayMultiSprite("fish1"));
  sprites.push_back( new TwoWayMultiSprite("fish1"));
  sprites.push_back( new TwoWayMultiSprite("fish1"));
  sprites.push_back( new TwoWayMultiSprite("fish4"));
  sprites.push_back( new TwoWayMultiSprite("fish4"));
  sprites.push_back( new TwoWayMultiSprite("fish4"));
  sprites.push_back( new TwoWayMultiSprite("fish5"));
  sprites.push_back( new TwoWayMultiSprite("fish5"));
  //sprites.push_back( new TwoWayMultiSprite("fish10"));
  
  // create another vector, and put the bubble in the vector
  // so that we don't track them
  for(int i =0; i< 300; i++)
  {
    Sprite* temp = new Sprite("bubble");
    temp->X( rand()% world.getWorldWidth() );
    temp->Y( rand() % world.getWorldHeight());  
    temp->velocityY( temp->velocityY() + rand()%80); 
    bubbleSprites.push_back(temp);
  }
  currentSprite = sprites.begin();
  viewport.setObjectToTrack(*currentSprite);
}

void Manager::draw() const {
  world.draw();
  clock.draw();
  std::vector<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }

  // draw the bubbles
  std::vector<Drawable*>::const_iterator ptrP = bubbleSprites.begin();
  while ( ptrP != bubbleSprites.end() ) {
    (*ptrP)->draw();
    ++ptrP;
  }

  io.printMessageAt("Press T to switch sprites", 10, 70);
  io.printMessageAt(title, 10, 600);
  viewport.draw();

  SDL_Flip(screen);
}

// Move this to IOManager
void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  ++currentSprite;
  if ( currentSprite == sprites.end() ) {
    currentSprite = sprites.begin();
  }
  viewport.setObjectToTrack(*currentSprite);
}

void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();

  std::vector<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }

  // update the bubbles
  std::vector<Drawable*>::const_iterator ptrP = bubbleSprites.begin();
  while ( ptrP != bubbleSprites.end() ) {
    (*ptrP)->update(ticks);
    ++ptrP;
  }

  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  world.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  clock.start();

  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_t] ) {
          switchSprite();
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_s]) {
           player->setVelocity(Vector2f(player->velocityX(),100)); 
        }

        if (keystate[SDLK_a]) {
           player->setVelocity(Vector2f(-100,player->velocityY())); 
           player->setDirection(false);
        }
        if (keystate[SDLK_d]) {
           player->setVelocity(Vector2f(100,player->velocityY())); 
           player->setDirection(true);
        }
        if (keystate[SDLK_w]) {
           player->setVelocity(Vector2f(player->velocityX(),-100)); 

        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
      }
      if(event.type == SDL_KEYUP) {
        if (keystate[SDLK_s] == false && keystate[SDLK_w] == false) {
           player->setVelocity(Vector2f(player->velocityX(),0)); 
        }
        if (keystate[SDLK_a] == false && keystate[SDLK_d] == false) {
           player->setVelocity(Vector2f(0,player->velocityY())); 
        }
      }
    }
    draw();
    update();
  }  
}
