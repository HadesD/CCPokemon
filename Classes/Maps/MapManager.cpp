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
	auto _barrier = this->mapInfo->getLayer("BARRIER");
	if (_barrier)
	{
		_barrier->setVisible(false);
	}
	//Hide Fighting _Grass Space
	auto _grass = this->mapInfo->getLayer("GRASS");
	if (_grass)
	{
		_grass->setVisible(false);
	}

	auto gates = mapInfo->getObjectGroup("GATES");
	if (gates)
	{
		for (auto gate : gates->getObjects())
		{
			auto v = gate.asValueMap();
			if (COCOS2D_DEBUG)
			{
				auto rect = DrawNode::create();
				rect->drawRect(
					Vec2(v.at("x").asFloat(), v.at("y").asFloat()),
					Vec2(v.at("x").asFloat()+v.at("width").asFloat(), v.at("y").asFloat()+v.at("width").asFloat()),
					Color4F::BLUE);
				mapInfo->addChild(rect, 10);
			}
			auto *particle = CCParticleSystemQuad::create(RD_PARTICLES + "/Gate_Particle.plist");
			particle->resetSystem();
			particle->setPosition(v.at("x").asFloat() + v.at("width").asFloat() / 2, v.at("y").asFloat());
			particle->setPosVar(Vec2(v.at("width").asFloat()/2, v.at("height").asFloat()));
			this->mapInfo->addChild(particle);
		}
	}

	auto _maxzorder = this->mapInfo->getLayer("MAXZORDER");
	if (_maxzorder)
	{
		_maxzorder->setZOrder(999);
	}

	//Load NPCs
	auto _npcs = mapInfo->getObjectGroup("NPCS");
	if (_npcs)
	{
		for (auto _npc : _npcs->getObjects())
		{
			auto v = _npc.asValueMap();

			auto newNPC = new Character;
			newNPC->setSprite(v.at("sprite").asString());
			newNPC->setCharType(Character::CHARTYPE::NPC);
			newNPC->build();
			this->addCharToMap(newNPC);
			newNPC->goTo(Vec2(v.at("x").asFloat(), v.at("y").asFloat()));

			CCLOG("Has NPC: %s", v.at("sprite").asString());
		}
	}

	this->addChild(this->mapInfo);
}

void MapManager::addCharToMap(Character* character)
{
	character->setIsMoving(false);
	character->setIsMoveActing(false);

	int zOrder = 100;

	auto _maxzorder = this->mapInfo->getLayer("MAXZORDER");

	if (_maxzorder)
	{
		if (zOrder >= _maxzorder->getZOrder())
		{
			zOrder = _maxzorder->getZOrder() - 1;
		}
	}


	this->mapInfo->addChild(character, zOrder);

	playSound("gotomap.wav", SOUNDTYPE::EFFECT, false);
}

void MapManager::setMapInfo(std::string mapInfo)
{
	this->mapInfo = TMXTiledMap::create(RD_MAPS + "/" + mapInfo);

	this->build();
}

TMXTiledMap *MapManager::getMapInfo()
{
	return this->mapInfo;
}

