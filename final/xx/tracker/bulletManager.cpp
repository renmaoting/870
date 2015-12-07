/*************************************************************************
	> File Name: bulletManager.cpp
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Sat 21 Nov 2015 10:16:28 PM EST
 ************************************************************************/

#include "bulletManager.h"
#include "gamedata.h"

BulletManager::BulletManager(const std::string& n):
    name(n),
    bulletList(),
    freeList(),
    vel(Gamedata::getInstance().getXmlInt(name + "/speedX"),
        Gamedata::getInstance().getXmlInt(name + "/speedY") ),
    liveNum(0),
    freeNum(0)
{}

BulletManager::~BulletManager()
{
    reset();
}

void BulletManager::reset()
{
    std::list<Bullet*>::iterator ptr = bulletList.begin();
    while(ptr != bulletList.end())
    {
        delete (*ptr);
        ptr = bulletList.erase(ptr);
    }
    
    ptr = freeList.begin();
    while(ptr != freeList.end())
    {
        delete (*ptr);
        ptr = bulletList.erase(ptr);
    }
    liveNum = 0;
    freeNum = 0;
}

void BulletManager::shoot(const Vector2f& pos, int direction)
{
    if(freeList.empty())
    {
        Bullet *b = new Bullet(pos,-1* vel* direction, name);
        bulletList.push_back(b);
    } 
    else
    {
        Bullet *b = freeList.front();
        freeList.pop_front();
        b->reset();
        b->setPosition(pos);
        b->setVelocity(-1* vel* direction);
        bulletList.push_back(b); 
    }
}

void BulletManager::draw()
{
    std::list<Bullet*>::iterator ptr = bulletList.begin();
    while(ptr != bulletList.end())
    {
        (*ptr)->draw();
        ptr++;
    }
}

void BulletManager::update(Uint32 ticks)
{
    std::list<Bullet*>::iterator ptr = bulletList.begin();
    while(ptr != bulletList.end())
    {
        (*ptr)->update(ticks);
        if((*ptr)->goneTooFar())
        {
            //std::cout << "go far" << std::endl;
            freeList.push_back(*ptr);
            ptr = bulletList.erase(ptr);
        }
        else
            ptr++;
    }
    liveNum = bulletList.size();
    freeNum = freeList.size();
}


