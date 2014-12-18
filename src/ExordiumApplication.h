#ifndef __ExordiumApplication_h_
#define __ExordiumApplication_h_

#include "Ogre.h"

class ExordiumApplication
{
public:
	ExordiumApplication(void);
	virtual ~ExordiumApplication(void);
	bool go(void);
protected:
	Ogre::Root *mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
};

//---------------------------------------------------------------------------

#endif // #ifndef __ExordiumApplication_h_
