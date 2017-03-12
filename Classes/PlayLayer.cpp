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

	this->setName("GamePlay");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Create BackToMainMenu Button
	auto back = MenuItemImage::create(RES_DIR + "/UI/Icons/Home.png", RES_DIR + "/UI/Icons/Home.png", CC_CALLBACK_1(PlayLayer::back, this));
    back->setPosition(Vec2(origin.x + visibleSize.width - back->getContentSize().width ,
                                origin.y + back->getContentSize().height));

    auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
	//Main Game
	char music[100];
	sprintf(music, "%s/PalletTownTheme.mp3", RD_S_MUSICS.c_str());
	playSound(music, "background", true);

	auto map = new MapManager;
	map->setInfo(TMXTiledMap::create(RD_MAPS + "/town2.tmx"));
	map->build();
	this->addChild(map, 0);
	auto playerStart = map->getInfo()->getObjectGroup("Events")->getObject("PLAYER_START");

	auto trainer = new Trainer;
	trainer->setSprite(Sprite::create(RD_C_TRAINERS + "/trainer1.png", Rect(0, 32.f*trainer->getDirection(), 32.f, 32.f)));
	trainer->setPosition(Vec2(playerStart["x"].asFloat(), playerStart["y"].asFloat()));
	trainer->build();

	map->addCharToMap(trainer, ZORDER_TRAINER);

	//CCLOG("%s", trainer->getPositionX());

    return true;
}

void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
