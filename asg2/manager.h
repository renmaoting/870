#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "sprite.h"
#include <vector>
#include <time.h>

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const IOManager* io;
  Clock& clock;

  SDL_Surface * const screen;
  SDL_Surface * bgscreen;

  SDL_Surface* orbSurface;
  const Frame * const orbFrame;
  std::vector<Sprite> spriteVec;

  bool makeVideo;
  int frameCount;
  std::string username;
  int frameMax;
  const std::string TITLE;
  int ballCount;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void drawBackground() const;
};
