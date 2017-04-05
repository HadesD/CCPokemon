#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__
#include "cocos2d.h"

USING_NS_CC;

class Character : public Node
{
public:
	enum class DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
	enum class CHARTYPE
	{
		NPC,
		PLAYER,
		MAIN_PLAYER,
	};
	enum class COLLISION
	{
		NONE,
		BARRIER,
		GRASS,
		JUMPPASS,
	};
	enum class ANIMETYPE
	{
		STAND,
		WALK,
		RUN,
		BIKE,
	};
public:
	Character();
	~Character();

	virtual void update(float delta);

	/*
	 * Important Function
	 * Must be called at the last of all Attr set
	 */
	virtual void build();

#pragma region GETs/SETs

	void setSprite(std::string sprite);
	Sprite* getSprite();

	void setDirection(Character::DIRECTION direction);
	Character::DIRECTION getDirection();

	void setIsMoving(bool isMoving);
	bool getIsMoving();

	void setIsMoveActing(bool isMoving);
	bool getIsMoveActing();

	void setName(std::string name);
	std::string getName();

	virtual void setMovePos(float delta);

	void setCanMove(bool canMove);
	bool getCanMove();

	void setCharType(Character::CHARTYPE charType);
	Character::CHARTYPE getCharType();

	void setCollision(Character::COLLISION collision);
	Character::COLLISION getCollision();

	void goTo(Vec2 pos);

#pragma endregion

protected:
	
#pragma region CharAttrs
	int id;
	std::string name;
	Sprite *sprite;
	bool canMove;
	bool isMoving;
	bool isMoveActing;
	bool isMoveEnded;
	Character::ANIMETYPE curAnimeType;
	float moveSpeed;
	Character::DIRECTION direction;
	int oldAnimePos;
	Character::CHARTYPE charType;
	Character::COLLISION collision;
#pragma endregion

	void updateSpriteAnimate(float delta);
};
#endif