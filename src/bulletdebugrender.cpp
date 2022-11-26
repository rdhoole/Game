//
//  bulletdebugrender.cpp
//  
//
//  Created by Ryan Hoole on 6/6/15.
//
//

#include "bulletdebugrender.h"

BulletDebugRender::BulletDebugRender() : btIDebugDraw()
{
    
}

void BulletDebugRender::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    drawLine(from, to, color, color);
}

void BulletDebugRender::drawLine(const btVector3& from,const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
    // convert bullet to irrlicht
    SColorf fromC;
    fromC.set(fromColor[0],fromColor[1],fromColor[2],fromColor[3]);
    
    SColorf toC;
    toC.set(toColor[0],toColor[1],toColor[2],toColor[3]);
    
    // convert btVector3 to vector3df
    vector3df fromV;
    fromV = vector3df(from.x(),
                      from.y(),
                      from.z());
    vector3df toV;
    toV = vector3df(to.x(),
                    to.y(),
                    to.z());
    
    //Graphics->drawLine(from, to, fromC, toC);
    // draw 3DLine on irrlicht driver
    
    SMaterial m;
    m.Lighting=false;
    m_Driver->setMaterial(m);
    
    m_Driver->setTransform(video::ETS_WORLD, core::matrix4());
    //m_Driver->draw3DLine(fromV, toV, fromC.toSColor());
    m_Driver->draw3DLine(fromV, toV, SColor(255,255,255,255)); //Draw White Lines
}

void BulletDebugRender::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
    
}

void BulletDebugRender::reportErrorWarning(const char* warningString)
{
    
}

void BulletDebugRender::draw3dText(const btVector3& location, const char* textString)
{
    
}

void BulletDebugRender::setDebugMode(int debugMode)
{
    m_debugMode = debugMode;
}

int BulletDebugRender::getDebugMode() const
{
    return m_debugMode;
}

void BulletDebugRender::setVideoDriver(IVideoDriver* driver)
{
    m_Driver = driver;
}