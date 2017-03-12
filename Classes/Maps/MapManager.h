#pragma once

#include "../stdafx.h"
#include "cocos2d.h"
#include <SimpleAudioEngine.h>
#include "../Characters/Trainers/Trainer.h"

USING_NS_CC;

class MapManager : public Node
{
public:
	MapManager();
	~MapManager();

	virtual void build();

	static TMXTiledMap* getMapInfo();
	void addPlayerToTheMap(Character* character);

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

