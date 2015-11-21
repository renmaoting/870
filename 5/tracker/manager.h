#ifndef _MANAGER_H
#define _MANAGER_H

#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "hud.h"
#include "sound.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();
  bool checkForCollisions() const; 

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World* world;
  Viewport& viewport;
  Player* player;

  std::vector<Drawable*> sprites;
  std::vector<Drawable*> bubbleSprites;

  bool makeVideo;
  int frameCount;
  const std::string title;
  const std::string username;
  const int frameMax;
  bool showHud;
  Hud* hud;
  SDLSound sound;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
#endif
