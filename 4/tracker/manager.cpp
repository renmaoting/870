#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "vector2f.h"
#include "multisprite.h"
#include "twoWayMultisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "extractSurface.h"
#include "scaledSprite.h"
#include "hud.h"
#include "frameFactory.h"

class ScaledSpriteCompare {
public:
    bool operator()(const Drawable* lhs, const Drawable* rhs) {
        return lhs->getScale() < rhs->getScale();
    }
};

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
  delete hud;
  delete world;
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world(),
  viewport( Viewport::getInstance() ),
  player(new Player("fish10")),

  sprites(),
  bubbleSprites(),
  currentSprite(),

  makeVideo( false ),
  frameCount( 0 ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  username( Gamedata::getInstance().getXmlStr("username") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  showHud(false),
  hud(new Hud())
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);

  std::vector<std::string> name;
  name.push_back("superbg");
  name.push_back("hill");
  std::vector<int> factor;
  factor.push_back(Gamedata::getInstance().getXmlInt("superbg/factor"));
  factor.push_back(Gamedata::getInstance().getXmlInt("hill/factor"));
  world = new World(name, factor);

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

  // create another vector, and put the bubble in the vector
  int cnt = Gamedata::getInstance().getXmlInt("bubble/number");
  for(int i =0; i< cnt; i++)
  {
    ScaledSprite* temp = new ScaledSprite("bubble");
    bubbleSprites.push_back(temp);
  }
  sort(bubbleSprites.begin(), bubbleSprites.end(), ScaledSpriteCompare());

  currentSprite = sprites.begin();
  viewport.setObjectToTrack(*currentSprite);
}

void Manager::draw() const {
  world->draw(0);

  // draw the bubbles
  std::vector<Drawable*>::const_iterator ptrP = bubbleSprites.begin();
  while ( ptrP != bubbleSprites.end() ) {
    if((*ptrP)->getScale() < 1.0)
        (*ptrP)->draw();
    else
        break;
    ++ptrP;
  }
  std::vector<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    if((*ptr)->getScale() <= 5)
        (*ptr)->draw();
    ++ptr;
  }


  world->draw(1);
  while(ptrP != bubbleSprites.end())
  {
    (*ptrP)->draw();
    ++ptrP;
  }

  ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    if((*ptr)->getScale() > 5)
        (*ptr)->draw();
    ++ptr;
  }

  io.printMessageCenteredAt(title, 10);
  viewport.draw();
  hud->draw();

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
  hud->update(ticks);
  
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
  world->update();
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

        if (keystate[SDLK_s] && keystate[SDLK_w]) {
            player->stop();
        }
        else if(keystate[SDLK_s])
        {
            player->goDown();
        }
        else if(keystate[SDLK_w])
        {
            player->goUp();
        }
        
        if (keystate[SDLK_a] && keystate[SDLK_d]) {
            player->stop();
        }
        else if(keystate[SDLK_a])
        {
            player->goLeft();
        }
        else if (keystate[SDLK_d]) {
           player->goRight();
        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        if (keystate[SDLK_F1]) {
            showHud = !showHud;
            hud->setShow(showHud);
        }

      }
      if(event.type == SDL_KEYUP) {
        if (keystate[SDLK_s] == false && keystate[SDLK_w] == false) {
           player->setVelocity(Vector2f(player->velocityX(),0)); 
        }
        else if (keystate[SDLK_s])
            player->goDown();
        else if(keystate[SDLK_w])
            player->goUp();

        if (keystate[SDLK_a] == false && keystate[SDLK_d] == false) {
           player->setVelocity(Vector2f(0,player->velocityY())); 
        }
        else if(keystate[SDLK_a])
        {
            player->goLeft();
        }
        else if(keystate[SDLK_d])
            player->goRight();
      }
    }
    draw();
    update();
  }  
}
