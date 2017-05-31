#include "stdafx.h"
#include "PlayLayer.h"
#include "UI/JoyStick.h"
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
	map->setMapInfo("MainMap.tmx");
	//map->setMapInfo("ROUTE_1.tmx");
	this->addChild(map);

	auto trainer = new Trainer;
	trainer->setSprite(RD_C_TRAINERS + "/male_frlg.png");
	trainer->setName("Dark.Hades");
    trainer->setMoveSpeed(50);
	auto toPos = Vec2(0, 0);
	auto playerStart = map->getMapInfo()->getObjectGroup("FLY_SPACE")->getObject("PALLETTOWN_CITY");
	if (playerStart.at("x").asBool())
	{
		toPos = Vec2(playerStart.at("x").asFloat(), playerStart.at("y").asFloat());
	}

	trainer->build();
	map->addCharToMap(trainer);
	trainer->goTo(toPos);

	this->setAnchorPoint(Vec2(0,0));

	this->setScale(SCALE);

    return true;
}

void PlayLayer::back(Ref* pSender)
{
    SceneManager::goMenu();
}
