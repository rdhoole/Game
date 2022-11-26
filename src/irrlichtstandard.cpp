//
//  irrlichtstandard.cpp
//  
//
//  Created by Ryan Hoole on 5/28/15.
//
//

#include "irrlichtstandard.h"

IrrlichtStandard::IrrlichtStandard()
{
    createIrrDevice();
}

bool IrrlichtStandard::createIrrDevice()
{
    // SETTINGS SHOULD BE SELECTED/CHANGED FROM A MENU
    SIrrlichtCreationParameters createParams;
    createParams.DriverType = EDT_OPENGL;
    createParams.Stencilbuffer = true;
    createParams.Vsync = false;
    // SET WINDOWS SIZE DEFAULT 800X600
    createParams.WindowSize = dimension2d<u32>(1100,900);
    
    m_Device = createDeviceEx(createParams);
    //m_Device = createDevice(EDT_OPENGL, dimension2d<u32>(800,600),32,false,false,false);
    if (m_Device == NULL)
        //failed to create device!
        return false;
        
    // resizeable
    m_Device->setResizable(true);
    
    // setup
    m_Driver = m_Device->getVideoDriver();
    m_Scene = m_Device->getSceneManager();
    m_GUI = m_Device->getGUIEnvironment();
    m_Timer = m_Device->getTimer();
    TimeStamp = m_Timer->getTime();
    DeltaTime = 0;
    
    return true;
}

// this needs to be looped
void IrrlichtStandard::startIrrScene()
{

    // timers needed for simulation
    DeltaTime = m_Timer->getTime() - TimeStamp;
    TimeStamp = m_Timer->getTime();
        
    m_Driver->beginScene(true, true, SColor(255,100,100,100));
        
    // draw 3d scene and 2d irrlicht gui
    m_Scene->drawAll();
    m_GUI->drawAll();
}

void IrrlichtStandard::endIrrScene()
{
    m_Driver->endScene();
    m_Device->run();
}

u32 IrrlichtStandard::getTimeStamp()
{
    return TimeStamp;
}

u32 IrrlichtStandard::getDeltaTime()
{
    return DeltaTime;
}

ISceneManager* IrrlichtStandard::getSceneManager()
{
    return m_Scene;
}

IVideoDriver* IrrlichtStandard::getVideoDriver()
{
    return m_Driver;
}

IrrlichtDevice* IrrlichtStandard::getDevice()
{
    return m_Device;
}

IGUIEnvironment* IrrlichtStandard::getGUI()
{
    return m_GUI;
}
ITimer* IrrlichtStandard::getTimer()
{
    return m_Timer;
}

void IrrlichtStandard::close()
{
    
    m_Device->drop();
}

void IrrlichtStandard::resetActiveCameraAspectRatio()
{
    if (m_Scene->getActiveCamera() == NULL)
        return;
    //m_Scene->getActiveCamera()->setAspectRatio(
    //        (f32) width() / (f32) height );
}
