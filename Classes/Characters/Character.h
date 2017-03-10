
#include "cocos2d.h"

USING_NS_CC;

enum DIRECTION
{
	UP    = 1,
	RIGHT = 2,
	DOWN  = 3,
	LEFT  = 4,
};

class Character : public Node
{
public:
	Character();
	~Character();
	//static Character* create();
	//static Character* getInstance();

	virtual void update(float delta);



#pragma region GETs/SETs

	void setSprite(Sprite *sprite);
	Sprite* getSprite();

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
#pragma endregion

};
