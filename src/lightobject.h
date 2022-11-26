//
//  lightobject.h
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#ifndef ____lightobject__
#define ____lightobject__

#include "gobject.h"

class LightObject : public GObject
{
public:
    explicit LightObject();
    void setRadius(f32 radius);
    f32 getRadius();
    void setPos(vector3df pos);
    vector3df getPos();
    ILightSceneNode* getLightNode();
    void setLightNode(ILightSceneNode* node);
    
private:
    ILightSceneNode* light_node;
};

#endif /* defined(____lightobject__) */
