//
//  gobject.cpp
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#include "gobject.h"

GObject::GObject() : isAnimated(false), debugMode(false), canDoPhysics(false), hasShadow(false)
{
    lifeTime = 0;
    objectType = 0;
    modelPath = "";
    collisionDistance = 0.0f;
}

GObject::GObject(ISceneNode* node)
{
    setIrrNode(node);
    GObject();
}

GObject::GObject(ISceneNode* node, IVideoDriver* driver)
{
    setIrrNode(node);
    GObject();
    m_driver = driver;
}

void GObject::setIrrNode(ISceneNode* node)
{
    irrlicht_node = node;
}

ISceneNode* GObject::getIrrNode()
{
    return irrlicht_node;
}

vector3df GObject::getPos()
{
    return irrlicht_node->getPosition();
}

vector3df GObject::getScale()
{
    return scale;
}

vector3df GObject::getAbsPos()
{
    return irrlicht_node->getAbsolutePosition();
}

vector3df GObject::getRotation()
{
    return irrlicht_node->getRotation();
}

int GObject::getID()
{
    return irrlicht_node->getID();
}

void GObject::setID(s32 _id)
{
    irrlicht_node->setID(_id);
}

void GObject::setPos(vector3df pos)
{
    irrlicht_node->setPosition(pos);
}

void GObject::setAbsPos(vector3df pos)
{
    irrlicht_node->setPosition(pos - irrlicht_node->getParent()->getAbsolutePosition());
}

void GObject::setRotation(vector3df rot)
{
    irrlicht_node->setRotation(rot);
}

void GObject::setScale(vector3df scale)
{
    irrlicht_node->setScale(vector3df(scale));
}

void GObject::addChild(ISceneNode* child)
{
    irrlicht_node->addChild(child);
}

void GObject::addShadow()
{
    return;
}

bool GObject::getShadow()
{
    return hasShadow;
}

void GObject::stepPhysicSimulation()
{
    return;
}

void GObject::setUpBullet()
{
    body = NULL; // gobjects should not have physics, this will be overloaded.
}

void GObject::updateBullet()
{
    //if (body->isInWorld() && body != NULL) // make sure body is in world
    if (body != NULL)
    {   
        world->removeRigidBody(body);
        setUpBullet();
    }
}

bool GObject::getCanDoPhysics()
{
    return canDoPhysics;
}

void GObject::setBulletDynamicsWorld(btDynamicsWorld* new_world)
{
    world = new_world;
}

void GObject::setDebugMode(bool debug)
{
    debugMode = debug;
}

bool GObject::getDebugMode()
{
    return debugMode;
}

void GObject::setLifeTime(u32 time)
{
    lifeTime = time;
}

u32 GObject::getLifeTime()
{
    return lifeTime;
}

int GObject::getObjectType()
{
    return objectType;
}

void GObject::setModelPath(std::string path)
{
    modelPath = path;
}

std::string GObject::getModelPath()
{
    return modelPath;
}

void GObject::remove()
{
    irrlicht_node->remove(); // delete irrlicht node
    world->removeRigidBody(body); // remove body from world
    // free up memory
    delete body->getMotionState();
    delete body->getCollisionShape();
    delete body;
}

void GObject::QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler)
{
    btScalar W = TQuat.getW();
    btScalar X = TQuat.getX();
    btScalar Y = TQuat.getY();
    btScalar Z = TQuat.getZ();
    float WSquared = W * W;
    float XSquared = X * X;
    float YSquared = Y * Y;
    float ZSquared = Z * Z;
    
    TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
    TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
    TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
    TEuler *= core::RADTODEG;
}

btRigidBody* GObject::getRigidBody()
{
    return body;
}

//used to take irrlicht mesh and get a bullet triangle mesh
btTriangleMesh* GObject::getBulletTriangleMesh(IMesh* const mesh, const vector3df scale)
{
    if (debugMode)
        printf("DEBUG INFO FOR GObject::getBulletTriangleMesh.\n\n");
    
    // for debugging
    u32 triangleCount = 0;
    
    btVector3 vertices[3];
    u32 i, j, k;
    s32 index, numVertices;
    u16* mb_indices;
    
    btTriangleMesh *pTriMesh = new btTriangleMesh();
    
    for(i = 0; i < mesh->getMeshBufferCount(); i++)
    {
        irr::scene::IMeshBuffer* mb = mesh->getMeshBuffer(i);

        if(mb->getVertexType() == irr::video::EVT_STANDARD)
        {
            if (debugMode)
                printf("VertexType: EVT_STANDARD\n");
            
            irr::video::S3DVertex* mb_vertices=(irr::video::S3DVertex*)mb->getVertices();
            
            if (debugMode)
                printf("Got Vertices.\n");
            
            mb_indices = mb->getIndices();
            
            if (debugMode)
                printf("Got Indices: %d\n", *mb_indices);
            
            numVertices = mb->getVertexCount();
            
            if (debugMode)
            {
                printf("Got VertexCount: %d\n", numVertices);
                printf("Index Count: %d\n", mb->getIndexCount());
            }
            
            for(j=0;j<mb->getIndexCount();j+=3)
            { //get index into vertex list
                
                if (debugMode)
                {
                    printf("Begin conversion:\n");
                    ++triangleCount;
                }
                
                for (k=0;k<3;k++)
                {   //three verts per triangle
                    index = mb_indices[j+k];
                    if (index > numVertices) continue;
                    //convert to btVector3
                    vertices[k] = btVector3(mb_vertices[index].Pos.X * scale.X, mb_vertices[index].Pos.Y * scale.Y,mb_vertices[index].Pos.Z * scale.Z); // 1100
                    
                }
                if (debugMode)
                {
                    printf(".............................\n");
                    printf("btVector3 Triangle: %d\n", triangleCount);
                    //printf("X: %32.32f,\n",vertices[0]);
                    //printf("Y: %32.32f,\n", vertices[1]);
                    //printf("Z: %32.32f,\n", vertices[2]);
                    printf(".............................\n");
                }
                pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
            }
            
        }
        else
            if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
            {
                if (debugMode)
                    printf("VertexType: EVT_2TCOORDS\n");
                
                // Same but for S3DVertex2TCoords data
                irr::video::S3DVertex2TCoords* mb_vertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
                
                if (debugMode)
                    printf("Got Vertices.\n");
                
                mb_indices = mb->getIndices();
                
                if (debugMode)
                    printf("Got Indices: %d\n", *mb_indices);
                
                s32 numVertices = mb->getVertexCount();
                
                if (debugMode)
                {
                    printf("Got VertexCount: %d\n", numVertices);
                    printf("Index Count: %d\n", mb->getIndexCount());
                }
                
                for(j=0;j<mb->getIndexCount();j+=3)
                { //index into irrlicht data
                    
                    if (debugMode)
                        printf("Begin conversion:\n");
                    
                    for (k=0;k<3;k++)
                    {
                        s32 index = mb_indices[j+k];
                        if (index > numVertices) continue;
                        vertices[k] = btVector3(mb_vertices[index].Pos.X * scale.X, mb_vertices[index].Pos.Y * scale.Y, mb_vertices[index].Pos.Z * scale.Z);
                    }
                    if (debugMode)
                    {
                        printf(".............................\n");
                        printf("btVector3 Triangle: %d\n", triangleCount);
                        //printf("X: %32.32f,\n",vertices[0]);
                        //printf("Y: %32.32f,\n", vertices[1]);
                        //printf("Z: %32.32f,\n", vertices[2]);
                        printf(".............................\n");
                    }
                    pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
                }
            }
        
        // Does not handle the EVT_TANGENTS type
    }
    
    if(pTriMesh)
    {
        return pTriMesh;
    }
    
    return NULL;
}

void GObject::setTarget(vector3df pos)
{
    //irrlicht_node->setTarget(pos);
    targetV = pos;
}

void GObject::setTarget(int obj, int id)
{
    targetObj = obj;
    targetID = id;
}

vector3df GObject::getTarget()
{
    return targetV;
}

int GObject::getTargetObject()
{
    return targetObj;
}

int GObject::getTargetID()
{
    return targetID;
}

bool GObject::hasCollidedWith(vector3df obj)
{
    float dist = 0;
    
    dist += pow(obj.X-getPos().X,2);
    dist += pow(obj.Y-getPos().Y,2);
    dist += pow(obj.Z-getPos().Z,2);
    
    dist = sqrt(dist);
    
    if (dist <= collisionDistance)
        return true;
    else
        return false;
}

void GObject::setCollisionDistance(float dist)
{
    collisionDistance = dist;
}
