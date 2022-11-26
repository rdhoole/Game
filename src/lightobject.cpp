//
//  lightobject.cpp
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#include "lightobject.h"

LightObject::LightObject() : GObject()
{
    objectType = 1;
}

ILightSceneNode* LightObject::getLightNode()
{
    return light_node;
}

void LightObject::setLightNode(ILightSceneNode* node)
{
    light_node = node;
}

void LightObject::setRadius(f32 rad)
{
    light_node->setRadius(rad);
}

f32 LightObject::getRadius()
{
    return light_node->getRadius();
}

vector3df LightObject::getPos()
{
    return light_node->getPosition();
}

void LightObject::setPos(vector3df pos)
{
    light_node->setPosition(pos);
}
