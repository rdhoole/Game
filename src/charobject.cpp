//
//  charobject.cpp
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#include "charobject.h"

CharObject::CharObject() : GObject()
{
    isAnimated = true;
    canDoPhysics = false;
    objectType = 4;
}

void CharObject::setIrrNode(IAnimatedMeshSceneNode* node)
{
    irrlicht_node = node;
}

IAnimatedMeshSceneNode* CharObject::getIrrNode()
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    return node;
}   

f32 CharObject::distance(vector3df A, vector3df B) const
{
    f32 dist = 0;
    
    dist += pow(B.X-A.X,2);
    dist += pow(B.Y-A.Y,2);
    dist += pow(B.Z-A.Z,2);
    
    dist = sqrt(dist);
    
    return dist;
}

void CharObject::remove()
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->remove(); // delete irrlicht node
    world->removeRigidBody(body); // remove body from world
    // free up memory
    delete body->getMotionState();
    delete body->getCollisionShape();
    delete body;
    
    if (debugMode)
        printf("Removed CharacterObject!\n");
}

void CharObject::updateBullet()
{
    if (body != NULL)
    {
        
    }
}

// char with box or formfit
void CharObject::setUpBullet(int mass, btVector3 inertia, bool box)
{
    if(mass <= 0) // character objects should not have infinte mass!!!
        mass = 10;
        
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    
    // make boxshape
    if (box)
    {
        vector3df edges[8];
        node->getMesh()->getBoundingBox().getEdges(edges);
        
        shape = new btBoxShape(btVector3(distance(edges[0], edges[4]) /2 + 0.1,
                                         distance(edges[0], edges[1]) /2,
                                         distance(edges[0], edges[2]) /2 + 0.1));
    }
    else // make Sphere
    {        
        //shape = new btBvhTriangleMeshShape(nodemesh, false);
        shape = new btSphereShape(2); // create sphere with radius 2
    }
            // TEST to add proper inertia
        // add mass
        btVector3 LocalInertia;
        shape->calculateLocalInertia(mass, LocalInertia);
        
        // fix bug of falling through objects was inertia issue
        //body = new btRigidBody(mass, new btDefaultMotionState, shape, inertia);
        
        body = new btRigidBody(mass, new btDefaultMotionState, shape, LocalInertia);
        
        if (body == NULL)
            canDoPhysics = false;
        else
            canDoPhysics = true;
        
        body->translate(btVector3(getPos().X, getPos().Y, getPos().Z));
        world->addRigidBody(body);
}

btRigidBody* CharObject::getRigidBody()
{
    if (!canDoPhysics)
        return NULL;
    return body;
}

bool CharObject::getCanDoPhysics()
{
    return canDoPhysics;
}

void CharObject::stepPhysicSimulation()
{
    if (canDoPhysics)
    {
        // update pos and rotation from bullet to irrlicht
        btVector3 pos = body->getCenterOfMassPosition();
        setPos(vector3df(pos.x(),
                         pos.y(),
                         pos.z()));
        
        btVector3 EulerRotation;
        QuaternionToEuler(body->getOrientation(), EulerRotation);
        setRotation(vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));
    }
}

void CharObject::setID(int _id)
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->setID(_id);
}

int CharObject::getID()
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    return node->getID();
}

void CharObject::addShadow()
{
    hasShadow = true;
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->addShadowVolumeSceneNode();
}

void CharObject::normalizeNormals(bool nn)
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->setMaterialFlag(EMF_NORMALIZE_NORMALS, nn);
}

void CharObject::setWireFrame(bool wf)
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->setMaterialFlag(EMF_WIREFRAME, wf);
}

void CharObject::setRotation(vector3df rot)
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->setRotation(rot);
}

vector3df CharObject::getRotation()
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    return node->getRotation();
}

void CharObject::faceTarget(vector3df target)
{    
    // get Y axis rotation
    deltaX = (target.X - getPos().X);
    deltaY = (target.Y - getPos().Y);
    deltaZ = (target.Z - getPos().Z);
    
    rad_y = atan2(deltaX, deltaZ);
    deg_y = rad_y * (180/ (atan(1)*4)); //180/pi
    
    // set Rotation, on y axis
    setRotation(vector3df(getRotation().X, deg_y, getRotation().Z));
}
