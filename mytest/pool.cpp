/*************************************************************************
	> File Name: pool.cpp
	> Author:Maoting Ren 
	> Mail: mren@g.clemson.edu
	> Created Time: Wed 18 Nov 2015 01:22:40 PM EST
 ************************************************************************/

#include<iostream>
#include<list>

class Bullet
{
    public:
        Bullet(int vel):velosity(vel){}
        inline void setVel(int vel){ velosity = vel;}
    private:
        int velosity;
};

std::list<Bullet*> freeList;
std::list<Bullet*> bulletList;

void shoot(int vel)
{
    if(freeList.empty())
    {
        Bullet* b = new Bullet(vel);
        bulletList.push_back(b);
        std::cout << "new one" << std::endl;
    }
    else
    {
        std::cout << "old one" << std::endl;
        Bullet* b = freeList.front();
        freeList.pop_front();
        b->setVel(vel);
        bulletList.push_back(b);
    }
}
int main()
{
    shoot(100);
    std::list<Bullet*>::iterator it; 
    for(it = bulletList.begin(); it != bulletList.end(); it++)
        delete *it;

    for(it = freeList.begin(); it != bulletList.end(); it++)
        delete *it;

    return 0;
}

