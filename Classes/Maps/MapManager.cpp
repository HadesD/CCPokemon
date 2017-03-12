#include "MapManager.h"

TMXTiledMap *MapManager::mapInfo = nullptr;

MapManager::MapManager()
{
	this->id = 0;
	this->name = "Undefined";
	//this->file
	//this->info
}

MapManager::~MapManager()
{
	delete(this->info);
}

void MapManager::build()
{

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