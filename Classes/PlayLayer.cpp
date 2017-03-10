//
//  PlayerLayer.cpp
//  MenuTutorial
//
//  Created by Denger on 14-2-12.
//
//

#include "PlayLayer.h"

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
    auto back = MenuItemImage::create("res/UI/Icons/Home.png", "res/UI/Icons/Home.png", CC_CALLBACK_1(PlayLayer::back, this));
    back->setPosition(Vec2(origin.x + visibleSize.width - back->getContentSize().width ,
                                origin.y + back->getContentSize().height));

    auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
	//Main Game


    return true;
}


void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
