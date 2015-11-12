#include <iostream>
#include "frameFactory.h"
#include "world.h"

World::World(const std::vector<std::string>& name, const std::vector<int>& fact) : 
//  io( IOManager::getInstance() ),
  //surface( io.loadAndSet(
  //  Gamedata::getInstance().getXmlStr(name + "/file"), 
  //  Gamedata::getInstance().getXmlBool(name +"/transparency")) ),
  //frame( new Frame(name, surface) ),
  frame(),
  factor(),
    frameWidth(),
    frameHeight(),
    worldWidth( Gamedata::getInstance().getXmlInt("world/width")),
    worldHeight( Gamedata::getInstance().getXmlInt("world/height") ),
    viewX(0.0), viewY(0.0), 
    view(Viewport::getInstance()) 
{
    for(unsigned int i =0; i< name.size(); i++)
    {
        frame.push_back(FrameFactory::getInstance().getFrame(name[i]));
        factor.push_back(fact[i]); 
        frameWidth.push_back(frame[i]->getWidth());
        frameHeight.push_back(frame[i]->getHeight());
        viewX.push_back(0.0);
        viewY.push_back(0.0);
    }
}

void World::update() {
    for(unsigned int i =0; i< frame.size(); i++)
    {
        viewX[i] = static_cast<int>(view.X() / factor[i]) % frameWidth[i];
        viewY[i] = static_cast<int>(view.Y() / factor[i]) % frameHeight[i];
    }
}

void World::draw(int i) const { 
    frame[i]->draw(viewX[i], viewY[i], 0, 0);// draw picture's pos(viewX, viewY) to the view's pos(0, 0) 
  //frame->draw(0, viewY, frameWidth-viewX, 0); 
  //frame->draw(viewX, 0, 0, frameHeight - viewY); 
  //frame->draw(0, 0, frameWidth-viewX, frameHeight - viewY); 
}









