#pragma once
#ifndef __TRAINER_H_INCLUDED__
#define __TRAINER_H_INCLUDED__
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

	virtual void update(float delta);

#pragma region GETs/SETs

	virtual void setMovePos(float delta);

#pragma endregion

protected:

	void cameraFollow();
};

#endif