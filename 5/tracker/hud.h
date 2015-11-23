/*************************************************************************
	> File Name: hud.h
	> Author:Maoting Ren 
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 11 Nov 2015 07:20:40 PM EST
 ************************************************************************/

#ifndef _HUD_H
#define _HUD_H

#include "aaline.h"
#include <SDL.h>
#include "clock.h"

class Hud
{
public:
    Hud();
    Hud(Hud&);
    Hud operator=(const Hud&);
    ~Hud(){ };
    void drawHud(Uint32 liveNum, Uint32 freeNum);
    void draw(Uint32 liveNum, Uint32 freeNum);
    void update( Uint32 ticks);
    void setShow(bool show);

private:
    SDL_Surface* screen;
    int HUD_HEIGHT;
    int HUD_WIDTH;
    int x;
    int y;
    int interval;
    int hudTime;
    bool showHud;
    int existTime;
};

#endif
