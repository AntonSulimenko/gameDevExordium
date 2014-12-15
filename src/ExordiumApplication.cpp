#include "ExordiumApplication.h"

#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

//-------------------------------------------------------------------------------------
ExordiumApplication::ExordiumApplication(void)
	: mRoot(0),
	mCamera(0),
	mSceneMgr(0),
	mWindow(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK)
{
}
//-------------------------------------------------------------------------------------
ExordiumApplication::~ExordiumApplication(void)
{
	delete mRoot;
}

bool ExordiumApplication::go(void)
{
	mRoot = new Ogre::Root();

	//-------------------------------------------------------------------------------------
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/materials/programs", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/materials/scripts", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/materials/textures", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/models", "FileSystem", "General");
	//-------------------------------------------------------------------------------------
	if (mRoot->restoreConfig() && mRoot->showConfigDialog())
	{
		mWindow = mRoot->initialise(true, "Exordium Window");
	}
	else
	{
		return false;
	}
	//-------------------------------------------------------------------------------------
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	//-------------------------------------------------------------------------------------
	mCamera = mSceneMgr->createCamera("PlayerCam");

	mCamera->setPosition(Ogre::Vector3(0, 0, 80));
	mCamera->lookAt(Ogre::Vector3(0, 0, -300));
	mCamera->setNearClipDistance(5);

	//-------------------------------------------------------------------------------------
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	//-------------------------------------------------------------------------------------
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//-------------------------------------------------------------------------------------
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	//-------------------------------------------------------------------------------------
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);
	//-------------------------------------------------------------------------------------

	while (true)
	{
		Ogre::WindowEventUtilities::messagePump();

		if (mWindow->isClosed())
		{
			return false;
		}

		if (!mRoot->renderOneFrame()) return false;
	}
	return true;
}

