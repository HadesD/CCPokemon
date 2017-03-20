#ifndef __POKEMON_H_CCPOKEMON__
#define __POKEMON_H_CCPOKEMON__

#include "../stdafx.h"
#include "cocos2d.h"

USING_NS_CC;

class Pokemon : public Node
{
public:
	Pokemon();
	~Pokemon();

#pragma region GETs/SETs
	void setAttr();
	void getAttr();
#pragma endregion
private:
	void build();

	int id;
	std::string name;
	Sprite *sprite;

#pragma region Attributes

	int qlt;//Quality -> Point that decided these below
	
	int hp;//Health Point
	int atk;//Attack
	int def;//Defend
	int spd;//Speed
	int agl;//Agility : fasty?
	int exp;//Experience

#pragma endregion

#pragma region Skill_ID
	int skill1;
	int skill2;
	int skill3;
	int skill4;
#pragma endregion
};

#endif