/*************************************************************************
	> File Name: bulletManager.h
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Sat 21 Nov 2015 10:04:09 PM EST
 ************************************************************************/

#ifndef _BULLETMANAGER_H
#define _BULLETMANAGER_H

#include "vector2f.h"
#include "bullet.h"
#include <list>

class BulletManager
{
public:
    BulletManager(const std::string& n);
    ~BulletManager();
    void shoot(const Vector2f& pos, int direction);
    void reset();
    void draw();
    void update(Uint32 ticks);
    Uint32 getLiveNum() { return liveNum; }
    Uint32 getFreeNum() { return freeNum; }
    std::list<Bullet*>& getBulletList(){ return bulletList;}

private:
    std::string name;
    std::list<Bullet*> bulletList;
    std::list<Bullet*> freeList;
    Vector2f vel;
    Uint32 liveNum;
    Uint32 freeNum;

    BulletManager(const BulletManager& bm);
};
#endif
