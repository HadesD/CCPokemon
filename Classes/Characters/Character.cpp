#include "Character.h"

Character::Character()
{
	this->id = 0;
	this->name = "Object";
	//this->sprite
	this->isMoving = false;
	this->canMove = false;
	this->direction = DIRECTION::DOWN;
	this->speed = 2.f;
}

Character::~Character()
{
	delete(this->sprite);
}

void Character::update(float delta)
{

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

#pragma endregion