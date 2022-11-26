//
//  getobject.cpp
//  
//
//  Created by Ryan Hoole on 10/22/15.
//
//

#include "gameengine.h"

// get pos of object by type and id
vector3df GameEngine::getObjectPos(int obj, int id)
{
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        if ((*it)->getObjectType() == obj)
        {
            if ((*it)->getID() == id)
            {
                return (*it)->getPos();
            }
        }
    }
    return vector3df(0,0,0); // if we can't find the object, look at origin!
}

//      CharObject* getObjectByID(new CharObject, 23)
//
// Passing a new Object into the function
// and it will return CharObject which its id is 23.
//
// I have it this way to allow overloading.
//
// Returns NULL if object not found

GObject* GameEngine::getObjectByID(GObject* obj, int id)
{
    GObject* object; // initialize object to parent class GObject
    
    // iterate thought list of objects and find the correct type of object
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        if ((*it)->getObjectType() == obj->getObjectType())
        {
            if ((*it)->getID() == id)
            {
                delete obj; // delete obj
                return object; // object is already GObject type.
            }
        }
    }
    delete obj; // delete obj
    return NULL; // object was not found.
}

LightObject* GameEngine::getObjectByID(LightObject* obj, int id)
{
    GObject* object; // initialize object to parent class GObject
    
    // iterate thought list of objects and find the correct type of object
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        if ((*it)->getObjectType() == obj->getObjectType())
        {
            if ((*it)->getID() == id)
            {
                delete obj; // delete obj
                LightObject* object = static_cast<LightObject*>(*it); // cast to proper type
                return object; // return proper type
            }
        }
    }
    delete obj; // delete obj
    return NULL; // object was not found.
}

CameraObject* GameEngine::getObjectByID(CameraObject* obj, int id)
{
    GObject* object; // initialize object to parent class GObject
    
    // iterate thought list of objects and find the correct type of object
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        if ((*it)->getObjectType() == obj->getObjectType())
        {
            if ((*it)->getID() == id)
            {
                delete obj; // delete obj
                CameraObject* object = static_cast<CameraObject*>(*it); // cast to proper type
                return object; // return proper type
            }
        }
    }
    delete obj; // delete obj
    return NULL; // object was not found.
}

EnvObject* GameEngine::getObjectByID(EnvObject* obj, int id)
{
    GObject* object; // initialize object to parent class GObject
    
    // iterate thought list of objects and find the correct type of object
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        if ((*it)->getObjectType() == obj->getObjectType())
        {
            if ((*it)->getID() == id)
            {
                delete obj; // delete obj
                EnvObject* object = static_cast<EnvObject*>(*it); // cast to proper type
                return object; // return proper type
            }
        }
    }
    delete obj; // delete obj
    return NULL; // object was not found.
}

CharObject* GameEngine::getObjectByID(CharObject* obj, int id)
{
    GObject* object; // initialize object to parent class GObject
    
    // iterate thought list of objects and find the correct type of object
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        if ((*it)->getObjectType() == obj->getObjectType())
        {
            if ((*it)->getID() == id)
            {
                delete obj; // delete obj
                CharObject* object = static_cast<CharObject*>(*it); // cast to proper type
                return object; // return proper type
            }
        }
    }
    delete obj; // delete obj
    return NULL; // object was not found.
}

PlayerObject* GameEngine::getObjectByID(PlayerObject* obj, int id)
{
    GObject* object; // initialize object to parent class GObject
    
    // iterate thought list of objects and find the correct type of object
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        if ((*it)->getObjectType() == obj->getObjectType())
        {
            if ((*it)->getID() == id)
            {
                delete obj; // delete obj
                PlayerObject* object = static_cast<PlayerObject*>(*it); // cast to proper type
                return object; // return proper type
            }
        }
    }
    delete obj; // delete obj
    return NULL; // object was not found.
}

TerrainObject* GameEngine::getObjectByID(TerrainObject* obj, int id)
{
    GObject* object; // initialize object to parent class GObject
    
    // iterate thought list of objects and find the correct type of object
    for (std::list<GObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
    {     
        if ((*it)->getObjectType() == obj->getObjectType())
        {
            if ((*it)->getID() == id)
            {
                delete obj; // delete obj
                TerrainObject* object = static_cast<TerrainObject*>(*it); // cast to proper type
                return object; // return proper type
            }
        }
    }
    delete obj; // delete obj
    return NULL; // object was not found.
}
