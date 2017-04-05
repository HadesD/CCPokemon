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

	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	auto camera = Camera::createOrthographic(visibleSize.width, visibleSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);

	auto map = new MapManager;
	map->setMapInfo("PALLETTOWN_CITY.tmx");
	//map->setMapInfo("ROUTE_1.tmx");
	this->addChild(map);
	auto mapDetails = map->getMapInfo()->getObjectGroup("DETAILS");

	auto trainer = new Trainer;
	trainer->setSprite(RD_C_TRAINERS + "/female_frlg.png");
	trainer->setName("Dark.Hades");
	auto toPos = Vec2(0, 0);
	if (mapDetails)
	{
		auto playerStart = mapDetails->getObject("FLY_SPACE");
		if (playerStart["x"].asBool())
		{
			toPos = Vec2(playerStart["x"].asFloat(), playerStart["y"].asFloat());
		}
	}

	trainer->build();
	map->addCharToMap(trainer, ZORDER_TRAINER);
	trainer->goTo(toPos);

	this->setAnchorPoint(Vec2(0,0));

	this->setScale(SCALE);

    return true;
}

void PlayLayer::back(Ref* pSender)
{
    SceneManager::goMenu();
}
