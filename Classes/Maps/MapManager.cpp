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

	//Draw Barrier Space
	auto barriersObj = this->info->getObjectGroup("BARRIERS");
	for (auto obj : barriersObj->getObjects())
	{
		auto val = obj.asValueMap();

		if (COCOS2D_DEBUG == 1)
		{
			auto rect = DrawNode::create();

			rect->drawRect(Vec2(val.at("x").asFloat(), val.at("y").asFloat()),
				Vec2(val.at("x").asFloat() + val.at("width").asFloat(), val.at("y").asFloat() + val.at("height").asFloat()),
				Color4F::RED);
			this->addChild(rect, 99);
		}
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