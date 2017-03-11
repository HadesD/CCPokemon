#include "Character.h"

Character::Character()
{
	this->id = 0;
	this->name = "Object";
	//this->sprite
	this->isMoving = false;
	this->canMove = true;
	this->oldAnimePos = 0;
	this->direction = DIRECTION::DOWN;
	this->speed = 2.f;
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

/*
 * Important Function
 * Must be called at the last of all Attr set
 */
void Character::build()
{
	schedule(schedule_selector(Character::moveAnimate), 0.17f);

	scheduleUpdate();

	this->addChild(this->sprite);
}

void Character::setMovePos(float delta)
{
	if (this->canMove == false)
	{
		return;
	}

	switch (this->direction)
	{
		case DIRECTION::UP:
			this->setPosition(Vec2(this->getPositionX(), (this->getPositionY() + this->speed)));
			break;
		case DIRECTION::DOWN:
		default:
			this->setPosition(Vec2(this->getPositionX(), (this->getPositionY() - this->speed)));
			break;
		case DIRECTION::LEFT:
			this->setPosition(Vec2(this->getPositionX() - this->speed, this->getPositionY()));
			break;
		case DIRECTION::RIGHT:
			this->setPosition(Vec2(this->getPositionX() + this->speed, this->getPositionY()));
			break;
	}
}

/*
* Set Character new Movement Animate
*/
void Character::moveAnimate(float delta)
{

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
#pragma endregion