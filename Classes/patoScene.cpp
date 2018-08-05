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
	chestnutInHandTime = 1;
	chestnutInvisibleTime = 3;
	chestnutInHand = false;
	score = 0;
	auto background = Sprite::create("ws_Summer_Meadow_&_Road_1920x1080.jpg");
	//background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(960, 540);
	this->addChild(background, 0);

	fif = Sprite::create("fif.png");
	fif->setAnchorPoint(Vec2(0, 0));
	fif->setPosition(700, 0);
	this->addChild(fif, 1);

	juch = Sprite::create("juch.png");
	juch->setAnchorPoint(Vec2(0, 0));
	juch->setPosition(1100, 0);
	this->addChild(juch, 1);

	chestnut = Sprite::create("chestnut.png");
	chestnut->setAnchorPoint(Vec2(0, 0));
	chestnut->setPosition(0,0);
	chestnut->setScale(0.3, 0.3);
	this->addChild(chestnut, 0);

	scoreLabel = Label::createWithSystemFont("score: 0", "Arial", 48);
	scoreLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	scoreLabel->setPosition(900, 900);
	this->addChild(scoreLabel, 1);

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
	chestnutTime += delta;

	// random, chaotic movement of juch
	if (juchTime > juchDebouncer)
	{
		juchTime = 0;
		juchDebouncer = (rand() % 10 + 5) / 10.0;

		int xx = rand() % 300 - 150;
		auto juchPos = juch->getPosition();
		if (xx + juchPos.x > 1050 || juchPos.x - xx < 0)
		{
			xx = -xx;
		}
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

	//the flight of the chestnut
	if (chestnutTime > chestnutInvisibleTime && !chestnutInHand)
	{
		chestnutInHand = true;
	}
	if (chestnutInHand)
	{
		// give juch a nut
		auto juchVec = juch->getPosition();
		juchVec.x += 153;
		juchVec.y += 243;
		chestnut->setPosition(juchVec);
		chestnut->setZOrder(0);
	}
	if (chestnutInHand && chestnutTime > (chestnutInvisibleTime + chestnutInHandTime))
	{
		chestnutInvisibleTime = (rand() % 20 + 20) / 10.0;
		chestnutInHandTime = (rand() % 30 + 5) / 10.0;
		chestnutInHand = false;
		chestnutTime = 0;

		int throwHeight = rand() % 500 + 500;
		int throwPosX = rand() % 600;
		float throwPower = (rand() % 150 + 100) / 100.0;

		auto jump = JumpTo::create(throwPower, Vec2(throwPosX, 0), throwHeight, 1);
		chestnut->runAction(jump);
		chestnut->setZOrder(1);

		log("H: %d, X: %d, t: %d", throwHeight, throwPosX, throwPower);
	}

	//check if fif chatches the chestnut - simply compare position of the sprites 
	if (!chestnutInHand)
	{
		auto posCup = fif->getPosition();
		// x = 124-150, y = 463 - position of fif's cup relative to fif sprite
		auto posChestnut = chestnut->getPosition();
		if ((posChestnut.y + 20 > posCup.y + 461) &&
			(posChestnut.y + 13 < posCup.y + 463) &&
			(posChestnut.x + 43 > posCup.x + 124) &&
			(posChestnut.x + 13 < posCup.x + 150))
		{
			score += 1;
			chestnut->stopAllActions();
			scoreLabel->setString("score: " + std::to_string(score));
			chestnutInHand = true; //temporary
		}
	}
}

void patoScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto keyIter = keyMap.find(keyCode);
	if (keyIter != keyMap.end())
	{
		// use bitmap for pressed keys to handle multiple pressed keys
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