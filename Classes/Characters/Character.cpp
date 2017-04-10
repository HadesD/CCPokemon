#include "Character.h"
#include "../Maps/MapManager.h"

Character::Character()
{
	this->id = 0;
	this->canMove = true;
	this->isMoving = false;
	this->isMoveActing = false;
	this->isMoveEnded = true;
	this->curAnimeType = Character::ANIMETYPE::STAND;
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
	if (this->curAnimeType != Character::ANIMETYPE::RUN)
	{
		if (this->isMoveActing == true)
		{
			this->curAnimeType = Character::ANIMETYPE::WALK;
		}
		else
		{
			this->curAnimeType = Character::ANIMETYPE::STAND;
		}
	}

	this->setMovePos(delta);
}

void Character::build()
{

	schedule(schedule_selector(Character::updateSpriteAnimate), 0.13f);

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
	
	if (this->charType == Character::CHARTYPE::MAIN_PLAYER || this->charType == Character::CHARTYPE::PLAYER)
	{
		//Trainer 's Name 's Label
		auto nameLabel = Label::createWithSystemFont(this->name, "Arial", 11);
		nameLabel->setColor(Color3B(255, 255, 255));
		float padding = 4.f;
		auto nameBGLayer = LayerColor::create(Color4B(0, 0, 0, 80), nameLabel->getContentSize().width + padding, nameLabel->getContentSize().height);
		nameLabel->setPosition(nameBGLayer->getContentSize().width / 2, nameBGLayer->getContentSize().height / 2);
		nameBGLayer->addChild(nameLabel);
		nameBGLayer->setPosition(-nameBGLayer->getContentSize().width / 2, this->sprite->getContentSize().height / 2 + 2);
		this->addChild(nameBGLayer);
	}

	this->sprite->setPosition(Vec2(0, 3));

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

	/*auto barriers = mapInfo->getLayer("BARRIER");
	if (barriers)
	{
		if(barriers->getTileAt(Vec2(xx / tileSize.width, ((mapSize.height * tileSize.height) - yy) / tileSize.height)))
		{
			this->collision = Character::COLLISION::BARRIER;
		}
	}*/

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
		if (this->charType == Character::CHARTYPE::MAIN_PLAYER)
		{
			return;
		}
	}

	float speed = this->moveSpeed;

	switch (this->curAnimeType)
	{
		case Character::ANIMETYPE::RUN:
			speed *= 1.5f;
			break;
		case Character::ANIMETYPE::BIKE:
			speed *= 1.8f;
			break;
	}

	float moveTime = tileSize.width / speed;
	
	auto moveStart = CallFunc::create([&]()
	{
		if (this->isMoveEnded == false)
		{
			this->updateSpriteAnimate(0.f);
		}

		this->isMoveEnded = false;
	});
	auto moveTo = MoveTo::create(moveTime, Vec2(xx, yy));
	auto moveEnd = CallFunc::create([&]()
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
	});

	auto moveAction = Sequence::create(moveStart, moveTo, moveEnd, nullptr);

	this->runAction(moveAction);

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

void Character::updateSpriteAnimate(float delta)
{
	int w, h, x, y;

	w = 16;
	h = 20;
	x = 0;
	y = 0;

	//this->curAnimeType = Character::ANIMETYPE::BIKE;

	switch (this->curAnimeType)
	{
		case Character::ANIMETYPE::STAND:
			x = w + 1;
			break;
		case Character::ANIMETYPE::RUN:
			x = (w + 1) * 3 + 5;
			if (this->isMoveActing == true)
			{
				x += (w + 1) * this->oldAnimePos;
				this->oldAnimePos++;
				if (this->oldAnimePos >= 3)
				{
					this->oldAnimePos = 0;
				}
			}
			else
			{
				x += w + 1;
			}
			break;
		case Character::ANIMETYPE::WALK:
			x = (w + 1) * this->oldAnimePos;

			this->oldAnimePos++;

			if (this->oldAnimePos >= 3)
			{
				this->oldAnimePos = 0;
			}
			break;
		case Character::ANIMETYPE::BIKE:
			x = (w + 1) * 3 + 5;
			x += (w + 1) * 3 + 5;

			w = 20;
			h = 22;

			if (this->isMoveActing == true)
			{
				x += (w + 1) * this->oldAnimePos;
				this->oldAnimePos++;
				if (this->oldAnimePos >= 3)
				{
					this->oldAnimePos = 0;
				}
			}
			else
			{
				x += w + 1;
			}
			break;
	}

	switch (this->direction) 
	{
		case Character::DIRECTION::UP:
			y = h + 1;
			break;
		case Character::DIRECTION::DOWN:
			y = 0;
			break;
		case Character::DIRECTION::LEFT:
			y = (h + 1) * 2;
			break;
		case Character::DIRECTION::RIGHT:
			y = (h + 1) * 3;
			break;
	}

	this->sprite->setTextureRect(Rect(x, y, w, h));
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

void Character::setSprite(std::string sprite)
{
	this->sprite = Sprite::create(sprite, Rect(0, 0, 16.f, 20.f));
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