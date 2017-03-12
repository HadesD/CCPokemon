#include "Trainer.h"

Trainer::Trainer()
{
}


Trainer::~Trainer()
{
}

/*
 * Important Function
 * Must be called at the last of all Attr set
 */
void Trainer::build()
{
	Character::build();

	//Adding code here

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Trainer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Trainer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
}

void Trainer::update(float delta)
{
	this->cameraFollow();

	Character::update(delta);
}

void Trainer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->setIsMoving(true);

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->setDirection(DIRECTION::UP);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->setDirection(DIRECTION::DOWN);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->setDirection(DIRECTION::RIGHT);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->setDirection(DIRECTION::LEFT);
			break;
	}
	CCLOG("Pushed Key: %d", (int)keyCode);
}

void Trainer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->setIsMoving(false);

	CCLOG("Released Key: %d", (int)keyCode);
}

void Trainer::cameraFollow()
{

	auto layer = Director::getInstance()->getRunningScene()->getChildByName("Game");
	auto tileMap = (TMXTiledMap*)this->getParent();

	CCLOG("MAP: %d", tileMap->getMapSize().width);

	return;

	Size winSize = Director::getInstance()->getWinSize();

	Vec2 position = this->getPosition();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
	layer->setPosition(viewPoint);
}