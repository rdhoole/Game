//
//  main.cpp
//  
//
//  Created by Ryan Hoole on 5/29/15.
//
//

#include "gameengine.h"
#include <cstdlib> // used for rand()
#include <math.h>

void spawnMonkey(GameEngine* game);
void spawnHealth(GameEngine* game);

// TEST can we create our own Actions??
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

// overload doAction with want we want OUR game to do
// assign the case's to the value that ACTION represents
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
		setActiveCamera(getObjectByID(new CameraObject,1));
            break;
        case 4: // set camera 2
            if (keystate == EventHandler::KEY_PRESSED)
		setActiveCamera(getObjectByID(new CameraObject,2));
            break;
        case 5: // set camera 3
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getObjectByID(new CameraObject,3));
            break;
        case 6: // set camera 4
            if (keystate == EventHandler::KEY_PRESSED)
                setActiveCamera(getObjectByID(new CameraObject,4));
            break;
        case 7:
            if (keystate == EventHandler::KEY_PRESSED ||
                keystate == EventHandler::KEY_DOWN)
                if (!isPaused())
                    //spawnCubes();
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

// override objectUpdate to add the ability to update playerobjects to targets
void GameEngine::objectUpdate()
{
    // add for game
    btVector3 v;
    
    gameTime = irrlicht->getTimeStamp();
    
    // iterate through list of objects added; runs each objects function for updating physics
    for (std::list<GObject*>::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
    {
        // bullet step physics
        (*it)->stepPhysicSimulation();
        
        // ADDED FOR THIS GAME: monkey targets/collision detect; health collision detect
        // detect health 'picked up'
        if ((*it)->getObjectType() == OBJECT_CHAROBJECT)
        {
            if ((*it)->getID() == 0) // our health
            {
                CharObject* health = static_cast<CharObject*>(*it);
                if (health->hasCollidedWith(getObjectByID(new CharObject, 1)->getPos()) )
                {
                    CharObject* player = getObjectByID(new CharObject, 1); // player
                    player->health += 25;
                    player->score += 100;
                    
                    // this is the best way HOWEVER; it actually doesn't do what we want...
                    //health->setLifeTime(1); // delete health
                    
                    health->remove(); // remove is a clean up for the object in
                                        // irrlicht and for bullet
                    it = objects.erase(it); // remove object from game object list
                    delete health; // now delete it 
                    
                }
            }
        }
        
        // update monkey targets
        if ((*it)->getObjectType() == OBJECT_PLAYEROBJECT)
        {   
            // check if player's target is set
            if ((*it)->getTargetObject() != -1 && (*it)->getTargetID() != -1)
            {
                PlayerObject* monkey = static_cast<PlayerObject*>(*it);
                // check if it has Collided with player
                // if we hit the player deincrement the players score by five
                // for every Cycle the player is touching monkey
                if (monkey->hasCollidedWith(getObjectPos(monkey->getTargetObject(),
                                                     monkey->getTargetID())) )
                {
                    //printf ("I Hit the player!\n");
                    CharObject* player = getObjectByID(new CharObject, 1); // player
                    player->health -= 5; 
                    
                    // your have fulfulled your purpose, DIE!
                    monkey->setLifeTime(1);
                }
                
                // rotation monkey to face target
                monkey->faceTarget(getObjectByID(new CharObject, 1)->getPos()); // player
                
                // move monkey
                // make monkey go to your last pos
                monkey->getRigidBody()->activate();
                
                v.setX((getObjectPos(monkey->getTargetObject(),
                                     monkey->getTargetID()).X - monkey->getPos().X) * 0.02);
                v.setY((getObjectPos(monkey->getTargetObject(),
                                     monkey->getTargetID()).Y - monkey->getPos().Y) * 0.02);
                v.setZ((getObjectPos(monkey->getTargetObject(),
                                     monkey->getTargetID()).Z - monkey->getPos().Z) * 0.02);
                
                monkey->getRigidBody()->applyCentralImpulse(v);
            }
        }
        
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
        if ((gameTime - oldgameTime) >= 200)
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
    if ((gameTime - oldgameTime) >= 200)
    {
        oldgameTime = gameTime;
        
        // print number of objects in game
        if (debugMode)
        {
            char buffer[25];
            sprintf(buffer, "Number of objects in game: %lu", objects.size());
            log(GameEngine::LOG_DBUG, buffer);
        }
    }
}

int main()
{
    GameEngine game;
   
    if (!game.start()) // start engine or not!
        return 1;

    // These Should ALWAYS be set 
    game.setObjectsPath("/home/rdh/Programs/C++/Project/media/");
    
    // add game objects
    
    // terrain
    TerrainObject* terrain =
    game.addTerrainObject(new TerrainObject,
                          game.getObjectsPath() + "terrain-heightmap.bmp" // heightmap of our terrain
                          );
    //terrain->setDebugMode(true); // print out information
    terrain->setPos(vector3df(-256,-50,-256)); // (-128 , 0 , -128)  should put center of 256x256 map at 0,0,0
    terrain->setMaterialTexture(0, // material layer
                                game.getIrrlicht()->getVideoDriver()->getTexture("/home/rdh/Programs/C++/Project/media/terrain-texture.jpg"));
    terrain->setMaterialTexture(1,
                                game.getIrrlicht()->getVideoDriver()->getTexture("/home/rdh/Programs/C++/Project/media/detailmap3.jpg"));
    terrain->setMaterialType(EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f,20.0f);
    terrain->setScale(vector3df(2.0f,0.05f,2.0f));
    terrain->setLOD(0); // set lvl of detail for collision 0 best , 5 worst but 0 in debuging mode is horrid!
    terrain->setID(2);
    
    // cube
    //CharObject* cube =
    //game.addCharObject(new CharObject, game.getObjectsPath() + "cube.obj");
    //cube->setPos(vector3df(0,12,0));
    //cube->setLifeTime(6000); // live only till game time is at 6000
    
    // fuzmonkey
    CharObject* player =
    game.addCharObject(new CharObject, game.getObjectsPath() + "fuzmonky.obj");
    //game.addCharObject(new CharObject(game.getIrrlicht()->getVideoDriver()), "../media/fuzmonky.obj"); // we spelled monkey wrong :S; pass video driver to draw debugin lines...
    player->setPos(vector3df(2,15,5));
    player->setScale(vector3df(1.0f,1.0f,1.0f));
    player->score = 5;
    player->health = 100;
    player->setID(1);
    
    // light, gets attached to Player node
    LightObject* light =
    game.addLightObject(new LightObject);
    light->setPos(vector3df(0,20,0));
    light->setRadius(50);
    
    // cameras
    CameraObject* camera1 =
    game.addCameraObject(new CameraObject);
    camera1->setPos(vector3df(5,0,10));
    camera1->setTarget(vector3df(0,5,0));

    camera1->setID(1); // set ID of camera object
    
    // TEST if new camera targeting feature works
    //camera1->setTarget(game.OBJECT_CHAROBJECT, 4); // fuzmonkey (charobject, id=3)
    
    CameraObject* camera2 =
    game.addCameraObject(new CameraObject);
    camera2->setPos(vector3df(0,50,0));
    camera2->setTarget(player->getPos());
    
    camera2->setID(2);
    
    // this allows us not to put the update in our loop, the gameengine will take care of this 
    camera2->setTarget(game.OBJECT_CHAROBJECT, 1); // fuzmonkey
    
    game.setActiveCamera(camera1); //active camera
    
    // enable collision from bullet
    //ground->setUpBullet();
    terrain->setUpBullet();
    //walter->setUpBullet();
    
    player->setUpBullet(10,btVector3(1,1,1),false); // sphere physic node
    
    //add shadows
    player->addShadow();
    player->normalizeNormals(true);
    
    
    //set shadow color like so
    game.setShadowColor(SColor(150,0,0,0));
    
    // wireframe
    //terrain->setWireFrame(true);
    
    // attach eventhandling system
    EventHandler eh;
    game.setEventHandler(&eh);
    
    // NOTE: Add this implementation into Player Class!!!
    //
    // create node player to add camera and empty node for cameras target
    // our attempt at rotating the camera.
    ISceneNode* Player = game.getIrrlicht()->getSceneManager()->addEmptySceneNode();
    ISceneNode* cameraTarget = game.getIrrlicht()->getSceneManager()->addEmptySceneNode();
    ISceneNode* playerTarget = game.getIrrlicht()->getSceneManager()->addEmptySceneNode();
    
    //Player->addChild(cameraTarget); // Player's pos will be updated to be at players pos
    //player->getIrrNode()->addChild(playerTarget); // should be on player and only move to y axis
    
    Player->addChild(camera1->getCameraNode());
    Player->addChild(cameraTarget);
    Player->addChild(playerTarget);
    Player->addChild(light->getLightNode()); // attach light

    camera1->setPos(vector3df(0,15,-15)); // set in Center of Player
    cameraTarget->setPosition(vector3df(0,0,200)); // in front of camera; reduces 'the shakes'
    playerTarget->setPosition(vector3df(0,0,1)); // zero movement speed
    
    // show cursor
    //game.getIrrlicht()->getDevice()->getCursorControl()->setVisible(true);
    
    // coords for mouse
    int y = 0;
    int x = 0;
    
    float lookSpeed = 0.05; // lookspeed for player camera
    
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
        eh.setAction(KEY_ESCAPE, ACTION_QUIT);           // set Escape to quit
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
    
    // used for moving sphere
    btVector3 v;
    
    // display Score
    IGUIFont* font = game.getIrrlicht()->getGUI()->getFont("/home/rdh/Programs/C++/Project/media/myfont-28px/myfont-28px.xml");
    stringw displayText = L"";
    IGUIStaticText* textScore = game.getIrrlicht()->getGUI()->addStaticText(displayText.c_str(), rect<s32>(20,20,500,55), true);
    textScore->setOverrideFont(font);
    
    // display Health
    IGUIStaticText* textHealth = game.getIrrlicht()->getGUI()->addStaticText(displayText.c_str(), rect<s32>(20,55,300,90), true);
    textHealth->setOverrideFont(font);
    
    // for keeping time
    int gameTime = game.getIrrlicht()->getTimeStamp();
    int oldTime = gameTime;
    int oldTime_score = gameTime;
    int oldTime_health = gameTime;
    int spawnTime = 0;
    
    while (game.isRunning())
    {
        
        if (!game.isPaused())
        {            
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
                }
                
                if (y != 0) // was  y > 0.5 || y < -0.5
                {
                    // roatate Player by y
                    Player->setRotation(vector3df(Player->getRotation().X,
                                                  Player->getRotation().Y + (y * lookSpeed),
                                                  Player->getRotation().Z
                                                  ));
                }
            } // end of is active window
            
            camera1->setTarget(player->getPos());
            
            
            if (eh.getKeyState(KEY_KEY_W) == EventHandler::KEY_DOWN)
            {
                playerTarget->setPosition(vector3df(0,0,2)); // forward
            
                player->getRigidBody()->activate();
                
                v.setX(playerTarget->getAbsolutePosition().X - player->getPos().X); 
                v.setY(playerTarget->getAbsolutePosition().Y - player->getPos().Y);
                v.setZ(playerTarget->getAbsolutePosition().Z - player->getPos().Z); 
                
                //player->getRigidBody()->setLinearVelocity(v);
                player->getRigidBody()->applyCentralImpulse(v);
                
            }
            
            if (eh.getKeyState(KEY_KEY_S) == EventHandler::KEY_DOWN)
            {
                playerTarget->setPosition(vector3df(0,0,-2)); // backward
            
                player->getRigidBody()->activate();
                
                v.setX(playerTarget->getAbsolutePosition().X - player->getPos().X); 
                v.setY(playerTarget->getAbsolutePosition().Y - player->getPos().Y);
                v.setZ(playerTarget->getAbsolutePosition().Z - player->getPos().Z); 
                
                //player->getRigidBody()->setLinearVelocity(v);
                player->getRigidBody()->applyCentralImpulse(v);
            }
            
            if (eh.getKeyState(KEY_KEY_A) == EventHandler::KEY_DOWN)
            {
                playerTarget->setPosition(vector3df(-2,0,0)); // left
            
                player->getRigidBody()->activate();
                
                v.setX(playerTarget->getAbsolutePosition().X - player->getPos().X); 
                v.setY(playerTarget->getAbsolutePosition().Y - player->getPos().Y);
                v.setZ(playerTarget->getAbsolutePosition().Z - player->getPos().Z); 
                
                //player->getRigidBody()->setLinearVelocity(v);
                player->getRigidBody()->applyCentralImpulse(v);
            }
            
            if (eh.getKeyState(KEY_KEY_D) == EventHandler::KEY_DOWN)
            {
                playerTarget->setPosition(vector3df(2,0,0)); // right
            
                player->getRigidBody()->activate();
                
                v.setX(playerTarget->getAbsolutePosition().X - player->getPos().X); 
                v.setY(playerTarget->getAbsolutePosition().Y - player->getPos().Y);
                v.setZ(playerTarget->getAbsolutePosition().Z - player->getPos().Z); 
                
                //player->getRigidBody()->setLinearVelocity(v);
                player->getRigidBody()->applyCentralImpulse(v);
            }
            
            if (eh.getKeyState(KEY_KEY_Z) == EventHandler::KEY_DOWN)
            {
                spawnMonkey(&game);
            }
            
            gameTime = game.getIrrlicht()->getTimeStamp();
            
            // longer you play, the more they spawn
            // every ten seconds double the speed they spawn
            //spawnTime = ((gameTime / 10000) * 3000) / 2;
            
            if (gameTime < 10000)
            {
                spawnTime = 6000;
            }
            else
            {
                spawnTime = 3000 / (gameTime / 10000);
            }
            
            if ((gameTime - oldTime) >= spawnTime) // spawn monkey
            {
                //printf("spawnTime %d\n", spawnTime);
                spawnMonkey(&game);
                oldTime = gameTime;
            }
            
            // incrment the score every second
            if ((gameTime - oldTime_score) >= 1000)
            {
                player->score += 5;
                printf("Player score: %d\n", player->score);
                oldTime_score = gameTime;
            }
            
            // spawn health every 10 seconds
            if ((gameTime - oldTime_health) >= 10000)
            {
                spawnHealth(&game);
                oldTime_health = gameTime;
            }
            
            // DISPLAY Score
            displayText = L"Your Score: ";
            displayText += player->score;
            textScore->setOverrideColor(SColor(255,255,255,255));
            textScore->setText(displayText.c_str());
            
            // DISPLAY Health
            displayText = L"Health: ";
            displayText += player->health;
            textHealth->setOverrideColor(SColor(255,0,255,0));
            textHealth->setText(displayText.c_str());
            
            // see were player target is
            Player->setPosition(player->getPos());
            
            // Player loser Conditions
            // Health is zero or less ; player fell off edge
            if (player->health <= 0 || player->getPos().Y <= -60)
            {
                displayText = L"YOU LOSE!  Score: ";
                displayText += player->score;
                textScore->setOverrideColor(SColor(255,255,0,0)); // a,r,g,b
                textScore->setText(displayText.c_str());
                game.Pause();
            }
        }
        game.loop(); // should be at bottom
    }
    //game.stop(); // cleans up resources
}

void spawnMonkey(GameEngine* game)
{
    // Player monkey
    PlayerObject* monkey =
    game->addPlayerObject(new PlayerObject, game->getObjectsPath() + "fuzmonky.obj");
    monkey->setScale(vector3df(2,2,2));
    monkey->setCollisionDistance(5.0f);
    //monkey->addShadow();
    //monkey->normalizeNormals(true);
    monkey->setID(0);
    
    int range = 256; // cover whole map
    
    int x = ((rand() % (range * 2 + 1))-range);
    int z = ((rand() % (range * 2 + 1))-range);
    
    // randomly select spawn for monkey 
    
    monkey->setPos(vector3df(x,0,z)); // rand grenerate pos
     
    monkey->setUpBullet();
     
    monkey->setTarget(game->OBJECT_CHAROBJECT, 1); // target the user
     
    // set lifetime of object
    monkey->setLifeTime(game->getIrrlicht()->getTimeStamp() + (rand() % 10000+10000)); // live for 10-20s
}

void spawnHealth(GameEngine* game)
{
    CharObject* health =
    game->addCharObject(new CharObject, game->getObjectsPath() + "cube.obj");
    health->setScale(vector3df(1,1,1));
    health->setCollisionDistance(4.0f);
    health->setID(0);
    
    // add light
    ILightSceneNode* light = game->getIrrlicht()->getSceneManager()->addLightSceneNode(
                                0,           // parent
                                vector3df(0,0,0), // pos
                                SColor(255,0,255,0), // color
                                20.0 // radius
                                );
    health->addChild(light);
    
    int range = 200; // cover whole map
    
    int x = ((rand() % (range * 2 + 1))-range);
    int z = ((rand() % (range * 2 + 1))-range);
    
    health->setPos(vector3df(x,0,z)); // rand pos
    
    health->setUpBullet();
    
    health->setLifeTime(game->getIrrlicht()->getTimeStamp() + (rand() % 10000+10000)); // live for 10-20s
}
