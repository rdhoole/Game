//
//  irrlichtstandard.h
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#ifndef ____irrlichtstandard__
#define ____irrlichtstandard__

#include <irrlicht.h>
#include <stdio.h>

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

class IrrlichtStandard
{
public:
    explicit IrrlichtStandard();
    ISceneManager* getSceneManager();
    IVideoDriver* getVideoDriver();
    IrrlichtDevice* getDevice();
    IGUIEnvironment* getGUI();
    ITimer* getTimer();
    
    void startIrrScene();
    void endIrrScene();
    u32 getTimeStamp();
    u32 getDeltaTime();
    void resetActiveCameraAspectRatio();
    void close();
    
protected:
    IrrlichtDevice* m_Device;
    ISceneManager* m_Scene;
    IVideoDriver* m_Driver;
    IGUIEnvironment* m_GUI;
    ITimer* m_Timer;
private:
    bool createIrrDevice();
    u32 TimeStamp;
    // DeltaTime is need for bt simulation
    u32 DeltaTime;
    //int lastfps;
    
};

#endif /* defined(____irrlichtstandard__) */
