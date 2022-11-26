//
//  createnode.cpp
//  
//
//  Created by Ryan Hoole on 10/20/15.
//
//

#include "gameengine.h"

IAnimatedMeshSceneNode* GameEngine::createAnimatedNode(std::string const& modelPath,
                                                       ISceneNode* parent)
{
    return irrlicht->getSceneManager()->addAnimatedMeshSceneNode(
                                                                 irrlicht->getSceneManager()->getMesh(modelPath.c_str()), parent);
}

IMeshSceneNode* GameEngine::createStaticNode(std::string const& modelPath,
                                             ISceneNode* parent)
{
    return irrlicht->getSceneManager()->addMeshSceneNode(
                                                         irrlicht->getSceneManager()->getMesh(modelPath.c_str()), parent);
}

ITerrainSceneNode* GameEngine::createTerrainNode(std::string const& modelPath,
                                                 ISceneNode* parent)
{
    return irrlicht->getSceneManager()->addTerrainSceneNode(modelPath.c_str(),
                                                            parent);
}