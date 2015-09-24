#include <iostream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include <cmath>
#include <SDL_image.h>

Manager::~Manager() { 
  // Manager made it, so Manager needs to delete it
  SDL_FreeSurface(orbSurface);
  SDL_FreeSurface(bgscreen);
  delete orbFrame;
  delete IOManager::getInstance();
  delete Gamedata::getInstance();
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io->getScreen() ),
  bgscreen( io->loadAndSet(
    Gamedata::getInstance()->getXmlStr("bg/file"), 
    Gamedata::getInstance()->getXmlBool("bg/transparency")) ),

  orbSurface( io->loadAndSet(
    Gamedata::getInstance()->getXmlStr("greenorb/file"), 
    Gamedata::getInstance()->getXmlBool("greenorb/transparency")) ),
  orbFrame( new Frame("greenorb", orbSurface) ),
  spriteVec(),
  
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance()->getXmlStr("username") ),
  frameMax( Gamedata::getInstance()->getXmlInt("frameMax") ),
  TITLE( Gamedata::getInstance()->getXmlStr("screenTitle") ),
  ballCount(Gamedata::getInstance()->getXmlInt("ballCount"))
{
  spriteVec.reserve(ballCount);
  for(unsigned int i =0; i< spriteVec.capacity(); i++)
    spriteVec.push_back(Sprite("greenorb", orbFrame));
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
}

void Manager::drawBackground() const {
  //SDL_FillRect( screen, NULL, 
    //SDL_MapRGB(screen->format, backRed, backGreen, backBlue) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( bgscreen, NULL, screen, &dest );
}

void Manager::draw() const {
  drawBackground();
  for(unsigned int i = 0; i< spriteVec.size(); i++)
    spriteVec[i].draw();
  clock.draw();
  SDL_Flip(screen);
}

void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();
  for(unsigned int i = 0; i< spriteVec.size(); i++)
    spriteVec[i].update(ticks);
  

  if ( makeVideo && frameCount < frameMax ) {
    std::stringstream strm;
    strm << "frames/" << username<< '.' 
         << std::setfill('0') << std::setw(4) 
         << frameCount++ << ".bmp";
    std::string filename( strm.str() );
    std::cout << "Making frame: " << filename << std::endl;
    SDL_SaveBMP(screen, filename.c_str());
  }
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  while ( not done ) {

    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if (event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }

        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        if (keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if(keystate[SDLK_s]){
            clock.toggleSloMo();
        }
      }
    }

    draw();
    update();
  }
}
