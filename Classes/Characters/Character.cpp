#include "Character.h"
#include "../Maps/MapManager.h"

Character::Character()
{
	this->id = 0;
	this->canMove = true;
	this->isMoving = false;
	this->isMoveActing = false;
	this->isMoveEnded = true;
	this->isRun = false;
	this->oldAnimePos = 0;
	this->direction = Character::DIRECTION::DOWN;
	this->moveSpeed = 112.f;// px/s
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
	this->sprite->setScale(0.85f);

	schedule(schedule_selector(Character::moveAnimate), 0.11f);

	scheduleUpdate();

	if (COCOS2D_DEBUG == 1)
	{
		auto rect = DrawNode::create();
		Size sprtSize = this->sprite->getContentSize();
		rect->drawRect(Vec2(-sprtSize.width, -sprtSize.height),
			Vec2(sprtSize.width, sprtSize.height),
			Color4F::RED);
		this->addChild(rect, 99);
	}

	this->addChild(this->sprite);
}

void Character::setMovePos(float delta)
{
	this->collision = Character::COLLISION::NONE;

	if (this->canMove == false)
	{
		return;
	}

	auto *mapManager = (MapManager*)this->getParent();

	if (mapManager == nullptr)
	{
		return;
	}

	auto *mapInfo = (TMXTiledMap*)this->getParent();

	if (mapInfo == nullptr)
	{
		return;
	}

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

	Size sprtSize = this->sprite->getContentSize();

	auto barriers = mapInfo->getLayer("BARRIER");
	if (barriers)
	{
		if(barriers->getTileAt(Vec2(xx / tileSize.width, ((mapSize.height * tileSize.height) - yy) / tileSize.height)))
		{
			this->collision = Character::COLLISION::BARRIER;
		}
	}

	if (this->isMoving == false)
	{
		return;
	}

	this->isMoving = false;

	this->isMoveActing = true;

	if (this->isMoveEnded == false)
	{
		return;
	}

	if (xx <= 0 || yy <= 0)
	{
		return;
	}
	if (xx >= (mapSize.width * tileSize.width) || yy >= (mapSize.height * tileSize.height))
	{
		return;
	}

	if (this->collision == Character::COLLISION::BARRIER)
	{
		if (this->charType == Character::CHARTYPE::MAIN)
		{
			return;
		}
	}

	float speed = this->moveSpeed;

	if (this->isRun)
	{
		speed *= 1.5f;
	}

	float moveTime = tileSize.width / speed;
	
	auto moveStart = CallFunc::create(this, CC_CALLFUNC_SELECTOR(Character::moveActionStart));
	auto moveTo = MoveTo::create(moveTime, Vec2(xx, yy));
	auto moveEnd = CallFunc::create(this, CC_CALLFUNC_SELECTOR(Character::moveActionEnd));

	this->moveAction = Sequence::create(moveStart, moveTo, moveEnd, nullptr);

	this->runAction(this->moveAction);

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

void Character::moveActionStart()
{
	if (this->isMoveEnded == false)
	{
		this->moveAnimate(0.f);
	}

	this->isMoveEnded = false;
}

void Character::moveActionEnd()
{
	this->isMoveEnded = true;

	if (this->isMoveActing == true)
	{
		if (this->isMoving == false)
		{
			this->isMoving = true;
		}
	}
	else
	{
		this->isMoving = false;
	}
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

void Character::goTo(Vec2 pos)
{
	auto *mapInfo = (TMXTiledMap*)this->getParent();

	if (mapInfo)
	{
		auto mapSize = mapInfo->getMapSize();
		auto tileSize = mapInfo->getTileSize();

		float tileW, tileH;

		tileW = floor(tileSize.width);
		tileH = floor(tileSize.height);

		for (int ix = 0; ix < mapSize.width*tileW; ix = ix + tileW)
		{
			if (ix >= pos.x)
			{
				pos.x = ix - tileW / 2;
				break;
			}
		}

		for (int iy = 0; iy < mapSize.height*tileH; iy = iy + tileH)
		{
			if (iy >= pos.y)
			{
				pos.y = iy - tileH / 2;
				break;
			}
		}
	}

	this->setPosition(pos);
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

void Character::setIsMoveActing(bool isMoveActing)
{
	this->isMoveActing = isMoveActing;
}

bool Character::getIsMoveActing()
{
	return this->isMoveActing;
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