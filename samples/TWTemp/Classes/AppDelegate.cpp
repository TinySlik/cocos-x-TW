#include "AppDelegate.h"
#include "GameSystemDelegate.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"

#define DEBUG_OPENGL_TW
//#define DEBUG_GAF_TW
//#define DEBUG_EYECANDY_TW
//#define DEBUG_LIQUIDFUNTESTBED_TW
//#define DEBUG_SteeringBehaviors_TW

#ifdef DEBUG_OPENGL_TW
#include "HelloShader.h"
#include "OpenGL1.h"
#include "OpenGL2.h"
#include "OpenGL3.h"
#include "OpenGL4.h"
#include "OpenGL5.h"
#include "OpenGL6.h"
#endif

#ifdef DEBUG_GAF_TW
#include "GafFeatures.h"
#include "GAFShaderManager.h"
#endif

#ifdef DEBUG_EYECANDY_TW
#include "EyeCandyLayer.h"
#endif

#ifdef DEBUG_LIQUIDFUNTESTBED_TW
#include "Box2dView.h"
#endif

#ifdef DEBUG_SteeringBehaviors_TW
#include "SteeringBehaviorsScene.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::FIXED_HEIGHT);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60000);

#ifdef DEBUG_OPENGL_TW
    //添加春林三赛的资源路径
    FileUtils::getInstance()->addSearchPath("mysource");
    
    // create a scene. it's an autorelease object
    director->runWithScene(OpenGL2::createScene());
    return true;
    
#endif
    
#ifdef DEBUG_GAF_TW
    
    FileUtils::getInstance()->addSearchPath("GAFexample");
    
    // create a scene. it's an autorelease object
    cocos2d::Scene *pScene = GafFeatures::scene();
    
    // run
    director->runWithScene(pScene);
    
    return true;
    
#endif
    
#ifdef DEBUG_EYECANDY_TW
    FileUtils::getInstance()->addSearchPath("eyeCandyResource");
    
    auto scene = Scene::create();
    auto layer = EyeCandyLayer::create();
    scene->addChild(layer);
    
    director->runWithScene(scene);
    
    return true;
#endif
    
#ifdef DEBUG_LIQUIDFUNTESTBED_TW
    FileUtils::getInstance()->addSearchPath("BoxwdTestBedResource");
    auto scene = Box2DView::createScene();
    
    director->runWithScene(scene);
    
    return true;
#endif
    
    
#ifdef DEBUG_SteeringBehaviors_TW
    auto scene = SteeringBehaviors::createScene();
    
    director->runWithScene(scene);
    
    return true;
#endif
    //初始化GameSystemDelegate,在创建UI之前
    GameSystemDelegate* _gameSystem=new GameSystemDelegate();
    // run
    director->runWithScene(WelcomeScene::scene());
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
