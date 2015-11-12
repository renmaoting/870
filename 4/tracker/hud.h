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

class Hud
{
public:
    Hud();
    ~Hud(){ };
    void drawHud(SDL_Surface* screen, int x, int y );
    void setHudSize(int w, int h);

private:
    int HUD_HEIGHT;
    int HUD_WIDTH;
};

#endif
