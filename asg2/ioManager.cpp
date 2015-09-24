#include <iostream>
#include <iomanip>
#include "ioManager.h"
using std::string;

IOManager* IOManager::getInstance() {
  static IOManager* instance = NULL;
  if ( !instance ) instance = new IOManager;
  return instance;
}

IOManager::IOManager( ) :
  gdata( Gamedata::getInstance() ),
  viewWidth( gdata->getXmlInt("view/width") ),
  viewHeight( gdata->getXmlInt("view/height") ),
  MAX_STRING_SIZE( gdata->getXmlInt("maxStringSize") ),
    // The 3rd and 4th parameters are just as important as the first 2!
    screen(SDL_SetVideoMode(viewWidth, viewHeight, 32, SDL_DOUBLEBUF)),
    font( NULL ), 
    color(),
    title( gdata->getXmlStr("screenTitle") ),
    inputString()  
{
  if (screen == NULL) { 
    throw string("Unable to set video mode; screen is NULL in IOMAnager"); 
  }
  if ( TTF_Init() == -1 ) {
    throw string("TTF_Init failed: ") + TTF_GetError();
  }
  font = TTF_OpenFont(
         gdata->getXmlStr("font/file").c_str(), 
         gdata->getXmlInt("font/size")
         );
  if ( !font ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  color.r = gdata->getXmlInt("font/red");
  color.g = gdata->getXmlInt("font/green");
  color.b = gdata->getXmlInt("font/blue");
  color.unused = gdata->getXmlInt("font/unused");
  SDL_EnableUNICODE( SDL_ENABLE );
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(TTF_Quit);
}

SDL_Surface* IOManager::loadAndSet(const string& filename, bool setcolorkey) const {
  SDL_Surface *tmp = IMG_Load(filename.c_str());
  if (tmp == NULL) {
    throw string("Unable to load bitmap ")+filename;
  }
  if ( setcolorkey ) {
    Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 0, 255);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  // Optimize the strip for fast display
  SDL_Surface *image = SDL_DisplayFormatAlpha(tmp);
  if (image == NULL) {
    image = tmp;
  } 
  else {
    SDL_FreeSurface(tmp);
  }
  return image;
}

void IOManager::printMessageAt(const string& msg, Sint16 x, Sint16 y) const {
   Uint16 zero = 0;
   SDL_Rect dest = {x,y,zero,zero};
   SDL_Surface * stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageAt");
   }
}

void IOManager::printMessageCenteredAt( const string& msg, Sint16 y) const {
   SDL_Surface *stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     Sint16 x = ( viewWidth - stext->w ) / 2;
     Uint16 zero = 0;
     SDL_Rect dest = {x,y,zero,zero};
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageCenteredAt");
   }
}

void IOManager::printStringAfterMessage( const string& msg,
       Sint16 x, Sint16 y ) const {
   printMessageAt(msg+inputString, x, y);
}

void IOManager::buildString(SDL_Event event) {
  if( inputString.size() <= MAX_STRING_SIZE) {
    unsigned ch = event.key.keysym.sym;
    if ( isalpha(ch) || isdigit(ch) || ch == ' ') {
      inputString += char(event.key.keysym.unicode);
    }
  }     
  if( event.key.keysym.sym == SDLK_BACKSPACE
      && inputString.length() > 0 ) {
      // remove a character from the end
      int length = inputString.size();
      inputString.erase( length - 1 );
  }
}

template <typename T>
void IOManager::printMessageValueAt(const string& msg, T value, 
     Sint16 x, Sint16 y) const {
   std::stringstream strm;
   std::string message = msg;
   strm << message << value << "\0";
   message = strm.str();
   Uint16 zero = 0;
   SDL_Rect dest = {x,y,zero,zero};
   SDL_Surface *stext = 
       TTF_RenderText_Blended(font, message.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageValueAt");
   }
}

template void IOManager::
printMessageValueAt(const string& msg, unsigned long, Sint16, Sint16) const;

template void IOManager::
printMessageValueAt(const string& msg, float, Sint16, Sint16) const;

template void IOManager::
printMessageValueAt(const string& msg, unsigned, Sint16, Sint16) const;

template void IOManager::
printMessageValueAt(const string& msg, int, Sint16, Sint16) const;
