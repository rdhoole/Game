//
//  envobject.h
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#ifndef ____envobject__
#define ____envobject__

#include "gobject.h"

class EnvObject : public GObject
{
public:
    EnvObject();
    void setIrrNode(IMeshSceneNode* node);
    void setUpBullet();
    vector3df getPos();
    
    virtual void setID(int _id);
    virtual int getID();
    virtual void remove();
    virtual void addShadow();
    virtual void normalizeNormals(bool nn);
    void setWireFrame(bool wf);

protected:
    IMeshSceneNode* irrlicht_node;
};

#endif /* defined(____envobject__) */
