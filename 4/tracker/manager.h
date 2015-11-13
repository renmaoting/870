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

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

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
  std::vector<Drawable*>::iterator currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string title;
  const std::string username;
  const int frameMax;
  bool showHud;
  Hud* hud;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
#endif
