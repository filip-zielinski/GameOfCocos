#pragma once

#include "cocos2d.h"
#include "patoScene.h"

USING_NS_CC;

class mainScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(mainScreen);

	void update(float) override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

private:
	// List of all scenes to choose from main screen
	std::vector<cocos2d::Scene*> scenesList;
	int currentScene;

};