//
//  keyconfig.cpp
//  
//
//  Created by Ryan Hoole on 10/20/15.
//
//

#include "gameengine.h"

/** \brief Save Key mapping */
bool GameEngine::saveKeyconfig()
{
    if (keyconfigPath != "")
    {
        // convert to wstring or stringw whatever, then return it
        std::wstring w_keyconfigPath = std::wstring(keyconfigPath.begin(), keyconfigPath.end());
        const wchar_t* c_keyconfigPath = w_keyconfigPath.c_str();
        return saveKeyconfig(c_keyconfigPath);
    }
    else
    {
        log(GameEngine::LOG_ERROR, "keyconfigPath was not set!");
        return false;
    }
}

bool GameEngine::saveKeyconfig(stringw const& path)
{
    // create xml writer
    IXMLWriter* xwriter = irrlicht->getDevice()->getFileSystem()->createXMLWriter( path );
    
    if (!xwriter)
        return false;
    
    // write out the obligatory xml header. Each xml-file needs to have exactly one.
    xwriter->writeXMLHeader();
    
    // start element
    xwriter->writeElement(L"keyconfig");
    xwriter->writeLineBreak();      // new line
    
    // iterate thought list of keys and assign actions
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
    {
        // we need to convert integers to wstrings
        std::wstring s_key = std::to_wstring(i);
        std::wstring s_action = std::to_wstring(events->getAction(i));
        
        // now convert wstring to wchar_t*
        const wchar_t* key = s_key.c_str();
        const wchar_t* action = s_action.c_str();
        
        // write element like <setting key=0 assigned=4 />
        xwriter->writeElement(L"setting", true, L"key", key, L"action", action);
        xwriter->writeLineBreak();
    }
    
    //close keyconfig
    xwriter->writeClosingTag(L"keyconfig");
    xwriter->writeLineBreak();
    
    //delete xml writer
    xwriter->drop();
    
    return true;
}

/** \brief Load Key mapping */
bool GameEngine::loadKeyconfig()
{
    if (keyconfigPath != "")
    {
        // convert to wstring or stringw whatever, then return it
        std::wstring w_keyconfigPath = std::wstring(keyconfigPath.begin(), keyconfigPath.end());
        const wchar_t* c_keyconfigPath = w_keyconfigPath.c_str();
        return loadKeyconfig(c_keyconfigPath);
    }
    else
    {
        log(GameEngine::LOG_ERROR, "keyconfigPath was not set!");
        return false;
    }
}

bool GameEngine::loadKeyconfig(stringw const& path)
{
    // create xml reader
    IXMLReader* xml = irrlicht->getDevice()->getFileSystem()->createXMLReader( path );
    
    if (!xml)
        return false;
    
    const stringw settingTag(L"setting"); // look for this tag in xml
    //stringw currentSection; // keep track of our current section
    //const stringw keyconfigTag(L"keyconfig"); // look for this tag in xml
    
    // while there is more to read
    while (xml && xml->read())
    {
        if (stringw("setting") == xml->getNodeName())
        {
            // read the key/convert to integer
            stringw key = xml->getAttributeValueSafe(L"key");
            // need to convert to wchar_t for wcstol
            const wchar_t* w_key = key.c_str();
            wchar_t* pEnd;
            long int i_key = wcstol(w_key, &pEnd, 10); // convert to base 10
            
            if (!key.empty())  //make sure not empty
            {
                // read the key assiged value/convert to integer
                stringw action = xml->getAttributeValueSafe(L"action");
                // need to convert to wchar_t for wcstol
                const wchar_t* w_action = action.c_str();
                long int i_action = wcstol(w_action, &pEnd, 10); // convert to base 10
                
                // set up the loaded key to action
                events->setAction(i_key, i_action);
            }
        }
    }
    // delete the xml reader
    xml->drop();
    
    return true;
}
