#include "mainScreen.h"

USING_NS_CC;

Scene* mainScreen::createScene()
{
	auto scene = Scene::create();

	auto layer = mainScreen::create();

	scene->addChild(layer);

	return scene;
}

bool mainScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto label = Label::createWithSystemFont("Game of Cocos", "Arial", 96);
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(label, 1);

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = CC_CALLBACK_2(mainScreen::onKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	return true;
}

void mainScreen::update(float delta)
{
	// main menu behaviour
}

void mainScreen::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto scene = patoScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
}