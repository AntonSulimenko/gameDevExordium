#ifndef __ExordiumApplication_h_
#define __ExordiumApplication_h_

//#include <OgreCamera.h>
//#include <OgreEntity.h>
//#include <OgreLogManager.h>
#include <OgreRoot.h>
//#include <OgreViewport.h>
//#include <OgreSceneManager.h>
//#include <OgreRenderWindow.h>
//#include <OgreConfigFile.h>

class ExordiumApplication
{
public:
	ExordiumApplication();
	virtual ~ExordiumApplication();

	void go();
private:
	void destroyScene();

private:
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::Root* mRoot;
};

//---------------------------------------------------------------------------

#endif // #ifndef __ExordiumApplication_h_

//---------------------------------------------------------------------------