#include "MapManager.h"

MapManager::MapManager()
{
	this->id = 0;
	//this->name = "";
	//this->mapInfo
}

MapManager::~MapManager()
{
	delete(this->mapInfo);
}

void MapManager::build()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto mapSize = Vec2((this->mapInfo->getMapSize().width*this->mapInfo->getTileSize().width), (this->mapInfo->getMapSize().height*this->mapInfo->getTileSize().height));
	auto mapPos = Vec2((mapSize.x - visibleSize.width) / 2, (mapSize.y - visibleSize.height) / 2);
	this->mapInfo->setPosition(MIN(0, mapPos.x), MIN(0, mapPos.y));
	CCLOG("Size X-Y: %f-%f", mapPos.x, mapPos.y);
	auto mapDetails = this->mapInfo->getObjectGroup("DETAILS");
	if (mapDetails)
	{
		auto moreInfo = mapDetails->getObject("MORE_INFO");

		std:string musicName = moreInfo.at("soundFile").asString();
		if (musicName != "")
		{
			playSound(musicName, "theme", true);
		}

		if (this->name == "")
		{
			this->name = moreInfo.at("mapName").asString();
		}
	}

	//Hide Barrier Color
	CCTMXLayer *_barrier;
	_barrier = this->mapInfo->getLayer("BARRIER");
	if (_barrier)
	{
		_barrier->setVisible(false);
	}
	//Hide Fighting _Grass Space
	CCTMXLayer *_grass;
	_grass = this->mapInfo->getLayer("GRASS");
	if (_grass)
	{
		_grass->setVisible(false);
	}

	this->addChild(this->mapInfo);
}
#pragma region GETs/SETs

void MapManager::setMapInfo(std::string mapInfo)
{
	this->mapInfo = TMXTiledMap::create(RD_MAPS + "/" + mapInfo);

	this->build();
}

TMXTiledMap *MapManager::getMapInfo()
{
	return this->mapInfo;
}
#pragma endregion

void MapManager::addCharToMap(Character* character, int zOrder)
{
	this->mapInfo->addChild(character, zOrder, "character");

}