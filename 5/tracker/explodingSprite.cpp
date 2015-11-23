#include <iostream>
#include <cmath>
#include "explodingSprite.h"

ExplodingSprite::ExplodingSprite(const Sprite& s) :
  Sprite(s), 
  chunks(), 
  freeList(),
  frames() {
  makeChunks(
    Gamedata::getInstance().getXmlInt(s.getName()+"/chunk/size")
  );
}

ExplodingSprite::~ExplodingSprite() { 
  for ( unsigned int i = 0; i < frames.size(); ++i ) {
    delete frames[i]; // ExplodingSprite made them, so it deletes them
  }

  chunks.clear();     // clearing a vector is a waste of time, but ...
  freeList.clear();   // still ...
}

void ExplodingSprite::draw() const { 
  // Override draw; use the draw in Chunk, which derives from Sprite.
  // So the draw we're using is actually in Sprite
  std::list<Chunk>::const_iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->draw();
    ++ptr;
  }
}

void ExplodingSprite::update(Uint32 ticks) { 
  std::list<Chunk>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {  // Check to see if we should free a chunk
      freeList.push_back(*ptr);
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
  }
}

void ExplodingSprite::makeChunks(unsigned int n) { 
  // Break the SDL_Surface into n*n squares; where each square
  // has width and height of frameWidth/n and frameHeight/n
  unsigned int chunk_width = std::max(1u, getFrame()->getWidth()/n);
  unsigned int chunk_height = std::max(1u, getFrame()->getHeight()/n);
  int speedx = static_cast<int>(velocityX()); // Wanna test for zero...
  int speedy = static_cast<int>(velocityY()); // Make sure it's an int.
  if (speedx == 0) speedx = 1; // Make sure it's not 0;
  if (speedy == 0) speedy = 1; // Make sure it's not 0;

  std::cout << "make chunk!" << std::endl;
  // Get the SDL_Surface so we can chunk it:
  SDL_Surface* spriteSurface(getFrame()->getSurface()); 
  Sint16 source_y = getFrame()->getSourceY();
  while  (source_y < getFrame()->getHeight() ) {
    Sint16 source_x = getFrame()->getSourceX();
    while ( source_x < getFrame()->getWidth() ) {
      // Give each chunk it's own speed/direction:
      float sx = (rand() % speedx + 40) * (rand()%2?-1:1); // 'cause %0 is 
      float sy = (rand() % speedy + 40) * (rand()%2?-1:1); // float except
      Frame* frame = 
            new Frame(spriteSurface, chunk_width, chunk_height,
                  source_x, source_y
                );
      Chunk chunk(
                Vector2f(X()+source_x,   // x coord of destination 
                         Y()+source_y), // y coord of destination
                Vector2f(sx, sy),
                getName()+"/chunk",
                frame);
      // chunks uses value semantics, as does frames, but there's
      // a big difference:
      chunks.push_back(chunk);
      frames.push_back(frame);
      source_x += chunk_width;
    }
    source_y += chunk_height;
  }
}

