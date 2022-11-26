//
//  envobject.cpp
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#include "envobject.h"

EnvObject::EnvObject() : GObject()
{
    objectType = 3;
}

void EnvObject::setIrrNode(IMeshSceneNode* node)
{
    irrlicht_node = node;
}

vector3df EnvObject::getPos()
{
    return irrlicht_node->getPosition();
}

int EnvObject::getID()
{
    IMeshSceneNode* mesh_node = (IMeshSceneNode*)irrlicht_node;
    return mesh_node->getID();
}

void EnvObject::setID(int _id)
{
    IMeshSceneNode* mesh_node = (IMeshSceneNode*)irrlicht_node;
    mesh_node->setID(_id);
}

void EnvObject::remove()
{
    IMeshSceneNode* mesh_node = (IMeshSceneNode*)irrlicht_node;
    mesh_node->remove(); // delete irrlicht node
    world->removeRigidBody(body); // remove body from world
    // free up memory
    delete body->getMotionState();
    delete body->getCollisionShape();
    delete body;
    
    if (debugMode)
        printf("Removed EnvObject!\n");
}

void EnvObject::setUpBullet()
{
    IMeshSceneNode* mesh_node = (IMeshSceneNode*)irrlicht_node;
    IMesh* mesh = mesh_node->getMesh();
    
    if (debugMode)
        printf("\n\nAbout to use getBulletTriangleMesh!\n");
    btTriangleMesh* envMesh = getBulletTriangleMesh(mesh);
    if (debugMode)
        printf("Finished getBulletTriangleMesh!\n");
    
    if (envMesh == NULL)
    {
        if (debugMode)
            printf("\n\nError in getBulletTriangleMesh!!!\n\n");
    }
    else
        shape = new btBvhTriangleMeshShape(envMesh, false);
    
    body = new btRigidBody(0, new btDefaultMotionState, shape);
    body->translate(btVector3(getPos().X, getPos().Y, getPos().Z));
    world->addRigidBody(body);
}

void EnvObject::addShadow()
{
    IMeshSceneNode* mesh_node = (IMeshSceneNode*)irrlicht_node;
    mesh_node->addShadowVolumeSceneNode();
}

void EnvObject::normalizeNormals(bool nn)
{
    IMeshSceneNode* mesh_node = (IMeshSceneNode*)irrlicht_node;
    mesh_node->setMaterialFlag(EMF_NORMALIZE_NORMALS, nn);
}

void EnvObject::setWireFrame(bool wf)
{
    IMeshSceneNode* mesh_node = (IMeshSceneNode*)irrlicht_node;
    mesh_node->setMaterialFlag(EMF_WIREFRAME, wf);
}