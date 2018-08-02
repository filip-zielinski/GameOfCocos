#include "AppDelegate.h"
#include "patoScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Really Pathological Game");
		glview->setFrameSize(1920, 1080);
		glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::EXACT_FIT);
		director->setOpenGLView(glview);
	}

	auto scene = patoScene::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}

