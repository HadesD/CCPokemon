//
//  PlayerLayer.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "stdafx.h"
#include "PlayLayer.h"
#include "Maps/MapManager.h"
#include "Characters/Trainers/Trainer.h"

USING_NS_CC;

PlayLayer::PlayLayer()
{
}

PlayLayer::~PlayLayer()
{
}

bool PlayLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Create BackToMainMenu Button
	auto back = MenuItemImage::create(RES_DIR + "/UI/Icons/Home.png", RES_DIR + "/UI/Icons/Home.png", CC_CALLBACK_1(PlayLayer::back, this));
    back->setPosition(Vec2(origin.x + visibleSize.width - back->getContentSize().width,
                                origin.y + back->getContentSize().height));

    auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
	//Main Game

	auto map = new MapManager;
	map->setInfo(TMXTiledMap::create(RD_MAPS + "/ROUTE_1.tmx"));
	map->build();
	this->addChild(map);
	auto mapDetails = map->getInfo()->getObjectGroup("DETAILS");

	auto trainer = new Trainer;
	trainer->setSprite(Sprite::create(RD_C_TRAINERS + "/trainer1.png", Rect(0, 32.f*trainer->getDirection(), 32.f, 32.f)));
	trainer->setName("Dark.Hades");
	trainer->build();

	if (mapDetails)
	{
		auto playerStart = mapDetails->getObject("FLY_SPACE");
		if (playerStart["x"].asBool())
		{
			trainer->setPosition(Vec2(playerStart["x"].asFloat(), playerStart["y"].asFloat()));
		}
	}

	map->addCharToMap(trainer, ZORDER_TRAINER);

    return true;
}

void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
