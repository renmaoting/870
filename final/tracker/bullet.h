/*************************************************************************
	> File Name: bullet.h
	> Author: Maoting Ren
	> Mail: mren@g.clemson.edu
	> Created Time: Sat 21 Nov 2015 08:28:38 PM EST
 ************************************************************************/

#ifndef _BULLET_H
#define _BULLET_H

#include "drawable.h"
#include "frameFactory.h"
#include "chunk.h"

class Bullet:public Chunk 
{
public:
    Bullet(const Vector2f& pos, const Vector2f& vel, const std::string& name):
        Chunk(pos, vel, name, FrameFactory::getInstance().getFrame(name))
    {}
};
#endif
