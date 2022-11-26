//
//  terrainobject.h
//  
//
//  Created by Ryan Hoole on 5/31/15.
//
//

#ifndef ____terrainobject__
#define ____terrainobject__

#include "gobject.h"

class TerrainObject : public GObject
{
public:
    TerrainObject();
    void setIrrNode(ITerrainSceneNode* node);
    void setUpBullet();
    
    btTriangleMesh* getBulletTriangleMesh(CDynamicMeshBuffer* const buffer, const vector3df scale=vector3df(1,1,1));
    
    vector3df getPos();
    vector3df getScale();
    virtual void setPos(vector3df pos = vector3df(0,0,0));
    
    virtual void normalizeNormals(bool nn);
    virtual void setWireFrame(bool wf);
    virtual void setMaterialTexture(u32 layer, ITexture* tex);
    virtual void setMaterialType(E_MATERIAL_TYPE type);
    virtual void setScale(vector3df s);
    virtual void setLOD(int lod);
    virtual int getLOD();
    virtual void setID(int _id);
    virtual int getID();
    virtual void scaleTexture(float a, float b);
    virtual void remove();
private:
    ITerrainSceneNode* irrlicht_node;
    vector3df scale;
    int m_LOD;
};

#endif /* defined(____terrainobject__) */
