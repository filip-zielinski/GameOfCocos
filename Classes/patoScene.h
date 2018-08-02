#pragma once

#include "cocos2d.h"

class patoScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(patoScene);

	void update(float) override;

private:
	cocos2d::Sprite *fif;
	cocos2d::Sprite *juch;

	cocos2d::JumpBy *jumps[4];

	float fifTime;
	float juchTime;

	float fifRand;
	float juchRand;


};



