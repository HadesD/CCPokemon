#include "MapManager.h"

TMXTiledMap *MapManager::mapInfo = nullptr;

MapManager::MapManager()
{
	this->id = 0;
	//this->name = "";
	//this->file
	//this->info
}

MapManager::~MapManager()
{
	delete(this->info);
}

void MapManager::build()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto mapSize = Vec2((this->info->getMapSize().width*this->info->getTileSize().width), (this->info->getMapSize().height*this->info->getTileSize().height));
	auto mapPos = Vec2((mapSize.x - visibleSize.width) / 2, (mapSize.y - visibleSize.height) / 2);
	this->info->setPosition(MIN(0, mapPos.x), MIN(0, mapPos.y));

	auto moreInfo = this->info->getObjectGroup("DETAILS")->getObject("MORE_INFO");

	std:string musicName = moreInfo.at("soundFile").asString();
	if (musicName != "")
	{
		playSound((char *)(RD_S_MUSICS +"/"+ musicName).c_str(), "background", true);
	}

	if (this->name == "")
	{
		this->name = moreInfo.at("mapName").asString();
	}

	this->addChild(this->info);
	MapManager::mapInfo = this->info;
}
#pragma region GETs/SETs

void MapManager::setInfo(TMXTiledMap *info)
{
	this->info = info;
}

TMXTiledMap *MapManager::getInfo()
{
	return this->info;
}

TMXTiledMap* MapManager::getMapInfo()
{
	return MapManager::mapInfo;
}
#pragma endregion

void MapManager::addCharToMap(Character* character, int zOrder)
{
	this->info->addChild(character, zOrder, "character");

}