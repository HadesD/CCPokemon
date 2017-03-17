#include "Character.h"
#include "../Maps/MapManager.h"

Character::Character()
{
	this->id = 0;
	//this->name;
	//this->sprite;
	this->isMoving = false;
	this->canMove = true;
	this->oldAnimePos = 0;
	this->direction = DIRECTION::DOWN;
	this->speed = 2.5f;

}

Character::~Character()
{
	delete(this->sprite);
}

void Character::update(float delta)
{
	if (this->isMoving)
	{
		this->setMovePos(delta);
	}
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
	if (this->canMove == false)
	{
		return;
	}

	if (this->isMoving == false)
	{
		return;
	}

	auto *mapManager = (MapManager*)this->getParent();

	if (!mapManager)
	{
		return;
	}
	auto *mapInfo = (TMXTiledMap*)this->getParent();

	float xx, yy;

	xx = this->getPositionX();
	yy = this->getPositionY();

	switch (this->direction)
	{
		case DIRECTION::UP:
			yy += this->speed;
			break;
		case DIRECTION::DOWN:
			yy -= this->speed;
			break;
		case DIRECTION::LEFT:
			xx -= this->speed;
			break;
		case DIRECTION::RIGHT:
			xx += this->speed;
			break;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Size sprtSize = this->sprite->getContentSize();

	if (xx - sprtSize.width/2 <= 0 || yy - sprtSize.height/2 <= 0)
	{
		return;
	}
	if (xx + sprtSize.width/2 >= (mapInfo->getMapSize().width * mapInfo->getTileSize().width) || yy + sprtSize.height/2 >= (mapInfo->getMapSize().height * mapInfo->getTileSize().height))
	{
		return;
	}

	auto barriers = mapInfo->getLayer("BARRIER");
	if (barriers) {
		if (barriers->getTileAt(Vec2(xx / mapInfo->getTileSize().width, ((mapInfo->getMapSize().height * mapInfo->getTileSize().height) - yy) / mapInfo->getTileSize().height)))
		{
			playSound("barrier.wav", "effect", false);
			return;
		}
	}

	this->setPosition(Vec2(xx, yy));
}

void Character::moveAnimate(float delta)
{
	if (this->canMove == false)
	{
		this->oldAnimePos = 0;
	}
	this->sprite->setTextureRect(Rect(32.f*this->oldAnimePos, 32.f*this->direction, 32.f, 32.f));

	if (this->isMoving)
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

void Character::setDirection(DIRECTION direction)
{
	this->direction = direction;
}
DIRECTION Character::getDirection()
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
#pragma endregion