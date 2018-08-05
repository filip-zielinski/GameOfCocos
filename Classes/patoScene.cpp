#include "patoScene.h"

USING_NS_CC;

Scene* patoScene::createScene()
{
	auto scene = Scene::create();

	auto layer = patoScene::create();
	
	scene->addChild(layer);

	return scene;
}

bool patoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	fifTime = 0;
	juchTime = 0;
	fifDebouncer = 0;
	juchDebouncer = 0;
	keyBitmap = 0;
	auto background = Sprite::create("ws_Summer_Meadow_&_Road_1920x1080.jpg");
	//background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(960, 480);
	this->addChild(background, 0);

	fif = Sprite::create("fif.png");
	fif->setAnchorPoint(Vec2(0, 0));
	fif->setPosition(700, 0);
	this->addChild(fif, 0);

	juch = Sprite::create("juch.png");
	juch->setAnchorPoint(Vec2(0, 0));
	juch->setPosition(1100, 0);
	this->addChild(juch, 0);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(patoScene::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(patoScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	keyMap = {
		{ EventKeyboard::KeyCode::KEY_LEFT_ARROW,  KEY_LEFT_BIT},
		{ EventKeyboard::KeyCode::KEY_RIGHT_ARROW, KEY_RIGHT_BIT },
		{ EventKeyboard::KeyCode::KEY_UP_ARROW,    KEY_UP_BIT },
		{ EventKeyboard::KeyCode::KEY_DOWN_ARROW,  KEY_DOWN_BIT },
		{ EventKeyboard::KeyCode::KEY_SPACE,       KEY_SPACE_BIT },
	};

	this->scheduleUpdate();
	return true;
}

void patoScene::update(float delta)
{
	fifTime += delta;
	juchTime += delta;
	
	// random, chaotic movement of juch
	if (juchTime > juchDebouncer)
	{
		juchTime = 0;
		juchDebouncer = (rand() % 10 + 5) / 10.0;

		int xx = rand() % 300 - 150;
		auto jump = JumpBy::create(0.5, Vec2(xx, 0), 100, 1);
		juch->runAction(jump);
	}
	
	// controlled movement of fif
	if (fifTime > fifDebouncer)
	{
		fifTime = 0;
		fifDebouncer = 0;
		if (keyBitmap == KEY_LEFT_BIT)
		{
			float pos = fif->getPositionX();
			pos -= 150 * delta;
			fif->setPositionX(pos);
		}
		else if (keyBitmap == KEY_RIGHT_BIT)
		{
			float pos = fif->getPositionX();
			pos += 150 * delta;
			fif->setPositionX(pos);
		}
		// arithmetic instead of bit operation to not confuse compiler
		else if (keyBitmap == (KEY_LEFT_BIT + KEY_UP_BIT))
		{
			auto jump = JumpBy::create(0.5, Vec2(-200, 0), 100, 1);
			fif->runAction(jump);
			fifDebouncer = 0.5;
		}
		else if (keyBitmap == (KEY_RIGHT_BIT + KEY_UP_BIT))
		{
			auto jump = JumpBy::create(0.5, Vec2(200, 0), 100, 1);
			fif->runAction(jump);
			fifDebouncer = 0.5;
		}
		else if (keyBitmap == KEY_UP_BIT)
		{
			auto jump = JumpBy::create(0.5, Vec2(0, 0), 100, 1);
			fif->runAction(jump);
			fifDebouncer = 0.5;
		}
		else
		{
		}
	}
}

void patoScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto keyIter = keyMap.find(keyCode);
	if (keyIter != keyMap.end())
	{
		// use bitmap for pressed keys for handling multiple pressed keys
		keyBitmap |= keyIter->second;
	}
}

void patoScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto keyIter = keyMap.find(keyCode);
	if (keyIter != keyMap.end())
	{
		keyBitmap &= ~keyIter->second;
	}
}