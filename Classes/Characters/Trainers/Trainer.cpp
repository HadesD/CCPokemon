#include "Trainer.h"
#include "../../Maps/MapManager.h"

Trainer::Trainer()
{
}


Trainer::~Trainer()
{
}

void Trainer::build()
{
	Character::build();

	//Listen to Keyboard Event
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Trainer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Trainer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	//Trainer 's Name 's Label
	LabelTTF* nameLabel = LabelTTF::create(this->getName(), "Marker Felt", 11);
	nameLabel->setColor(ccc3(255, 255, 255));
	float padding = 4.f;
	CCLayerColor* nameBGLayer = CCLayerColor::create(ccc4(0, 0, 0, 80), nameLabel->getContentSize().width + padding, nameLabel->getContentSize().height);
	nameLabel->setPosition(nameBGLayer->getContentSize().width / 2, nameBGLayer->getContentSize().height / 2);
	nameBGLayer->addChild(nameLabel);
	nameBGLayer->setPosition(-this->getSprite()->getContentSize().width, this->getSprite()->getContentSize().height / 2);
	this->addChild(nameBGLayer, 99);

	schedule(schedule_selector(Trainer::onGate), 0.01f);

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

	bool foundGate = false;
	ValueMap g;
	Size sprtSize = Size(4.f, 4.f);
	Rect charRect = Rect(xx, yy, xx + sprtSize.width, yy + sprtSize.height);
	for (auto gate : gates->getObjects())
	{
		g = gate.asValueMap();
		Rect gRect = Rect(g.at("x").asFloat(), g.at("y").asFloat(), g.at("width").asFloat() + g.at("x").asFloat(), g.at("height").asFloat() + g.at("y").asFloat());

		if (gRect.intersectsRect(charRect))
		{
			foundGate = true;
			CCLOG("Player x-y-W-H: %f-%f-%f-%f", xx, yy, sprtSize.width, sprtSize.height);
			CCLOG("Gate x-y-W-H: %f-%f-%f-%f", g.at("x").asFloat(), g.at("y").asFloat(), g.at("width").asFloat(), g.at("height").asFloat());
			break;
		}
	}

	if (foundGate == false)
	{
		return;
	}
	auto toMap = g["mapFile"];
	if (toMap.asString() == "")
	{
		return;
	}
	//Move to next map
	auto *layer = (PlayLayer *)mapManager->getParent();
	this->retain();
	mapInfo->removeChild(this, false);
	mapInfo->removeAllChildren();
	mapManager->removeAllChildren();
	layer->removeChild(mapManager);
	auto map = new MapManager;
	map->setMapInfo(toMap.asString());
	layer->addChild(map);
	auto toPos = Vec2(0, 0);
	auto toX = g["toX"];
	auto toY = g["toY"];
	if (toX.asFloat())
	{
		toPos = Vec2(toX.asFloat() + map->getMapInfo()->getTileSize().width/2, map->getMapInfo()->getMapSize().height * map->getMapInfo()->getTileSize().height - toY.asFloat());
	}
	else
	{
		auto mapDetails = map->getMapInfo()->getObjectGroup("DETAILS");
		if (mapDetails)
		{
			auto playerStart = mapDetails->getObject("FLY_SPACE");
			if (playerStart["x"].asBool())
			{
				toPos = Vec2(playerStart["x"].asFloat() + map->getMapInfo()->getTileSize().width / 2, playerStart["y"].asFloat() + map->getMapInfo()->getTileSize().height / 2);
			}
		}
	}
	this->setPosition(toPos);
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

	auto grass = mapInfo->getLayer("GRASS");
	if (grass) {
		if (grass->getTileAt(Vec2(xx / mapInfo->getTileSize().width, ((mapInfo->getMapSize().height * mapInfo->getTileSize().height) - yy) / mapInfo->getTileSize().height)))
		{
			//playSound("Footsteps - Grass Sound Effect.mp3", "effect", false);

			srand(time(NULL));
			int rate =  50;

			if ((rand() % rate + 1) > (rate / 2 + rate / 3))
			{
				//this->setCanMove(false);
			}
		}
	}
}

void Trainer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Pressed Key: %d", (int)keyCode);

	if (this->getCanMove())
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			this->setDirection(DIRECTION::UP);
			this->setIsMoving(true);
			this->lastKeyCode = keyCode;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			this->setDirection(DIRECTION::DOWN);
			this->setIsMoving(true);
			this->lastKeyCode = keyCode;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			this->setDirection(DIRECTION::RIGHT);
			this->setIsMoving(true);
			this->lastKeyCode = keyCode;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			this->setDirection(DIRECTION::LEFT);
			this->setIsMoving(true);
			this->lastKeyCode = keyCode;
			break;
		}
	}
}

void Trainer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Released Key: %d", (int)keyCode);
	if (this->lastKeyCode == keyCode)
	{
		this->setIsMoving(false);
	}
}

void Trainer::cameraFollow()
{
	auto *mapManager = (MapManager*)this->getParent();

	if (!mapManager)
	{
		return;
	}

	auto *tileMap = (TMXTiledMap*)this->getParent();

	auto *layer = (PlayLayer*)mapManager->getParent();

	if (!layer)
	{
		return;
	}

	Camera *cam;
	for (auto child : layer->getChildren())
	{
		auto tmp = (Camera*)child;
		if (tmp)
		{
			cam = (Camera*)tmp->getDefaultCamera();
			break;
		}
	}

	if (!cam)
	{
		return;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	float x, y;

	x = MAX(visibleSize.width / 2, this->getPositionX());
	y = MAX(visibleSize.height / 2, this->getPositionY());

	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - visibleSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	//cam->setPosition(this->getPosition());
	cam->setPosition(actualPosition);
}