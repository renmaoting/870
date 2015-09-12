#ifndef _GAME_H
#define _GAME_H

#include <string.h>
#include "source.h"
class Game
{
public:
    Game(const char* heroname):superman(new char[strlen(heroname)])
    {
        strcpy(superman, heroname);
    }
    Game(const Game& game):superman(new char[strlen(game.superman)])
    {
        superman= game.superman;
    }
    Game& operator=(const Game& game);
    int operator()();
    ~Game();
    
private:
    char* superman;
};
#endif
