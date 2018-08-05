#pragma once

#include "cocos2d.h"

USING_NS_CC;

class patoScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(patoScene);

	void update(float) override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
	enum
	{
		KEY_LEFT_BIT  = 0x1,
		KEY_RIGHT_BIT = 0x2,
		KEY_UP_BIT    = 0x4,
		KEY_DOWN_BIT  = 0x8,
		KEY_SPACE_BIT = 0x10
	};
	cocos2d::Sprite *fif;
	cocos2d::Sprite *juch;
	cocos2d::Sprite *chestnut;
	cocos2d::Label *scoreLabel;

	float fifTime;
	float juchTime;
	float chestnutTime;

	float chestnutInvisibleTime;
	float chestnutInHandTime;
	bool chestnutInHand;

	float fifDebouncer;
	float juchDebouncer;
	
	std::map<EventKeyboard::KeyCode, unsigned int> keyMap;
	unsigned int keyBitmap;

	int score;
};



