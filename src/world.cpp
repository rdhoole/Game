//
//  world.cpp
//  
//
//  Created by Ryan Hoole on 10/20/15.
//
//

#include "gameengine.h"

/** \brief Save world if good then return true, else false */
bool GameEngine::saveWorld()
{
    if (worldPath != "")
    {
        // convert to wstring or stringw whatever, then return it
        std::wstring w_worldPath = std::wstring(worldPath.begin(), worldPath.end());
        const wchar_t* c_worldPath = w_worldPath.c_str();
        return saveWorld(c_worldPath);
    }
    else
    {
        log(GameEngine::LOG_ERROR, "worldPath was not set!");
        return false;
    }
}

bool GameEngine::saveWorld(stringw const& path)
{
    // create xml writer
    IXMLWriter* xwriter = irrlicht->getDevice()->getFileSystem()->createXMLWriter( path );
    
    if (!xwriter)
        return false;
    
    // write out the necessary XML header
    xwriter->writeXMLHeader();
    
    // start element
    xwriter->writeElement(L"world"); // world element
    xwriter->writeLineBreak();  // new line
    
    xwriter->writeElement(L"objects"); // objects element
    xwriter->writeLineBreak();
    
    // iterate thought list of objects and save attributes
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        GObject* object; // initialize object to parent class GObject
        
        switch ((*it)->getObjectType())
        {
            case OBJECT_GOBJECT:
                break;
            case OBJECT_LIGHTOBJECT:
            {
                object = static_cast<LightObject*>(*it);
            }
                break;
            case OBJECT_CAMERAOBJECT:
            {
                CameraObject* object = static_cast<CameraObject*>(*it);
                
                if (!object)
                    return false;
                
                // TargetObject (int)
                std::wstring w_targetobj = std::to_wstring(object->getTargetObject());
                const wchar_t* targetobj = w_targetobj.c_str();
                    
                // TargetID (int)
                std::wstring w_targetid = std::to_wstring(object->getTargetID());
                const wchar_t* targetid = w_targetid.c_str();    
                    
                // ID (int)
                std::wstring w_id = std::to_wstring(object->getID());
                const wchar_t* id = w_id.c_str();    
                    
                // POS (3 x float)
                std::wstring w_pos_x = std::to_wstring(object->getPos().X);
                std::wstring w_pos_y = std::to_wstring(object->getPos().Y);
                std::wstring w_pos_z = std::to_wstring(object->getPos().Z);
                const wchar_t* pos_x = w_pos_x.c_str();
                const wchar_t* pos_y = w_pos_y.c_str();
                const wchar_t* pos_z = w_pos_z.c_str();
                
                // Rotation (3 x float)
                std::wstring w_rot_x = std::to_wstring(object->getRotation().X);
                std::wstring w_rot_y = std::to_wstring(object->getRotation().Y);
                std::wstring w_rot_z = std::to_wstring(object->getRotation().Z);
                const wchar_t* rot_x = w_rot_x.c_str();
                const wchar_t* rot_y = w_rot_y.c_str();
                const wchar_t* rot_z = w_rot_z.c_str();
                
                xwriter->writeElement(L"cameraobject"); // charobject element
                xwriter->writeLineBreak();
                
                // variables 
                xwriter->writeElement(L"variables", true,
                                      L"targetobj", targetobj, // target's object 
                                      L"targetid", targetid,   // target's id
                                      L"id", id  // id of object
                                      );
                xwriter->writeLineBreak();
                
                // position 
                xwriter->writeElement(L"pos", true,
                                      L"x", pos_x,
                                      L"y", pos_y,
                                      L"z", pos_z
                                      );
                xwriter->writeLineBreak();
                
                // rotation 
                xwriter->writeElement(L"rotation", true,
                                      L"x", rot_x,
                                      L"y", rot_y,
                                      L"z", rot_z
                                      );
                xwriter->writeLineBreak();
                
                xwriter->writeClosingTag(L"cameraobject"); // end of charobject element
                xwriter->writeLineBreak();
            }
                break;
            case OBJECT_ENVOBJECT:
            {
                object = static_cast<EnvObject*>(*it);
            }
                break;
            case OBJECT_CHAROBJECT:
            {
                CharObject* object = static_cast<CharObject*>(*it);
                
                if (!object)
                    return false;
                
                // We have to convert types to const wchar_t* for the XML
                
                // ModelPath (string)
                // first widen string then cast
                std::string model = object->getModelPath();
                std::wstring widestr = std::wstring(model.begin(), model.end());
                const wchar_t* modelpath = widestr.c_str();
                
                // LifeTime (int)
                // first int to cast to wstring, then cast to wchar_t
                std::wstring w_lifetime = std::to_wstring(object->getLifeTime());
                const wchar_t* lifetime = w_lifetime.c_str();
                
                // Physics (bool)
                // 1 for True, 0 for false, Can or Can't do physics
                std::wstring w_physics;
                if (object->getCanDoPhysics())
                {
                    w_physics = L"1";
                }
                else
                {
                    w_physics = L"0";
                }
                const wchar_t* physics = w_physics.c_str();
                
                // Shadow (bool)
                // 1 for True, 0 for false, Does or Doesn't have shadows
                std::wstring w_shadow;
                if (object->getShadow())
                {
                    w_shadow = L"1";
                }
                else
                {
                    w_shadow = L"0";
                }
                const wchar_t* shadow = w_shadow.c_str();
                
                // ID (int)
                std::wstring w_id = std::to_wstring(object->getID());
                const wchar_t* id = w_id.c_str();
                
                // POS (3 x float)
                std::wstring w_pos_x = std::to_wstring(object->getPos().X);
                std::wstring w_pos_y = std::to_wstring(object->getPos().Y);
                std::wstring w_pos_z = std::to_wstring(object->getPos().Z);
                const wchar_t* pos_x = w_pos_x.c_str();
                const wchar_t* pos_y = w_pos_y.c_str();
                const wchar_t* pos_z = w_pos_z.c_str();
                
                // Scale (3 x float)
                std::wstring w_scale_x = std::to_wstring(object->getScale().X);
                std::wstring w_scale_y = std::to_wstring(object->getScale().Y);
                std::wstring w_scale_z = std::to_wstring(object->getScale().Z);
                const wchar_t* scale_x = w_scale_x.c_str();
                const wchar_t* scale_y = w_scale_y.c_str();
                const wchar_t* scale_z = w_scale_z.c_str();
                
                // Rotation (3 x float)
                std::wstring w_rot_x = std::to_wstring(object->getRotation().X);
                std::wstring w_rot_y = std::to_wstring(object->getRotation().Y);
                std::wstring w_rot_z = std::to_wstring(object->getRotation().Z);
                const wchar_t* rot_x = w_rot_x.c_str();
                const wchar_t* rot_y = w_rot_y.c_str();
                const wchar_t* rot_z = w_rot_z.c_str();
                
                xwriter->writeElement(L"charobject"); // charobject element
                xwriter->writeLineBreak();
                
                // variables for charobject
                xwriter->writeElement(L"variables", true,
                                      L"filepath", modelpath, // filepath of model
                                      L"timelife", lifetime, // the time object should stay alive
                                      L"physics", physics, // is physics get for object?
                                      L"shadow", shadow, // has shadows
                                      L"id", id  // id of object
                                      );
                xwriter->writeLineBreak();
                
                // position of charobject
                xwriter->writeElement(L"pos", true,
                                      L"x", pos_x,
                                      L"y", pos_y,
                                      L"z", pos_z
                                      );
                xwriter->writeLineBreak();
                
                // scale of charobject
                xwriter->writeElement(L"scale", true,
                                      L"x", scale_x,
                                      L"y", scale_y,
                                      L"z", scale_z
                                      );
                xwriter->writeLineBreak();
                
                // rotation of charobject
                xwriter->writeElement(L"rotation", true,
                                      L"x", rot_x,
                                      L"y", rot_y,
                                      L"z", rot_z
                                      );
                xwriter->writeLineBreak();
                
                xwriter->writeClosingTag(L"charobject"); // end of charobject element
                xwriter->writeLineBreak();
                
            }
                break;
            case OBJECT_PLAYEROBJECT:
            {
                PlayerObject* object = static_cast<PlayerObject*>(*it);
                
                if (!object)
                    return false;
                
                // We have to convert types to const wchar_t* for the XML
                
                // ModelPath (string)
                // first widen string then cast
                std::string model = object->getModelPath();
                std::wstring widestr = std::wstring(model.begin(), model.end());
                const wchar_t* modelpath = widestr.c_str();
                
                // LifeTime (int)
                // first int to cast to wstring, then cast to wchar_t
                std::wstring w_lifetime = std::to_wstring(object->getLifeTime());
                const wchar_t* lifetime = w_lifetime.c_str();
                
                // Physics (bool)
                // 1 for True, 0 for false, Can or Can't do physics
                std::wstring w_physics;
                if (object->getCanDoPhysics())
                {
                    w_physics = L"1";
                }
                else
                {
                    w_physics = L"0";
                }
                const wchar_t* physics = w_physics.c_str();
                
                // Shadow (bool)
                // 1 for True, 0 for false, Does or Doesn't have shadows
                std::wstring w_shadow;
                if (object->getShadow())
                {
                    w_shadow = L"1";
                }
                else
                {
                    w_shadow = L"0";
                }
                const wchar_t* shadow = w_shadow.c_str();
                
                // ID (int)
                std::wstring w_id = std::to_wstring(object->getID());
                const wchar_t* id = w_id.c_str();
                
                // POS (3 x float)
                std::wstring w_pos_x = std::to_wstring(object->getPos().X);
                std::wstring w_pos_y = std::to_wstring(object->getPos().Y);
                std::wstring w_pos_z = std::to_wstring(object->getPos().Z);
                const wchar_t* pos_x = w_pos_x.c_str();
                const wchar_t* pos_y = w_pos_y.c_str();
                const wchar_t* pos_z = w_pos_z.c_str();
                
                // Scale (3 x float)
                std::wstring w_scale_x = std::to_wstring(object->getScale().X);
                std::wstring w_scale_y = std::to_wstring(object->getScale().Y);
                std::wstring w_scale_z = std::to_wstring(object->getScale().Z);
                const wchar_t* scale_x = w_scale_x.c_str();
                const wchar_t* scale_y = w_scale_y.c_str();
                const wchar_t* scale_z = w_scale_z.c_str();
                
                // Rotation (3 x float)
                std::wstring w_rot_x = std::to_wstring(object->getRotation().X);
                std::wstring w_rot_y = std::to_wstring(object->getRotation().Y);
                std::wstring w_rot_z = std::to_wstring(object->getRotation().Z);
                const wchar_t* rot_x = w_rot_x.c_str();
                const wchar_t* rot_y = w_rot_y.c_str();
                const wchar_t* rot_z = w_rot_z.c_str();
                
                xwriter->writeElement(L"playerobject"); // charobject element
                xwriter->writeLineBreak();
                
                // variables 
                xwriter->writeElement(L"variables", true,
                                      L"filepath", modelpath, // filepath of model
                                      L"timelife", lifetime, // the time object should stay alive
                                      L"physics", physics, // is physics get for object?
                                      L"shadow", shadow, // has shadows
                                      L"id", id  // id of object
                                      );
                xwriter->writeLineBreak();
                
                // position 
                xwriter->writeElement(L"pos", true,
                                      L"x", pos_x,
                                      L"y", pos_y,
                                      L"z", pos_z
                                      );
                xwriter->writeLineBreak();
                
                // scale 
                xwriter->writeElement(L"scale", true,
                                      L"x", scale_x,
                                      L"y", scale_y,
                                      L"z", scale_z
                                      );
                xwriter->writeLineBreak();
                
                // rotation 
                xwriter->writeElement(L"rotation", true,
                                      L"x", rot_x,
                                      L"y", rot_y,
                                      L"z", rot_z
                                      );
                xwriter->writeLineBreak();
                
                xwriter->writeClosingTag(L"playerobject"); // end of charobject element
                xwriter->writeLineBreak();
            }
                break;
            case OBJECT_TERRAINOBJECT:
            {
                object = static_cast<TerrainObject*>(*it);
            }
                break;
        }
    }
    
    // close object section
    xwriter->writeClosingTag(L"objects");
    xwriter->writeLineBreak();
    
    /**** add other world attributes */
    //
    //
    //
    
    xwriter->writeClosingTag(L"world");
    
    // delete xml writer
    xwriter->drop();
    
    return true;
}

/** \brief Load world if good then return true, else false */
bool GameEngine::loadWorld()
{
    if (worldPath != "")
    {
        // convert to wstring or stringw whatever, then return it
        std::wstring w_worldPath = std::wstring(worldPath.begin(), worldPath.end());
        const wchar_t* c_worldPath = w_worldPath.c_str();
        return loadWorld(c_worldPath);
    }
    else
    {
        log(GameEngine::LOG_ERROR, "worldPath was not set!");
        return false;
    }
}

bool GameEngine::loadWorld(stringw const& path)
{
    return false;
}
