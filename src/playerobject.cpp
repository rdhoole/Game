//
//  playerobject.cpp
//  
//
//  Created by Ryan Hoole on 6/5/15.
//
//

#include "playerobject.h"

PlayerObject::PlayerObject() : CharObject()
{
    objectType = 5;
}

void PlayerObject::setID(int _id)
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->setID(_id);
}

int PlayerObject::getID()
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    return node->getID();
}

// Setup player with capsuleshape

void PlayerObject::setUpBullet(int mass)
{
    if(mass <= 0) // character objects should not have infinte mass!!!
        mass = 10;
    
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    //vector3df edges[8];
    //node->getMesh()->getBoundingBox().getEdges(edges);
    
    // should be dynamic size...
    shape = new btCapsuleShape(2,     //radius
                               4      //height
                               );

    btVector3 LocalInertia;
    shape->calculateLocalInertia(mass, LocalInertia);
    
    // set up
    Transform.setIdentity();
    Transform.setOrigin(btVector3(getPos().X, getPos().Y, getPos().Z));
    
    MotionState = new btDefaultMotionState(Transform);
    
    body = new btRigidBody(mass, MotionState, shape, LocalInertia);
    
    // set Friction
    //body->setFriction(10.0f);
    
    // set angular facter
    // (were trying to keep capsule upright)
    body->setAngularFactor(btVector3(0, 0, 0));
    //body->setCollisionFlags( body->getCollisionFlags() |
    //                        btCollisionObject::CF_KINEMATIC_OBJECT);
    
    // allow us to move object
    body->setActivationState(DISABLE_DEACTIVATION);
    
    if (body == NULL)
        canDoPhysics = false;
    else
        canDoPhysics = true;
    
    //body->translate(btVector3(getPos().X, getPos().Y, getPos().Z));
    world->addRigidBody(body);
}

// Player stepPhysicSimulation should not rotate but only y axis
/* It should stay upright for now! 
   so it can climb
      _____
     /     \
    |       |
    |       |
     \     /
      -----
 
 */

void PlayerObject::stepPhysicSimulation()
{
    if (canDoPhysics)
    {
        // update if user moved object
        // OBJECT DISAPEARS goes up FAST!!!
        //body->translate(btVector3(getPos().X,
        //                          getPos().Y,
        //                          getPos().Z));
        //Transform.setOrigin(btVector3(getPos().X,
        //                              getPos().Y,
        //                              getPos().Z));
        
        //MotionState->getWorldTransform(Transform);
        //MotionState->setWorldTransform(Transform);
        
        // update pos and rotation from bullet to irrlicht
        btVector3 pos = body->getCenterOfMassPosition();
        setPos(vector3df(pos.x(),
                         pos.y(),
                         pos.z()));
        
        //btVector3 EulerRotation;
        //QuaternionToEuler(body->getOrientation(), EulerRotation);
        //setRotation(vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));
        
        // here we update the y axis
        //setRotation(vector3df(NULL, EulerRotation[1], NULL));
    }
}

void PlayerObject::setRotation(vector3df rot)
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    node->setRotation(rot);
}

vector3df PlayerObject::getRotation()
{
    IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) irrlicht_node;
    return node->getRotation();
}

void PlayerObject::faceTarget(vector3df target)
{
    // get Y axis rotation
    deltaX = (target.X - getPos().X);
    deltaY = (target.Y - getPos().Y);
    deltaZ = (target.Z - getPos().Z);
    
    rad_y = atan2(deltaX, deltaZ);
    deg_y = rad_y * (180/ (atan(1)*4)); //180/pi
    
    // set Rotation, on y axis
    //setRotation(vector3df(deg_x, deg_y, getRotation().Z));
    setRotation(vector3df(getRotation().X, deg_y, getRotation().Z));
}
