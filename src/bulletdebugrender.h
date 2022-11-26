//
//  bulletdebugrender.h
//  
//
//  Created by Ryan Hoole on 6/6/15.
//
//

#ifndef ____bulletdebugrender__
#define ____bulletdebugrender__

#include "gameengine.h"

class BulletDebugRender : public btIDebugDraw
{
    int m_debugMode;
public:
    BulletDebugRender();
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    virtual void drawLine(const btVector3& from,const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    virtual void reportErrorWarning(const char* warningString);
    virtual void draw3dText(const btVector3& location, const char* textString);
    virtual void setDebugMode(int debugMode);
    virtual int getDebugMode() const;
    
    virtual void setVideoDriver(IVideoDriver* driver);
private:
    IVideoDriver* m_Driver;
};

#endif /* defined(____bulletdebugrender__) */
