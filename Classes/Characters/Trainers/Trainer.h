#pragma once

#include "../Character.h"

USING_NS_CC;

class Trainer : public Character
{
public:
	Trainer();
	~Trainer();

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual void build();

	void update(float delta);

protected:

	void cameraFollow();
};

