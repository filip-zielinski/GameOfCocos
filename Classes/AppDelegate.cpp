#include "AppDelegate.h"

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
		glview = GLViewImpl::create("Game of Cocos");
		glview->setFrameSize(1920, 1080);
		glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
		director->setOpenGLView(glview);
	}

	auto scene = mainScreen::createScene();
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}


