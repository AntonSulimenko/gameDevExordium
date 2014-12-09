#include "ExordiumApplication.h"

//---------------------------------------------------------------------------
ExordiumApplication::ExordiumApplication()
	: mResourcesCfg(Ogre::StringUtil::BLANK)
	, mPluginsCfg(Ogre::StringUtil::BLANK)
	, mRoot(0)
{

}

//---------------------------------------------------------------------------
ExordiumApplication::~ExordiumApplication()
{
	delete mRoot;
}

//---------------------------------------------------------------------------
void ExordiumApplication::go()
{
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";

    //if (!setup())
    //    return;

    //mRoot->startRendering();

    //// Clean up
    //destroyScene();
}

//---------------------------------------------------------------------------
void ExordiumApplication::destroyScene()
{
}
