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
	juchRand = 1;
	fifRand = 1;
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

	this->scheduleUpdate();
	return true;
}

void patoScene::update(float delta)
{
	fifTime += delta;
	juchTime += delta;
	
	if (fifTime > fifRand)
	{
		fifTime = 0;
		fifRand = (rand() % 10 + 1) / 10.0;

		int xx = rand() % 300 - 150;
		auto jump2 = JumpBy::create(0.5, Vec2(xx, 0), 100, 1);
		fif->runAction(jump2);

	}

	if (juchTime > juchRand)
	{
		juchTime = 0;
		juchRand = (rand() % 10 + 5) / 10.0;


		int xx = rand() % 300 - 150;
		auto jump = JumpBy::create(0.5, Vec2(xx, 0), 100, 1);
		juch->runAction(jump);

	}

	
}