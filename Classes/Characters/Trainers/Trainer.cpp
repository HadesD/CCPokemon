#include "Trainer.h"


Trainer::Trainer()
{
}


Trainer::~Trainer()
{
}

void Trainer::build()
{
	Character::build();

	//Adding code here

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Trainer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Trainer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
}

void Trainer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:

		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		break;
	}
	CCLOG("Pushed Key: %d", (int)keyCode);
}

void Trainer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Released Key: %d", (int)keyCode);
}