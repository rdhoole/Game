//
//  cameraobject.h
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#ifndef ____cameraobject__
#define ____cameraobject__

#include "gobject.h"

class CameraObject : public GObject
{
public:
    CameraObject();
    ICameraSceneNode* getCameraNode();
    void getIrrNode() {}
    void setCameraNode(ICameraSceneNode* node);
    
    vector3df getPos();
    vector3df getAbsPos();

    void setPos(vector3df pos = vector3df(0,0,0));
    void setAbsPos(vector3df pos = vector3df(0,0,0));
    void setTarget(vector3df pos = vector3df(0,0,0));
    void setTarget(int obj, int id);
    int getTargetObject();
    int getTargetID();
    
    void setID(s32 _id);
    s32 getID();
    
private:
    ICameraSceneNode* camera_node;
    s32 camera_id;
    
    int targetObj;
    int targetID;
    
};

#endif /* defined(____cameraobject__) */
