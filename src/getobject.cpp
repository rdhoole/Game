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
