#include "MapManager.h"

MapManager::MapManager()
{
	this->id = 0;
}

MapManager::~MapManager()
{
	delete(this->mapInfo);
}

void MapManager::build()
{
	auto mapDetails = this->mapInfo->getObjectGroup("DETAILS");
	if (mapDetails)
	{
		auto moreInfo = mapDetails->getObject("MORE_INFO");

		playSound(moreInfo.at("soundFile").asString(), SOUNDTYPE::BACKGROUND, true);

		if (this->name == "")
		{
			this->name = moreInfo.at("mapName").asString();
		}
	}

	//Hide Barrier Color
	TMXLayer *_barrier;
	_barrier = this->mapInfo->getLayer("BARRIER");
	if (_barrier)
	{
		_barrier->setVisible(false);
	}
	//Hide Fighting _Grass Space
	TMXLayer *_grass;
	_grass = this->mapInfo->getLayer("GRASS");
	if (_grass)
	{
		_grass->setVisible(false);
	}

	auto gates = mapInfo->getObjectGroup("GATES");

	if (gates)
	{
		if (COCOS2D_DEBUG)
		{
			for (auto gate : gates->getObjects())
			{
				auto g = gate.asValueMap();
				auto rect = DrawNode::create();
				rect->drawRect(
					Vec2(g.at("x").asFloat(), g.at("y").asFloat()),
					Vec2(g.at("x").asFloat()+g.at("width").asFloat(), g.at("y").asFloat()+g.at("width").asFloat()),
					Color4F::BLUE);
				mapInfo->addChild(rect, 10);
			}
		}
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
	this->mapInfo->addChild(character, zOrder);
}