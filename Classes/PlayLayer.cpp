//
//  PlayerLayer.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "stdafx.h"
#include "PlayLayer.h"
#include <SimpleAudioEngine.h>

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
    back->setPosition(Vec2(origin.x + visibleSize.width - back->getContentSize().width ,
                                origin.y + back->getContentSize().height));

    auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
	//Main Game
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	char music[100];
	sprintf(music, "%s/PalletTownTheme.mp3", RD_S_MUSICS.c_str());
	audio->playBackgroundMusic(music, true);

	Sprite *trainer;
	trainer = Sprite::create(RD_C_TRAINERS + "/trainer2.png", Rect(0, 32.f, 32.f, 32.f));
	trainer->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(trainer);

    return true;
}

void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
