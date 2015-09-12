/*************************************************************************
	> File Name: Game.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 09 Sep 2015 01:50:56 AM EDT
 ************************************************************************/

#include "game.h"
#include <iostream>

int Game::operator()()
{
    std::cout<< superman <<" ";
    Source* instance;
    instance = Source::getInstance();
    return instance->getValue();
}

Game& Game::operator=(const Game& game)
{
    strcpy(superman, game.superman);
    return *this;
}

Game::~Game()
{
    delete[] superman;
}
