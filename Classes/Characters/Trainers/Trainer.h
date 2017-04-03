#ifndef __TRAINER_H_INCLUDED__
#define __TRAINER_H_INCLUDED__
#include "../Character.h"

USING_NS_CC;

class Trainer : public Character
{
public:
	Trainer();
	~Trainer();

	virtual void build();

	virtual void update(float delta);

#pragma region GETs/SETs

	virtual void setMovePos(float delta);

#pragma endregion

protected:

	EventKeyboard::KeyCode lastMoveKeyCode;

	void cameraFollow();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//Check if At the Gate
	void onGate(float dt);
	//Check if Stand On The Grass
	void onGrass(float dt);
	//On Collision with Barrier
	void onCollisionBarrier(float dt);

};

#endif