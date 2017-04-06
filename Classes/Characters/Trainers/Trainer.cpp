#include "Trainer.h"
#include "../../Maps/MapManager.h"

Trainer::Trainer()
{
	this->lastMoveKeyCode = EventKeyboard::KeyCode::KEY_NONE;
}

Trainer::~Trainer()
{
}

void Trainer::build()
{
	this->charType = Trainer::CHARTYPE::MAIN_PLAYER;

	//Listen to Keyboard Event
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Trainer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Trainer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	//this->sprite->setContentSize(Size(this->sprite->getContentSize().width / 3, this->sprite->getContentSize().height / 2));

	schedule(schedule_selector(Trainer::onGate), 0.01f);

	schedule(schedule_selector(Trainer::onGrass), 0.7f);

	schedule(schedule_selector(Trainer::onCollisionBarrier), 1.1f);

	Character::build();
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

void Trainer::onCollisionBarrier(float delta)
{
	if (this->isMoveActing == false)
	{
		return;
	}
	if (this->collision != Trainer::COLLISION::BARRIER)
	{
		return;
	}
	playSound("emerald_0017.mp3", SOUNDTYPE::EFFECT, false);
}

void Trainer::onGate(float delta)
{
	auto *mapManager = (MapManager*)this->getParent();
	auto *mapInfo = (TMXTiledMap*)this->getParent();

	if (mapInfo == nullptr)
	{
		return;
	}

	float xx, yy;

	xx = this->getPositionX();
	yy = this->getPositionY();

	auto gates = mapInfo->getObjectGroup("GATES");

	if (gates == nullptr)
	{
		return;
	}

	bool foundGate = false;
	ValueMap g;
	auto charRect = this->getBoundingBox();
	for (auto gate : gates->getObjects())
	{
		g = gate.asValueMap();
		Rect gRect = Rect(g.at("x").asFloat(), g.at("y").asFloat(), g.at("width").asFloat(), g.at("height").asFloat());

		if (charRect.intersectsRect(gRect))
		{
			foundGate = true;
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
	if (toX.asBool() && toY.asBool())
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
	map->addCharToMap(this);
	this->goTo(toPos);
	this->release();
}

void Trainer::onGrass(float delta)
{
	if (this->isMoveActing == false)
	{
		return;
	}

	auto *mapInfo = (TMXTiledMap*)this->getParent();

	auto mapSize = mapInfo->getMapSize();
	auto tileSize = mapInfo->getTileSize();

	float xx, yy;

	xx = this->getPositionX();
	yy = this->getPositionY();

	auto grass = mapInfo->getLayer("GRASS");
	if (grass == nullptr)
	{
		return;
	}
	if (grass->getTileAt(Vec2(xx / tileSize.width, ((mapSize.height * tileSize.height) - yy) / tileSize.height)) == nullptr)
	{
		return;
	}

	playSound("Footsteps - Grass Sound Effect.mp3", SOUNDTYPE::EFFECT, false);

	srand(time(NULL));
	int rate = 50;

	if ((rand() % rate + 1) > (rate / 2 + rate / 3))
	{
		//this->setCanMove(false);
	}
}

void Trainer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Pressed Key: %d", (int)keyCode);

	if (this->canMove)
	{
		bool isMoveKey = false;
		switch (keyCode)
		{
			//Movement Key
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
			case EventKeyboard::KeyCode::KEY_W:
				this->direction = Trainer::DIRECTION::UP;
				isMoveKey = true;
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			case EventKeyboard::KeyCode::KEY_S:
				this->direction = Trainer::DIRECTION::DOWN;
				isMoveKey = true;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				this->direction = Trainer::DIRECTION::RIGHT;
				isMoveKey = true;
				break;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				this->direction = Trainer::DIRECTION::LEFT;
				isMoveKey = true;
				break;
			//Run Key
			case EventKeyboard::KeyCode::KEY_2:
				this->curAnimeType = Character::ANIMETYPE::RUN;
				break;
		}
		if (isMoveKey)
		{
			this->isMoving = true;
			this->lastMoveKeyCode = keyCode;
			this->updateSpriteAnimate(0.f);
		}
	}
}

void Trainer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	CCLOG("Released Key: %d", (int)keyCode);
	if (this->lastMoveKeyCode == keyCode)
	{
		this->isMoving = false;
		this->isMoveActing = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_2)
	{
		this->curAnimeType = Character::ANIMETYPE::WALK;
	}
}


void Trainer::cameraFollow()
{
	auto *mapManager = (MapManager*)this->getParent();

	if (mapManager == nullptr)
	{
		return;
	}

	auto *tileMap = (TMXTiledMap*)this->getParent();

	auto *layer = (PlayLayer*)mapManager->getParent();

	if (layer == nullptr)
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

	if (cam == nullptr)
	{
		return;
	}

	auto visibleSize = Director::getInstance()->getWinSize();

	auto position = this->getPosition();

	position = position * SCALE;

	auto mapSize = Size(tileMap->getMapSize().width * tileMap->getTileSize().width, tileMap->getMapSize().height * tileMap->getTileSize().height);

	mapSize = mapSize * SCALE;

	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	x = MIN(x, mapSize.width - visibleSize.width / 2);
	y = MIN(y, mapSize.height - visibleSize.height / 2);

	auto actualPosition = Vec2(x, y);

	auto centerOfView = Vec2(mapSize.width / 2, mapSize.height / 2);

	if (visibleSize.width > mapSize.width)
	{
		x = MAX(x, centerOfView.x);
	}
	if (visibleSize.height > mapSize.height)
	{
		y = MAX(y, centerOfView.y);
	}
	auto viewPoint = Vec2(x, y);

	cam->setPosition(viewPoint);
}