//
//  gameengine.cpp
//  
//
//  Created by Ryan Hoole on 5/29/15.
//
//

#include "gameengine.h"

GameEngine::GameEngine() : debugMode(false), btDebugMode(false), Running(false), Paused(false)
{
    oldgameTime = 0;
    
    // create world physics
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver();
    
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
                                                broadphase,
                                                solver,
                                                collisionConfiguration);
    //dynamicsWorld->setGravity(btVector3(0,-9.81,0));
    dynamicsWorld->setGravity(btVector3(0,-16,0));
}

void GameEngine::setWorld(GObject* object)
{
    object->setBulletDynamicsWorld(dynamicsWorld);
}

/** \brief Set the debugging mode. */
void GameEngine::setDebugMode(bool dbug)
{
    debugMode = dbug;
}

/** \brief Check if debugging mode. */
bool GameEngine::getDebugMode()
{
    return debugMode;
}

void GameEngine::setbtDebugMode(bool dbug)
{
    btDebugMode = dbug;
}

bool GameEngine::getbtDebugMode()
{
    return btDebugMode;
}

/** \brief Update Objects in world.

    We go through the list of game objects placed in the world and first update the physics
 by calling GObject::stepPhysicSimulation in each object. Then we see if its a camera and update the target Next, we check to see if objects should be removed
 from the world and list by calling GObject::getLifeTime. If the returned time is less than but not
 equal to 0, we figure out what type of object it is, cast the approperite data type then
 call GObject::remove (GRIMREAPER). This will properly handle deleting the Irrlicht node and Bullet stuff.
 */
void GameEngine::objectUpdate()
{
    gameTime = irrlicht->getTimeStamp();
    
    // iterate through list of objects added; runs each objects function for updating physics
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        // bullet step physics
        (*it)->stepPhysicSimulation();
        
        // update camera targets
        if ((*it)->getObjectType() == OBJECT_CAMERAOBJECT)
        {
            CameraObject* camera = static_cast<CameraObject*>(*it);
            
            // check if camera's target is set
            if (camera->getTargetObject() != -1 && camera->getTargetID() != -1)
            {
                // update camera target by getting the objects current position
                camera->setTarget(getObjectPos(camera->getTargetObject(),
                                               camera->getTargetID()));
            }
        }
        
        // GRIMREAPER reaping the objects!!!
        // we dont want to check if an object time is up every cycle...
        if ((gameTime - oldgameTime) >= 1000)
        {
            // check if time is up on object & check what type of object it is.
            if (((*it)->getLifeTime() != 0) && (gameTime >= (*it)->getLifeTime()))
            {
                GObject* object; // initialize object to GObject
                
                // check what type of object and cast
                switch ((*it)->getObjectType())
                {
                    case OBJECT_GOBJECT:
                        break;
                    case OBJECT_LIGHTOBJECT:
                        object = static_cast<LightObject*>(*it);
                        break;
                    case OBJECT_CAMERAOBJECT:
                        object = static_cast<CameraObject*>(*it);
                        break;
                    case OBJECT_ENVOBJECT:
                        object = static_cast<EnvObject*>(*it);
                        break;
                    case OBJECT_CHAROBJECT:
                        object = static_cast<CharObject*>(*it);
                        break;
                    case OBJECT_PLAYEROBJECT:
                        object = static_cast<PlayerObject*>(*it);
                        break;
                    case OBJECT_TERRAINOBJECT:
                        object = static_cast<TerrainObject*>(*it);
                        break;
                }
                
                object->remove(); // remove is a clean up for the object in
                                    // irrlicht and for bullet
                it = objects.erase(it); // remove object from game object list
                delete object; // now delete it 
            }
        }
    }
    
    // get DeltaTime from irrlicht loop
    dynamicsWorld->stepSimulation(irrlicht->getDeltaTime() * 0.001f, 60);
    
    // update oldgameTime if its been a second since last GrimReaper update
    if ((gameTime - oldgameTime) >= 1000)
    {
        oldgameTime = gameTime;
        
        // print number of objects in game
        if (debugMode)
        {
            char buffer[50];
            snprintf(buffer, 50, "Number of objects in game: %lu", objects.size());
            log(GameEngine::LOG_DBUG, buffer);
        }
    }
}

bool GameEngine::isRunning()
{
    return Running;
}

bool GameEngine::isPaused()
{
    return Paused;
}

void GameEngine::Pause()
{
    Paused = true;
}

void GameEngine::Unpause()
{
    Paused = false;
}

/** \brief Pointer to IrrlichtStandard */
IrrlichtStandard* GameEngine::getIrrlicht()
{
    return irrlicht;
}

/** \brief Create IrrlichtStandard Object*/
bool GameEngine::start()
{
    irrlicht = new IrrlichtStandard();
    if (!irrlicht)
    {   
        Running = false;
        return false; // failed to create irrlicht device
    }
    Running = true;
    return true;
}

/** \brief Draw Debugging lines for Bullet Collisions */
void GameEngine::loadbtDebug()
{
    BulletDebugRender* m_bulletDebug = new BulletDebugRender();
    m_bulletDebug->setVideoDriver(irrlicht->getVideoDriver());
    m_bulletDebug->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    dynamicsWorld->setDebugDrawer( m_bulletDebug );
}

/** \brief Game update loop.
 
 objectUpdate gets called first, then IrrlichtStandard::startIrrScene. If debugMode is true
 we draw debugging collision lines. Last IrrlichtStandard::endIrrScene is called, this is 
 the end of the game loop.
 */
void GameEngine::loop()
{
    // TEST event stuff
    
    // getGUID returns the id of the GUI event 101 is from an example enum
    //if(events->getGUIID(EGET_BUTTON_CLICKED) == 101) //GUI_ID_QUIT_BUTTON)
    //{
        //irrlicht->getDevice()->closeDevice();
       // stop();
       // printf("Close button clicked!\n");
        //have a function to reset the id so we know its been handled
        //events->guiEventHandled();
    //}
    
    // do cycle
    
    // start the event process, must be at the begining of main game loop
    events->startEventProcess();
    
    if (!isPaused())
    {
        //std::thread oU(&GameEngine::objectUpdate, this);
        //oU.detach();

        objectUpdate();
        //irrlicht->startIrrScene();
        
        //draw stuffs here
        
        //irrlicht->endIrrScene();
    }
    else
    {
        // we need to save the Paused virtual time then restore it
        // this is done in for ACTION_PAUSE
    }
    
    irrlicht->startIrrScene();
    
    // do debugging, this must be under startIrrScene because it uses draw3DLines
    // to draw debugging lines.
    if(btDebugMode)
        dynamicsWorld->debugDrawWorld();
        
    //draw stuffs here
    
    irrlicht->endIrrScene();
   
    // check for Events and preform action assigned, should be at the end
    checkEvents();
    
    // end the event process, must be at the end of main game loop
    events->endEventProcess();
}

/** \brief Delete Bullet Objects. */
void GameEngine::cleanup()
{
    //NEED DELETE ALL OBJECTS
    
    //delete bt Objects
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete broadphase;
    delete collisionConfiguration;
}

/** \brief Set our EventHandler. */
void GameEngine::setEventHandler(EventHandler *eh)
{
    // set eventhandler to gameengine and irrlicht device
    events = eh;
    irrlicht->getDevice()->setEventReceiver(eh);
}

/** \brief Set the Shadow color */
void GameEngine::setShadowColor(SColor color)
{
    irrlicht->getSceneManager()->setShadowColor(color);
}

void GameEngine::setWorldPath(std::string const& path)
{
    worldPath = path;
}

void GameEngine::setSettingsPath(std::string const& path)
{
    settingsPath = path;
}

void GameEngine::setKeyconfigPath(std::string const& path)
{
    keyconfigPath = path;
}

void GameEngine::setObjectsPath(std::string const& path)
{
    objectsPath = path;
}

std::string GameEngine::getWorldPath()
{
    return worldPath;
}

std::string GameEngine::getSettingsPath()
{
    return settingsPath;
}

std::string GameEngine::getKeyconfigPath()
{
    return keyconfigPath;
}

std::string GameEngine::getObjectsPath()
{
    return objectsPath;
}

void GameEngine::log(GameEngine::LOG_TYPE type, const char* msg)
{
    switch (type)
    {
        case GameEngine::LOG_ERROR:
            printf("ERROR: %s\n", msg);
            break;
        case GameEngine::LOG_MSG:
            printf("MESSAGE: %s\n", msg);
            break;
        case GameEngine::LOG_DBUG:
            printf("DEBUG: %s\n", msg);
            break;
    }   
}
