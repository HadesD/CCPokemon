#pragma once
/*
 Map Create by TiledMap (TMX)
 Must have:
 - (Object)DETAILS.MORE_INFO.(soundFlle,mapName)
 - 
 */

#ifndef __MAPMANAGER_H_INCLUDED__
#define __MAPMANAGER_H_INCLUDED__
#include "../stdafx.h"
#include "cocos2d.h"
#include "../Characters/Trainers/Trainer.h"
#include "../PlayLayer.h"
USING_NS_CC;

#ifndef ZORDER_ABOVE
#define ZORDER_ABOVE 15
#endif
#ifndef ZORDER_CHARACTER
#define ZORDER_CHARACTER 3
#endif
#ifndef ZORDER_TRAINER
#define ZORDER_TRAINER 4
#endif

class MapManager : public Node
{
public:
	MapManager();
	~MapManager();

	virtual void build();

	static TMXTiledMap* getMapInfo();
	void addCharToMap(Character* character, int zOrder);

#pragma region GETs/SETs
	void setInfo(TMXTiledMap *info);
	TMXTiledMap *getInfo();
#pragma endregion

private:
	int id;
	std::string name;
	std::string file;
	TMXTiledMap *info;
	//Scene *scene;

	static TMXTiledMap *mapInfo;
};

#endif