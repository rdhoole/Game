//
//  eventhandler.h
//  
//
//  Created by Ryan Hoole on 5/30/15.
//
//

#ifndef ____eventhandler__
#define ____eventhandler__

#include <irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;

class EventHandler : public IEventReceiver
{
public:
    
    /** \brief States for keys */
    enum KEYSTATE
    {
        KEY_UP = 0,
        KEY_DOWN,
        KEY_PRESSED,
        KEY_RELEASED
    };
    
    /** \brief Hold information about mouse state.
     *
     * We store the position the mouse is on the screen as well as if buttons are down(more to be implemented).
     */
    struct SMouseState
    {
        /// Position of mouse on screen
        position2di Position;
        /// True if left mouse button is pressed down
        bool LeftButtonDown;
        SMouseState() : LeftButtonDown(false) { }
    } MouseState;
    
    EventHandler()
    {
        // set all keys to false
        for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
            keyState[i] = KEY_UP;
        
        // set all gui event ids to zero NOT TESTED!!!
        for (u32 i = 0; i < EGET_COUNT; ++i)
            guiEventID[i] = 0;
        
        // set all actions to 0 or nothing
        for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
            action[i] = 0;
    }
    
    virtual bool OnEvent( const SEvent& event)
    {
        // keyboard event
        if (event.EventType == EET_KEY_INPUT_EVENT)
        {
            if (eventState) // processing events
            {
                // if key is pressed down
                if (event.KeyInput.PressedDown)
                {
                    // if key was not down before
                    if (keyState[event.KeyInput.Key] != KEY_DOWN)
                    {
                        keyState[event.KeyInput.Key] = KEY_PRESSED; // set to pressed
                    }
                    else
                    {
                        // if key was down before
                        keyState[event.KeyInput.Key] = KEY_DOWN; // set to down
                    }
                }
                else
                {
                    // if key is down
                    if (keyState[event.KeyInput.Key] != KEY_UP)
                    {
                        keyState[event.KeyInput.Key] = KEY_RELEASED; // set to released
                    }
                }
            } // end of eventState
        }
    
        // were are just attempting to copy the code above
        // except storing the id of the event to respective eventtype
        if (event.EventType == EET_GUI_EVENT)
            guiEventID[event.GUIEvent.EventType] = event.GUIEvent.Caller->getID();
        
        // remember the mouse state
        if (event.EventType == EET_MOUSE_INPUT_EVENT)
        {
            if (eventState) // processing events
            {
                switch (event.MouseInput.Event)
                {
                    case EMIE_LMOUSE_PRESSED_DOWN:
                        MouseState.LeftButtonDown = true;
                        break;
                        
                    case EMIE_LMOUSE_LEFT_UP:
                        MouseState.LeftButtonDown = false;
                        break;
                        
                    case EMIE_MOUSE_MOVED:
                        MouseState.Position.X = event.MouseInput.X;
                        MouseState.Position.Y = event.MouseInput.Y;
                        break;
                        
                    default:
                        break;
                }
            }
        }
        
        return false;
        
    }
    
    //! \brief Returns key state up, down, pressed, released
    virtual KEYSTATE getKeyState(EKEY_CODE keyCode) const
    {
        return keyState[keyCode];
    }
    virtual KEYSTATE getKeyState(int keyCode) const
    {
        return keyState[keyCode];
    }
    
    //! \brief Returns guiEventID that was interacted with.
    virtual s32 getGUIID(EGUI_EVENT_TYPE et) const
    {
        return guiEventID[et];
    }
    
    const SMouseState & getMouseState(void) const
    {
        return MouseState;
    }
    
    //! \brief Set key to an action.
    void setAction(EKEY_CODE keyCode, int act)
    {
        action[keyCode] = act; // set key to an action
    }
    void setAction(int keyCode, int act)
    {
        action[keyCode] = act; // set key to an action
    }
    
    //! \brief Get action to key.
    int getAction(EKEY_CODE keyCode)
    {
        return action[keyCode];
    }
    int getAction(int keyCode)
    {
        return action[keyCode];
    }
    
    // this is used so that key state will not be changed during execution of main game loop
    // place at the very END of main game loop
    void endEventProcess()
    {
        eventState = false;
    }
    
    // this is used so that key state will not be changed during execution of main game loop
    // place at the very START of main game loop
    void startEventProcess()
    {
        eventState = true;
        
        // keyboard key states
        for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        {
            if (keyState[i] == KEY_RELEASED)
                keyState[i] = KEY_UP;
                
            if (keyState[i] == KEY_PRESSED)
                keyState[i] = KEY_DOWN;
        }
    }
    
private:
    //! Array to hold current state of each key.
    //bool KeyIsDown[KEY_KEY_CODES_COUNT]; // old
    KEYSTATE keyState[KEY_KEY_CODES_COUNT];
    
    //! Array to hold pointer to do an action.
    int action[KEY_KEY_CODES_COUNT];
    
    s32 guiEventID[EGET_COUNT]; //!< Array to hold ID of interacted object.
    
    // keep track of the event process state so that key states are not changed during main game loop
    bool eventState;
};

#endif /* defined(____eventhandler__) */
