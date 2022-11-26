//
//  gobject.h
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#ifndef ____gobject__
#define ____gobject__

#include <string>
#include <irrlicht.h>

#include <btVector3.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class GObject
{
public:
    explicit GObject();
    explicit GObject(ISceneNode* node);
    explicit GObject(ISceneNode* node, IVideoDriver* device);
    virtual void setIrrNode(ISceneNode* node);
    ISceneNode* getIrrNode();
    virtual vector3df getPos();
    virtual vector3df getScale();
    virtual vector3df getAbsPos();
    virtual void setBulletDynamicsWorld(btDynamicsWorld* new_world);
    
    btTriangleMesh* getBulletTriangleMesh(IMesh* const mesh, const vector3df scale=vector3df(1,1,1));
    btRigidBody* getRigidBody();
    
    void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler);
    
    virtual void setPos(vector3df pos = vector3df(0,0,0));
    virtual void setAbsPos(vector3df pos = vector3df(0,0,0));
    virtual void setRotation(vector3df rot = vector3df(0,0,0));
    virtual vector3df getRotation();
    virtual void setScale(vector3df scale = vector3df(1,1,1));
    virtual void setID(s32 _id);
    virtual s32 getID();
    
    virtual void setTarget(vector3df pos = vector3df(0,0,0));
    virtual void setTarget(int obj, int id);
    virtual vector3df getTarget();
    virtual int getTargetObject();
    virtual int getTargetID();
    
    virtual bool hasCollidedWith(vector3df obj);
    virtual void setCollisionDistance(float dist);
    
    virtual void addShadow();
    virtual bool getShadow();
    
    virtual void addChild(ISceneNode* child);
    
    virtual void stepPhysicSimulation();
    virtual void setUpBullet();
    virtual void updateBullet();
    virtual bool getCanDoPhysics();
    
    virtual void setDebugMode(bool debug);
    virtual bool getDebugMode();
    
    virtual int getObjectType();
    
    virtual void setLifeTime(u32 time);
    virtual u32  getLifeTime();
    
    virtual void setModelPath(std::string path);
    std::string getModelPath();
    
    virtual void remove();
protected:
    ISceneNode* irrlicht_node;
    IVideoDriver* m_driver;
    vector3df scale;
    bool isAnimated;
    bool canDoPhysics;
    bool debugMode;
    bool hasShadow;
    
    std::string modelPath;
    
    u32 lifeTime;
    
    btCollisionShape* shape;
    btRigidBody* body;
    btDynamicsWorld* world;
    btTransform Transform;
    btDefaultMotionState* MotionState;
    
    int objectType;
    
    int targetObj;
    int targetID;
    vector3df targetV;
    
    float collisionDistance;
};

#endif /* defined(____gobject__) */
