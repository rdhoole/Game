//
//  terrainobject.cpp
//  
//
//  Created by Ryan Hoole on 5/31/15.
//
//

#include "terrainobject.h"

TerrainObject::TerrainObject() : GObject()
{
    objectType = 6;
}

void TerrainObject::setIrrNode(ITerrainSceneNode* node)
{
    irrlicht_node = node;
}

vector3df TerrainObject::getPos()
{
    return irrlicht_node->getPosition();
}

vector3df TerrainObject::getScale()
{
    return irrlicht_node->getScale();
}

void TerrainObject::setPos(vector3df pos)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->setPosition(pos);
}

void TerrainObject::setUpBullet()
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    
    CDynamicMeshBuffer* buffer = new CDynamicMeshBuffer(EVT_2TCOORDS, EIT_16BIT);
    terrain_node->getMeshBufferForLOD(*buffer, // mesh buffer
                                      m_LOD        // LOD Level Of Detail
                                      );
    
    
    if (debugMode)
        printf("About to use getBulletTriangleMesh!\n");
    btTriangleMesh* terrainMesh = getBulletTriangleMesh(buffer,scale);
    if (debugMode)
        printf("Finished getBulletTriangleMesh!\n");
    
    if (terrainMesh == NULL)
    {
        if (debugMode)
            printf("\n\nError in getBulletTriangleMesh!!!\n\n");
    }
    else
        shape = new btBvhTriangleMeshShape(terrainMesh, false);
    
    body = new btRigidBody(0, new btDefaultMotionState, shape);
    body->translate(btVector3(getPos().X, getPos().Y, getPos().Z));
    world->addRigidBody(body);
}

void TerrainObject::normalizeNormals(bool nn)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->setMaterialFlag(EMF_NORMALIZE_NORMALS, nn);
}

void TerrainObject::setWireFrame(bool wf)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->setMaterialFlag(EMF_WIREFRAME, wf);
}

void TerrainObject::setMaterialTexture(u32 layer, ITexture* tex)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->setMaterialTexture(layer, tex);
}

void TerrainObject::setMaterialType(E_MATERIAL_TYPE type)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->setMaterialType(type);
}

void TerrainObject::scaleTexture(float a, float b)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->scaleTexture(a, b);
}

void TerrainObject::setScale(vector3df s)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    scale = s;
    terrain_node->setScale(s);
}

void TerrainObject::setID(int _id)
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->setID(_id);
}

int TerrainObject::getID()
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    return terrain_node->getID();
}

void TerrainObject::setLOD(int lod)
{
    m_LOD = lod;
}

int TerrainObject::getLOD()
{
    return m_LOD;
}

void TerrainObject::remove()
{
    ITerrainSceneNode* terrain_node = (ITerrainSceneNode*)irrlicht_node;
    terrain_node->remove(); // delete irrlicht node
    world->removeRigidBody(body); // remove body from world
    // free up memory
    delete body->getMotionState();
    delete body->getCollisionShape();
    delete body;
    
    if (debugMode)
        printf("Removed TerrainObject!\n");
}

//used to take irrlicht mesh and get a bullet triangle mesh
btTriangleMesh* TerrainObject::getBulletTriangleMesh(CDynamicMeshBuffer* const buffer, const vector3df scale)
{
    if (debugMode)
    {
        printf("DEBUG INFO FOR TerrainObject::getBulletTriangleMesh.\n\n");
    }
    // for debugging
    u32 triangleCount = 0;
    
    btVector3 vertices[3];
    u32 i, j, k;
    s32 index, numVertices;
    u16* buffer_indices;
    
    btTriangleMesh* pTriMesh = new btTriangleMesh();
    
    if (debugMode)
        printf("VertexType: EVT_2TCOORDS\n");
            
    // Same but for S3DVertex2TCoords data
    irr::video::S3DVertex2TCoords* buffer_vertices=(irr::video::S3DVertex2TCoords*)buffer->getVertices();
            
    if (debugMode)
        printf("Got Vertices.\n");
            
    buffer_indices = buffer->getIndices();
            
    if (debugMode)
        printf("Got Indices: %d\n", *buffer_indices);
            
    numVertices = buffer->getVertexCount();
            
    if (debugMode)
    {
        printf("Got VertexCount: %d\n", numVertices);
        printf("Index Count: %d\n", buffer->getIndexCount());
    }
            
    for(j=0;j<buffer->getIndexCount();j+=3)
    { //index into irrlicht data
                
        if (debugMode)
            printf("Begin conversion:\n");
                
        for (k=0;k<3;k++)
        {
            s32 index = buffer_indices[j+k];
            if (index > numVertices) continue;
            vertices[k] = btVector3(buffer_vertices[index].Pos.X * scale.X, buffer_vertices[index].Pos.Y * scale.Y, buffer_vertices[index].Pos.Z * scale.Z);
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
    
    if(pTriMesh)
    {
        return pTriMesh;
    }
    
    return NULL;
    
}
