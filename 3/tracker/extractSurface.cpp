#include <SDL.h>
#include "extractSurface.h"

ExtractSurface& ExtractSurface::getInstance() {
  static ExtractSurface instance;
  return instance;
}

SDL_Surface* 
ExtractSurface::get(SDL_Surface* source, int frameWidth, int frameHeight,
  int topX, int topY) const {
  SDL_Surface * croppedSurface = SDL_CreateRGBSurface(
    SDL_SWSURFACE | SDL_SRCALPHA, 
		frameWidth, frameHeight, 
		source->format->BitsPerPixel, 
		source->format->Rmask, 
		source->format->Gmask, 
		source->format->Bmask, 
		source->format->Amask 
  );

  SDL_LockSurface(croppedSurface);
  SDL_LockSurface(source); 
  int targetX = 0;
  int targetY = 0;
  for (int x = topX; x < topX+frameWidth; ++x) {
    for (int y = topY; y < frameHeight+topY; ++y) {
      putpixel(croppedSurface, targetX, targetY, getpixel(source, x, y));
      targetY++;
    }
    targetY=0;
    ++targetX;
  }
  SDL_UnlockSurface(croppedSurface);
  SDL_UnlockSurface(source);
				
	return croppedSurface;
}

Uint32 ExtractSurface::getpixel(SDL_Surface *surface, int x, int y) const {
  int bpp = surface->format->BytesPerPixel;
  // Here p is the address to the pixel we want to retrieve
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
    case 1: return *p;
    case 2: return *(Uint16 *)p;
    case 3: {
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    }
    case 4: return *(Uint32 *)p;
    default: return 0;       // shouldn't happen, but avoids warnings
  }
}

void ExtractSurface::putpixel(SDL_Surface *surface, 
     int x, int y, Uint32 pixel) const {
  int bpp = surface->format->BytesPerPixel;
  // Here p is the address to the pixel we want to set
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch(bpp) {
    case 1: {
      *p = pixel;
      break;
    }
    case 2: {
      *(Uint16 *)p = pixel;
      break;
    }
    case 3: {
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
    }
    case 4: {
      *(Uint32 *)p = pixel;
      break;
    }
  }
}

