#include "Character.h"
#include "../Maps/MapManager.h"

Character::Character()
{
	this->id = 0;
	this->canMove = true;
	this->isMoving = false;
	this->isMoveActing = false;
	this->oldAnimePos = 0;
	this->direction = Character::DIRECTION::DOWN;
	this->speed = 0.2;// s/Tile
	this->charType = Character::CHARTYPE::PLAYER;
}

Character::~Character()
{
	delete(this->sprite);
}

void Character::update(float delta)
{
	this->setMovePos(delta);
}

void Character::build()
{
	schedule(schedule_selector(Character::moveAnimate), 0.11f);

	scheduleUpdate();

	if (COCOS2D_DEBUG == 1)
	{
		auto rect = DrawNode::create();
		Size sprtSize = this->sprite->getContentSize();
		rect->drawRect(Vec2(-sprtSize.width / 2, -sprtSize.height / 2),
			Vec2(sprtSize.width/2, sprtSize.height/2),
			Color4F::RED);
		this->addChild(rect, 99);
	}
	this->sprite->setScale(0.75);

	this->addChild(this->sprite);
}

void Character::setMovePos(float delta)
{
	this->collision = Character::COLLISION::NONE;

	if (this->canMove == false)
	{
		return;
	}

	if (this->isMoving == false) {
		return;
	}

	this->isMoving = false;

	auto *mapManager = (MapManager*)this->getParent();

	if (!mapManager)
	{
		return;
	}
	auto *mapInfo = (TMXTiledMap*)this->getParent();
	auto mapSize = mapInfo->getMapSize();
	auto tileSize = mapInfo->getTileSize();

	float xx, yy, tileW, tileH;

	xx = this->getPositionX();
	yy = this->getPositionY();

	tileW = tileSize.width;
	tileH = tileSize.height;

	switch (this->direction)
	{
		case Character::DIRECTION::UP:
			yy += tileH;
			break;
		case Character::DIRECTION::DOWN:
			yy -= tileH;
			break;
		case Character::DIRECTION::LEFT:
			xx -= tileW;
			break;
		case Character::DIRECTION::RIGHT:
			xx += tileW;
			break;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Size sprtSize = Size(4.f, 16.f);//this->sprite->getContentSize();

	if (xx - sprtSize.width/2 <= 0 || yy - sprtSize.height/2 <= 0)
	{
		return;
	}
	if(xx + sprtSize.width / 2 >= (mapSize.width * tileSize.width) || yy + sprtSize.height / 2 >= (mapSize.height * tileSize.height))
	{
		return;
	}

	auto barriers = mapInfo->getLayer("BARRIER");
	if (barriers) {
		if(barriers->getTileAt(Vec2(xx / tileSize.width, ((mapSize.height * tileSize.height) - yy) / tileSize.height)))
		{
			this->collision = Character::COLLISION::BARRIER;
			if(this->charType == Character::CHARTYPE::MAIN)
			{
				return;
			}
		}
	}

	auto moveTo = MoveTo::create(this->speed, Vec2(xx, yy));
	auto endAction = CallFuncN::create([&](Node* sender) {
		if (this->isMoveActing) {
			this->isMoving = true;
		}
	});

	this->runAction(Sequence::create(moveTo, endAction, nullptr));

	auto grass = mapInfo->getLayer("GRASS");
	if (grass) {
		if(grass->getTileAt(Vec2(xx / tileSize.width, ((mapSize.height * tileSize.height) - yy) / tileSize.height)))
		{
			this->collision = Character::COLLISION::GRASS;
		}
	}

	/*auto jumpSpace = mapInfo->getLayer("JUMPPASS");
	if (jumpSpace) {
		if (jumpSpace->getTileAt(Vec2(xx / mapInfo->getTileSize().width, ((mapInfo->getMapSize().height * mapInfo->getTileSize().height) - yy) / mapInfo->getTileSize().height)))
		{
			if (this->direction != DIRECTION::DOWN)
			{
				return;
			}
			this->setPositionY(yy - mapInfo->getTileSize().height);
		}
	}*/

}

void Character::moveAnimate(float delta)
{

	if (this->canMove == false)
	{
		this->oldAnimePos = 0;
	}
	if(this->isMoveActing)
	{
		this->oldAnimePos++;
		if (this->oldAnimePos == 3)
		{
			this->oldAnimePos = 0;
		}
	}
	else
	{
		this->oldAnimePos = 0;
	}
	this->sprite->setTextureRect(Rect(32.f*this->oldAnimePos, 32.f*this->direction, 32.f, 32.f));
}

#pragma region GETs/SETs

void Character::setSprite(Sprite *sprite)
{
	this->sprite = sprite;
}

Sprite* Character::getSprite()
{
	return this->sprite;
}

void Character::setIsMoving(bool isMoving)
{
	this->isMoving = isMoving;
}

bool Character::getIsMoving()
{
	return this->isMoving;
}

void Character::setDirection(Character::DIRECTION direction)
{
	this->direction = direction;
}
Character::DIRECTION Character::getDirection()
{
	return this->direction;
}
void Character::setName(std::string name)
{
	this->name = name;
}
std::string Character::getName()
{
	return this->name;
}
void Character::setCanMove(bool canMove)
{
	this->canMove = canMove;
}
bool Character::getCanMove()
{
	return this->canMove;
}
void Character::setCharType(Character::CHARTYPE charType)
{
	this->charType = charType;
}
Character::CHARTYPE Character::getCharType()
{
	return this->charType;
}
void Character::setCollision(Character::COLLISION collision)
{
	this->collision = collision;
}
Character::COLLISION Character::getCollision()
{
	return this->collision;
}
#pragma endregion