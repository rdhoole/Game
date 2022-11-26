//
//  main.cpp
//  
//
//  Created by Ryan Hoole on 5/29/15.
//
//

#include "gameengine.h"

enum ACTION
{
    ACTION_NO_ACTION = 0,
    ACTION_QUIT,
    ACTION_PAUSE,
    ACTION_SET_CAMERA_1,
    ACTION_SET_CAMERA_2,
    ACTION_SET_CAMERA_3,
    ACTION_SET_CAMERA_4,
    ACTION_SPAWN_CUBES,
    ACTION_PLAYER_FORWARD,
    ACTION_PLAYER_JUMP,
    ACTION_COUNT // 10
};

// overload doAction with what we want our game to do
// assign the cases to the value that ACTION represents
void GameEngine::doAction(int keystate, int act)
{
    switch (act)
    {
        case 0: // no action
            if (keystate == EventHandler::KEY_PRESSED)
                log(GameEngine::LOG_MSG, "KEY NOT ASSIGNED!");
            break;
        case 1: // Quit
            if (keystate == EventHandler::KEY_PRESSED)
                stop();
            break;
        case 2: // pause
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
        case 3: // set camera 1
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getCameraByID(1));
            break;
        case 4: // set camera 2
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getCameraByID(2));
            break;
        case 5: // set camera 3
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getCameraByID(3));
            break;
        case 6: // set camera 4
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getCameraByID(4));
            break;
        case 7:
            if (keystate == EventHandler::KEY_PRESSED ||
                keystate == EventHandler::KEY_DOWN)
                if (!isPaused())
                    spawnCubes();
            break;
        case 8: // move player forward
            if (keystate == EventHandler::KEY_PRESSED)
                //printf("MOVE PLAYER FORWARD\n");
            break;
        case 9:
            if (keystate == EventHandler::KEY_PRESSED)
                log(GameEngine::LOG_MSG, "PLAYER JUMP");
            break;
    }
}

// test out engine

int main()
{
    GameEngine game;
   
    if (!game.start()) // start engine
        return 1;
    
    // set path for object location
    //game.setObjectsPath("/Users/rhoole/Programs/C++/Project/media/");
    //game.setWorldPath("/Users/rhoole/world.xml");
    //game.setKeyconfigPath("/Users/rhoole/keyconfig.xml");

    game.setObjectsPath("/home/ryan/gameengine/media/");
    game.setWorldPath("/home/ryan/world.xml");
    game.setKeyconfigPath("/home/ryan/keyconfig.xml");
    
    // add game objects
    
    // ground
    EnvObject* ground =
    game.addEnvObject(new EnvObject, game.getObjectsPath() + "ground.obj");
    
    // terrain
    TerrainObject* terrain =
    game.addTerrainObject(new TerrainObject,
                          game.getObjectsPath() + "terrain-heightmap.bmp" // heightmap of our terrain
                          );
    //terrain->setDebugMode(true); // print out information
    terrain->setPos(vector3df(-128,-50,-128)); // (-128 , 0 , -128)  should put center of 256x256 map at 0,0,0
    terrain->setMaterialTexture(0, // material layer
                                game.getIrrlicht()->getVideoDriver()->getTexture("/home/ryan/gameengine/media/terrain-texture.jpg"));
    terrain->setMaterialTexture(1,
                                game.getIrrlicht()->getVideoDriver()->getTexture("/home/ryan/gameengine/media/detailmap3.jpg"));
    terrain->setMaterialType(EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f,20.0f);
    terrain->setScale(vector3df(2.0f,0.3f,2.0f));
    terrain->setLOD(5); // set lvl of detail for collision 0 best , 5 worst but 0 in debuging mode is horrid!
    terrain->setID(2);
    
    // cube
    CharObject* cube =
    game.addCharObject(new CharObject, game.getObjectsPath() + "cube.obj");
    cube->setPos(vector3df(0,12,0));
    cube->setLifeTime(6000); // live only till game time is at 6000
    
    // cube with id set to 2
    CharObject* cube2 = 
    game.addCharObject(new CharObject, game.getObjectsPath() + "cube.obj");
    cube2->setPos(vector3df(0,20,0));
    cube2->setID(2);
    
    // gary's walter
    CharObject* walter =
    game.addCharObject(new CharObject, game.getObjectsPath() + "Walter.obj");
    walter->setPos(vector3df(0,24,0));
    
    // ninja!
    CharObject* ninja =
    game.addCharObject(new CharObject, game.getObjectsPath() + "ninja.b3d");
    ninja->setPos(vector3df(7,5,0));
    ninja->setScale(vector3df(0.2f,0.2f,0.2f));
    ninja->setID(3);
    
    // ninja2!!
    CharObject* ninja2 =
    game.addCharObject(new CharObject, game.getObjectsPath() + "ninja.b3d");
    ninja2->setPos(vector3df(5,10,0));
    ninja2->setScale(vector3df(0.3f,0.3f,0.3f));
    
    //printf("modelpath for ninja!: %s\n", ninja->getModelPath().c_str());
    
    // fuzmonkey
    CharObject* fuzmonkey =
    game.addCharObject(new CharObject, game.getObjectsPath() + "fuzmonky.obj");
    fuzmonkey->setPos(vector3df(2,15,5));
    fuzmonkey->setScale(vector3df(1.0f,1.0f,1.0f));
    
    // Player monkey
    PlayerObject* player =
    game.addPlayerObject(new PlayerObject, game.getObjectsPath() + "fuzmonky.obj");
    player->setPos(vector3df(0,20,0));
    player->setScale(vector3df(2,2,2));
    player->setID(1);
    
    // light
    LightObject* light =
    game.addLightObject(new LightObject);
    light->setPos(vector3df(0,0,0));
    light->setRadius(50);
    
    // cameras
    CameraObject* camera1 =
    game.addCameraObject(new CameraObject);
    camera1->setPos(vector3df(5,0,10));
    camera1->setTarget(vector3df(0,5,0));
    game.setActiveCamera(camera1); // last camera setup is active camera, but you may add
                                  // as many as you wish and can change between them.
    camera1->setID(1); // set ID of camera object
    
    // TEST if new camera targeting feature works
    camera1->setTarget(game.OBJECT_CHAROBJECT, 2); // cube (charobject, id=2)
    
    CameraObject* camera2 =
    game.addCameraObject(new CameraObject);
    camera2->setPos(vector3df(0,15,0));
    camera2->setTarget(fuzmonkey->getPos());
    
    camera2->setID(2);
    
    CameraObject* camera3 =
    game.addCameraObject(new CameraObject);
    camera3->setPos(vector3df(10,10,0));
    camera3->setTarget(vector3df(0,5,0));
    
    camera3->setID(3);
    
    CameraObject* camera4 =
    game.addCameraObject(new CameraObject);
    camera4->setPos( vector3df(0,0,0));
    //camera4->setTarget(vector3df(0,0,0));
    
    camera4->setID(4);
    
    // enable collision from bullet
    //ground->setUpBullet();
    terrain->setUpBullet();
    cube->setUpBullet();
    //walter->setUpBullet();
    ninja->setUpBullet();
    ninja2->setUpBullet();
    fuzmonkey->setUpBullet();
    player->setUpBullet();
    
    //add shadows
    ninja->addShadow();
    ninja->normalizeNormals(true); //used to adjust shadows and lighting for scaled objects
                                // doesn't seem to do much this small..
    player->addShadow();
    player->normalizeNormals(true);
    
    
    //set shadow color like so
    game.setShadowColor(SColor(150,0,0,0));
    
    // wireframe
    ninja2->setWireFrame(true);
    ground->setWireFrame(true);
    //terrain->setWireFrame(true);
    
    // attach eventhandling system
    EventHandler eh;
    game.setEventHandler(&eh);
    
    // remove character object from world
    //ninja->setDebugMode(true);
    //if (!game.removeObject(ninja))
     //   printf ("Did not remove ninja!\n");
    
    // loop here
    // END LOOP THROUGH EVENT INPUT!!!

    // rot is rotation for monkey
    float rot = 0;
    
    // this attaches walter to fuzmonkey; fuzmonkey's pos is (0,0,0) to walter,
    // vector3df(0,0,5) puts walter 5m in front of fuzmonkey. later in the loop
    // we rotate fuzmonkey, making walter 'orbit' around fuzmonkey while fuzmonkey
    // is rotating.
    fuzmonkey->addChild(walter->getIrrNode());
    walter->setPos(vector3df(0,0,5));
    
    // NOTE: Add this implementation into Character Class!!!
    //
    // create node player to add camera and empty node for cameras target
    // our attempt at rotating the camera.
    ISceneNode* Player = game.getIrrlicht()->getSceneManager()->addEmptySceneNode();
    ISceneNode* cameraTarget = game.getIrrlicht()->getSceneManager()->addEmptySceneNode();
    ISceneNode* playerTarget = game.getIrrlicht()->getSceneManager()->addEmptySceneNode();
    
    //player->getIrrNode()->addChild(camera3->getCameraNode());
    
    //Player->addChild(cameraTarget); // Player's pos will be updated to be at players pos
    //player->getIrrNode()->addChild(playerTarget); // should be on player and only move to y axis
    
    Player->addChild(camera3->getCameraNode());
    Player->addChild(cameraTarget);
    Player->addChild(playerTarget);

    camera3->setPos(vector3df(0,0,0)); // set in Center of Player
    cameraTarget->setPosition(vector3df(0,0,200)); // in front of camera; reduces 'the shakes'
    playerTarget->setPosition(vector3df(0,0,0.1)); // zero movement speed
    
    // show cursor
    game.getIrrlicht()->getDevice()->getCursorControl()->setVisible(true);
    
    int y = 0;
    int x = 0;
    
    float lookSpeed = 0.05; // lookspeed for player camera
    
    float mSpeed = 10;
    float gravity = -9.81;
    float jump = 10;
    
    game.setDebugMode(true); // debugging mode for gameengine
    
    // SEGFAULTS!!!
    //game.loadbtDebug(); // load necessary things for debugging Bulletphysics
    
    //game.setbtDebugMode(true); // draw debugging lines? MUST HAVE CALLED LOADBTDEBUG!
    
    // load keyconfig or create default
    //if (!game.loadKeyconfig())
    //{
    
        // assign keys to actions
        ///////////////////////////////////////////////////////
        eh.setAction(KEY_SPACE, ACTION_PLAYER_JUMP);    // set SPACE to player jump
        eh.setAction(KEY_KEY_W, ACTION_PLAYER_FORWARD); // set W to player Forward
        eh.setAction(KEY_KEY_E, ACTION_SPAWN_CUBES);    // set E to Spawn Cubes
        eh.setAction(KEY_KEY_Q, ACTION_QUIT);           // set Q to quit
        eh.setAction(KEY_KEY_1, ACTION_SET_CAMERA_1);   // set active camera to camera id 1
        eh.setAction(KEY_KEY_2, ACTION_SET_CAMERA_2);   // set active camera to camera id 2
        eh.setAction(KEY_KEY_3, ACTION_SET_CAMERA_3);   // set active camera to camera id 3
        eh.setAction(KEY_KEY_4, ACTION_SET_CAMERA_4);   // set active camera to camera id 4
        ///////////////////////////////////////////////////////
        
        //TEST out the save/load features of kindbindings
        eh.setAction(KEY_KEY_P, ACTION_PAUSE);
    
        //save keyconfig feature
        //if (!game.saveKeyconfig())
        //    game.log(game.LOG_ERROR, "can't save keyconfig!");
    //}
    
    while (game.isRunning())
    {
        game.loop();
        
        if (!game.isPaused())
        {
            // deminstrate ablity to switch kepmapping
            if (game.getIrrlicht()->getTimeStamp() > 6000 && game.getIrrlicht()->getTimeStamp() < 7000)
            {
                eh.setAction(KEY_ESCAPE, game.ACTION_QUIT);
            }
            
            // reset cursor to center, give control back to system if not active window
            if (game.getIrrlicht()->getDevice()->isWindowActive())
            {
                game.getIrrlicht()->getDevice()->getCursorControl()->setPosition(
                                                                                 (s32)game.getIrrlicht()->getVideoDriver()->getScreenSize().Width/2,
                                                                                 (s32)game.getIrrlicht()->getVideoDriver()->getScreenSize().Height/2
                                                                                 );
            
                // get mouse movement move the Player node
                // try multiplying both mouse position and screen center by a float less then 1 to slow or stedy the action.
            
                y = (eh.getMouseState().Position.X - game.getIrrlicht()->getVideoDriver()->getScreenSize().Width/2);
                x = (eh.getMouseState().Position.Y - game.getIrrlicht()->getVideoDriver()->getScreenSize().Height/2);
                
                if (x != 0) // was  x > 0.5 || x < -0.5
                {
                    // rotate Player by x axis
                    Player->setRotation(vector3df(Player->getRotation().X + (x * lookSpeed),
                                                  Player->getRotation().Y,
                                                  Player->getRotation().Z
                                                  ));
                    camera3->setTarget(cameraTarget->getAbsolutePosition());
                }
                
                if (y != 0) // was  y > 0.5 || y < -0.5
                {
                    //rotate player ONLY by y axis
                    player->setRotation(vector3df(player->getRotation().X,
                                                  player->getRotation().Y + (y * lookSpeed),
                                                  player->getRotation().Z
                                                  ));
                    // roatate Player by y
                    Player->setRotation(vector3df(Player->getRotation().X,
                                                  Player->getRotation().Y + (y * lookSpeed),
                                                  Player->getRotation().Z
                                                  ));
                    camera3->setTarget(cameraTarget->getAbsolutePosition());
                }
            }
            
            // Player Node movement, below is the code for the mouse to control "looking around"
            // move forward
            if (eh.getKeyState(KEY_KEY_W) == EventHandler::KEY_DOWN)
            {
                
                Player->setPosition(playerTarget->getAbsolutePosition());
            
            }
            
            // TEST new function for getObjectByID
            if (eh.getKeyState(KEY_KEY_G) == EventHandler::KEY_PRESSED)
            {
                TerrainObject* obj = game.getObjectByID(new TerrainObject, 2); // get terrainobject with id 2
                if (obj != NULL)
                {
                    obj->setPos(vector3df(cameraTarget->getAbsolutePosition().X,
                                          cameraTarget->getAbsolutePosition().Y,
                                          cameraTarget->getAbsolutePosition().Z
                                          ));
                    obj->updateBullet(); // now update bullet
                                          
                    //obj->setRotation(Player->getRotation());
                }
                else
                    game.log(game.LOG_ERROR, "can't find object!");
            }
            
            // TEST new function for getObjectByID
            if (eh.getKeyState(KEY_KEY_H) == EventHandler::KEY_PRESSED)
            {
                CharObject* obj = game.getObjectByID(new CharObject, 2); // get CharObject with id 2
                if (obj != NULL)
                {
                    obj->setPos(playerTarget->getAbsolutePosition());
                    obj->updateBullet(); // now update bullet
                                          
                    //obj->setRotation(Player->getRotation());
                }
                else
                    game.log(game.LOG_ERROR, "can't find object!");
            }
            
            // always update pos
            // camera3 for player prospective
            camera3->setTarget(cameraTarget->getAbsolutePosition());
            //Player->setPosition(vector3df(player->getPos().X,
            //                              player->getPos().Y,
            //                              player->getPos().Z
            //                              ));
            
            
            // make monkey rotate on y axis (left right)
            rot = rot + 0.5f;
            //reset ... 360 = 0 nerd
            if (rot > 360)
                rot = 0;
            fuzmonkey->setRotation(vector3df(0,rot,0));
            walter->setRotation(vector3df(0,rot,0));
            
            // NOW cameras should be able to update by selves!
            // TEST for new setTarget/getObjectByID or getObjectPos
            //camera1->setTarget(player->getPos());
            //camera1->setTarget(game.getObjectByID(new CharObject, 2)->getPos());
            //camera1->setTarget(game.getObjectPos(GameEngine::OBJECT_CHAROBJECT, 2));
            
            // camera update 
            camera4->setPos( vector3df(player->getPos().X,
                                       player->getPos().Y + 10,
                                       player->getPos().Z));
            camera4->setTarget(vector3df(player->getPos().X,
                                         player->getPos().Y,
                                         player->getPos().Z));
        }
    }
    //game.stop(); // cleans up resources
}
