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

class MapManager : public Node
{
public:
	MapManager();
	~MapManager();

	virtual void build();

	void addCharToMap(Character* character);

public:
	void setMapInfo(std::string fileName);
	TMXTiledMap *getMapInfo();

private:
	int id;
	std::string name;
	TMXTiledMap *mapInfo;
};

#endif
