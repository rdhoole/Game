//
//  actions.cpp
//  
//
//  Created by Ryan Hoole on 10/20/15.
//
//

#include "gameengine.h"

/** \brief Check if events are happening, if so, do actions they are assigned to.*/
void GameEngine::checkEvents()
{
    // go through list of keys, see what the state of the keys are.
    // this is here for more control over the events processed
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
    {
        switch (events->getKeyState(i))
        {
            case EventHandler::KEY_UP:
                // shouldn't really do anything here
                break;
            case EventHandler::KEY_DOWN:
                doAction(events->getKeyState(i), events->getAction(i)); // if an action is set, ... do it.
                break;
            case EventHandler::KEY_PRESSED:
                doAction(events->getKeyState(i), events->getAction(i)); // if an action is set, ... do it.
                break;
            case EventHandler::KEY_RELEASED:
                break;
        }
    }
}

/** \brief Do actions that are assigned to the keymap */
// This function SHOULD be overridin in the game
void GameEngine::doAction(int keystate, int act)
{
    // we pass the keystate so that we have better control of each action.
    // be sure to add conditional statement otherwise you may get undesired
    // actions.
    switch (act)
    {
        case ACTION_NO_ACTION:
            if (keystate == EventHandler::KEY_PRESSED)
                log(GameEngine::LOG_MSG, "KEY NOT ASSIGNED!");
            break;
        case ACTION_QUIT:
            if (keystate == EventHandler::KEY_PRESSED)
                stop();
            break;
        case ACTION_PAUSE:
            if (keystate == EventHandler::KEY_PRESSED)
            {
                if (isPaused())
                {
                    Paused = false;
                    log(GameEngine::LOG_MSG, "Unpaused");
                    irrlicht->getTimer()->setTime(pausedTime);
                }
                else
                {
                    Paused = true;
                    log(GameEngine::LOG_MSG, "Paused");
                    pausedTime = irrlicht->getTimer()->getTime();
                }
                    
            }
            break;
        case ACTION_BTDEBUG_BOOL:
            if (keystate == EventHandler::KEY_PRESSED)
            {
                if (getbtDebugMode())
                {
                    setbtDebugMode(false);
                }
                else
                {
                    setbtDebugMode(true);
                }
            }
            break;
        case ACTION_SET_CAMERA_1:
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getObjectByID(new CameraObject,1));
            break;
        case ACTION_SET_CAMERA_2:
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getObjectByID(new CameraObject,2));
            break;
        case ACTION_SET_CAMERA_3:
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getObjectByID(new CameraObject,3));
            break;
        case ACTION_SET_CAMERA_4:
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getObjectByID(new CameraObject,4));
            break;
        case ACTION_SPAWN_CUBES:
            if (keystate == EventHandler::KEY_PRESSED ||
                keystate == EventHandler::KEY_DOWN)
                if (!isPaused())
                    spawnCubes();
            break;
        case ACTION_PLAYER_FORWARD:
            if (keystate == EventHandler::KEY_PRESSED)
                //printf("MOVE PLAYER FORWARD\n");
            break;
        case ACTION_PLAYER_JUMP:
            if (keystate == EventHandler::KEY_PRESSED)
                log(GameEngine::LOG_MSG, "PLAYER JUMP");
            break;
        case ACTION_SAVE_WORLD:
            if (keystate == EventHandler::KEY_PRESSED)
            {
                if (!isPaused())
                    Paused = true;
                    
                if (!saveWorld())
                    log(GameEngine::LOG_ERROR, "Failed to Save world!");
                    
                Paused = false;
            }
            break;
        case ACTION_SAVE_KEYCONFIG:
            if (keystate == EventHandler::KEY_PRESSED)
            {
                if (!saveKeyconfig())
                    log(GameEngine::LOG_ERROR, "Failed to save Keyconfig!");
            }
            break;
        case ACTION_LOAD_KEYCONFIG:
            if (keystate == EventHandler::KEY_PRESSED)
            {
                if (!loadKeyconfig())
                    log(GameEngine::LOG_ERROR, "Failed to load Keyconfig!");
            }
            break;
    }
}

/** \brief Stop the Engine.
 
 First call GameEngine::cleanup then close the Irrlicht device down and then delete irrlicht.
 */
void GameEngine::stop()
{
    cleanup();
    irrlicht->close();
    delete irrlicht;
    Running = false;
}

/** \brief Set the active camera the user will be seeing through */
void GameEngine::setActiveCamera(CameraObject* camera)
{
    if (camera)
    {
        if (irrlicht->getSceneManager()->getActiveCamera() != camera->getCameraNode())
        {
            irrlicht->getSceneManager()->setActiveCamera(camera->getCameraNode());
            //irrlicht->resetActiveCameraAspectRatio(); // resets camera ratio INCOMPLETE
        }
    }
}

/** \brief Spawn Cubes! */
void GameEngine::spawnCubes()
{
    CharObject* cube = addCharObject(new CharObject, getObjectsPath() + "cube.obj");
    //cube->setPos(vector3df(0,12,0));
    //cube->setPos(playerTarget->getAbsolutePosition());
    cube->setLifeTime(getIrrlicht()->getTimeStamp() + 6000); // lives for 6 seconds
    cube->setUpBullet();
    cube->addShadow();
}
