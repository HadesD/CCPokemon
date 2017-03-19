#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__
#include "cocos2d.h"

USING_NS_CC;

enum DIRECTION
{
	UP = 0,
	DOWN = 2,
	LEFT = 1,
	RIGHT = 3,
};
enum CHARTYPE
{
	NPC,
	PLAYER,
	MAIN,
};
enum COLLISION
{
	NONE,
	BARRIER,
	GRASS,
};

class Character : public Node
{
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

	void setDirection(DIRECTION direction);
	DIRECTION getDirection();

	void setIsMoving(bool isMoving);
	bool getIsMoving();

	void setName(std::string name);
	std::string getName();

	virtual void setMovePos(float delta);

	void setCanMove(bool canMove);
	bool getCanMove();

	void setCharType(CHARTYPE charType);
	CHARTYPE getCharType();

	void setCollision(COLLISION collision);
	COLLISION getCollision();

#pragma endregion

private:

#pragma region CharAttrs
	int id;
	std::string name;
	Sprite *sprite;
	bool isMoving;
	bool canMove;
	float speed;
	DIRECTION direction;
	int oldAnimePos;
	CHARTYPE charType;
	COLLISION collision;
#pragma endregion

	void moveAnimate(float delta);

};
#endif