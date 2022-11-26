//
//  playerobject.h
//  
//
//  Created by Ryan Hoole on 6/5/15.
//
//

#ifndef ____playerobject__
#define ____playerobject__

#include "charobject.h"

class PlayerObject : public CharObject
{
public:
    PlayerObject();
    virtual void setUpBullet(int mass = 10);
    virtual void stepPhysicSimulation();
    virtual void setID(int _id);
    virtual int getID();
    virtual void setRotation(vector3df rot = vector3df(0,0,0));
    virtual vector3df getRotation();
    virtual void faceTarget(vector3df target);
    
private:
};

#endif /* defined(____playerobject__) */
