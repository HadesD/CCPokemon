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

	//Listen to Keyboard Event
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Trainer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Trainer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	//Trainer 's Name
	LabelTTF* nameLabel = LabelTTF::create(this->getName(), "Marker Felt", 11);
	nameLabel->setColor(ccc3(255, 255, 255));
	float padding = 4.f;
	CCLayerColor* nameBGLayer = CCLayerColor::create(ccc4(0, 0, 0, 80), nameLabel->getContentSize().width + padding, nameLabel->getContentSize().height);
	nameLabel->setPosition(nameBGLayer->getContentSize().width / 2, nameBGLayer->getContentSize().height / 2);
	nameBGLayer->addChild(nameLabel);
	nameBGLayer->setPosition(-this->getSprite()->getContentSize().width, this->getSprite()->getContentSize().height / 2);
	this->addChild(nameBGLayer, 99);

}

void Trainer::update(float delta)
{
	Character::update(delta);

	this->cameraFollow();
}

void Trainer::setMovePos(float delta)
{
	Character::setMovePos(delta);

	auto *mapManager = (MapManager*)this->getParent();
	auto *mapInfo = (TMXTiledMap*)this->getParent();

	float xx, yy;

	xx = this->getPositionX();
	yy = this->getPositionY();

	//Move to next map
	auto *layer = (PlayLayer *)mapManager->getParent();
	this->retain();
	mapManager->removeChild(this);
	this->release();
	mapManager->retain();
	layer->removeChild(mapManager);
	//delete(mapManager);
	mapManager->setMapInfo("PALLETTOWN_CITY.tmx");
	//mapManager->build();
	mapManager->release();

	//Fight in Grass
	TMXLayer *barriers = mapInfo->getLayer("GRASS");
	if (barriers) {
		if (barriers->getTileAt(Point(Point(xx, yy).x / mapInfo->getTileSize().width, ((mapInfo->getMapSize().height * mapInfo->getTileSize().height) - Point(xx, yy).y) / mapInfo->getTileSize().height)))
		{
			playSound("Footsteps - Grass Sound Effect.mp3", "effect", false);

			srand(time(NULL));
			int a = rand() % 50 + 1;

			if (a > 30)
			{
				this->setCanMove(false);
			}
		}
	}
}

void Trainer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Pushed Key: %d", (int)keyCode);

	if (this->getCanMove() == false)
	{
		return;
	}
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
}

void Trainer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Released Key: %d", (int)keyCode);

	this->setIsMoving(false);
}

void Trainer::cameraFollow()
{
	auto *mapManager = (MapManager*)this->getParent();

	if (!mapManager)
	{
		return;
	}
	auto *tileMap = (TMXTiledMap*)this->getParent();

	if (!tileMap)
	{
		return;
	}

	Size winSize = Director::getInstance()->getWinSize();

	Vec2 position = this->getPosition();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
	auto *layer = (PlayLayer *)mapManager->getParent();
	layer->setPosition(viewPoint);
}