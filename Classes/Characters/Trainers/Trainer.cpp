#include "Trainer.h"
#include "../../Maps/MapManager.h"

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

	LabelTTF* closeLabel = LabelTTF::create(this->getName(), "Marker Felt", 11);
	closeLabel->setPositionY(this->getSprite()->getContentSize().height/2);
	this->addChild(closeLabel, 99);
}

void Trainer::update(float delta)
{
	Character::update(delta);

	this->cameraFollow();
}

void Trainer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->setDirection(DIRECTION::UP);
			this->setIsMoving(true);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->setDirection(DIRECTION::DOWN);
			this->setIsMoving(true);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->setDirection(DIRECTION::RIGHT);
			this->setIsMoving(true);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->setDirection(DIRECTION::LEFT);
			this->setIsMoving(true);
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
	auto layer = (Layer *)this->getParent();
	auto *tileMap = (TMXTiledMap*)this->getParent();

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