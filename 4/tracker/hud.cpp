/*************************************************************************
	> File Name: /home/mren/870/4/hud.c
	> Author:Maoting Ren 
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 11 Nov 2015 07:26:59 PM EST
 ************************************************************************/

#include "hud.h" 
#include "ioManager.h"
#include "gamedata.h"
#include "clock.h"

Hud::Hud():HUD_HEIGHT(300),
    HUD_WIDTH(200)
{
}

void Hud::drawHud(SDL_Surface* screen, int x, int y )
{
    const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
    Draw_AALine(screen, x, y +HUD_HEIGHT/2,
            x + HUD_WIDTH, y+ HUD_HEIGHT/2,
            HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
    Draw_AALine(screen, x, y, x + HUD_WIDTH, y, 3, RED);
    Draw_AALine(screen, x, y, x , y + HUD_HEIGHT, 3, RED);
    Draw_AALine(screen, x + HUD_WIDTH, y ,x + HUD_WIDTH, y + HUD_HEIGHT, 3, RED);
    Draw_AALine(screen, x, y + HUD_HEIGHT, x + HUD_WIDTH, y + HUD_HEIGHT, 3, RED);
    //IOManager::getInstance().printMessageValueAt
    IOManager::getInstance().
        printMessageValueAt("Sec: ",Clock::getInstance().getSeconds(), x+10, y+10);
    IOManager::getInstance().
        printMessageValueAt("FPS: ", Clock::getInstance().getFps(), x +10, y+40);
    IOManager::getInstance().printMessageAt("use a to left", x + 10, y + 70);
    IOManager::getInstance().printMessageAt("use d to right", x + 10, y + 100);
    IOManager::getInstance().printMessageAt("use w to up", x + 10, y + 130);
    IOManager::getInstance().printMessageAt("use s to down", x + 10, y + 160);
}

void Hud::setHudSize(int w, int h)
{
    HUD_WIDTH = w;
    HUD_HEIGHT = h;
}

