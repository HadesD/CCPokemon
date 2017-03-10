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
    
    auto back = MenuItemFont::create("back", CC_CALLBACK_1(PlayLayer::back, this));
    auto menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width/2, visibleSize.height/2);

    this->addChild(menu);
    
    return true;
}


void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
