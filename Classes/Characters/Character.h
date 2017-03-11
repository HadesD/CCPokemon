
#include "cocos2d.h"

USING_NS_CC;

enum DIRECTION
{
	UP = 0,
	DOWN = 2,
	LEFT = 1,
	RIGHT = 3,
};

class Character : public Node
{
public:
	Character();
	~Character();

	virtual void update(float delta);

	virtual void build();

#pragma region GETs/SETs

	void setSprite(Sprite *sprite);
	Sprite* getSprite();

	void setDirection(DIRECTION direction);

	void setIsMoving(bool isMoving);
	bool getIsMoving();

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
#pragma endregion

	void moveAnimate(float delta);
};
