#include "ExordiumApplication.h"

ExordiumApplication::ExordiumApplication(void)
   : mRoot(0),
   mCamera(0),
   mSceneMgr(0),
   mWindow(0),
   mResourcesCfg(Ogre::StringUtil::BLANK),
   mPluginsCfg(Ogre::StringUtil::BLANK)
{
}

ExordiumApplication::~ExordiumApplication(void)
{
}


bool ExordiumApplication::go(void)
{
   bool result = true;
   mRoot = new Ogre::Root();

   Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/materials/programs", "FileSystem", "General");
   Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/materials/scripts", "FileSystem", "General");
   Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/materials/textures", "FileSystem", "General");
   Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../resources/models", "FileSystem", "General");

   if (!mRoot->restoreConfig())
   {
      result = mRoot->showConfigDialog();
   }

   if (result)
   {
      mWindow = mRoot->initialise(true, "Exordium Window");
      mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
      mCamera = mSceneMgr->createCamera("PlayerCam");

      mCamera->setPosition(Ogre::Vector3(0, 10, 200));
      mCamera->setNearClipDistance(50);

      Ogre::Viewport* vp = mWindow->addViewport(mCamera);
      vp->setBackgroundColour(Ogre::ColourValue(0.01f, 0, 0));

      Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

      Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
      Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

      mCamera->lookAt(headNode->getPosition());

      headNode->attachObject(ogreHead);

      mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1f, 0.0f, 0.0f));

      {
         Ogre::Light* light = mSceneMgr->createLight("MainLight");
         light->setSpecularColour(Ogre::ColourValue(1.f, 1.f, 1.f));
         light->setDiffuseColour(Ogre::ColourValue(1.0f, 0.75f, 0.5f));
         light->setPosition(-100, 200, 50);
         Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
         lightNode->attachObject(light);
      }

      {
         Ogre::Light* light = mSceneMgr->createLight("BackLight");
         light->setSpecularColour(Ogre::ColourValue(1.f, 1.f, 1.f));
         light->setDiffuseColour(Ogre::ColourValue(0.9f, 0.9f, 1.0f));
         light->setPosition(50, 50, -50);
         Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
         lightNode->attachObject(light);
      }

      while (result)
      {
         Ogre::WindowEventUtilities::messagePump();

         if (!mRoot->renderOneFrame())
         {
            result = false;
         }

         if (mWindow->isClosed())
         {
            result = false;
         }
      }
   }

   delete mRoot;
   return result;
}
