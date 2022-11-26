//
//  addobject.cpp
//  
//
//  Created by Ryan Hoole on 10/20/15.
//
//

#include "gameengine.h"

/** \brief Adds GObject object.
 
 Add the object to our list of game objects, then return the object.
 */
GObject* GameEngine::addGObject(GObject* object)
{
    objects.push_back(object);
    return object;
}

/** \brief Adds animated GObject object.
 
 Add the object to our list of game objects, then set up physics, next
 create the object with GameEngine::createAnimatedNode then return it.
 */
GObject* GameEngine::addAnimatedGObject(GObject *object,
                                        std::string const& modelPath,
                                        ISceneNode* parent)
{
    objects.push_back(object);
    setWorld(object);
    object->setIrrNode(createAnimatedNode(modelPath, parent));
    object->setModelPath(modelPath);
    return object;
}

GObject* GameEngine::addStaticGObject(GObject* object,
                                      std::string const& modelPath,
                                      ISceneNode* parent)
{
    objects.push_back(object);
    setWorld(object);
    object->setIrrNode(createStaticNode(modelPath, parent));
    object->setModelPath(modelPath);
    return object;
}

EnvObject* GameEngine::addEnvObject(EnvObject* object,
                                    std::string const& modelPath,
                                    ISceneNode* parent)
{
    objects.push_back(object);
    setWorld(object);
    object->setIrrNode(createStaticNode(modelPath, parent));
    object->setModelPath(modelPath);
    return object;
}

CharObject* GameEngine::addCharObject(CharObject* object,
                                      std::string const& modelPath,
                                      ISceneNode* parent)
{
    objects.push_back(object);
    setWorld(object);
    object->setIrrNode(createAnimatedNode(modelPath, parent));
    object->setModelPath(modelPath);
    return object;
}

PlayerObject* GameEngine::addPlayerObject(PlayerObject* object,
                                          std::string const& modelPath,
                                          ISceneNode* parent)
{
    objects.push_back(object);
    setWorld(object);
    object->setIrrNode(createAnimatedNode(modelPath, parent));
    object->setModelPath(modelPath);
    return object;
}

TerrainObject* GameEngine::addTerrainObject(TerrainObject* object,
                                            std::string const& modelPath,
                                            ISceneNode* parent)
{
    objects.push_back(object);
    setWorld(object);
    object->setIrrNode(createTerrainNode(modelPath, parent));
    object->setModelPath(modelPath);
    return object;
}

CameraObject* GameEngine::addCameraObject(CameraObject* camera,
                                          ISceneNode* parent)
{
    objects.push_back(camera);
    camera->setCameraNode(irrlicht->getSceneManager()->addCameraSceneNode(
                                                                          parent,
                                                                          vector3df(5,5,5), // position
                                                                          vector3df(0,0,0) // look at vector
                                                                          ));
    return camera;
}

LightObject* GameEngine::addLightObject(LightObject* light,
                                        ISceneNode* parent)
{
    objects.push_back(light);
    light->setLightNode(irrlicht->getSceneManager()->addLightSceneNode(parent));
    return light;
}