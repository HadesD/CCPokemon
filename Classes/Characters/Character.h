#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__
#include "cocos2d.h"

USING_NS_CC;

class Character : public Node
{
public:
	enum DIRECTION
	{
		UP = 0,
		DOWN = 2,
		LEFT = 1,
		RIGHT = 3,
	};
	enum class CHARTYPE
	{
		NPC,
		PLAYER,
		MAIN,
	};
	enum class COLLISION
	{
		NONE,
		BARRIER,
		GRASS,
		JUMPPASS,
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

	void setSprite(Sprite *sprite);
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

	Sequence *moveAction;
	
#pragma region CharAttrs
	int id;
	std::string name;
	Sprite *sprite;
	bool canMove;
	bool isMoving;
	bool isMoveActing;
	bool isMoveEnded;
	bool isRun;
	float moveSpeed;
	Character::DIRECTION direction;
	int oldAnimePos;
	Character::CHARTYPE charType;
	Character::COLLISION collision;
#pragma endregion

	virtual void moveActionStart();
	virtual void moveActionEnd();
	void moveAnimate(float delta);
};
#endif