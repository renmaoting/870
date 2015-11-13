/*************************************************************************
	> File Name: /home/mren/870/4/hud.c
	> Author:Maoting Ren 
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 11 Nov 2015 07:26:59 PM EST
 ************************************************************************/

#include "hud.h" 
#include "ioManager.h"
#include "gamedata.h"

Hud::Hud():
    screen(IOManager::getInstance().getScreen()),
    HUD_HEIGHT(Gamedata::getInstance().getXmlInt("hud/height")),
    HUD_WIDTH( Gamedata::getInstance().getXmlInt("hud/width")),
    x(Gamedata::getInstance().getXmlInt("hud/startLoc/x")),
    y(Gamedata::getInstance().getXmlInt("hud/startLoc/y")),
    interval(Gamedata::getInstance().getXmlInt("hud/interval")),
    hudTime(0),
    showHud(false),
    existTime(Gamedata::getInstance().getXmlInt("hud/existTime"))
{
}

void Hud::drawHud()
{
    const Uint32 col = SDL_MapRGB(screen->format, 
            Gamedata::getInstance().getXmlInt("hud/red"),
            Gamedata::getInstance().getXmlInt("hud/green"),
            Gamedata::getInstance().getXmlInt("hud/blue"));
    Draw_AALine(screen, x, y +HUD_HEIGHT/2,
            x + HUD_WIDTH, y+ HUD_HEIGHT/2,
            HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
    Draw_AALine(screen, x, y, x + HUD_WIDTH, y, 3, col);
    Draw_AALine(screen, x, y, x , y + HUD_HEIGHT, 3, col);
    Draw_AALine(screen, x + HUD_WIDTH, y ,x + HUD_WIDTH, y + HUD_HEIGHT, 3, col);
    Draw_AALine(screen, x, y + HUD_HEIGHT, x + HUD_WIDTH, y + HUD_HEIGHT, 3, col);

    IOManager::getInstance().
        printMessageValueAt("Sec: ",Clock::getInstance().getSeconds(), 2*x, 2*y);
    IOManager::getInstance().
        printMessageValueAt("FPS: ", Clock::getInstance().getFps(), 2*x, 2*y + interval);
    IOManager::getInstance().printMessageAt("A:  Move left", 2*x, 2*y + 2*interval);
    IOManager::getInstance().printMessageAt("D:  Move right", 2*x, 2*y + 3*interval);
    IOManager::getInstance().printMessageAt("W:  Move up", 2*x, 2*y + 4*interval);
    IOManager::getInstance().printMessageAt("S:  Move down", 2*x, 2*y + 5*interval);
}

void Hud::draw()
{
   if(hudTime <= existTime || showHud == true) 
   {
        drawHud();
   }
}

void Hud::update( Uint32 ticks)
{
    hudTime += ticks;
}

void Hud::setShow(bool show)
{
    showHud = show;
}











