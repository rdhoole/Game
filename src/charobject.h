//
//  charobject.h
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#ifndef ____charobject__
#define ____charobject__

#include <iostream>
#include "gobject.h"
#include <cmath>

class CharObject : public GObject
{
public:
    CharObject();
    virtual void setIrrNode(IAnimatedMeshSceneNode* node);
    virtual IAnimatedMeshSceneNode* getIrrNode();
    virtual void updateBullet();
    virtual void setUpBullet(int mass = 10, btVector3 inertia = btVector3(1,1,1), bool box = true);
    btRigidBody* getRigidBody();
    bool getCanDoPhysics();
    virtual void stepPhysicSimulation();
    virtual void addShadow();
    virtual void normalizeNormals(bool nn);
    virtual void setWireFrame(bool wf);
    virtual void remove();
    
    virtual void setID(int _id);
    virtual int getID();
    
    virtual void setRotation(vector3df rot = vector3df(0,0,0));
    virtual vector3df getRotation();
    
    virtual void faceTarget(vector3df target);
    
    IVideoDriver* m_driver;
    
    // game attributes
    int health;
    int score;
    
private:
    f32 distance(vector3df A, vector3df B) const;
protected:
    bool canDoPhysics;
    float deltaX, deltaY, deltaZ;
    float rad_y, deg_y, rad_x, deg_x;
};

#endif /* defined(____charobject__) */
