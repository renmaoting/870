#include <string>
#include <vector>
#include <map>
#include "frame.h"
#include "gamedata.h"

// The FrameFactory makes frames and reads the corresponding SDL_Surface,
// storing the frames and their corresponding SDL_Surface (es) in maps. 
// The FrameFactory treats the Frame class as a Flyweight in the sense 
// that if you use the FrameFactory to make a frame you are assuming 
// that you will also reuse both the Frame and the corresponding 
// SDL_Surface.  The intent of this FrameFactory is to facilitate 
// efficient management of resources (i.e., both construction and 
// deletion) and that both the Frame and the SDL_Surface will be 
// available until the end of the animation.

class FrameFactory {
public:
  static FrameFactory& getInstance();
  ~FrameFactory();

  // The next constructor s/ only be used when the Frames's surface
  // starts at (0, 0) in the sprite sheet, and the frame uses the
  // entire sheet. For example, a Frame containing an orb or background.
  // The original surface is read from a file and stored in surfaces, 
  // and ExtractSurface is not used. This surface is passed to Frame.
  Frame* getFrame(const std::string&);

  // The next constructor is for a MultiSprite, a multi-frame sprite.
  // The sprite sheet surface is saved in the surfaces map, and
  // individual surfaces will be extracted, using ExtractSurface, from 
  // the sprite sheet surface and these individual surfaces will
  // be stored in the vector of Frames in multiframes.
  // Therefore, this constructor should be used when an individual
  // Frame's surface is found on only a part of sprite sheet. 
  // src_x and src_y are passed will be computed in getFrames and
  // passed as parameters to the Frame constructor, but the Frame
  // width and height will be obtained from the XML:
  std::vector<Frame*> getFrames(const std::string&);

private:
  const Gamedata& gdata;
  // The next map stores surfaces for single frame sprites:
  std::map<std::string, SDL_Surface*> surfaces;

  // The next map stores surfaces for Multi-frame sprites. The frames
  // will be extracted from the sprite sheet and stored in multiSurfaces:
  std::map<std::string, std::vector<SDL_Surface*> > multiSurfaces;

  // The next map stores Frames for single frame sprites:
  std::map<std::string, Frame*> frames;
  // The next map stores Frames for Multi-frame sprites:
  std::map<std::string, std::vector<Frame*> > multiFrames;

  FrameFactory() : 
    gdata( Gamedata::getInstance() ), 
    surfaces(),
    multiSurfaces(),
    frames(),
    multiFrames()
  {}
  FrameFactory(const FrameFactory&);
  FrameFactory& operator=(const FrameFactory&);
};
