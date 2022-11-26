//
//  gameengine.h
//  
//
//  Created by Ryan Hoole on 5/29/15.
//
//

#ifndef ____gameengine__
#define ____gameengine__

#include <list>
#include <string>
#include <cwchar>

#include <thread>

#include "irrlichtstandard.h"
#include "cameraobject.h"
#include "lightobject.h"
#include "envobject.h"
#include "terrainobject.h"
#include "playerobject.h"
#include "eventhandler.h"
#include "bulletdebugrender.h"

class GameEngine
{
public:
    
    /** Defines log types.
    
        This is so that when messages of sorts are sent to log(), we can manage their output.
    
    */
    enum LOG_TYPE
    {
        LOG_ERROR = 0,
        LOG_MSG,
        LOG_DBUG
    };
    
    /** Defines object types.
     
        We define object types so that we can properly type cast it back from the game object list in do object.
     
     */
    enum OBJECT_TYPE
    {
        OBJECT_GOBJECT = 0,
        OBJECT_LIGHTOBJECT,
        OBJECT_CAMERAOBJECT,
        OBJECT_ENVOBJECT,
        OBJECT_CHAROBJECT,
        OBJECT_PLAYEROBJECT,
        OBJECT_TERRAINOBJECT,
        OBJECT_COUNT
    };
    
    /** Defines Actions to be mapped to keys
     
        We define the actions that can be mapped to key in EventHandler::setAction
     */
    enum ACTION
    {
        ACTION_NO_ACTION = 0,
        ACTION_QUIT,
        ACTION_PAUSE,
        ACTION_BTDEBUG_BOOL,
        ACTION_SET_CAMERA_1,
        ACTION_SET_CAMERA_2,
        ACTION_SET_CAMERA_3,
        ACTION_SET_CAMERA_4,
        ACTION_SAVE_KEYCONFIG,
        ACTION_LOAD_KEYCONFIG,
        ACTION_SAVE_WORLD,
        ACTION_SPAWN_CUBES,
        ACTION_PLAYER_FORWARD,
        ACTION_PLAYER_JUMP,
        ACTION_COUNT
    };
    
    // gameengine.cpp
    GameEngine();
    IrrlichtStandard* getIrrlicht();
    void setShadowColor(SColor color);
    void setWorld(GObject* object);
    void setDebugMode(bool dbug);
    bool getDebugMode();
    void setbtDebugMode(bool dbug);
    bool getbtDebugMode();
    bool start();
    void loadbtDebug();
    void loop();
    void cleanup();
    void objectUpdate();
    bool isRunning();
    bool isPaused();
    void Pause();
    void Unpause();
    void setEventHandler(EventHandler* eh);
    void setWorldPath(std::string const& path);
    void setSettingsPath(std::string const& path);
    void setKeyconfigPath(std::string const& path);
    void setObjectsPath(std::string const& path);
    std::string getWorldPath();
    std::string getSettingsPath();
    std::string getKeyconfigPath();
    std::string getObjectsPath();
    void log(GameEngine::LOG_TYPE type, const char* msg);
    
    // world.cpp
    bool saveWorld(stringw const& path);
    bool saveWorld();
    bool loadWorld(stringw const& path);
    bool loadWorld();
    
    // keyconfig.cpp
    bool saveKeyconfig(stringw const& path);
    bool saveKeyconfig();
    bool loadKeyconfig(stringw const& path);
    bool loadKeyconfig();
    
    // settings.cpp
    bool saveSettings(stringw const& path);
    bool loadSettings(stringw const& path);
    
    // getobject.cpp
    vector3df getObjectPos(int obj, int id);
    GObject* getObjectByID(GObject* obj, int id);
    LightObject* getObjectByID(LightObject*, int id);
    CameraObject* getObjectByID(CameraObject*, int id);
    EnvObject* getObjectByID(EnvObject* obj, int id);
    CharObject* getObjectByID(CharObject* obj, int id);
    PlayerObject* getObjectByID(PlayerObject* obj, int id);
    TerrainObject* getObjectByID(TerrainObject* obj, int id);
    
    
    // actions.cpp
    void checkEvents();
    void doAction(int keystate,int act);
    void stop();
    void setActiveCamera(CameraObject* camera);
    void spawnCubes();
    
    // addobject.cpp
    GObject* addGObject(GObject* object);
    GObject* addAnimatedGObject(GObject* object,
                                std::string const& modelPath,
                                ISceneNode* parent = NULL);
    GObject* addStaticGObject(GObject* object,
                              std::string const& modelPath,
                              ISceneNode* parent = NULL);
    
    CameraObject* addCameraObject(CameraObject* camera,
                                  ISceneNode* parent = NULL);
    
    
    
    LightObject* addLightObject(LightObject* light,
                                ISceneNode* parent = NULL);
    EnvObject* addEnvObject(EnvObject* object,
                            std::string const& modelPath,
                            ISceneNode* parent = NULL);
    CharObject* addCharObject(CharObject* object,
                              std::string const& modelPath,
                              ISceneNode* parent = NULL);
    PlayerObject* addPlayerObject(PlayerObject* object,
                                  std::string const& modelPath,
                                  ISceneNode* parent = NULL);
    TerrainObject* addTerrainObject(TerrainObject* object,
                                    std::string const& modelPath,
                                    ISceneNode* parent = NULL);

private:
    IAnimatedMeshSceneNode* createAnimatedNode(std::string const& modelPath,
                                               ISceneNode* parent = NULL);
    IMeshSceneNode* createStaticNode(std::string const& modelPath,
                                     ISceneNode* parent = NULL);
    ITerrainSceneNode* createTerrainNode(std::string const& modelPath,
                                         ISceneNode* parent = NULL);
    
    // irrlicht
    IrrlichtStandard* irrlicht;
    EventHandler* events;
    
    // bullet
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    bool debugMode;
    bool btDebugMode;
    
    u32 gameTime;
    u32 oldgameTime;
    
    u32 pausedTime;
    
    // game engine
    bool Running;
    bool Paused;
    std::list <GObject *> objects;
    std::string keyconfigPath;
    std::string worldPath;
    std::string settingsPath;
    std::string objectsPath;
};

#endif /* defined(____gameengine__) */
