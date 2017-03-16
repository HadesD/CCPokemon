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

	//Check if Stand On The Grass
	schedule(schedule_selector(Trainer::onGate), 0.01f);

	//Check if Stand On The Grass
	schedule(schedule_selector(Trainer::onGrass), 0.01f);
}

void Trainer::update(float delta)
{
	Character::update(delta);

	this->cameraFollow();
}

void Trainer::setMovePos(float delta)
{
	Character::setMovePos(delta);

}

void Trainer::onGate(float dt)
{
	auto *mapManager = (MapManager*)this->getParent();
	auto *mapInfo = (TMXTiledMap*)this->getParent();

	if (!mapInfo)
	{
		return;
	}

	float xx, yy;

	xx = this->getPositionX();
	yy = this->getPositionY();

	auto gates = mapInfo->getObjectGroup("GATES");

	if (!gates)
	{
		return;
	}

	for (auto gate : gates->getObjects())
	{
		auto g = gate.asValueMap();
		Rect charRect = Rect(xx, yy, this->getContentSize().width/2, this->getContentSize().height/2);
		Rect gRect = Rect(g.at("x").asFloat(), g.at("y").asFloat(), g.at("width").asFloat(), g.at("height").asFloat());

		CCLOG("Player %f", xx);
		CCLOG("Gate Found!!!! %f", g.at("x").asFloat());
		if (gRect.intersectsRect(charRect))
		{
			CCLOG("Gate Found!!!!");
		}
	}

	return;

	//Move to next map
	auto *layer = (PlayLayer *)mapManager->getParent();
	this->retain();
	mapInfo->removeChild(this, false);
	mapInfo->removeAllChildren();
	mapManager->removeAllChildren();
	layer->removeAllChildren();
	auto map = new MapManager;
	map->setMapInfo("PALLETTOWN_CITY.tmx");
	layer->addChild(map);
	auto mapDetails = map->getMapInfo()->getObjectGroup("DETAILS");

	if (mapDetails)
	{
		auto playerStart = mapDetails->getObject("FLY_SPACE");
		if (playerStart["x"].asBool())
		{
			this->setPosition(Vec2(playerStart["x"].asFloat(), playerStart["y"].asFloat()));
		}
	}
	this->setIsMoving(false);
	map->addCharToMap(this, ZORDER_TRAINER);
	this->release();
}

void Trainer::onGrass(float dt)
{
	if (this->getIsMoving() == false)
	{
		return;
	}

	auto *mapManager = (MapManager*)this->getParent();
	auto *mapInfo = (TMXTiledMap*)this->getParent();

	if (!mapInfo)
	{
		return;
	}

	float xx, yy;

	xx = this->getPositionX();
	yy = this->getPositionY();

	TMXLayer *grass = mapInfo->getLayer("GRASS");
	if (grass) {
		if (grass->getTileAt(Vec2(Vec2(xx, yy).x / mapInfo->getTileSize().width, ((mapInfo->getMapSize().height * mapInfo->getTileSize().height) - Vec2(xx, yy).y) / mapInfo->getTileSize().height)))
		{
			playSound("Footsteps - Grass Sound Effect.mp3", "effect", false);

			srand(time(NULL));
			int a = rand() % 50 + 1;

			if (a > 30)
			{
				//this->setCanMove(false);
			}
		}
	}
}

void Trainer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Pressed Key: %d", (int)keyCode);

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

	Size winSize = Director::getInstance()->getVisibleSize();

	Vec2 position = this->getPosition();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	//CCLOG("Trainer: %f:%f", position.x, position.y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
	auto *layer = (PlayLayer *)mapManager->getParent();
	//CCLOG("MapPos: %f:%f", mapManager->getPosition().x, mapManager->getPosition().x);
	//CCLOG("ViewPos: %f:%f", viewPoint.x, viewPoint.y);
	tileMap->setPosition(viewPoint);
}