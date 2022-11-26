//
//  cameraobject.cpp
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#include "cameraobject.h"

CameraObject::CameraObject()
{
    objectType = 2;
    camera_id = 0;
    targetObj = -1;
    targetID = -1;
}

void CameraObject::setCameraNode(ICameraSceneNode* node)
{
    camera_node = node;
}

ICameraSceneNode* CameraObject::getCameraNode()
{
    return camera_node;
}

void CameraObject::setID(s32 _id)
{
    camera_id = _id;
}

s32 CameraObject::getID()
{
    return camera_id;
}

void CameraObject::setPos(vector3df pos)
{
    camera_node->setPosition(pos);
}

vector3df CameraObject::getAbsPos()
{
    return camera_node->getAbsolutePosition();
}

void CameraObject::setAbsPos(vector3df pos)
{
    camera_node->setPosition(pos - camera_node->getParent()->getAbsolutePosition());
}

vector3df CameraObject::getPos()
{
    return camera_node->getPosition();
}

void CameraObject::setTarget(vector3df pos)
{
    camera_node->setTarget(pos);
}

void CameraObject::setTarget(int obj, int id)
{
    targetObj = obj;
    targetID = id;
}

int CameraObject::getTargetObject()
{
    return targetObj;
}

int CameraObject::getTargetID()
{
    return targetID;
}
